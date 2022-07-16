#include "unit.h"

Unit::Unit(Game *g, int id) : QObject(), QGraphicsEllipseItem() {
    game = g;
    player_id = id;

    setRect(-1, -1, 1, 1);

    outter = new QGraphicsEllipseItem(this);
    outter->setRect(-8, -16, 16, 16);

    if (player_id == game->id) ang = new AngleIndicator(this);

    ftimer.start(10);
    connect(&ftimer, &QTimer::timeout, this, &Unit::update);
}

void Unit::update() {
    bool on_ground = false;
    // TODO: DEBUG
    on_ground = true;

    // drop
    if (!on_ground) {
        auto cur_pos = pos();
        cur_pos.setY(cur_pos.y() + 1);
        setPos(cur_pos);
    }

    // out of screen(die)
    if (y() > 500) delete this;
    // TODO: inform the server
}
