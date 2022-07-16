// This is only the client.
// For server, see ../server/

#include <QApplication>

#include "chat/chat.h"
#include "game/game.h"
#include "net/udp_client.h"
#include "view.h"

int main(int argc, char *argv[]) {
#ifdef __WIN32__
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #include <windows.h>
    FreeConsole();
#endif
    QApplication a(argc, argv);

    View v;
    Chat c(&v);
    Game g(&v);
    Net n(&c, &g);
    v.get_net(&n);
    c.reg();

    return a.exec();
}
