#include "include/mainwindow.h"
#include "include/client.h"

#include <QApplication>
#include <QTcpServer>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client::Client client;
    client.start();
    return a.exec();
}
