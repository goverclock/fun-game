#pragma once
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QVector>
#include <QGraphicsEllipseItem>

class Game;
class Unit;
class FlyObject;

class BGObjects : public QObject {
    Q_OBJECT
   public:
    BGObjects(Game*);
    ~BGObjects();

    Game *game;

    void init();
    void create_crater(Unit*, FlyObject*);
    void clear();

    QVector<QGraphicsPolygonItem*> objs;
    QVector<QGraphicsEllipseItem*> craters;
};
