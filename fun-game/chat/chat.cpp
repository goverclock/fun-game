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
    if (p.type == Packet::chat) {
        view->shell.push_msg(p.pack.chat_info.msg, false);
    } else if (p.type == Packet::reg_success) {
        id = p.pack.reg_success_info.new_id;
        view->shell.push_msg("[sys]注册成功.", false);
    } else if (1) {
        // ...
    }
}

// resolve user input
void Chat::box_msg() {
    // qDebug() << view->chat_box->text();
    QString m(view->chat_box->text());
    view->chat_box->clear();
    Packet p;

    if (id == -1 && m != "/reg") {
        view->shell.push_msg("[sys]需要先使用/reg进行注册.", false);
        return;
    } else if (m.isEmpty())
        return;
    else if (m[0] == '/') {  // some command
        if (m == "/reg") {
            if (id != -1) {
                view->shell.push_msg("[sys]你已经注册过了.", false);
                return;
            }
            p.type = Packet::clnt_reg;
        }
        // else if(...)
    } else {  // chat message
        p.type = Packet::chat;
        p.pack.chat_info.id = id;
        strcpy(p.pack.chat_info.msg, m.toStdString().c_str());
    }

    emit user_msg(p);
}
