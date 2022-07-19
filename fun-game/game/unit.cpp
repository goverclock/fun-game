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
    if (player_id != game->id) return;

    ang = new AngleIndicator(this);

    auto &v(game->view);
    auto &info(game->cur_opt.pack.game_playeropt_info);
    info.id = player_id;
    connect(v, &View::user_event, this,
            &Unit::event_resolv);  // key press/release event
    // fly button
    connect(v->fly, &Button::clicked, [&] {
        if (game->your_turn && energy >= 100) {
            qDebug("飞行");
            info.fly = true;
            energy -= 100;
            v->MP->set_text("体力:" + QString::number(energy));
        }
    });
    // multiple button
    connect(v->multi, &Button::clicked, [&] {
        if (game->your_turn && energy >= 60) {
            qDebug("散射");
            info.multi = true;
            energy -= 60;
            v->MP->set_text("体力:" + QString::number(energy));
        }
    });
    // duplicate button
    connect(v->dupli, &Button::clicked, [&] {
        if (game->your_turn && energy >= 50) {
            qDebug("连发");
            info.times += 2;
            energy -= 50;
            v->MP->set_text("体力:" + QString::number(energy));
        }
    });
    // violence button
    connect(v->violen, &Button::clicked, [&] {
        if (game->your_turn && energy >= 40) {
            qDebug("重击");
            info.violence++;
            energy -= 40;
            v->MP->set_text("体力:" + QString::number(energy));
        }
    });
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

    QKeyEvent *ke = static_cast<QKeyEvent *>(e);
    if (ke->key() == Qt::Key_A)
        ang->set_dir(1);
    else if (ke->key() == Qt::Key_D)
        ang->set_dir(-1);
}
