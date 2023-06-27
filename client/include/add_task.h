#ifndef ADD_TASK_H
#define ADD_TASK_H

#include <QDialog>
#include "projectwindow.h"

namespace Ui {
class AddTask;
}

class AddTask : public QDialog {
    Q_OBJECT

public:
    explicit AddTask(
        QWidget *parent = nullptr,
        ProjectWindow *project_window = nullptr
    );
    ~AddTask();

private:
    Ui::AddTask *ui;
    ProjectWindow *m_project_window;
};

#endif  // ADD_TASK_H
