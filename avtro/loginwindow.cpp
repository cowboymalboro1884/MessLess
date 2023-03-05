#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("User Login"));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
