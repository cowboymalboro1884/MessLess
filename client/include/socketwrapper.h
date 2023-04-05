#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QTcpSocket>


namespace client::network {
class PrivateUserInfo {
public:
    QString status;
    QString email;
    QString password;
    QString user_role;
};
class SocketWrapper : public QObject {
  Q_OBJECT
  QTcpSocket *m_socket_wrap;
  QString ip;
  qint16 port;

public:
  SocketWrapper(QString ip, qint16 port);
  ~SocketWrapper();

  void connect();
  void send_data(const QByteArray &data);
  PrivateUserInfo validateUser(const QString &email, const QString &password);
};
} // namespace client::network

#endif // SOCKETWRAPPER_H
