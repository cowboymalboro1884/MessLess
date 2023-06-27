#include "include/client.h"
#include "include/mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QTcpServer>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  client::Client client;
  client.start();
  return a.exec();
}
