#include "fly_object.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QtMath>
#include "bg_objects.h"
#include "unit.h"

FlyObject::FlyObject(Unit *u, Packet p, int lag) : QObject() {
    unit = u;
    // setParent(unit);
    auto &info(p.pack.game_playeropt_info);
    dmg = 10 * (1 + static_cast<double>(info.violence) * 0.5);
    fly = info.fly;
    if (info.fly)
        body = new QGraphicsRectItem;
    else
        body = new QGraphicsEllipseItem;
    QGraphicsEllipseItem *e = static_cast<QGraphicsEllipseItem *>(body);
    e->setParentItem(unit);
    e->setRect(-4, -11, 8, 6);
    e->setTransformOriginPoint(e->rect().center());

    inner = new QGraphicsEllipseItem(body);
    inner->setRect(-0.5, -0.5, 1, 1);
    inner->hide();
    inner->setPos(e->rect().center());

    connect(&ftimer, &QTimer::timeout, this, &FlyObject::update);

    QTimer *lag_timer = new QTimer(this);
    lag_timer->start(lag);
    connect(lag_timer, &QTimer::timeout, [=] {
        delete lag_timer;
        set_power(p);
        ftimer.start(10);
    });
}

FlyObject::~FlyObject() { delete body; }

void FlyObject::set_power(Packet power_info) {
    auto &info(power_info.pack.game_playeropt_info);
    vx = info.power * qCos(qDegreesToRadians((float)info.angle)) * 0.07;
    vy = info.power * qSin(qDegreesToRadians((float)info.angle)) * 0.07;
}

void FlyObject::update() {
    QGraphicsEllipseItem *e = static_cast<QGraphicsEllipseItem *>(body);
    if (e->y() >= 500) {
        delete this;
        return;
    }

    // move
    e->setRotation(e->rotation() + 3);
    e->setPos(e->x() + vx, e->y() + vy);
    vy += 0.01;

    // explode
    bool touch = true;
    for (const auto &bg : unit->game->bgobjs->craters)
        if (inner->collidesWithItem(bg)) {
            touch = false;
            break;
        }
    if (touch) {
        touch = false;
        for (const auto &bg : unit->game->bgobjs->objs)
            if (inner->collidesWithItem(bg)) {
                touch = true;
                break;
            }
    }
    if (touch) {
        if (fly) {
            auto p(e->parentItem()->mapToScene(e->pos()));
            p.setY(p.y() - e->rect().height());
            unit->setPos(p);
            delete this;
        }
        // teleport
        else
            unit->game->bgobjs->create_crater(unit, this);
    }
}
