#include "include/auth_window.h"
#include "ui_auth_window.h"
#include <QScreen>
#include <QDebug>

auth_window::auth_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::auth_window)
{
    ui->setupUi(this);
    setWindowTitle("Authorization");
//    setWindowIcon("icon.ico");
    ui->errorMessage->hide();
//    QRect screenRect = QApplication::screens().at(0)->geometry();
//    this->resize(screenRect.width() * (70/100), screenRect.height() * (25/100));
}

auth_window::~auth_window()
{
    delete ui;
}

QString auth_window::getLogin()
{
    return auth_window::m_username;
}

QString auth_window::getPass()
{
    return auth_window::m_userpass;
}

void auth_window::on_lineEdit_textEdited(const QString &arg1)
{
    auth_window::m_username = arg1;
}

void auth_window::on_lineEdit_2_textEdited(const QString &arg1)
{
    auth_window::m_userpass = arg1;
}

void auth_window::on_loginPushButton_clicked()
{
    emit login_button_clicked();
    on_lineEdit_textEdited(ui->lineEdit->text());
    on_lineEdit_2_textEdited(ui->lineEdit_2->text());
    //Вынести проверку в отдельную функцию
    if(getLogin()=="" && getPass()==""){
        ui->errorMessage->setText("Введите логин и пароль");
        ui->errorMessage->show();
    }
    else if(getLogin()==""){
        ui->errorMessage->setText("Введите логин");
        ui->errorMessage->show();
    }else if(getPass()==""){
        ui->errorMessage->setText("Введите пароль");
        ui->errorMessage->show();
    }
    else{
        qDebug() << getLogin();
    }
}

void auth_window::on_registerPushButton_clicked()
{
    emit register_button_clicked();
}



