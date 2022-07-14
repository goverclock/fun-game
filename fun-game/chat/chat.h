#pragma once
#include <QObject>
#include "net/protocol.h"

class View;

class Chat : public QObject {
    Q_OBJECT
   public:
    Chat(View *);

    View *view;

   public slots:
    void serv_msg(Packet);  // signal at Net::rec_serv

   signals:
    void user_msg(Packet);  // slot at Net::send_user
                            // commands(begin with '/') are resolved at server
};
