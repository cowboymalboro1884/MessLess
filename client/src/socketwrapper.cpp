#include "include/socketwrapper.h"

namespace client::network {

SocketWrapper::SocketWrapper(QString ip_, qint16 port_) {
    m_socket_wrap = new QTcpSocket(this);
    ip = ip_;
    port = port_;
}

void SocketWrapper::connect() {
    m_socket_wrap->connectToHost(ip, port);
    if (m_socket_wrap->waitForConnected()) {
        qDebug() << "Connected, i think...";
    }
}

void SocketWrapper::send_data(const QByteArray &data) {
    m_socket_wrap->write(data);
    m_socket_wrap->waitForBytesWritten();
}

PrivateUserInfo SocketWrapper::registerCompanyAndUser(
    const QString &name,
    const QString &surname,
    const QString &email,
    const QString &password,
    const QString &company_name,
    const QString &company_bio
) {
    QJsonObject jsonquery;
    jsonquery["type"] = "registration";
    jsonquery["name"] = name;
    jsonquery["surname"] = surname;
    jsonquery["company_bio"] = company_bio;
    jsonquery["company_name"] = company_name;
    jsonquery["email"] = email;
    jsonquery["password"] = password;

    QJsonDocument doc(jsonquery);
    send_data(doc.toJson());

    m_socket_wrap->waitForReadyRead();

    // TODO: add error process
    QByteArray response = m_socket_wrap->readAll();
    QJsonParseError json_data_error;
    QJsonDocument json_data =
        QJsonDocument::fromJson(response, &json_data_error);

    QString got_email = json_data.object().value("email").toString();
    QString got_password = json_data.object().value("password").toString();
    QString got_user_role = json_data.object().value("user_role").toString();
    QString status = json_data.object().value("status").toString();

    return {status, got_email, got_password, got_user_role};
}

bool SocketWrapper::createProject(
    const QString &email,
    const QString &password,
    const QString &user_role,
    const QString &project_name,
    const QString &project_bio
) {
    QJsonObject jsonquery;
    jsonquery["type"] = "add_project";
    jsonquery["email"] = email;
    jsonquery["password"] = password;
    jsonquery["user_role"] = user_role;
    jsonquery["project_name"] = project_name;
    jsonquery["project_bio"] = project_bio;

    QJsonDocument doc(jsonquery);

    send_data(doc.toJson());
    m_socket_wrap->waitForReadyRead();
    QByteArray response = m_socket_wrap->readAll();
    QJsonParseError json_data_error;
    QJsonDocument json_data =
        QJsonDocument::fromJson(response, &json_data_error);

    return (json_data.object().value("status") == "success");
}

PrivateUserInfo
SocketWrapper::validateUser(const QString &email, const QString &password) {
    QJsonObject jsonquery;
    jsonquery["type"] = "authorization";
    jsonquery["email"] = email;
    jsonquery["password"] = password;

    QJsonDocument doc(jsonquery);

    send_data(doc.toJson());
    m_socket_wrap->waitForReadyRead();
    QByteArray response = m_socket_wrap->readAll();
    QJsonParseError json_data_error;

    QJsonDocument json_data =
        QJsonDocument::fromJson(response, &json_data_error);

    QString got_email = json_data.object().value("email").toString();
    QString got_password = json_data.object().value("password").toString();
    QString got_user_role = json_data.object().value("user_role").toString();
    QString status = json_data.object().value("status").toString();

    return {status, got_email, got_password, got_user_role};
}

SocketWrapper::~SocketWrapper() {
    m_socket_wrap->deleteLater();
}

}  // namespace client::network
