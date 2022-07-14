#include "chat.h"

#include <QDebug>

#include "net/protocol.h"
#include "view.h"

Chat::Chat(View *v) {
    view = v;

    static char data[MAX_MSG_LEN];
    connect(view->chat_box, &QLineEdit::returnPressed, [&] {
        // qDebug() << view->chat_box->text();
        strcpy(data, view->chat_box->text().toStdString().c_str());
        if (!view->chat_box->text().isEmpty()) emit user_msg(data);
        view->chat_box->clear();
    });
}

void Chat::serv_msg(char *m) { view->shell.push_msg(m, false); }
