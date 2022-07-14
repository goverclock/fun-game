#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QObject>
#include <QPointF>
#include <QString>

#include "text.h"

class Button : public QObject, public QGraphicsRectItem {
    Q_OBJECT
   public:
    Button(QString txt = "no text", int w = 100, int h = 100);

    // swit -> switch, but "switch" is reserved
    enum button_mode { normal, label, men, swit };

    bool is_on();
    void on(QGraphicsScene &);
    void off(QGraphicsScene &);
    bool is_down();
    void down();
    void up();
    void set_text(QString);
    void set_mode(button_mode);
    void set_edge(bool);
    void set_size(int, int);
    void set_point_size(int);

   signals:
    void clicked();  // pressed
    void released();
    void hover_enter();
    void hover_leave();

   private:
    bool _is_on;
    bool _is_down;
    button_mode mode;
    int width;
    int height;
    Text *text;
    QGraphicsPixmapItem *ico;

    QPointF center_pos(int aw, int ah, int bw, int bh) {
        QPointF ret;
        ret.setX(aw / 2 - bw / 2);
        ret.setY(ah / 2 - bh / 2);
        return ret;
    }

    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
};