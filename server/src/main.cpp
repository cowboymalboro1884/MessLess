#include <QCoreApplication>
#include "server.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    qint16 port = 1339;
    std::string config_file = "/root/database.config";

    if (!Server::get_instance().start_server(port, config_file)) {
        return 1;
    };

    return a.exec();
}
