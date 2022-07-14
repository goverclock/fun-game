#include "chat.h"
#include "view.h"

Chat::Chat(View *v) {
    shell.setParent(this);
    shell.on(v->sce);

}

void Chat::send_msg(const QString &m) {}

void Chat::rec_msg(const QString &) {}
