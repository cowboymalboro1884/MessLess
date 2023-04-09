#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  qint16 port = 1338;
  std::string config_file = "/root/database.config";

  if (!Server::getInstance().startServer(port, config_file)) {
    return 0;
  };

  return a.exec();
}
