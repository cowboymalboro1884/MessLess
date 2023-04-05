#include "include/client.h"

namespace client {



Client::Client(QObject *parent) : m_window(new MainWindow()) {
    connect(m_window, SIGNAL(got_auth_data()), this, SLOT(got_auth_data()));
    connect(m_window, SIGNAL(got_register_data()), this, SLOT(got_register_data()));
};

void Client::start() {
    m_window->display();
    m_socketwrapper = new network::SocketWrapper("127.0.0.1", 1338);
    m_socketwrapper->connect();
//    send_data("hi from client!\n");
}

void Client::got_register_data() {
//    QJsonObject json;
//    json.insert("type", "registration");
//    json.insert("username", m_window->ui_Reg.getPass());
//    json.insert("password", m_window->ui_Reg.getPass());//узнать про это все
//    QJsonDocument jsonDoc(json);
//    qDebug() << jsonDoc;
//    send_data(jsonDoc.toJson());
}

void Client::got_auth_data() {
//    QJsonObject json;
//    json.insert("type", "authorization");
//    json.insert("username", m_window->get_username());
//    json.insert("password", m_window->get_password());
//    QJsonDocument jsonDoc(json);
//    qDebug() << jsonDoc;
    user = m_socketwrapper->validateUser(m_window->get_username(), m_window->get_password());
    if(user.status=="success"){
        m_window->ui_Auth.close();
        m_window->show();
    }else{

    }
}

Client::~Client(){
    m_window->deleteLater();
}

} // namespace client
