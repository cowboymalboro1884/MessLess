#include "include/add_project.h"
#include "ui_add_project.h"

add_project::add_project(QWidget *parent, MainWindow *main_window)
    : QWidget(parent), ui(new Ui::add_project), main_wind(main_window) {
  ui->setupUi(this);
  this->setFixedSize(400, 200);
  main_wind->setEnabled(false);
  this->setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("MessLess");
  connect(ui->addProject, &QPushButton::clicked,
          [&] { //TODO мб надо будт изменить на this
            main_wind->project_name = get_project_name();
            main_wind->project_description = get_project_description();
            main_wind->add_new_project();
            if (!main_wind->flag) {
              //TODO написать какой-нибудь popup с ошибкой
            } else {
              this->close();
              main_wind->clear_projects();
              qDebug() << "проекты очищены";
              main_wind->update_projects();
              qDebug() << "проекты обновлены";
            }
          });
}

QString add_project::get_project_name() { return ui->name_lineEdit->text(); }

QString add_project::get_project_description() {
  return ui->description_lineEdit->text();
}

add_project::~add_project() {
  qDebug() << "add project window deleted";
  main_wind->setEnabled(true);
  delete ui;
}
