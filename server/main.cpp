// server

#include <arpa/inet.h>
#include <sys/socket.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <list>
#include <string>

#include "protocol.h"

int sock;
struct sockaddr_in clnt_adr;
struct ClientInfo {
    bool used;
    struct sockaddr_in adr;
} clients[MAX_CLIENTS];

struct GameInfo {
    bool run;
    int turn_ind;                 // index of player_ids
    int player_ids[MAX_CLIENTS];  // end with -1
} game_info;
int current_online;
int current_turn_player_id;

void pack_resolv(Packet, struct sockaddr_in);
void send_to_all(Packet);
void msg_to_all(const char[]);
int next_turn();

int main() {
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock != -1);

    memset(&clnt_adr, 0, sizeof(clnt_adr));
    clnt_adr.sin_family = AF_INET;
    clnt_adr.sin_addr.s_addr = INADDR_ANY;
    clnt_adr.sin_port = htons(PORT);

    int ret = bind(sock, (struct sockaddr *)&clnt_adr, sizeof(clnt_adr));
    assert(ret >= 0);

    Packet p;
    while (1) {
        int clnt_adr_len = sizeof(clnt_adr);
        int msg_len =
            recvfrom(sock, (char *)&p, MAX_MSG_LEN, 0,
                     (struct sockaddr *)&clnt_adr, (socklen_t *)&clnt_adr_len);
        if (msg_len <= 0) continue;
        printf("new data\n");

        pack_resolv(p, clnt_adr);
    }

    return 0;
}

void pack_resolv(Packet in, struct sockaddr_in adr) {
    Packet p;

    switch (in.type) {
        case Packet::clnt_reg: {
            p.type = Packet::reg_response;
            int nid = -1;
            for (int i = 0; i < MAX_CLIENTS; i++)
                if (!clients[i].used) {
                    nid = i;
                    break;
                }
            if (nid != -1) {
                clients[nid].used = true;
                clients[nid].adr = adr;
            }
            p.pack.reg_success_info.new_id = nid;
            sendto(sock, (char *)&p, sizeof(Packet), 0, (struct sockaddr *)&adr,
                   sizeof(adr));

            p.type = Packet::chat;
            sprintf(p.pack.chat_info.msg, "[all]用户%d加入.", nid);
            send_to_all(p);
            current_online++;
            sprintf(p.pack.chat_info.msg, "[all]当前在线:%d.", current_online);
            send_to_all(p);
            break;
        }

        case Packet::chat:
            p.type = Packet::chat;
            sprintf(p.pack.chat_info.msg, "[%d]%s", in.pack.chat_info.id,
                    in.pack.chat_info.msg);
            send_to_all(p);
            break;

        case Packet::clnt_quit: {
            send_to_all(in);
            int quit_id = p.pack.clnt_quit_info.id;

            p.type = Packet::chat;
            clients[in.pack.clnt_quit_info.id].used = false;
            sprintf(p.pack.chat_info.msg, "[all]用户%d离开.",
                    in.pack.clnt_quit_info.id);
            send_to_all(p);

            current_online--;
            sprintf(p.pack.chat_info.msg, "[all]当前在线:%d.", current_online);
            send_to_all(p);

            if(!current_online) game_info.run = false;
            if (game_info.run && quit_id == current_turn_player_id)
                next_turn();
            break;
        }
        case Packet::game_start: {
            p.type = Packet::game_start;
            game_info.run = true;
            int ind = 0;
            auto &info(p.pack.game_start_info);
            for (int i = 0; i < MAX_CLIENTS; i++)
                if (clients[i].used) {
                    info.player_ids[ind] = i;
                    info.x[ind] = ind * 100 + LEFT_OFFSET + 25;
                    info.y[ind] = 0;  // drop to ground
                    ind++;
                }
            info.player_ids[ind] = -1;
            send_to_all(p);
            msg_to_all("[all]游戏开始.");
            memcpy(game_info.player_ids, info.player_ids,
                   sizeof(info.player_ids));
            game_info.turn_ind = -1;

            next_turn();
            break;
        }

        case Packet::game_end:
            game_info.run = false;
            p.type = Packet::game_end;
            send_to_all(p);
            msg_to_all("[all]游戏结束.");
            memset(&game_info, -1, sizeof(game_info));
            break;

        case Packet::game_playeropt:
            send_to_all(in);
            next_turn();
            break;
    }
}

void send_to_all(Packet p) {
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (clients[i].used)
            sendto(sock, (char *)&p, sizeof(Packet), 0,
                   (struct sockaddr *)&clients[i].adr, sizeof(clients[i].adr));
}

void msg_to_all(const char m[]) {
    Packet p;
    p.type = Packet::chat;
    sprintf(p.pack.chat_info.msg, m);
    send_to_all(p);
}

// find next turn_ind and returns player_ids[turn_ind]
int next_turn() {
    // send your_turn packet
    Packet p;
    p.type = Packet::game_your_turn;

    int ret;
    do {
        if (game_info.player_ids[++game_info.turn_ind] == -1)
            game_info.turn_ind = 0;
        ret = game_info.player_ids[game_info.turn_ind];
    } while (!clients[ret].used);

    auto adr = clients[ret].adr;
    sendto(sock, (char *)&p, sizeof(Packet), 0, (struct sockaddr *)&adr,
           sizeof(adr));

    p.type = Packet::chat;
    sprintf(p.pack.chat_info.msg, "[all]玩家%d的回合.", ret);
    send_to_all(p);

    return current_turn_player_id = ret;
}
