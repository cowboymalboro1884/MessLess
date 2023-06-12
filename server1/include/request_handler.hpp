#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <random>

#include "database.hpp"
#include "database_chats.hpp"
#include "database_project.hpp"
#include "errors_templates.hpp"

using namespace templates::ResponseTemplate;
using namespace messless;

class RequestHandler {
    messless::Database *database;

public:
    RequestHandler(messless::Database *database_);

    [[nodiscard]] QJsonDocument proccess_data(const QByteArray &incoming_data
    ) const;

    [[nodiscard]] QJsonDocument validate_user(const QJsonObject &request) const;
    [[nodiscard]] QJsonDocument register_company_with_admin(
        const QJsonObject &request
    ) const;

    [[nodiscard]] QJsonDocument add_user_to_company(const QJsonObject &request
    ) const;

    [[nodiscard]] QJsonDocument create_project(const QJsonObject &request
    ) const;
    [[nodiscard]] QJsonDocument get_projects(const QJsonObject &request) const;

    [[nodiscard]] QJsonDocument add_or_delete_user_in_project(
        const QJsonObject &request
    ) const;

    [[nodiscard]] QJsonDocument delete_project(const QJsonObject &request
    ) const;

    [[nodiscard]] QJsonDocument create_task(const QJsonObject &request) const;
    [[nodiscard]] QJsonDocument get_tasks(const QJsonObject &request) const;
    [[nodiscard]] QJsonDocument change_task_condition(const QJsonObject &request
    ) const;

    [[nodiscard]] QJsonDocument delete_task(const QJsonObject &request) const;

    [[nodiscard]] QJsonDocument send_message_to_company(
        const QJsonObject &request
    ) const;
    [[nodiscard]] QJsonDocument send_message_to_project(
        const QJsonObject &request
    ) const;

    [[nodiscard]] messless::PrivateUserInfo extract_user_info_from_qjson(
        const QJsonObject &request
    ) const noexcept {
        std::string email = request.value("sender_email").toString().toStdString();
        std::string password =
            request.value("sender_password").toString().toStdString();
        std::string user_role =
            request.value("sender_user_role").toString().toStdString();

        qDebug() << QString::fromStdString(email);
        return {email, password, user_role};
    };

    [[nodiscard]] QJsonArray get_raw_projects_and_tasks(
        messless::PrivateUserInfo user
    ) const noexcept;

    [[nodiscard]] QJsonArray get_raw_chat(int company_id, int project_id)
        const noexcept;

    void get_actual_global_condition_response(
        SendActualGlobalConditionResponse &response,
        messless::PrivateUserInfo &user
    ) const;
};

#endif  // REQUEST_HANDLER_H
