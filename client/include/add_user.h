#ifndef ADD_USER_H
#define ADD_USER_H

#include "projectwindow.h"
#include <QWidget>

namespace Ui {
class AddUser;
}

class AddUser : public QWidget {
  Q_OBJECT

public:
  explicit AddUser(QWidget *parent = nullptr,
                   ProjectWindow *project_window = nullptr);
  ~AddUser();

private:
  Ui::AddUser *ui;
  ProjectWindow *m_project_window;
};

#endif // ADD_USER_H
