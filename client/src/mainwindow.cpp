#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/auth_window.h"
#include "include/reg_window.h"
#include <QtDebug>


MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
    ui_Main(new Ui::MainWindow)
{
    user_counter = 0;
    m_loginSuccesfull = false;
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
    connect(&ui_Auth,SIGNAL(successfullAuth()),
            this, SLOT(showMainWindow()));

    ui_Main->setupUi(this);
}

void MainWindow::authorizeUser()
{
    /// TODO
}

void MainWindow::registerUser()
{
    /// TODO
}

void MainWindow::showMainWindow(){
    ui_Auth.close();
    this->show();
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
    if(m_loginSuccesfull)
    {
        /// TODO
    }
    qDebug() << "MainWindow Destroyed";
    delete ui_Main;
    exit(0);
}
