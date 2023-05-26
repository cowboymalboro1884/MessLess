#include "server.hpp"

using namespace templates::ResponseTemplate;

QJsonDocument RequestHandler::validate_user(const QJsonObject &request) const {
    qDebug() << "got for authorization" << request;

    QString entered_email = request.value("email").toString();
    QString entered_password = request.value("password").toString();

    qDebug() << "---------";

    messless::PrivateUserInfo is_login_success =
        messless::DatabaseUser::login_user(
            *database, entered_email.toStdString(),
            entered_password.toStdString()
        );

    UserResponse auth_response(
        "got_status_of_authorization",
        QString::fromStdString(is_login_success.email),
        QString::fromStdString(is_login_success.password),
        QString::fromStdString(is_login_success.user_role)
    );

    if (!auth_response.is_success()) {
        auth_response.set_status("failed");
        auth_response.set_error_text("couldn't authorize");
    } else {
        int company_id = messless::DatabaseChats::get_company_id(
            *database, is_login_success
        );
        std::string message_to_send =
            get_raw_projects_and_tasks(is_login_success);

        qDebug() << company_id;
        auth_response.set_company_id(company_id);
        auth_response.set_status("success");
        auth_response.set_recipient("to sender");
        auth_response.set_message(QString::fromStdString(message_to_send));
    }

    return auth_response.to_qjson_document();
}

QJsonDocument RequestHandler::register_company_with_admin(
    const QJsonObject &request
) const {
    qDebug() << "got for registration" << request;

    QString entered_email = request.value("email").toString();
    QString entered_password = request.value("password").toString();

    QString entered_name = request.value("name").toString();
    QString entered_surname = request.value("surname").toString();

    QString entered_company_bio = request.value("company_bio").toString();
    QString entered_company_name = request.value("company_name").toString();

    int company_id = messless::DatabaseCompany::create_company(
        *database, entered_company_name.toStdString(),
        entered_company_bio.toStdString()
    );

    qDebug() << company_id;
    qDebug() << "---------";

    messless::PrivateUserInfo is_registration_success =
        messless::DatabaseCompany::create_user(
            *database, entered_email.toStdString(),
            entered_password.toStdString(), entered_name.toStdString(),
            entered_surname.toStdString(), company_id, "admin"
        );

    UserResponse reg_response(
        "got_status_of_registration",
        QString::fromStdString(is_registration_success.email),
        QString::fromStdString(is_registration_success.password),
        QString::fromStdString(is_registration_success.user_role)
    );

    if (!reg_response.is_success()) {
        reg_response.set_status("failed");
        reg_response.set_error_text("couldn't register");

    } else {
        std::string message_to_send =
            get_raw_projects_and_tasks(is_registration_success);

        reg_response.set_company_id(company_id);
        reg_response.set_status("success");
        reg_response.set_recipient("to sender");
        reg_response.set_message(QString::fromStdString(message_to_send));
    }

    return reg_response.to_qjson_document();
}
