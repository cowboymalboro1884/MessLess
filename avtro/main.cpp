#include "mainwindow.h"
#include <QApplication>
#include <QTcpServer>

#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.display();
    return a.exec();
}
