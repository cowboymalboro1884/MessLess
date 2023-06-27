#include "include/network_manager.h"

NetworkManager::NetworkManager(client::Client *client_, const QString &ip_,
                               int port_) {
  client = client_;
  ip = std::move(ip_);
  port = port_;
  m_response_handler = new ResponseHandler();
  m_query_sender = new QuerySender();
}

void NetworkManager::run() {
  m_socket_wrap = new SocketWrapper("194.87.210.109", 1339);
  m_socket_wrap->connect_to_host();

  connect(m_query_sender,
          SIGNAL(ready_to_write_data_to_socket(const QByteArray &)),
          m_socket_wrap, SLOT(send_data(const QByteArray &)));

  connect(m_socket_wrap, SIGNAL(ready_to_proccess_data(const QByteArray &)),
          m_response_handler, SLOT(proccess_data(const QByteArray &)));

  connect(m_socket_wrap->m_socket_wrap, &QTcpSocket::disconnected,
          []() { throw "Connection is lost!"; });
}

NetworkManager::~NetworkManager() {
  delete m_query_sender;
  delete m_response_handler;
  delete m_socket_wrap;
}
