#include "angle_indicator.h"

#include <QPen>

#include "unit.h"

AngleIndicator::AngleIndicator(Unit *parent) : QObject(), QGraphicsLineItem() {
    setParentItem(parent);

    setLine(0, 0, 50, 0);
    setPen(QPen(Qt::DotLine));

    ftimer.start(10);
    connect(&ftimer, &QTimer::timeout, [&] {
        int ang = rotation();
        setRotation(ang - dir);
    });
}

// 1 -> counter clockwise, -1 -> clockwise
void AngleIndicator::set_dir(int v) { dir = v; }
