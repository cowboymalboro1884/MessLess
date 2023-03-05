#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QHostAddress>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _socket(this)
{
    ui->setupUi(this);
    _socket.connectToHost(QHostAddress("194.87.210.109"), 1234);
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyRead()
{
//    QByteArray datas = _socket.readAll();
//    qDebug() << datas;
    qDebug() << "asahfa";
    _socket.write(QByteArray("ok !\n"));
}

void MainWindow::on_knopka_clicked()
{
   const QString input = ui->input->text();
   qDebug() << input;
//    onReadyRead();
    _socket.write(QByteArray(input.toStdString().c_str()));

}

