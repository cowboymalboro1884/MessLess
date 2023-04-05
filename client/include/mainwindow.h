#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "auth_window.h"
#include "reg_window.h"
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
  void display(); // прототип пользовательской функции отображения
  QString get_username();
  QString get_password();
  void update_projects();
  Ui::MainWindow *get_ui() const;
  std::vector<std::pair<std::string, bool>>projects;        //нужен будет для сортировки
  std::vector<std::pair<std::pair<std::string, std::string>, std::string>> user;
  QWidget *techArea;
  QScrollArea *scroll;

private:
  Ui::MainWindow *ui_Main;
  auth_window ui_Auth; // экземпляры окна авторизации и окна регистрации
  reg_window ui_Reg;   // принадлежат главному окну

private slots:
  void authorizeUser(); // пользовательские слоты
  void registerWindowShow();
  void registerUser();
  void check_auth();

signals:
  void got_auth_data();
};

#endif // MAINWINDOW_H
