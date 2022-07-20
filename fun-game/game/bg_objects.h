#pragma once
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QVector>

class Game;

class BGObjects : public QObject {
    Q_OBJECT
   public:
    BGObjects(Game*);
    // ~BGObject();

    QVector<QGraphicsPolygonItem*> objs;
};
