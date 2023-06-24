#include "include/delete_user.h"
#include "ui_delete_user.h"
#include <QDebug>
#include <QMessageBox>

DeleteTask::DeleteTask(QWidget *parent, ProjectWindow *project_window)
    : QWidget(parent), ui(new Ui::DeleteTask),
      m_project_window(project_window) {
  ui->setupUi(this);
  m_project_window->setEnabled(false);
  this->setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("MessLess");
  connect(ui->delete_button, &QPushButton::clicked, [&] {
      if(ui->email->text().isEmpty()){
          QMessageBox::warning(this, "Warning" ,"Enter user email!");
      }else{
         project_window->delete_user(ui->email->text());
      }
  });

}

DeleteTask::~DeleteTask() {
  m_project_window->setEnabled(true);
  qDebug() << "окно удаления удалилось";
  delete ui;
}
