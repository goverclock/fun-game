#pragma once
#include <QObject>
#include <QUdpSocket>

#include "protocol.h"

class Chat;

// client
class Net : public QObject {
    Q_OBJECT
   public:
    Net(Chat *);

    Chat *c;

    QUdpSocket sock;
    QString serv_ip;
    int serv_port;

    void process_data();

   public slots:
    void send_user(char *);

   signals:
    void rec_serv(char *);
};
