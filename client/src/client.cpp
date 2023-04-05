#include "include/client.h"

namespace client {

Client::Client(QObject *parent) : m_window(new MainWindow()) {
  connect(m_window, SIGNAL(got_auth_data()), this, SLOT(got_auth_data()));
};

void Client::start() {
  m_window->display();
  m_socketwrapper = new network::SocketWrapper("194.87.210.109", 1337);
  m_socketwrapper->connect();
  send_data("hi from client!\n");
}

void Client::send_data(const QByteArray &data) {
  qDebug() << "try to send";
  m_socketwrapper->send_data(data);
}

void Client::got_auth_data() {
  QString name = m_window->get_username();
  QString pass = m_window->get_password();
  QJsonObject json;
  json.insert("event", "authorization");
  json.insert("username", name);
  json.insert("password", pass);

  QJsonDocument jsonDoc(json);

  qDebug() << jsonDoc;
  send_data(jsonDoc.toJson());

  is_auth_correct(); //пока что просто заглушка
}

void Client::is_auth_correct() {
  if (true) {
    m_window->is_auth = true;
  } else {
    m_window->is_auth = false;
  }
}

Client::~Client() { m_window->deleteLater(); }

} // namespace client
