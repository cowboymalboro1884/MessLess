#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <random>
#include "database.hpp"
#include "database_chats.hpp"
#include "database_project.hpp"

class RequestHandler {
    messless::Database *database;

public:
    RequestHandler(messless::Database *database_);
    QJsonDocument proccess_data(const QByteArray &incoming_data) const noexcept;

    QJsonDocument validate_user(const QJsonObject &request) const noexcept;

    QJsonDocument register_company_with_admin(const QJsonObject &request
    ) const noexcept;

    QJsonDocument create_project(const QJsonObject &request) const noexcept;
    QJsonDocument create_task(const QJsonObject &request) const noexcept;

    QJsonDocument get_tasks(const QJsonObject &request) const noexcept;
    QJsonDocument get_projects(const QJsonObject &request) const noexcept;

    QJsonDocument send_message_to_company(const QJsonObject &request
    ) const noexcept;

    QJsonDocument add_user_to_project(const QJsonObject &request
    ) const noexcept;

    messless::PrivateUserInfo extract_user_info_from_qjson(const QJsonObject &request) const noexcept;
    std::string get_raw_projects_and_tasks(messless::PrivateUserInfo user) const noexcept;
};

#endif  // REQUEST_HANDLER_H
