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
    line.setLine(200, 0, 200, 480);
    sce.addItem(&line);

    chat_box = new QLineEdit(this);
    chat_box->setGeometry(0, 0, 151, 20);
    chat_box->setPlaceholderText("聊天...");
    chat_box->move(0, 460);

    chat_send.setPos(150, 460 - 1);
    chat_send.set_size(50, 20);
    chat_send.set_text("发送");
    chat_send.set_point_size(12);
    chat_send.on(sce);
    // connect(&chat_send, &Button::clicked, [] { qDebug("fuck"); });

    shell.setParent(this);
    shell.on(sce);
}

bool View::eventFilter(QObject *obj, QEvent *e) {
    if (e->type() == QEvent::Wheel)
        return true;
    else
        return QObject::eventFilter(obj, e);
}
