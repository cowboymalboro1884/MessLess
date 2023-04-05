#include "include/auth_window.h"
#include "ui_auth_window.h"
#include <QDebug>
#include <QScreen>

auth_window::auth_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::auth_window) {
  ui->setupUi(this);
  setWindowTitle("Authorization");
  ui->errorMessage->hide();
  ui->passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
}

auth_window::~auth_window() { delete ui; }

QString auth_window::getLogin() { return ui->loginLineEdit->text(); }

QString auth_window::getPass() { return ui->passwordLineEdit->text(); }


void auth_window::on_loginPushButton_clicked() {

  //Вынести проверку в отдельную функцию

  if (getLogin() == "" && getPass() == "") {
    ui->errorMessage->setText("Введите логин и пароль");
    ui->errorMessage->show();
  } else if (getLogin() == "") {
    ui->errorMessage->setText("Введите логин");
    ui->errorMessage->show();
  } else if (getPass() == "") {
    ui->errorMessage->setText("Введите пароль");
    ui->errorMessage->show();
  } else {
    qDebug() << "login: " << getLogin();
    qDebug() << "password: " << getPass();
    m_username = getLogin();
    m_userpass = getPass();
    //        emit login_button_clicked();
    emit auth_check();
    ui->errorMessage->setText("Такого пользователя не существует");
  }
}

void auth_window::on_registerPushButton_clicked() {
  emit register_button_clicked();
}

void auth_window::on_showPassword_clicked() {
  ui->passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
}
