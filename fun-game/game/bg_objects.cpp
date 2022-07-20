#include "bg_objects.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

#include "game.h"
#include "net/protocol.h"

BGObjects::BGObjects(Game* g) {
    QFile f(QDir::currentPath() + "/" BGOBJ_FILE);
    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << "BGObjects(): fail to open" << f.fileName();
        exit(1);
    }
    QTextStream ts(&f);
    QString s;
    QStringList sl;
    while (!ts.atEnd()) {
        s = ts.readLine();
        qDebug() << s;
    }
}
