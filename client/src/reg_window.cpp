#include "include/reg_window.h"
#include "ui_reg_window.h"
#include <QWidget>
#include <QtDebug>

reg_window::reg_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::reg_window) {
  ui->setupUi(this);
  setWindowTitle("Registration");
  ui->confirmLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
  ui->passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
}

reg_window::~reg_window() { delete ui; }

QString reg_window::getName() { return m_userName; }

QString reg_window::getSurname() { return m_userSurname; }

QString reg_window::getPass() { return m_userPass; }

QString reg_window::getBio() { return m_companyBio; }

QString reg_window::getCompName() { return m_companyName; }

QString reg_window::getConfPass() { return m_confirmation; }

bool reg_window::checkPass() { return (m_confirmation == m_userPass); }

void reg_window::on_nameLineEdit_textEdited(const QString &arg1) {
  reg_window::m_userName = arg1;
}

void reg_window::on_passwordLineEdit_textEdited(const QString &arg1) {
  reg_window::m_userPass = arg1;
}

void reg_window::on_confirmLineEdit_textEdited(const QString &arg1) {
  reg_window::m_confirmation = arg1;
}

void reg_window::on_surnameLineEdit_textEdited(const QString &arg1) {
  reg_window::m_userSurname = arg1;
}

void reg_window::on_companyNameLineEdit_textEdited(const QString &arg1) {
  reg_window::m_companyName = arg1;
}

void reg_window::on_companyBioLineEdit_textEdited(const QString &arg1) {
  reg_window::m_companyBio = arg1;
}

void reg_window::on_registerPushButton_clicked() {
  emit register_button_clicked2();
}
