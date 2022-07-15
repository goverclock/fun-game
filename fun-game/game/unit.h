#pragma once

#include <QObject>
#include "net/protocol.h"
#include <QGraphicsEllipseItem>

class Unit : public QObject {
    Q_OBJECT
   public:
    Unit();

    int player_id;
    int health = 100;
    int energe = 100;
    // AngleIndicator ang;
    QGraphicsEllipseItem body;

};
