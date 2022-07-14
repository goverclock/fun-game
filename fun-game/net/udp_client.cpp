#include "udp_client.h"

#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

#include "chat/chat.h"

Net::Net(Chat *c) {
    chat = c;

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
    connect(this, &Net::rec_serv, chat, Chat::serv_msg);
    connect(chat, &Chat::user_msg, this, send_user);
};

// read and resolve
void Net::process_data() {
    Packet p;
    while (sock.hasPendingDatagrams()) {
        sock.readDatagram((char *)&p, sock.pendingDatagramSize());
        if (p.type == Packet::chat) {
            emit rec_serv(p);
        } else if (p.type == Packet::client_join) {
            // ...
        }  // ...
    }
}

void Net::send_user(Packet p) {
    // qDebug() << "sending to server: " << p.un.ch.msg;
    sock.writeDatagram((char *)&p, QHostAddress(serv_ip), serv_port);
}
