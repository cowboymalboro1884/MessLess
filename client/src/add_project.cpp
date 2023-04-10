#include "include/add_project.h"
#include "ui_add_project.h"

add_project::add_project(QWidget *parent, MainWindow *main_window)
    : QWidget(parent), ui(new Ui::add_project), main_wind(main_window) {
  ui->setupUi(this);
  this->setFixedSize(400, 200);
  main_wind->setEnabled(false);
  this->setAttribute(Qt::WA_DeleteOnClose);
//  ui->name_lineEdit->setStyleSheet(
//      ".QLineEdit {background-color : #191919;border-width: 2px; "
//      "border-radius: 10px; padding: 6px;}");

  connect(ui->addProject, &QPushButton::clicked,
          [&] { //мб надо будт изменить на this
            std::string project_name = ui->name_lineEdit->text().toStdString();
            std::string project_descririon =
                ui->description_lineEdit->text().toStdString();
            // передам имя проекта и описание
            bool flag = true; //// убрать заглушку
            if (!flag) {
              //написать какой-нибудь popup с ошибкой

            } else {

//              main_wind->projects.push_back({"1","2","3"});//функция, которая
              main_wind->clear_projects();


              main_wind->update_projects(); //написать функцию в main
              hide();
              this->close();
            }
          });
}

add_project::~add_project() {
    qDebug() << "add project window deleted";
    main_wind->setEnabled(true);
    delete ui; }
