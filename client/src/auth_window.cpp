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
    ui->errorMessage->hide();
    ui->lineEdit_2->setEchoMode(QLineEdit::EchoMode::Password);

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
//    on_lineEdit_textEdited(ui->lineEdit->text());
//    on_lineEdit_2_textEdited(ui->lineEdit_2->text());//зачем я их вообще вызываю
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
        qDebug() << "login: " << getLogin();
        qDebug() << "password: " << getPass();
        m_username = getLogin();
        m_userpass = getPass();
//        emit login_button_clicked();
        emit auth_check();
        ui->errorMessage->setText("Такого пользователя не существует");
    }
}

void auth_window::on_registerPushButton_clicked()
{
    emit register_button_clicked();
}




void auth_window::on_showPassword_clicked()
{
    ui->lineEdit_2->setEchoMode(QLineEdit::EchoMode::Normal);

}
