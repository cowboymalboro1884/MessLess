#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "auth_window.h"
#include "reg_window.h"
#include "socketwrapper.h"
#include <QBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QString>
#include <QTcpSocket>
#include <unordered_map>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QString project_name;
  QString current_window;
  std::unordered_map<std::string, std::vector<Task>> all_tasks;
  QBoxLayout *techArea;
  QScrollArea *scroll;
  auth_window ui_Auth;
  reg_window ui_Reg;
  Ui::MainWindow *get_ui() const;
  void display();
  void update_projects();
  void update_tasks();
  void clear_projects();
  QString get_username();
  QString get_password();
  void add_new_project(const QString &project_name,
                       const QString &project_description);
  void add_new_task(const QString &task_name, const QString &task_description,
                    const QString &task_deadline);
  void change_task_condition(const QString &name, const QString &condition);

private:
  Ui::MainWindow *ui_Main;

private slots:
  void authorizeUser();
  void registerUser();
  void registerWindowShow();
  void authorizeWindowShow();

signals:
  void update_task_condition(const QString &, const QString &);
  void update_current_tasks();
  void got_auth_data();
  void got_register_data();
  void got_new_project_data(const QString &, const QString &);
  void got_project_tasks();
  void got_new_task_data(const QString &, const QString &, const QString &);
};

#endif // MAINWINDOW_H
