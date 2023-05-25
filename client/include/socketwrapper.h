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

class Task {
public:
    QString task_name;
    QString deadline;
    QString condition;
};

class Project {
public:
    QString project_name;
    QString project_bio;
    QString project_id;
};

class Message {
public:
    QString name_of_sender;
    QString surname_of_sender;
    QString message_as_it_is;
    QString user_role;
    QString file_path;
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

    void connect_to_host();
    bool send_data(const QByteArray &data);
    bool validate_user_request(const QString &email, const QString &password);
    bool register_company_and_user_request(
        const QString &name,
        const QString &surname,
        const QString &email,
        const QString &password,
        const QString &company_name,
        const QString &company_bio
    );
    bool create_project_request(
        const QString &email,
        const QString &password,
        const QString &user_role,
        const QString &project_name,
        const QString &project_bio
    );

    bool create_task_request(
        const QString &email,
        const QString &password,
        const QString &user_role,
        const QString &task_name,
        const QString &description,
        const QString &deadline,
        const QString &project_name
    );

    bool get_tasks_request(
        const QString &email,
        const QString &password,
        const QString &user_role,
        const QString &project_name
    );

    bool get_projects_request(
        const QString &email,
        const QString &password,
        const QString &user_role
    );

    bool send_message_to_company_request(
        const QString &email,
        const QString &password,
        const QString &user_role,
        const QString &message
    );

    bool get_all_message_of_company_request(
        const QString &email,
        const QString &password,
        const QString &user_role
    );

    bool add_user_to_project(const QString &email,
                             const QString &password,
                             const QString &user_role,
                             const QString &project_name);
    void wait_for_data() {
        while(m_socket_wrap->bytesAvailable() == 0){
            m_socket_wrap->waitForReadyRead(100);
        }
    };

public slots:
    void update();

signals:
    void got_status_of_registration(client::network::PrivateUserInfo user);
    void got_status_of_authorization(client::network::PrivateUserInfo user);
    void got_projects_to_update(std::vector<std::string> projects_to_update);
    void somebody_updated_project();
    void got_tasks_to_update(std::vector<client::network::Task> tasks_to_update, QString project_name);
    void somebody_updated_tasks();
};
}  // namespace client::network

#endif  // SOCKETWRAPPER_H
