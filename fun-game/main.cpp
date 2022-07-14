// This is only the client.
// For server, see ../server/

#include <QApplication>
#include "view.h"

int main(int argc, char *argv[]) {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    
    View v;
    
    return a.exec();
}
