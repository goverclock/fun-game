#include "fly_object.h"
#include "unit.h"

FlyObject::FlyObject(bool is_round, int r, int x, int y) : QObject(), QGraphicsItem() {
    ftimer.start(10);
    connect(&ftimer, &QTimer::timeout, this, &FlyObject::update);
}

void FlyObject::update() {

}
