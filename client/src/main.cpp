#include "include/mainwindow.h"
#include "include/client.h"

#include <QApplication>
#include <QTcpServer>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QList<client::Client*> clients;
    for(int i = 0; i <= 2; i++){
        clients.push_back(new client::Client());
        clients.back()->start();
        clients.back()->userid = i;
        clients.back()->got_auth_data();
    }
    return a.exec();
}
