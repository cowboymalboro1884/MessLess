#include "include/delete_task.h"
#include "ui_delete_task.h"
#include <QDebug>

DeleteTask::DeleteTask(QWidget *parent, ProjectWindow *project_window) :
    QWidget(parent),
    ui(new Ui::DeleteTask), m_project_window(project_window)
{
    ui->setupUi(this);
    m_project_window->setEnabled(false);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("MessLess");
}

DeleteTask::~DeleteTask()
{
    m_project_window->setEnabled(true);
    qDebug() << "окно удаления таски удалилось";
    delete ui;
}
