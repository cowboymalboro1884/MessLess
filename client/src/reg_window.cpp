#include "include/reg_window.h"
#include "ui_reg_window.h"
#include <QWidget>
#include <QtDebug>

reg_window::reg_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::reg_window) {
  ui->setupUi(this);
  ui->label_Error->hide();
  setWindowTitle("Registration");
  ui->confirmLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
  ui->passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
  connect(this, SIGNAL(pushButtonSignIn_clicked()), this,
          SLOT(on_pushButtonSignIn_clicked()));
}

reg_window::~reg_window() {
  qDebug() << "reg_delete";
  delete ui;
}

QString reg_window::getName() { return ui->nameLineEdit->text(); }

QString reg_window::getSurname() { return ui->surnameLineEdit->text(); }

QString reg_window::getPass() { return ui->passwordLineEdit->text(); }

QString reg_window::getBio() { return ui->companyBioLineEdit->text(); }

QString reg_window::getCompName() { return ui->companyNameLineEdit->text(); }

QString reg_window::getConfPass() { return ui->confirmLineEdit->text(); }

QString reg_window::getLogin() { return ui->emailLineEdit->text(); }

bool reg_window::checkPass() { return (getPass() == getConfPass()); }

void reg_window::on_pushButtonSignIn_clicked() {
  if (getName().isEmpty() || getSurname().isEmpty() || getLogin().isEmpty() ||
      getPass().isEmpty() || getConfPass().isEmpty() ||
      getCompName().isEmpty() || getBio().isEmpty()) {
    ui->label_Error->setText("Пустое поле");
    ui->label_Error->show();
  } else {
    if (checkPass()) {
      emit register_button_clicked2();
    } else {
      ui->label_Error->setText("Пароли отличаются");
      ui->label_Error->show();
    }
  }
}

void reg_window::on_pushButtonBack_clicked() { emit pushButtonBack_clicked(); }
