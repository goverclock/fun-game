#pragma once
#include <QObject>
#include <QUdpSocket>

#include "protocol.h"

class Chat;
class Game;

// client
class Net : public QObject {
    Q_OBJECT
   public:
    Net(Chat *, Game*);

    Chat *chat;
    Game *game;

    QUdpSocket sock;
    QString serv_ip;
    int serv_port;

    void process_data();
    void send_end_pack();

   public slots:
    void send_user(Packet);

   signals:
    void rec_serv(Packet);
};
