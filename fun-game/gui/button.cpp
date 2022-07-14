#include "button.h"

Button::Button(QString txt, int w, int h) : QObject(), QGraphicsRectItem() {
    width = w;
    height = h;
    setRect(0, 0, width, height);
    setBrush(Qt::white);
    setAcceptHoverEvents(true);
    set_mode(normal);

    // text position will be changed if call:
    // set_ico
    // set_point_size
    text = new Text(this, txt);
    set_point_size(50);
}

bool Button::is_on() { return _is_on; }
void Button::on(QGraphicsScene &s) {
    s.addItem(this);
    _is_on = true;
}
void Button::off(QGraphicsScene &s) {
    if (is_on()) s.removeItem(this);
    _is_on = false;
}

bool Button::is_down() { return _is_down; }
void Button::down() {
    _is_down = true;
    QColor c;
    c = QColor::fromRgb(214, 216, 217);
    setBrush(c);
}
void Button::up() {
    _is_down = false;
    setBrush(Qt::white);
}

void Button::set_text(QString t) { text->set_text(t); }

// note: calls disconnect()
// always connect event to clicked signal
void Button::set_mode(button_mode m) {
    disconnect();
    switch (m) {
        case normal:
            connect(this, &Button::clicked, &Button::down);
            connect(this, &Button::released, &Button::up);
            break;
        case label:
            break;
        case men:
            connect(this, &Button::hover_enter, &Button::down);
            connect(this, &Button::hover_leave, &Button::up);
            break;
        case swit:
            connect(this, &Button::clicked, &Button::down);
            // connect other events to call up()
            break;
    }
}

void Button::set_edge(bool a) {
    if (!a)
        setPen(QPen(Qt::transparent));
    else
        setPen(QPen(Qt::black));
}

// note: reset the point size
void Button::set_size(int w, int h) {
    width = w;
    height = h;
    setRect(0, 0, w, h);
    set_point_size(50);
}

void Button::set_point_size(int n) {
    text->set_point_size(n);
    text->setPos(center_pos(rect().width(), rect().height(), text->width(),
                            text->height()));
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    emit hover_enter();
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    emit hover_leave();
}
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked();
}
void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    emit released();
}
