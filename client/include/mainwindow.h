#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "auth_window.h"
#include "reg_window.h"
#include "socketwrapper.h"
#include <QBoxLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QString>
#include <QTcpSocket>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  Ui::MainWindow *get_ui() const;
  void display(); // прототип пользовательской функции отображения
  void update_projects();
  void clear_projects();
  QString get_username();
  QString get_password();
  QString project_name;
  QString project_description;
  bool flag;
  std::vector<std::string> projects; //нужен будет для сортировки
  QBoxLayout *techArea;
  QScrollArea *scroll;
  auth_window ui_Auth; // экземпляры окна авторизации и окна регистрации
  reg_window ui_Reg;   // принадлежат главному окну

  void add_new_project();

private:
  Ui::MainWindow *ui_Main;

private slots:
  void authorizeUser(); // пользовательские слоты
  void registerUser();
  void registerWindowShow();
  void authorizeWindowShow();

signals:
  void got_auth_data();
  void got_register_data();
  void got_new_project_data();
};

#endif // MAINWINDOW_H
