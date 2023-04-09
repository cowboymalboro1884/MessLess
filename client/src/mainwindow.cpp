#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/auth_window.h"
#include "include/reg_window.h"
#include <QtDebug>


MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
    ui_Main(new Ui::MainWindow)
{
    connect(&ui_Auth, SIGNAL(login_button_clicked()),
            this, SLOT(authorizeUser()));
    connect(&ui_Auth,SIGNAL(destroyed()),
            this, SLOT(show()));
    connect(&ui_Auth,SIGNAL(register_button_clicked()),
            this,SLOT(registerWindowShow()));
    connect(&ui_Reg,SIGNAL(register_button_clicked2()),
            this,SLOT(registerUser()));
    connect(&ui_Reg,SIGNAL(destroyed()),
            &ui_Auth, SLOT(show()));

    ui_Main->setupUi(this);
}

void MainWindow::authorizeUser()
{
    emit got_auth_data();
}

QString MainWindow::get_username(){
    return ui_Auth.getLogin();
}

QString MainWindow::get_password(){
    return ui_Auth.getPass();
}

void MainWindow::registerUser()
{
    emit got_register_data();
}

void MainWindow::display()
{
    ui_Auth.show();
}

void MainWindow::registerWindowShow()
{
    ui_Auth.hide();
    ui_Reg.show();
}


MainWindow::~MainWindow()
{
    qDebug() << "MainWindow Destroyed";
    delete ui_Main;
    exit(0);
}
