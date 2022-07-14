#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include "gui/button.h"

class View : public QGraphicsView {
    Q_OBJECT
   public:
    View();


   private:
    const int window_w = 800;
    const int window_h = 480;

    QGraphicsScene sce;

    // gui
    QGraphicsLineItem *line;
    Button *bt;

    void init();

    bool eventFilter(QObject *, QEvent *);
};
