#include "unit.h"

Unit::Unit() : QObject(), QGraphicsEllipseItem() {
    setRect(-1, -1, 1, 1);

    outter = new QGraphicsEllipseItem(this);
    outter->setRect(-8, -16, 16, 16);

    ftimer.start(10);
    connect(&ftimer, &QTimer::timeout, this, &Unit::update);
}

void Unit::update() {
    bool on_ground = false;

    // drop
    if (!on_ground) {
        auto cur_pos = pos();
        cur_pos.setY(cur_pos.y() + 1);
        setPos(cur_pos);
    }

}
