#include "udp_client.h"

#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

#include "chat/chat.h"

Net::Net(Chat *c) {
    this->c = c;

    // read server address
    QFile f(QDir::currentPath() + "/servadr");
    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << "Net(): fail to open" << f.fileName();
        exit(1);
    }
    QTextStream ts(&f);
    serv_ip = ts.readLine();
    serv_port = ts.readLine().toInt();
    f.close();
    sock.bind(QHostAddress(serv_ip), serv_port);

    connect(&sock, &QUdpSocket::readyRead, this, process_data);
    connect(this, &Net::rec_serv, c, Chat::serv_msg);
    connect(c, &Chat::user_msg, this, send_user);
};

// read and resolve
void Net::process_data() {
    static char data[MAX_MSG_LEN];
    while (sock.hasPendingDatagrams()) {
        sock.readDatagram(data, sock.pendingDatagramSize());
        Packet *p = (Packet *)data;
        if (p->type == Packet::chat) {
            emit rec_serv(p->un.ch.msg);
        } else if (p->type == Packet::client_join) {
            // ...
        }  // ...
    }
}

void Net::send_user(char *m) {
    // qDebug() << "sending to server: " << m;
    
}
