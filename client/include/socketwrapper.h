#ifndef SOCKETWRAPPER_H
#define SOCKETWRAPPER_H

#include "query_handler.h"
#include "response_types.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QTcpSocket>

namespace client::network {

struct SocketWrapper : public QObject {
  Q_OBJECT
  QString ip;
  qint16 port;

public:
  SocketWrapper(QString ip, qint16 port);
  ~SocketWrapper();

  void connect_to_host();
  QTcpSocket *m_socket_wrap;

signals:
  void ready_to_proccess_data(const QByteArray &);

public slots:
  void update();
  bool send_data(const QByteArray &data);
};
} // namespace client::network

#endif // SOCKETWRAPPER_H
