#ifndef DELETE_TASK_H
#define DELETE_TASK_H

#include "projectwindow.h"
#include <QWidget>

namespace Ui {
class DeleteTask;
}

class DeleteTask : public QWidget {
  Q_OBJECT

public:
  explicit DeleteTask(QWidget *parent = nullptr,
                      ProjectWindow *project_window = nullptr);
  ~DeleteTask();

private:
  Ui::DeleteTask *ui;
  ProjectWindow *m_project_window;
};

#endif // DELETE_TASK_H
