#ifndef CLIENT_H
#define CLIENT_H

#include "include/mainwindow.h"
#include "socketwrapper.h"

#include <QObject>

namespace client {

class Client : public QObject {
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

  void got_status_of_registration_slot(client::network::PrivateUserInfo);
  void got_status_of_authorization_slot(client::network::PrivateUserInfo);
  void got_projects_to_update_slot(std::vector<std::string> projects_to_update);
  void somebody_updated_project_slot();
  void got_tasks_to_update_slot(std::vector<client::network::Task> tasks_to_update, QString project_name);

private:
  MainWindow *m_window;
  QString m_username;
  QString m_password;
  network::SocketWrapper *m_socketwrapper;
  network::PrivateUserInfo user;

};
} // namespace client
#endif // CLIENT_H
