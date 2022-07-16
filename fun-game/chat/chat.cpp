#include "chat.h"

#include <QDebug>

#include "net/protocol.h"
#include "view.h"

Chat::Chat(View *v) {
    view = v;

    static char data[MAX_MSG_LEN];
    connect(view->chat_box, &QLineEdit::returnPressed, this, &Chat::box_msg);
}

void Chat::serv_msg(Packet p) {
    // only resolve: chat, reg_success
    // others are resolved by Net::serv_msg
    switch (p.type) {
        case Packet::chat: {
            view->shell.push_msg(p.pack.chat_info.msg, false);
            break;
        }
        case Packet::reg_response: {
            id = p.pack.reg_success_info.new_id;
            if (id != -1) {
                char t[MAX_MSG_LEN];
                sprintf(t, "[sys]注册为用户%d.", id);
                view->shell.push_msg(t, false);
                view->get_id(id);
            } else
                view->shell.push_msg("[sys]注册失败.", false);
            break;
        }
        default:
            break;
    }
}

// resolve user input
void Chat::box_msg() {
    // qDebug() << view->chat_box->text();
    QString m(view->chat_box->text());
    view->chat_box->clear();
    Packet p;

    if (m.isEmpty()) return;
    if (id == -1 && m != "/reg") {
        view->shell.push_msg("[sys]需要先使用/reg进行注册.", false);
        return;
    }

    if (m[0] == '/') {  // some command
        if (m == "/reg") {
            if (id != -1) {
                view->shell.push_msg("[sys]你已经注册过了.", false);
                return;
            }
            p.type = Packet::clnt_reg;
        } else if (m == "/start" || m == "/s") {
            p.type = Packet::game_start;
        } else if (m == "/end" || m == "/e") {
            p.type = Packet::game_end;
        } else if (m == "/help") {
            view->shell.push_msg("[sys]我比较懒.", false);
            return;
        } else {
            view->shell.push_msg("[sys]未知指令,使用/help获取帮助.", false);
            return;
        }
    } else {  // char message
        p.type = Packet::chat;
        p.pack.chat_info.id = id;
        strcpy(p.pack.chat_info.msg, m.toStdString().c_str());
    }

    emit user_msg(p);
}

void Chat::reg() {
    Packet p;
    p.type = Packet::clnt_reg;
    emit user_msg(p);
}