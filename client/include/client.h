#ifndef CLIENT_H
#define CLIENT_H

#include "include/windowmanager.h"
#include "socketwrapper.h"

#include <QObject>

namespace client {
class Client : public QObject {
  Q_OBJECT
public:
  Client(QObject *parent = nullptr);
  ~Client();
  void start();
  void send_data(const QByteArray &data);
  void is_auth_correct();

public slots:
  void got_auth_data();

private:
  MainWindow *m_window;
  WindowManager *w_manager;
  QString m_username;
  QString m_password;
  network::SocketWrapper *m_socketwrapper;
};
} // namespace client
#endif // CLIENT_H
