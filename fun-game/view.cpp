#include "view.h"

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

    show();
}

void View::get_net(Net *n) { net = n; }

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
