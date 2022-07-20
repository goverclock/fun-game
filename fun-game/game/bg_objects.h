#pragma once
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QVector>

class Game;

class BGObject : public QObject {
    Q_OBJECT
   public:
    BGObject(Game*);
    // ~BGObject();

    QVector<QGraphicsPolygonItem*> objs;
};
