#include "unit.h"

#include "view.h"

Unit::Unit(Game *g, int id) : QObject(), QGraphicsEllipseItem() {
    game = g;
    player_id = id;

    setRect(-1, -1, 1, 1);

    outter = new QGraphicsEllipseItem(this);
    outter->setRect(-8, -16, 16, 16);

    ftimer.start(10);
    connect(&ftimer, &QTimer::timeout, this, &Unit::update);

    // for this client only
    if (player_id == game->id) {
        ang = new AngleIndicator(this);
        connect(game->view, &View::user_event, this, &Unit::event_resolv);
    }
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

void Unit::event_resolv(bool is_down, QEvent *e) {
    if (!is_down) {
        ang->set_dir(0);
        return;
    }

    QKeyEvent *ke = static_cast<QKeyEvent*>(e);
    if(ke->key() == Qt::Key_A) ang->set_dir(1);
    else if(ke->key() == Qt::Key_D) ang->set_dir(-1);
}
