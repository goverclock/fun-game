#include "fly_object.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>

#include "unit.h"

FlyObject::FlyObject(Unit *unit, Packet p, int lag) : QObject() {
    auto &info(p.pack.game_playeropt_info);
    fly = info.fly;
    if (info.fly)
        body = new QGraphicsRectItem;
    else
        body = new QGraphicsEllipseItem;
    QGraphicsEllipseItem *e = static_cast<QGraphicsEllipseItem *>(body);
    e->setParentItem(unit);
    e->setRect(-4, -11, 8, 6);
    e->setTransformOriginPoint(e->rect().center());

    connect(&ftimer, &QTimer::timeout, this, &FlyObject::update);

    QTimer *lag_timer = new QTimer(this);
    lag_timer->start(lag);
    connect(lag_timer, &QTimer::timeout, [=] {
        delete lag_timer;
        set_power(p);
        ftimer.start(10);
    });
}

void FlyObject::set_power(Packet power_info) {
    auto &info(power_info.pack.game_playeropt_info);
    dmg = 10 * (1 + static_cast<double>(info.violence) * 0.5);
    vx = info.power * qCos(qDegreesToRadians(info.angle)) * 0.07;
    vy = info.power * qSin(qDegreesToRadians(info.angle)) * 0.07;
}

void FlyObject::update() {
    QGraphicsEllipseItem *e = static_cast<QGraphicsEllipseItem *>(body);
    if (e->y() >= 500) {
        delete this;
        return;
    }
    e->setRotation(e->rotation() + 3);

    e->setPos(e->x() + vx, e->y() + vy);
    vy += 0.01;
}
