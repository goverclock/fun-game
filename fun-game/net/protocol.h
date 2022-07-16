#pragma once

#define MAX_MSG_LEN 128
#define PORT 9998
#define MAX_CLIENTS 256

struct Packet {
    enum {
        clnt_reg,       // no info
        reg_response,
        clnt_quit,
        chat,
        game_start,
        game_end,       // no info
        game_playeropt,
        game_your_turn  // no info
    } type;

    union {
        struct {
            int new_id;
        } reg_success_info;
        struct {
            int id;
        } clnt_quit_info;
        struct {
            int id;
            char msg[MAX_MSG_LEN];
        } chat_info;
        struct {
            // client send: empty
            // server response:
            int player_ids[MAX_CLIENTS];  // end with -1
            int x[MAX_CLIENTS], y[MAX_CLIENTS];
        } game_start_info;
        struct {
            int id;
            bool fly;
            int times;
            bool multi;
            int violence;
            int power;  // 0 ~ 100
            // int angle;
        } game_playeropt_info;
    } pack;
};
