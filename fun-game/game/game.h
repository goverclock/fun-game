#pragma once
#include <QObject>

#include "net/protocol.h"

class View;
class Unit;

class Game : public QObject {
    Q_OBJECT
   public:
    Game(View *);

    View *view;

    int id = -1;  // same as Chat::id
    bool run = false;
    bool your_turn = false;
    Unit *units[MAX_CLIENTS];
    Unit *clnt_unit;

    Packet cur_opt;

   public slots:
    void end_turn();
    void serv_msg(Packet);
   signals:
    void user_msg(Packet);
};
