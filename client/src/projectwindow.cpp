#include "include/projectwindow.h"
#include "include/add_task.h"
#include "ui_projectwindow.h"

ProjectWindow::ProjectWindow(QWidget *parent, MainWindow *main_window, QString project_name) :
    QDialog(parent),
    ui(new Ui::ProjectWindow), m_main_window(main_window)
{
    ui->setupUi(this);
    m_main_window->setEnabled(false);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("MessLess("+project_name+")");
    ui->project_name->setText(project_name);
    update_tasks();
    connect(ui->add_new_task, &QPushButton::clicked, [&]{
       AddTask *add_task_window = new AddTask(nullptr, this);
       add_task_window->show();
    });


}

ProjectWindow::~ProjectWindow()
{
    qDebug() << "project window deleted";
    m_main_window->setEnabled(true);
    delete ui;
}

void ProjectWindow::add_new_task(){
    m_main_window->task_name = name;
    m_main_window->task_description = description;
    m_main_window->task_deadline = deadline;
    m_main_window->add_new_task();
}

void ProjectWindow::update_tasks(){
    QLayout *to_do = ui->task_to_do_layout->layout();//изменил что-то
    QLayout *in_progress = ui->task_in_progress_layout->layout();
    QLayout *done = ui->task_done_layout->layout();
    for(const auto &i: m_main_window->tasks){
        QLabel *task = new QLabel(i.task_name);
        task->setAlignment(Qt::AlignHCenter);
        if(i.condition == "to do"){
            to_do->addWidget(task);
        }else if(i.condition == "in progress"){
            in_progress->addWidget(task);
        }else{
            done->addWidget(task);
        }
    }
}

void ProjectWindow::clear_tasks(){
    QLayoutItem *task;
    while((task=ui->task_to_do->takeAt(0))!=nullptr){
        delete task->widget();
        delete task;

    }
    while((task=ui->task_in_progress->takeAt(0))!=nullptr){
        delete task->widget();
        delete task;

    }
    while((task=ui->task_done->takeAt(0))!=nullptr){
        delete task->widget();
        delete task;

    }

}


