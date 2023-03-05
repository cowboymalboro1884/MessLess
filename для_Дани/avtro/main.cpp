#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>
#include <QTcpServer>

#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    LoginWindow loginWindow;
//    mainWindow.hide();
//    loginWindow.show();//TODO
    mainWindow.show();
    return a.exec();
}
