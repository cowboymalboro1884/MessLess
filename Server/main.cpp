#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    qint16 port = 1337;

    Server server(port);
    server.startServer();
    return a.exec();
}
