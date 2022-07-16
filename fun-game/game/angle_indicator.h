#pragma once
#include <QObject>
#include <QGraphicsLineItem>
#include <QTimer>

class Unit;

class AngleIndicator : public QObject, public QGraphicsLineItem {
    Q_OBJECT
   public:
    AngleIndicator(Unit*);

   public slots:
    void set_dir(int);

   private:
    int dir = 0;        // 1 -> counter clockwise, -1 -> clockwise
    QTimer ftimer;
};
