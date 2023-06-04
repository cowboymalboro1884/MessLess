#ifndef CLIENT_H
#define CLIENT_H

#include "include/mainwindow.h"
#include "network_manager.h"

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
  void got_add_project_data();
  void got_project_tasks();
  void got_add_task_data();

  void got_status_of_registration_slot(PrivateUserInfo);
  void got_status_of_authorization_slot(PrivateUserInfo);
  void got_projects_to_update_slot(std::vector<std::string> projects_to_update);
  void somebody_updated_project_slot();
  void got_tasks_to_update_slot(std::vector<Task> tasks_to_update, QString project_name);

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
