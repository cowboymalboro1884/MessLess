#include "include/projectwindow.h"
#include "ui_projectwindow.h"
#include <QtDebug>

projectWindow::projectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::projectWindow)
{
    ui->setupUi(this);
}

projectWindow::~projectWindow()
{
    qDebug() << "удалено";
    delete ui;
}
