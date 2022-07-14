#pragma once
#include <QGraphicsView>

class View : public QGraphicsView {
    Q_OBJECT
   public:
    View();


   private:
    const int window_w = 800;
    const int window_h = 480;

};
