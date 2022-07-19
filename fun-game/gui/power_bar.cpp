#include "power_bar.h"

void PowerBar::clear() { shade->setRect(0, 0, 0, 0); }

void PowerBar::set_dir(double v) { dir = v; }

void PowerBar::event_resolv(bool is_down, QEvent *e) {
    QKeyEvent *ke = static_cast<QKeyEvent *>(e);
    if (ke->key() != Qt::Key_Space) return;

    if (is_down)
        set_dir(0.3);
    else {
        set_dir(0);
        emit released(cur_power);
    }
}

void PowerBar::update() {
    cur_power += dir;
    label->set_text(QString::number(int(cur_power)));
    if (int(cur_power) >= 100) {
        set_dir(0);
        emit released(cur_power);
    }

    int len = rect().width() * cur_power / max_power;
    shade->setRect(0, 1, len, 21);
}
