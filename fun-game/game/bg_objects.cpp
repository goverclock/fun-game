#include "bg_objects.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

#include "game.h"
#include "net/protocol.h"
#include "view.h"

BGObjects::BGObjects(Game* g) { game = g; }

void BGObjects::init() {
    clear();
    // read from file
    QFile f(QDir::currentPath() + "/" BGOBJ_FILE);
    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << "BGObjects(): fail to open" << f.fileName();
        exit(1);
    }
    QTextStream ts(&f);
    QString s;
    QStringList sl;
    QVector<QPointF> points;
    while (!ts.atEnd()) {
        s = ts.readLine();
        if (s == "") {
            auto n = new QGraphicsPolygonItem(QPolygonF(points));
            n->setBrush(Qt::gray);
            n->setPen(QPen(Qt::transparent));

            game->view->sce.addItem(n);
            objs.push_back(n);
            points.clear();
            continue;
        }
        sl = s.split(" ");
        QPointF p(sl[0].toInt() + LEFT_OFFSET, sl[1].toInt());
        points.push_back(p);
    }
}

void BGObjects::clear() {
    for (const auto i : objs) delete i;
    objs.clear();
}

BGObjects::~BGObjects() { clear(); }
