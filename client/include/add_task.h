#ifndef ADD_TASK_H
#define ADD_TASK_H

#include "projectwindow.h"
#include <QDialog>

namespace Ui {
class AddTask;
}

class AddTask : public QDialog {
  Q_OBJECT

public:
  explicit AddTask(QWidget *parent = nullptr,
                   ProjectWindow *project_window = nullptr);
  ~AddTask();
  QString get_task_name();
  QString get_task_description();
  QString get_task_deadline();

private:
  Ui::AddTask *ui;
  ProjectWindow *m_project_window;
};

#endif // ADD_TASK_H
