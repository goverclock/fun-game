#pragma once
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QVector>

class Game;

class BGObjects : public QObject {
    Q_OBJECT
   public:
    BGObjects(Game*);
    ~BGObjects();

    Game *game;

    void init();
    void clear();

    QVector<QGraphicsPolygonItem*> objs;
};
