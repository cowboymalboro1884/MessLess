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
    send_data("hi from client!\n");
}

void Client::send_data(const QByteArray &data) {
    qDebug() << "try to send";
    m_socketwrapper->send_data(data);
}

void Client::got_register_data() {
    QJsonObject json;
    json.insert("type", "registration");
    json.insert("username", m_window->ui_Reg.m_userName);
    json.insert("password", m_window->ui_Reg.m_userPass);
    QJsonDocument jsonDoc(json);
    qDebug() << jsonDoc;
    send_data(jsonDoc.toJson());
}

void Client::got_auth_data() {
    QJsonObject json;
    json.insert("type", "authorization");
    json.insert("username", userid);
    json.insert("password", m_window->get_password());
    QJsonDocument jsonDoc(json);
    qDebug() << jsonDoc;
    send_data(jsonDoc.toJson());
}

Client::~Client(){
    m_window->deleteLater();
}

} // namespace client
