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

private:
  MainWindow *m_window;
  QString m_username;
  QString m_password;
  network::SocketWrapper *m_socketwrapper;
  network::PrivateUserInfo user;

};
} // namespace client
#endif // CLIENT_H
