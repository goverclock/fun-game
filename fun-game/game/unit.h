#pragma once

#include "net/protocol.h"
#include <QGraphicsEllipseItem>

class Unit : public QGraphicsEllipseItem {
   public:
    Unit();

    int player_id;
    int health = 100;
    int energe = 100;
    // AngleIndicator *ang;

    void act(Packet);
};
