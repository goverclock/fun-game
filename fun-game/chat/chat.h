#pragma once
#include <QObject>
#include "net/protocol.h"

class View;

class Chat : public QObject {
    Q_OBJECT
   public:
    Chat(View *);

    View *view;

    int id = -1;

   public slots:
    void serv_msg(Packet);  // signal at Net::rec_serv
    void box_msg();

   signals:
    void user_msg(Packet);  // slot at Net::send_user
                            // commands(begin with '/') are resolved at server
};
