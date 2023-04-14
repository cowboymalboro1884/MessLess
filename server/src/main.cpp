#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    qint16 port = 1339;
    std::string config_file = "/root/database.config";

    if (!Server::get_instance().start_server(port, config_file)) {
        return 0;
    };

    return a.exec();
}
