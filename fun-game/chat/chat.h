#pragma once
#include <QObject>
#include "gui/shell.h"

class View;

class Chat : public QObject {
    Q_OBJECT
   public:
    Chat(View *);

    Shell shell;
    
   public slots:
    void send_msg(const QString &);
    void rec_msg(const QString &);
};
