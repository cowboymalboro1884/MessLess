#include "request_handler.hpp"

void RequestHandler::get_actual_global_condition_response(
    SendActualGlobalConditionResponse &response,
    PrivateUserInfo &user
) const {  // DONE
    response.set_user_info(user.email, user.password, user.user_role);

    int company_id = DatabaseChats::get_company_id(*database, user);

    response.set_company_id(company_id);

    QJsonArray projects_with_tasks = get_raw_projects_and_tasks(user);

    response.set_projects_with_tasks(projects_with_tasks);

    QJsonArray company_chat = get_raw_chat(company_id, 0);

    QJsonArray projects_chats;
    for (const std::string &project_name :
         DatabaseProject::get_projects(*database, user)) {
        int project_id =
            DatabaseProject::get_project_id(*database, user, project_name);
        QJsonArray raw_chat = get_raw_chat(company_id, project_id);
        QJsonObject project_chat;
        project_chat["project_name"] = QString::fromStdString(project_name);
        project_chat["raw_chat"] = raw_chat;

        projects_chats.append(project_chat);
    }

    response.set_company_chat(company_chat);
    response.set_projects_chats(projects_chats);

    qDebug() << company_id;
}

QJsonDocument RequestHandler::validate_user(const QJsonObject &request
) const {  // DONE
    qDebug() << "got for authorization" << request;

    QString entered_email = request["email"].toString();
    QString entered_password = request["password"].toString();

    PrivateUserInfo is_login_success = DatabaseUser::login_user(
        *database, entered_email.toStdString(), entered_password.toStdString()
    );

    if (is_login_success.email.empty()) {
        return AuthorizationError::get_instance().to_qjson_document();
    }

    AuthorizationIsSuccess authorization_response;
    get_actual_global_condition_response(
        authorization_response, is_login_success
    );

    return authorization_response.to_qjson_document();
}

QJsonDocument RequestHandler::register_company_with_admin(
    const QJsonObject &request
) const {  // DONE
    qDebug() << "got for registration" << request;

    std::string entered_email =
        request["entered_email"].toString().toStdString();
    std::string entered_password =
        request["entered_password"].toString().toStdString();

    std::string entered_name = request["name"].toString().toStdString();
    std::string entered_surname = request["surname"].toString().toStdString();

    std::string entered_company_bio =
        request["company_bio"].toString().toStdString();
    std::string entered_company_name =
        request["company_name"].toString().toStdString();

    int company_id = DatabaseCompany::create_company(
        *database, entered_company_name, entered_company_bio
    );

    if (company_id == 0) {
        return RegistrationCompanyError::get_instance().to_qjson_document();
    }

    PrivateUserInfo is_registration_success = DatabaseCompany::create_user(
        *database, entered_email, entered_password, entered_name,
        entered_surname, company_id, "admin"
    );

    if (is_registration_success.email.empty()) {
        return RegistrationUserError::get_instance().to_qjson_document();
    }

    RegistrationCompanyIsSuccess registration_response;

    get_actual_global_condition_response(
        registration_response, is_registration_success
    );

    return registration_response.to_qjson_document();
}

QJsonDocument RequestHandler::add_user_to_company(const QJsonObject &request
) const {  // DONE
    qDebug() << "got for add user to company" << request;

    PrivateUserInfo sender = extract_user_info_from_qjson(request);

    std::string entered_email_to_add =
        request["email_to_add"].toString().toStdString();
    std::string entered_password_to_add =
        request["password_to_add"].toString().toStdString();
    std::string entered_user_role_to_add =
        request["user_role_to_add"].toString().toStdString();

    std::string entered_name = request["name"].toString().toStdString();
    std::string entered_surname = request["surname"].toString().toStdString();


    int company_id = DatabaseChats::get_company_id(*database, sender);

    PrivateUserInfo is_registration_success = DatabaseCompany::create_user(
        *database, entered_email_to_add, entered_password_to_add, entered_name,
        entered_surname, company_id, entered_user_role_to_add
    );

    if (is_registration_success.email.empty()) {
        return RegistrationUserError::get_instance().to_qjson_document();
    }

    return RegistrationUserIsSuccess().to_qjson_document();
}
