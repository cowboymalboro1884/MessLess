#include "include/mainwindow.h"
#include "include/auth_window.h"
#include "include/reg_window.h"
#include "include/socketwrapper.h"
#include "include/add_project.h"
#include "include/projectwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_Main(new Ui::MainWindow) {
  ui_Main->setupUi(this);
  connect(&ui_Auth, SIGNAL(login_button_clicked()), this,
          SLOT(authorizeUser()));
  connect(&ui_Auth, SIGNAL(register_button_clicked()), this,
          SLOT(registerWindowShow()));
  connect(&ui_Reg, SIGNAL(pushButtonBack_clicked()), this,
          SLOT(authorizeWindowShow()));
  connect(&ui_Reg, SIGNAL(register_button_clicked2()), this,
          SLOT(registerUser()));
  connect(ui_Main->newProjetButton, &QPushButton::clicked, [&] {
    add_project *chooseWindow = new add_project(nullptr, this);
    chooseWindow->show();
  });

}

void MainWindow::authorizeUser() { emit got_auth_data(); }

QString MainWindow::get_username() { return ui_Auth.getLogin(); }
//наверное нужно удалить обе
QString MainWindow::get_password() { return ui_Auth.getPass(); }

void MainWindow::registerUser() { emit got_register_data(); }

void MainWindow::clear_projects() {
  QLayoutItem *child;
  while ((child = ui_Main->project_lay->takeAt(0)) != nullptr) {
    delete child->widget();
    delete child;
  }
}

void MainWindow::add_new_project(){
    emit got_new_project_data();
}

void MainWindow::add_new_task(){
    emit got_new_task_data();
}

void MainWindow::update_projects() {

  QLayout *lay = ui_Main->project_lay->layout();

  for (const auto &i : projects) {
      qDebug()<< QString::fromStdString(i);
      QPushButton *button = new QPushButton(QString::fromStdString(i));
      project_name = button->text();
      //возможно, что тут есть ошибки
      connect(button, &QPushButton::clicked,[=]{
          project_name = button->text();
          emit got_project_tasks();
          if (true){ //потом изменить flag вместо заглушки
            ProjectWindow *project_window = new ProjectWindow(nullptr, this, project_name);
            project_window->show();
          } else{
              //добавить ошибку
          }
          });
    lay->addWidget(button);
  }
}

void MainWindow::display() { ui_Auth.show(); }

Ui::MainWindow *MainWindow::get_ui() const { return ui_Main; }

void MainWindow::registerWindowShow() {
  ui_Auth.hide();
  ui_Reg.show();
}

void MainWindow::authorizeWindowShow() {
  ui_Auth.show();
  ui_Reg.hide();
}

MainWindow::~MainWindow() {
  qDebug() << "MainWindow Destroyed";
  delete ui_Main;

  //Возможно нужно будет поудалять все
  exit(0);
}
