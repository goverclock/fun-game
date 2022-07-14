#include "view.h"

#include "gui/button.h"

View::View() {
    setFixedSize(window_w, window_h);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(&sce);
    setSceneRect(0, 0, window_w, window_h);

    init();

    show();
}

void View::init() {
    bt = new Button("好");
    bt->set_mode(Button::normal);
    bt->setPos(0, 0);
    bt->on(sce);
    connect(bt, &Button::clicked, [] { qDebug("fuck"); });

    line = new QGraphicsLineItem();
    line->setLine(200, 0, 200, 480);
    sce.addItem(line);
}

bool View::eventFilter(QObject *obj, QEvent *e) {
    if (e->type() == QEvent::Wheel)
        return true;
    else
        return QObject::eventFilter(obj, e);
}
