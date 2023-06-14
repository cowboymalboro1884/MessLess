#ifndef CLIENT_H
#define CLIENT_H

#include "mainwindow.h"
#include "network_manager.h"
#include "response_types.h"

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
  void got_add_project_data(const QString &project_name, const QString &project_description);
  void got_project_tasks(QString project_name);
  void got_add_task_data(const QString &name, const QString &description, const QString &deadline);
  void got_new_task_condition(const QString &name, const QString &condition);
  void got_status_of_registration_slot(PrivateUserInfo);
  void got_status_of_authorization_slot(PrivateUserInfo);
  void got_projects_to_update_slot(std::unordered_map<std::string, std::vector<Task>> projects_to_update);
  void somebody_updated_project_slot();
  void got_tasks_to_update_slot(const QString &project_name, std::vector<Task> tasks_to_update);

private:
  QThread* network_thread;
  MainWindow *m_window;
  QString m_username;
  QString m_password;
  NetworkManager* m_network_manager;
  PrivateUserInfo user;

};
} // namespace client
#endif // CLIENT_H
