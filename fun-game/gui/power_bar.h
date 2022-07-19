#pragma once
#include <QGraphicsRectItem>
#include <QTimer>

#include "button.h"
#include "text.h"

class Game;

class PowerBar : public Button {
    Q_OBJECT
   public:
    PowerBar(Game *g, int w, int h) : Button("", w, h) {
        game = g;
        
        set_mode(Button::label);

        label = new Text(this, "0");
        label->set_point_size(10);
        label->setPos(300, 0);
        label->setZValue(2);

        shade = new QGraphicsRectItem(this);
        shade->setBrush(Qt::gray);
        shade->setPen(QPen(Qt::transparent));
        shade->setRect(0, 1, 0, 21);

        ftimer.start(10);
        connect(&ftimer, &QTimer::timeout, this, &PowerBar::update);
    }

    Game *game;
    double cur_power = 0;
    const double max_power = 100;
    Text *label;
    QGraphicsRectItem *shade;
    QTimer ftimer;
    double dir = 0;

    void clear();
    void set_dir(double);
 
   signals:
    void released();
    
   public slots:
    void event_resolv(bool, QEvent *);

   private slots:
    void update();
};
