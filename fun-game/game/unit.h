#pragma once

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QTimer>

#include "angle_indicator.h"
#include "game.h"
#include "net/protocol.h"

class Unit : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
   public:
    Unit(Game *, int);

   private:
    Game *game;
    int player_id;
    int health = 100;
    int energe = 100;
    QGraphicsEllipseItem *outter;
    QTimer ftimer;
    AngleIndicator *ang = nullptr;

    void act(Packet);

   private slots:
    void update();
};
