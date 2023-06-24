#include "include/add_user.h"
#include "ui_add_user.h"
#include <QDebug>
#include <QMessageBox>

AddUser::AddUser(QWidget *parent, ProjectWindow *project_window)
    : QWidget(parent), ui(new Ui::AddUser), m_project_window(project_window) {
  ui->setupUi(this);
  m_project_window->setEnabled(false);
  this->setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("MessLess");
  connect(ui->administrator, &QPushButton::clicked,
          [&] { role = "administrator"; });
  connect(ui->employer, &QPushButton::clicked, [&] { role = "employer"; });
  connect(ui->add_user, &QPushButton::clicked, [&] {
    if (role.isEmpty() || ui->email->text().isEmpty()) {
      QMessageBox::warning(this, "Warning", "All fields must be filled out!");
    } else {
      qDebug() << ui->email->text() << role;
      m_project_window->add_user_to_project(ui->email->text(), role);
      this->close();
    }
  });
}

AddUser::~AddUser() {
  m_project_window->setEnabled(true);
  qDebug() << "окно добавления юзера удалилось";
  delete ui;
}
