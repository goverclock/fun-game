#pragma once
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>

#include "net/protocol.h"

class Unit;

class FlyObject : public QObject {
    Q_OBJECT
   public:
    FlyObject(Unit *, Packet, int = 0);
    ~FlyObject();

    Unit *unit;
    bool fly;
    QGraphicsItem *body;
    QGraphicsEllipseItem *inner;
    double dmg;
    double vx, vy;
    QTimer ftimer;
   
   private:
    void set_power(Packet);
   private slots:
    void update();
};
