#ifndef CLIENT_H
#define CLIENT_H

#include "mainwindow.h"
#include "network_manager.h"
#include "response_types.h"
#include <QMessageBox>
#include <QObject>

namespace client {

struct Client : public QObject {
  Q_OBJECT
public:
  Client(QObject *parent = nullptr);
  ~Client();
  void start();
  void send_data(const QString &email, const QString &password);
  int userid;

public slots:
  void got_auth_data();
  void got_register_data();
  void got_add_project_data(const QString &project_name,
                            const QString &project_description);
  void got_project_tasks(QString project_name);
  void got_add_task_data(const QString &name, const QString &description,
                         const QString &deadline);
  void got_new_task_condition(const QString &name, const QString &condition);

  void got_status_of_authorization_or_registration_slot(PrivateUserInfo);

  void got_projects_to_update_slot(
      std::unordered_map<std::string, std::vector<Task>> projects_to_update);
  void somebody_updated_project_slot();
  // передаю по ссылке, надеюсь не поломается
  void got_tasks_to_update_slot(const QString &project_name,
                                const std::vector<Task> &tasks_to_update);
  void add_user_to_project(const QString &email, const QString &role);
  void add_user_to_company(const QString &email, const QString &name,
                           const QString &surname, const QString &password,
                           const QString &role);
  void send_message_to_company(const QString &message);
  void got_company_messages_slot(const std::vector<Message> &messages);
  void got_company_message_slot(Message message);
  void delete_project(const QString &project);
  void delete_user(const QString &email);
  void send_project_message(const QString &project_name,
                            const QString &message);
  void got_project_message_slot(const QString &project_name, Message message);
  void got_error_slot(const QString &error);
  void got_project_chats_slot(
      const std::unordered_map<std::string, std::vector<Message>> &chats);

private:
  QThread *network_thread;
  MainWindow *m_window;
  QString m_username;
  QString m_password;
  NetworkManager *m_network_manager;
  PrivateUserInfo user;
};
} // namespace client
#endif // CLIENT_H
