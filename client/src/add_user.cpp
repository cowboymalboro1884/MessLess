#include "include/add_user.h"
#include "ui_add_user.h"
#include <QDebug>

AddUser::AddUser(QWidget *parent, ProjectWindow *project_window) :
    QWidget(parent),
    ui(new Ui::AddUser), m_project_window(project_window)
{
    ui->setupUi(this);
    m_project_window->setEnabled(false);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("MessLess");
}

AddUser::~AddUser()
{
    m_project_window->setEnabled(true);
    qDebug() << "окно добавления юзера удалилось";
    delete ui;
}
