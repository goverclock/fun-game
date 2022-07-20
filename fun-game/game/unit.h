#pragma once

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QTimer>
#include <QEvent>
#include "angle_indicator.h"
#include "game.h"
#include "net/protocol.h"

class Unit : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
   public:
    Unit(Game *, int);

    QGraphicsEllipseItem *outter;

    Game *game;
    int player_id;
    int health = 100;
    int energy = 100;
    QTimer ftimer;
    AngleIndicator *ang = nullptr;

    void change_health(int);

   private slots:
    void update();
    void event_resolv(bool, QEvent*);
};
