#pragma once

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QTimer>

#include "net/protocol.h"

class Unit : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
   public:
    Unit();

    int player_id;
    int health = 100;
    int energe = 100;
    QGraphicsEllipseItem *outter;
    QTimer ftimer;
    // AngleIndicator *ang;

    void act(Packet);

   private slots:
    void update();
};
