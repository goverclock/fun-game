#include "shell.h"

#include <QDebug>
#include <QDir>
#include <QGraphicsScene>
#include <QPen>
#include <QString>
#include <QTime>

Shell::Shell() : QObject(), QGraphicsRectItem() {
    setRect(-1, -1, 201, 460);
    setPos(0, 0);
    setPen(QPen(Qt::black, 1));
    setBrush(Qt::black);

    // shell_log.setFileName(QDir::currentPath() + "/saves/shell.log");
    // if (!shell_log.open(QIODevice::ReadWrite | QIODevice::Text |
    //                     QIODevice::Append))
    //     qDebug("Fail to open shell.log");

    msg_queue = new MsgQueue(this);
    set_mode(Qt::white);
}

Shell::~Shell() {
    // shell_log.close();
}

bool Shell::is_on() { return _is_on; }

void Shell::on(QGraphicsScene& s) {
    s.addItem(this);
    _is_on = true;
}

void Shell::off(QGraphicsScene& s) {
    if (is_on()) s.removeItem(this);
    _is_on = false;
}

void Shell::push_msg(QString m, bool has_time) {
    // add time as header
    // QTime ti = parent->gui->digit_clock->current_time();
    // QString tis = QString("[%1:%2]")
    //                   .arg(QString::number(ti.minute()))
    //                   .arg(QString::number(ti.second()));
    // if (has_time) m.prepend(tis);

    // save to log
    // QString t = m + "\n";
    // shell_log.write(t.toUtf8());

    if (m.size() < 23) {
        msg_queue->push_msg(Msg{plain, m, 0, 0});
        return;
    }
    QString front_m;
    int chop_len = m.size() - 23;
    front_m = m.chopped(chop_len);
    msg_queue->push_msg(Msg{plain, front_m, 0, 0});
    m.remove(0, 23);
    msg_queue->push_msg(Msg{plain, m, 0, 0});
}

void Shell::clear_msg(bool clear_buffer) { msg_queue->clear_msg(clear_buffer); }

void Shell::set_mode(enum Qt::GlobalColor c) {
    if (c == Qt::black)
        msg_queue->set_mode(Qt::white);
    else if (c == Qt::white)
        msg_queue->set_mode(Qt::black);

    setBrush(c);
}

void Shell::push_msg_core(QString m, bool t) { push_msg(m, t); }
