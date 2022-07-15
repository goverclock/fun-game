#pragma once

#define MAX_MSG_LEN 128

struct Packet {
    enum { clnt_reg, reg_success, clnt_quit, chat, game } type;

    union {
        struct {
            // nothing
        } clnt_reg_info;
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
            int obj_id;
            int x, y;
        } game_info;
    } pack;
};
