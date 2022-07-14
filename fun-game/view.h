#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QLineEdit>
#include "gui/button.h"

class View : public QGraphicsView {
    Q_OBJECT
   public:
    View();

    QGraphicsScene sce;

   private:
    const int window_w = 800;
    const int window_h = 480;


    // gui
    QGraphicsLineItem line;
    Button chat_send;
    QLineEdit *chat_box;    


    void init();

    bool eventFilter(QObject *, QEvent *);
};
