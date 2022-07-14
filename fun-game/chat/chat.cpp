#include "chat.h"

#include "view.h"

Chat::Chat(View *v) {
    this->v = v;

    connect(v->chat_box, &QLineEdit::returnPressed, [&] {
        qDebug("user msgl");
        v->chat_box->clear();
        if (!v->chat_box->text().isEmpty()) emit user_msg(v->chat_box->text());
    });
}

void Chat::serv_msg(const QString &m) { v->shell.push_msg(m, false); }
