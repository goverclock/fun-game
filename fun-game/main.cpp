// This is only the client.
// For server, see ../server/

#include <QApplication>
#include "view.h"
#include "chat/chat.h"
#include "net/udp_client.h"

int main(int argc, char *argv[]) {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    
    View v;
    Chat c(&v);
    // Game g;
    Net n(&c);  // Net n(&c, &g);
    
    return a.exec();
}
