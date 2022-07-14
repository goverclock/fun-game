// server

#include <arpa/inet.h>
#include <sys/socket.h>

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <list>
#include <cstdio>

#include "protocol.h"

#define PORT 9998

struct sockaddr_in clnt_adr;

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
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

        if (p.type == Packet::chat) {
            sendto(sock, (char*)&p, msg_len, 0, (struct sockaddr*)&clnt_adr,
                   sizeof(clnt_adr));
        } else exit(1);
    }

    return 0;
}
