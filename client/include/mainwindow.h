#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "auth_window.h"
#include "reg_window.h"
#include "socketwrapper.h"
#include <QBoxLayout>
#include <QMainWindow>
#include <QMessageBox>
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
  std::vector<Message> company_messages;
  std::unordered_map<std::string, std::vector<Message>> all_message;
  bool update_company_chat_flag;
  int message_counter;
  auth_window ui_Auth;
  reg_window ui_Reg;
  QString user_role;
  void display();
  void update_projects();
  void update_tasks();
  void clear_projects();
  void clear_messages();
  void send_project_message(const QString &project_name,
                            const QString &message);
  void add_new_project(const QString &project_name,
                       const QString &project_description);
  void add_new_task(const QString &task_name, const QString &task_description,
                    const QString &task_deadline);
  void change_task_condition(const QString &name, const QString &condition);
  void add_user_to_project(const QString &email, const QString &role);
  void add_user_to_company(const QString &email, const QString &name,
                           const QString &surname, const QString &password,
                           const QString &role);
  void add_new_messages();
  void hide_button();
  void delete_project();
  void delete_user(const QString &email);
  void update_project_chat(const QString &project_name, Message message);

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
  void got_project_user_data(const QString &, const QString &);
  void add_new_user_to_company(const QString &, const QString &,
                               const QString &, const QString &,
                               const QString &);
  void send_message(const QString &);
  void delete_project_signal();
  void delete_user_signal(const QString &);
  void send_project_message_signal(const QString &, const QString &);
  void got_project_message(Message);
};

#endif // MAINWINDOW_H
