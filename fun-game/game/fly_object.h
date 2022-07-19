#pragma once
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

class Unit;

// TODO: implement bullet and fly as successor
class FlyObject :public QObject, QGraphicsItem {
    Q_OBJECT
   public:
    FlyObject(bool is_round, int r = 8, int x = 0, int y = 0);

    QTimer ftimer;

   private slots:
    void update();
};
