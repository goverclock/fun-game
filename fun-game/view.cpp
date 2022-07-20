#include "view.h"

#include "game/game.h"
#include "gui/button.h"

View::View() {
    setFixedSize(window_w, window_h);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(&sce);
    setSceneRect(0, 0, window_w, window_h);
    line.setLine(200, 0, 200, 480);
    sce.addItem(&line);

    chat_box = new QLineEdit(this);
    chat_box->setGeometry(0, 0, 201, 20);
    chat_box->setPlaceholderText("聊天或指令...");
    chat_box->move(0, 460);

    shell.setParent(this);
    shell.on(sce);

    fly = new Button("飞行(100)", 80, 40);
    fly->set_point_size(12);
    fly->setPos(200, 420);

    multi = new Button("散射(60)", 80, 40);
    multi->set_point_size(12);
    multi->setPos(280, 420);

    dupli = new Button("连发(40)", 80, 40);
    dupli->set_point_size(12);
    dupli->setPos(360, 420);

    violen = new Button("重击(40)", 80, 40);
    violen->set_point_size(12);
    violen->setPos(440, 420);

    HP = new Button("生命:100", 80, 20);
    HP->set_mode(Button::label);
    HP->set_point_size(8);
    HP->setPos(520, 420);

    MP = new Button("体力:100", 80, 20);
    MP->set_mode(Button::label);
    MP->set_point_size(8);
    MP->setPos(520, 440);

    end_turn = new Button("结束回合", 80, 40);
    end_turn->set_point_size(12);
    end_turn->setPos(720, 420);

    pb = new PowerBar(game, 600, 20);
    pb->setPos(200, 460);
    connect(this, &View::user_event, pb, &PowerBar::event_resolv);

    show();
}

void View::set_game_gui_on_off(bool b) {
    if (b) {
        fly->on(sce);
        multi->on(sce);
        dupli->on(sce);
        violen->on(sce);
        HP->on(sce);
        MP->on(sce);
        end_turn->on(sce);
        pb->on(sce);
    } else {
        fly->off(sce);
        multi->off(sce);
        dupli->off(sce);
        violen->off(sce);
        HP->off(sce);
        MP->off(sce);
        end_turn->off(sce);
        pb->off(sce);
    }
}

void View::get_net(Net *n) { net = n; }

void View::get_game(Game *g) { game = g; }

void View::get_id(int v) { id = v; }

void View::keyPressEvent(QKeyEvent *e) {
    if (game->run && game->your_turn) emit user_event(true, e);
    return QWidget::keyPressEvent(e);
}

void View::keyReleaseEvent(QKeyEvent *e) {
    if (game->run && game->your_turn) emit user_event(false, e);
    return QWidget::keyReleaseEvent(e);
}

bool View::eventFilter(QObject *obj, QEvent *e) {
    if (e->type() == QEvent::Wheel)
        return true;
    else
        return QObject::eventFilter(obj, e);
}

void View::closeEvent(QCloseEvent *e) {
    net->send_end_pack();
    QWidget::closeEvent(e);
}
