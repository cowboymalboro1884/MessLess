#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

struct ResponseHandler : QObject {
    Q_OBJECT

public:
    ResponseHandler() = default;

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

public slots:
    void proccess_data(const QByteArray &);
};

#endif  // RESPONSE_HANDLER_H
