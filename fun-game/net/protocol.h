#pragma once

#define MAX_MSG_LEN 128

struct Packet {
    enum { chat, game } type;

    union {
        struct chat {
            char msg[MAX_MSG_LEN];
        };
        struct game {
            int obj_id;
            int x, y;
        };
        // struct ...(type)
        // 
    };
};
