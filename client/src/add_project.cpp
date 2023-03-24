#include "add_project.h"
#include "ui_add_project.h"

add_project::add_project(QWidget *parent, MainWindow *main_wind)
    : QMainWindow(parent), ui(new Ui::add_project), main_wind(main_wind) {
  ui->setupUi(this);
  this->setFixedSize(400, 400);
  ui->name->setStyleSheet(
      ".QLineEdit {background-color : #191919;border-width: 2px; "
      "border-radius: 10px; padding: 6px;}");

  connect(
      ui->addProject, &QPushButton::clicked,
      [&] { //мб надо будт изменить на this
        std::string project_name = ui->name->text().toStdString();
        std::string project_descririon = ui->description->text().toStdString();
        // передам имя проекта и описание
        bool flag = true; //// убрать заглушку
        if (!flag) {
          //написать какой-нибудь popup с ошибкой

        } else {

          //            main_wind->get_ui().pro

          main_wind->projects; //функция, которая возвращает массив проектов
          main_wind->centralWidget()
              ->tab; //понять как обращаться нормально к полю и вызывать clear()
          main_wind->update_projects(); //написать функцию в main
          hide();
          this->close();
        }
      });
}

add_project::~add_project() { delete ui; }
