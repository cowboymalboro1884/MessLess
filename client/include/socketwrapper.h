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
    PrivateUserInfo user;

public:
    SocketWrapper(QString ip, qint16 port);
    ~SocketWrapper();

    void connect();
    void send_data(const QByteArray &data);
    PrivateUserInfo validateUser(const QString &email, const QString &password);
    PrivateUserInfo registerCompanyAndUser(
        const QString &name,
        const QString &surname,
        const QString &email,
        const QString &password,
        const QString &company_name,
        const QString &company_bio
    );
    bool createProject(
        const QString &email,
        const QString &password,
        const QString &user_role,
        const QString &project_name,
        const QString &project_bio
    );

    bool createTask(
        const QString &task_name,
        const QString &description,
        const QString &deadline,
        const QString &project_name
    );

    std::vector<std::string> getProjects(const QString &email, const QString &password, const QString &user_role);
};
}  // namespace client::network

#endif  // SOCKETWRAPPER_H
