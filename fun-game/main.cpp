// This is only the client.
// For server, see ../server/

#include <QApplication>
#include "view.h"
#include "chat/chat.h"

int main(int argc, char *argv[]) {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    
    View v;
    Chat c(&v);
    
    return a.exec();
}
