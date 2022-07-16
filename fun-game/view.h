#pragma once
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLineEdit>

#include "gui/button.h"
#include "gui/shell.h"
#include "net/protocol.h"
#include "net/udp_client.h"

class View : public QGraphicsView {
    Q_OBJECT
   public:
    View();

    QGraphicsScene sce;
    Net *net;

    const int window_w = 800;
    const int window_h = 480;

    int id = -1;
    Packet end_pack;
    // gui
    QGraphicsLineItem line;
    QLineEdit *chat_box;
    Shell shell;

    void get_net(Net *);
    void get_id(int);

    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    bool eventFilter(QObject *, QEvent *);
    void closeEvent(QCloseEvent *);

   signals:
    void user_event(bool, QEvent *);    // true - press, false - release
};
