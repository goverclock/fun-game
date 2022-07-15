#pragma once
#include <QObject>

#include "net/protocol.h"
#include "unit.h"

class View;

class Game : public QObject {
    Q_OBJECT
   public:
    Game(View *);

    View *view;

    int id = -1;  // same as Chat::id
    bool run = false;
    bool your_turn = false;
    Unit *units[MAX_CLIENTS];

    Packet cur_opt;
    // commands
    // called after receiving server message
    void start();
    void end();

   public slots:
    void serv_msg(Packet);
   signals:
    void user_msg(Packet);
};
