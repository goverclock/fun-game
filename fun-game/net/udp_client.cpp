#include "udp_client.h"

#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include "game/game.h"
#include "chat/chat.h"

Net::Net(Chat *c, Game *g) {
    chat = c;
    game = g;

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

    connect(&sock, &QUdpSocket::readyRead, this, &Net::process_data);
    
    // Chat signals and slots
    connect(this, &Net::rec_serv, chat, &Chat::serv_msg);
    connect(chat, &Chat::user_msg, this, &Net::send_user);
    // Game signals and slots
    connect(this, &Net::rec_serv, game, &Game::serv_msg);
    connect(game, &Game::user_msg, this, &Net::send_user);
};

// read and emit a packet
void Net::process_data() {
    Packet p;
    while (sock.hasPendingDatagrams()) {
        sock.readDatagram((char *)&p, sock.pendingDatagramSize());
        emit rec_serv(p);
    }
}

Packet Net::send_end_pack() {
    Packet p;
    p.type = Packet::clnt_quit;
    p.pack.clnt_quit_info.id = chat->id;
    send_user(p);
}

void Net::send_user(Packet p) {
    sock.writeDatagram((char *)&p, sizeof(Packet), QHostAddress(serv_ip), serv_port);
}
