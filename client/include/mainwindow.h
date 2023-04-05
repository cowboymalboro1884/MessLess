#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "auth_window.h"
#include "reg_window.h"
#include "socketwrapper.h"
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
  QString get_username();
  QString get_password();

  std::vector<std::pair<std::string, bool>>projects;        //нужен будет для сортировки
  QWidget *techArea;
  QScrollArea *scroll;
  auth_window ui_Auth; // экземпляры окна авторизации и окна регистрации
  reg_window ui_Reg; // принадлежат главному окну

private:
  Ui::MainWindow *ui_Main;


private slots:
  void authorizeUser(); // пользовательские слоты
  void registerWindowShow();
  void registerUser();


signals:
  void got_auth_data();
};

#endif // MAINWINDOW_H
