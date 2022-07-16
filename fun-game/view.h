#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
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

    bool eventFilter(QObject *, QEvent *);
    void closeEvent(QCloseEvent *);
};
