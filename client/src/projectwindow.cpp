#include "include/projectwindow.h"
#include "include/project_settings.h"
#include "ui_projectwindow.h"

ProjectWindow::ProjectWindow(QWidget *parent, MainWindow *main_window,
                             QString project_name)
    : QDialog(parent), ui(new Ui::ProjectWindow), m_main_window(main_window) {
  ui->setupUi(this);
  m_main_window->setEnabled(false);
  this->setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("MessLess(" + project_name + ")");
  ui->project_name->setText(project_name);
  update_tasks();

  connect(main_window, SIGNAL(update_current_tasks()), this,
          SLOT(delete_and_update_tasks()));
  connect(ui->settings, &QPushButton::clicked, [&] {
    ProjectSettings *project_settings_window =
        new ProjectSettings(nullptr, this);
    project_settings_window->show();
  });
}

ProjectWindow::~ProjectWindow() {
  qDebug() << "project window deleted";
  m_main_window->setEnabled(true);
  clear_tasks();
  m_main_window->current_window = "main_window";
  delete ui;
}

void ProjectWindow::add_new_task(const QString &task_name,
                                 const QString &task_description,
                                 const QString &task_deadline) {
  m_main_window->add_new_task(task_name, task_description, task_deadline);
}

void ProjectWindow::add_user_to_project(const QString &name, const QString &role){
    m_main_window->add_user_to_project(name, role);
}

void ProjectWindow::update_tasks() {
  QLayout *to_do = ui->task_to_do_layout->layout();
  QLayout *in_progress = ui->task_in_progress_layout->layout();
  QLayout *done = ui->task_done_layout->layout();
  for (const auto &task :
       m_main_window->all_tasks[m_main_window->current_window.toStdString()]) {
      qDebug() << task.condition;
    QPushButton *task_button = new QPushButton(task.task_name);
    connect(task_button, &QPushButton::clicked, [&] {
      if (task.condition == "to do") {
        m_main_window->change_task_condition(task.task_name, "in progress");
      } else if (task.condition == "in progress") {
        m_main_window->change_task_condition(task.task_name, "done");
      } else {
        m_main_window->change_task_condition(task.task_name, "to do");
      }
    });

    if (task.condition == "to do") {
      to_do->addWidget(task_button);
    } else if (task.condition == "in progress") {
      in_progress->addWidget(task_button);
    } else {
      done->addWidget(task_button);
    }
  }
}

void ProjectWindow::clear_tasks() {
  QLayoutItem *task;
  while ((task = ui->task_to_do_layout->takeAt(0)) != nullptr) {
    delete task->widget();
    delete task;
  }
  while ((task = ui->task_in_progress_layout->takeAt(0)) != nullptr) {
    delete task->widget();
    delete task;
  }
  while ((task = ui->task_done_layout->takeAt(0)) != nullptr) {
    delete task->widget();
    delete task;
  }
}

void ProjectWindow::delete_and_update_tasks() {
  clear_tasks();
  update_tasks();
}
