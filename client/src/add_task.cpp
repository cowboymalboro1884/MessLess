#include "include/add_task.h"
#include <QDebug>
#include "ui_add_task.h"

AddTask::AddTask(QWidget *parent, ProjectWindow *project_window)
    : QDialog(parent), ui(new Ui::AddTask), m_project_window(project_window) {
    ui->setupUi(this);
    this->setFixedSize(400, 200);
    m_project_window->setEnabled(false);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("MessLess");
    connect(ui->add_task, &QPushButton::clicked, [&] {
        m_project_window->add_new_task(
            ui->task_name_edit->text(), ui->task_description_edit->text(),
            ui->task_deadline_edit->text()
        );
        this->close();
    });
}

AddTask::~AddTask() {
    m_project_window->setEnabled(true);
    qDebug() << "окно добавления таски удалилось";
    delete ui;
}
