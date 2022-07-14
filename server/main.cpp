// server

#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <list>

#include "protocol.h"

#define PORT 9998
#define MAX_CLIENTS 256

int sock;
struct sockaddr_in clnt_adr;
struct ClientInfo {
    bool used;
    struct sockaddr_in adr;
} clients[MAX_CLIENTS];

void pack_resolv(Packet, struct sockaddr_in);

int main() {
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock != -1);

    memset(&clnt_adr, 0, sizeof(clnt_adr));
    clnt_adr.sin_family = AF_INET;
    clnt_adr.sin_addr.s_addr = INADDR_ANY;
    clnt_adr.sin_port = htons(PORT);

    int ret = bind(sock, (struct sockaddr*)&clnt_adr, sizeof(clnt_adr));
    assert(ret >= 0);

    Packet p;
    while (1) {
        int clnt_adr_len = sizeof(clnt_adr);
        int msg_len =
            recvfrom(sock, (char*)&p, MAX_MSG_LEN, 0,
                     (struct sockaddr*)&clnt_adr, (socklen_t*)&clnt_adr_len);
        if (msg_len <= 0) continue;
        printf("new data\n");

        pack_resolv(p, clnt_adr);
    }

    return 0;
}

void pack_resolv(Packet in, struct sockaddr_in adr) {
    Packet p;

    if (in.type == Packet::clnt_reg) {
        p.type = Packet::reg_success;
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
        printf("a client registered with %d\n", nid);
        sendto(sock, (char*)&p, sizeof(Packet), 0, (struct sockaddr*)&adr,
               sizeof(adr));
    } else if (in.type == Packet::chat) {
        p.type = Packet::chat;
        // send to all client
        sprintf(p.pack.chat_info.msg, "[%d]%s", in.pack.chat_info.id, in.pack.chat_info.msg);
        for (int i = 0; i < MAX_CLIENTS; i++)
            if (clients[i].used) 
                sendto(sock, (char*)&p, sizeof(Packet), 0,
                       (struct sockaddr*)&clients[i].adr,
                       sizeof(clients[i].adr));
    }
}
