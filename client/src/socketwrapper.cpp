#include <sstream>
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

std::vector<std::string> SocketWrapper::getProjects(
    const QString &email,
    const QString &password,
    const QString &user_role
) {
    QJsonObject jsonquery;
    jsonquery["type"] = "get_projects";
    jsonquery["email"] = email;
    jsonquery["password"] = password;
    jsonquery["user_role"] = user_role;

    QJsonDocument doc(jsonquery);

    send_data(doc.toJson());
    m_socket_wrap->waitForReadyRead();
    QByteArray response = m_socket_wrap->readAll();

    QJsonParseError json_data_error;
    QJsonDocument json_data =
        QJsonDocument::fromJson(response, &json_data_error);

    std::string projects =
        json_data.object().value("message").toString().toStdString();
    std::vector<std::string> vec;
    std::stringstream ss(projects);
    std::string proj;
    while (std::getline(ss, proj, '|')) {
        vec.push_back(proj);
    }
    return vec;
}

std::vector<Task> SocketWrapper::getTasks(
    const QString &email,
    const QString &password,
    const QString &user_role,
    const QString &project_name
) {
    QJsonObject jsonquery;
    jsonquery["type"] = "get_tasks";
    jsonquery["email"] = email;
    jsonquery["password"] = password;
    jsonquery["project_name"] = project_name;
    jsonquery["user_role"] = user_role;

    QJsonDocument doc(jsonquery);
    send_data(doc.toJson());

    m_socket_wrap->waitForReadyRead();
    QByteArray response = m_socket_wrap->readAll();

    QJsonParseError json_data_error;
    QJsonDocument json_data =
        QJsonDocument::fromJson(response, &json_data_error);

    std::string tasks =
        json_data.object().value("message").toString().toStdString();
    std::vector<Task> vec;
    std::stringstream ss1(tasks);
    std::string task;
    while (std::getline(ss1, task, '|')) {
        std::stringstream ss2(task);
        std::string condition;
        std::string deadline;
        std::string task_name;
        std::getline(ss2, task_name, '\n');
        std::getline(ss2, condition, '\n');
        std::getline(ss2, deadline, '\n');
        vec.push_back(Task{
            QString::fromStdString(task_name), QString::fromStdString(deadline),
            QString::fromStdString(condition)});
    }

    return vec;
}

bool SocketWrapper::createTask(
    const QString &email,
    const QString &password,
    const QString &user_role,
    const QString &task_name,
    const QString &description,
    const QString &deadline,
    const QString &project_name
) {
    QJsonObject jsonquery;
    jsonquery["type"] = "create_task";
    jsonquery["task_name"] = task_name;
    jsonquery["description"] = description;
    jsonquery["deadline"] = deadline;
    jsonquery["project_name"] = project_name;

    jsonquery["email"] = email;
    jsonquery["password"] = password;
    jsonquery["user_role"] = user_role;

    QJsonDocument doc(jsonquery);

    send_data(doc.toJson());
    m_socket_wrap->waitForReadyRead();

    QByteArray response = m_socket_wrap->readAll();
    QJsonParseError json_data_error;
    QJsonDocument json_data =
        QJsonDocument::fromJson(response, &json_data_error);

    return true;
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
    user = PrivateUserInfo{status, got_email, got_password, got_user_role};
    return user;
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
    user = PrivateUserInfo{status, got_email, got_password, got_user_role};

    return user;
}

SocketWrapper::~SocketWrapper() {
    m_socket_wrap->deleteLater();
}

}  // namespace client::network
