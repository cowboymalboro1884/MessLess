#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    std::ifstream input("/root/database.config");
    std::string private_salt, connection_string;
    std::getline(input, connection_string);
    std::getline(input, private_salt);
    messless::Database db(connection_string, private_salt);
    qint16 port = 1337;
    Server server(port, &db);

    server.startServer();
    return a.exec();
}
