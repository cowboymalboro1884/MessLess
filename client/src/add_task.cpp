#include "include/add_task.h"
#include "ui_add_task.h"
#include <QDebug>

AddTask::AddTask(QWidget *parent, ProjectWindow *project_window)
    : QDialog(parent), ui(new Ui::AddTask), m_project_window(project_window) {
  ui->setupUi(this);
  this->setFixedSize(400, 200);
  m_project_window->setEnabled(false);
  this->setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("MessLess");
  connect(ui->add_task, &QPushButton::clicked, [&] {
    m_project_window->name = get_task_name();
    m_project_window->description = get_task_description();
    m_project_window->deadline = get_task_deadline();
    m_project_window->add_new_task();
    this->close();
    //        if(true){//убрать заглушку
    //            m_project_window->clear_tasks();
    //            m_project_window->update_tasks();
    //           this->close();
    //        }else{
    //        ////TODO добавить ошибку
    //        }
  });
}

AddTask::~AddTask() {
  m_project_window->setEnabled(true);
  qDebug() << "окно добавления таски удалилось";
  delete ui;
}

QString AddTask::get_task_name() { return ui->task_name_edit->text(); }

QString AddTask::get_task_description() {
  return ui->task_description_edit->text();
}

QString AddTask::get_task_deadline() { return ui->task_deadline_edit->text(); }
