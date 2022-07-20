#include "unit.h"

#include "bg_objects.h"
#include "view.h"

Unit::Unit(Game *g, int id) : QObject(), QGraphicsEllipseItem() {
    game = g;
    player_id = id;

    setRect(-1, -1, 1, 1);
    setZValue(2);

    outter = new QGraphicsEllipseItem(this);
    outter->setRect(-8, -16, 16, 16);

    ftimer.start(10);
    connect(&ftimer, &QTimer::timeout, this, &Unit::update);

    // for this client only
    if (player_id != game->id) return;
    ang = new AngleIndicator(this);
    auto &v(game->view);
    connect(v, &View::user_event, this,
            &Unit::event_resolv);  // key press/release event
}

void Unit::update() {
    bool on_ground = true;
    for (const auto &bg : game->bgobjs->craters)
        if (collidesWithItem(bg)) {
            on_ground = false;
            break;
        }
    if (on_ground) {
        on_ground = false;
        for (const auto &bg : game->bgobjs->objs)
            if (collidesWithItem(bg)) {
                on_ground = true;
                break;
            }
    }

    // drop
    if (!on_ground) {
        auto cur_pos = pos();
        cur_pos.setY(cur_pos.y() + 1);
        setPos(cur_pos);
    }

    // out of screen(die)
    // TODO: inform the server
}

void Unit::event_resolv(bool is_down, QEvent *e) {
    if (!is_down) {
        ang->set_dir(0);
        return;
    }

    QKeyEvent *ke = static_cast<QKeyEvent *>(e);
    if (ke->key() == Qt::Key_A)
        ang->set_dir(1);
    else if (ke->key() == Qt::Key_D)
        ang->set_dir(-1);
}
