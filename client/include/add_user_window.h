#ifndef ADD_USER_WINDOW_H
#define ADD_USER_WINDOW_H

#include "mainwindow.h"
#include <QMessageBox>

namespace Ui {
class AddUserWindow;
}

class AddUserWindow : public QWidget {
  Q_OBJECT

public:
  explicit AddUserWindow(QWidget *parent = nullptr,
                         MainWindow *main_window = nullptr);
  ~AddUserWindow();

private:
  Ui::AddUserWindow *ui;
  MainWindow *m_main_window;
  QString role;
};

#endif // ADD_USER_WINDOW_H
