#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <unordered_map>

class PrivateUserInfo {
public:
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



struct ResponseHandler : QObject {
    Q_OBJECT

public:
    ResponseHandler() = default;

    void error(const QJsonObject &request) const;

    void got_status_of_user_authorization(const QJsonObject &request) const;

    void got_status_of_user_registration(const QJsonObject &request) const;

    void got_status_of_user_and_company_registration(const QJsonObject &request
    ) const;

    void update_projects(const QJsonObject &request) const;

    void new_condition_of_projects(const QJsonObject &request) const;

    void update_tasks(const QJsonObject &request) const;

    void new_condition_of_tasks(const QJsonObject &request) const;

    void recieved_message_to_company(const QJsonObject &request) const;

    void recieved_message_to_project(const QJsonObject &request) const;

signals:
    void got_status_of_authorization(PrivateUserInfo new_user) const;
    void got_status_of_registration(PrivateUserInfo new_user) const;
    void get_new_condition_of_projects() const;
    void get_new_task_of_project(const QString &) const;
    void got_projects_with_tasks(std::unordered_map<std::string, std::vector<Task>>) const;
    void got_new_tasks_of_project(const QString &, std::vector<Task>) const;

public slots:
    void proccess_data(const QByteArray &);


};

#endif  // RESPONSE_HANDLER_H
