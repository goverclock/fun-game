#include "chat.h"

#include <QDebug>

#include "net/protocol.h"
#include "view.h"

Chat::Chat(View *v) {
    view = v;

    static char data[MAX_MSG_LEN];
    connect(view->chat_box, &QLineEdit::returnPressed, [&] {
        // qDebug() << view->chat_box->text();
        if (!view->chat_box->text().isEmpty()) {
            Packet p;
            p.type = Packet::chat;
            strcpy(p.un.ch.msg, view->chat_box->text().toStdString().c_str());
            emit user_msg(p);
        }
        view->chat_box->clear();
    });
}

void Chat::serv_msg(Packet p) {
    if (p.type == Packet::chat) {
        view->shell.push_msg(p.un.ch.msg, false);
    } else {
        // ...
    }
}
