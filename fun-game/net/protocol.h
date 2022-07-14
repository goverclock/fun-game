#pragma once

#define MAX_MSG_LEN 128

struct Packet {
    enum { client_join, client_quit, chat, game } type;

    union {
        struct client_join {} cj;
        struct client_quit {} cq;
        struct chat {
            char msg[MAX_MSG_LEN];
        } ch;
        struct game {
            int obj_id;
            int x, y;
        } ga;
    } un;
};
