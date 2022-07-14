#pragma once
#include <QObject>


class View;

class Chat : public QObject {
    Q_OBJECT
   public:
    Chat(View *);

    View *v;
    
   public slots:
    void serv_msg(const QString &);     // signal at Net::rec_serv

   signals:
    void user_msg(const QString &);     // slot at Net::send_user
};
