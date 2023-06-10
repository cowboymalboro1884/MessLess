#include "include/project_settings.h"
#include "ui_project_settings.h"
#include "include/add_task.h"
#include "include/add_user.h"
#include "include/delete_task.h"

ProjectSettings::ProjectSettings(QWidget *parent,ProjectWindow *project_window) :
    QWidget(parent),
    ui(new Ui::ProjectSettings), m_project_window(project_window)
{
    m_project_window->setEnabled(false);
    this->setFixedSize(400, 300);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("MessLess");
    ui->setupUi(this);
      connect(ui->add_new_task, &QPushButton::clicked, [&] {
        this->close();//TODO: возможно тут будет ошибка из-за того, что окно удаляется, надо будет исправить
        AddTask *add_task_window = new AddTask(nullptr, m_project_window);
        add_task_window->show();
      });
      connect(ui->delete_task, &QPushButton::clicked, [&]{
          this->close();//TODO: возможно тут будет ошибка из-за того, что окно удаляется, надо будет исправить
          DeleteTask *delete_task_window = new DeleteTask(nullptr, m_project_window);
          delete_task_window->show();
      });
      connect(ui->add_new_user, &QPushButton::clicked, [&]{
          this->close();//TODO: возможно тут будет ошибка из-за того, что окно удаляется, надо будет исправить
          AddUser *add_user_window = new AddUser(nullptr, m_project_window);
          add_user_window->show();
      });
}

ProjectSettings::~ProjectSettings()
{
    qDebug() << "окно настроек удалилось";
    m_project_window->setEnabled(true);
    delete ui;
}
