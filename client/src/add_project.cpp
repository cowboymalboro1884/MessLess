#include "include/add_project.h"
#include "ui_add_project.h"

add_project::add_project(QWidget *parent, MainWindow *main_window)
    : QWidget(parent), ui(new Ui::add_project), main_wind(main_window) {
  ui->setupUi(this);
  this->setFixedSize(400, 200);
  main_wind->setEnabled(false);
  this->setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("MessLess");
  connect(ui->addProject, &QPushButton::clicked, [&] {
    main_wind->add_new_project(ui->name_lineEdit->text(),
                               ui->description_lineEdit->text());
  });
}

add_project::~add_project() {
  qDebug() << "add project window deleted";
  main_wind->setEnabled(true);
  delete ui;
}
