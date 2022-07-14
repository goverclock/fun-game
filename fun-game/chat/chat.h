#pragma once
#include <QObject>

class View;

class Chat : public QObject {
    Q_OBJECT
   public:
    Chat(View *);

    View *view;

   public slots:
    void serv_msg(char *);  // signal at Net::rec_serv

   signals:
    void user_msg( char *);  // slot at Net::send_user
                            // commands(begin with '/') are resolved at server
};
