#include "include/client.h"

namespace client {

Client::Client(QObject *parent) : m_window(new MainWindow()) {
  connect(m_window, SIGNAL(got_auth_data()), this, SLOT(got_auth_data()));
  connect(m_window, SIGNAL(got_register_data()), this,
          SLOT(got_register_data()));
};

void Client::start() {
  m_window->display();
  m_socketwrapper = new network::SocketWrapper("127.0.0.1", 1338);
  m_socketwrapper->connect();
}

void Client::got_register_data() {
//  user = m_socketwrapper->registerCompanyAndUser(
//      m_window->ui_Reg.getName(), m_window->ui_Reg.getSurname(),
//      m_window->ui_Reg.getLogin(), m_window->ui_Reg.getPass(),
//      m_window->ui_Reg.getCompName(), m_window->ui_Reg.getBio());
  if (true) {
    m_window->ui_Auth.close();
    m_window->ui_Reg.close();
    m_window->show();

  } else {
    //добавить ошибку
  }
}

void Client::got_auth_data() {
  user = m_socketwrapper->validateUser(m_window->ui_Auth.getLogin(),
                                       m_window->ui_Auth.getPass());
  if (user.status == "success") {
    m_window->ui_Auth.close();
    m_window->show();
  } else {
    //добавить ошибку
  }
}

Client::~Client() { m_window->deleteLater(); }

} // namespace client
