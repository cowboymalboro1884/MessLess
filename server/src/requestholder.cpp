#include "server.h"

RequestHolder::RequestHolder(messless::Database *database_)
    : database(database_) {
    qDebug() << database->connection.is_open() << "RH\n";
}

QJsonDocument RequestHolder::validate_user(const QJsonObject &request
) const noexcept {
    qDebug() << "got for authorization" << request;
    QString entered_email = request.value("email").toString();
    QString entered_password = request.value("password").toString();
    qDebug() << "email: " << entered_email;
    qDebug() << "password: " << entered_password;
    messless::PrivateUserInfo is_login_success =
        messless::DatabaseUser::login_user(
            *database, entered_email.toStdString(),
            entered_password.toStdString()
        );
    QJsonObject jsonResponse;
    jsonResponse["email"] = QString::fromStdString(is_login_success.email);
    jsonResponse["password"] =
        QString::fromStdString(is_login_success.password);
    jsonResponse["user_role"] =
        QString::fromStdString(is_login_success.user_role);

    if (is_login_success.email.empty() || is_login_success.password.empty() ||
        is_login_success.user_role.empty()) {
        jsonResponse["status"] = "failed";
        jsonResponse["error_text"] = "couldn't authorize";
    } else {
        jsonResponse["status"] = "success";
        user = messless::PrivateUserInfo{
            is_login_success.email, is_login_success.password,
            is_login_success.user_role};
    }

    QJsonDocument response(jsonResponse);

    return response;
}

QJsonDocument RequestHolder::register_company_with_admin(
    const QJsonObject &request
) const noexcept {
    qDebug() << "got for registration" << request;

    QString entered_email = request.value("email").toString();
    QString entered_password = request.value("password").toString();
    QString entered_name = request.value("name").toString();
    QString entered_surname = request.value("surname").toString();
    QString entered_company_bio = request.value("company_bio").toString();
    QString entered_company_name = request.value("company_name").toString();

    unsigned int company_id = messless::DatabaseCompany::create_company(
        *database, entered_company_name.toStdString(),
        entered_company_bio.toStdString()
    );
    qDebug() << company_id;
    messless::PrivateUserInfo is_registration_success =
        messless::DatabaseCompany::create_user(
            *database, entered_email.toStdString(),
            entered_password.toStdString(), entered_name.toStdString(),
            entered_surname.toStdString(), company_id, "admin"
        );

    QJsonObject jsonResponse;
    jsonResponse["email"] =
        QString::fromStdString(is_registration_success.email);
    jsonResponse["password"] =
        QString::fromStdString(is_registration_success.password);
    jsonResponse["user_role"] =
        QString::fromStdString(is_registration_success.user_role);

    qDebug() << jsonResponse;

    if (is_registration_success.email.empty() ||
        is_registration_success.password.empty() ||
        is_registration_success.user_role.empty()) {
        jsonResponse["status"] = "failed";
        jsonResponse["error_text"] = "couldn't register";
    } else {
        jsonResponse["status"] = "success";
        user = messless::PrivateUserInfo{
            is_registration_success.email, is_registration_success.password,
            is_registration_success.user_role};
    }
    QJsonDocument response(jsonResponse);

    return response;
}

QJsonDocument RequestHolder::get_projects(const QJsonObject &request
) const noexcept {
    qDebug() << "----------------------------\ngot for get project list";
    std::string email = request.value("email").toString().toStdString();
    std::string password = request.value("password").toString().toStdString();
    std::string user_role = request.value("user_role").toString().toStdString();
    messless::PrivateUserInfo sender{email, password, user_role};
    std::vector<std::string> resp =
        messless::DatabaseProject::get_projects(*database, sender);
    std::string message;
    for (const std::string &str : resp) {
        message += str + '|';
    }

    QJsonObject jsonquery;
    jsonquery["status"] = "success";
    jsonquery["message"] = QString::fromStdString(message);
    QJsonDocument doc(jsonquery);

    qDebug() << "----------------------------";
    return doc;
}

QJsonDocument RequestHolder::create_project(const QJsonObject &request
) const noexcept {
    qDebug() << "----------------------------\ngot for create_project"
             << request;
    std::string email = request.value("email").toString().toStdString();
    std::string password = request.value("password").toString().toStdString();
    std::string user_role = request.value("user_role").toString().toStdString();
    messless::PrivateUserInfo sender{email, password, user_role};

    std::string project_name =
        request.value("project_name").toString().toStdString();
    std::string project_bio =
        request.value("project_bio").toString().toStdString();

    qDebug() << "name_of_project" << QString::fromStdString(project_name);
    qDebug() << "bio_of_project" << QString::fromStdString(project_bio);

    QJsonObject jsonResponse;
    if (!messless::DatabaseProject::is_project_exist(
            *database, sender, project_name
        )) {
        unsigned int project_id = messless::DatabaseProject::create_project(
            *database, sender, project_name, project_bio
        );
        jsonResponse["status"] = "success";
        qDebug() << "success";
        jsonResponse["project_id"] = QString::number(project_id);
        jsonResponse["project_name"] = QString::fromStdString(project_name);
        jsonResponse["project_bio"] = QString::fromStdString(project_bio);
        qDebug() << "project id " << project_id;
    } else {
        jsonResponse["type"] = "failed";
        jsonResponse["error_text"] = "project with such name is already exist";
    }

    QJsonDocument response(jsonResponse);
    return response;
}

QJsonDocument RequestHolder::create_task(const QJsonObject &request
) const noexcept {
    qDebug() << "----------------------------\ngot for create_task\n"
             << request;
    std::string task_name = request.value("task_name").toString().toStdString();
    std::string description =
        request.value("description").toString().toStdString();
    std::string deadline = request.value("deadline").toString().toStdString();
    std::string project_name =
        request.value("project_name").toString().toStdString();

    std::string email = request.value("email").toString().toStdString();
    std::string password = request.value("password").toString().toStdString();
    std::string user_role = request.value("user_role").toString().toStdString();
    messless::PrivateUserInfo sender{email, password, user_role};

    qDebug() << "task name:" << QString::fromStdString(task_name);
    qDebug() << "description:" << QString::fromStdString(description);
    qDebug() << "deadline:" << QString::fromStdString(deadline);
    qDebug() << "project name:" << QString::fromStdString(project_name);

    int project_id = messless::DatabaseProject::get_project_id(
        *database, sender, project_name
    );

    std::vector<messless::User> user_list =
        messless::DatabaseProject::get_project_user_list(*database, project_id);

    int status = messless::DatabaseProject::create_new_task(
        *database, project_id, task_name, description, deadline, user_list
    );
    qDebug() << status;
    QJsonObject response;
    if (status == 0) {
        response["status"] = "failed";
    } else {
        response["status"] = "success";
        response["task_id"] = status;
    }
    QJsonDocument doc(response);
    qDebug() << "----------------------------\n";
    return doc;
}

QJsonDocument RequestHolder::get_tasks(const QJsonObject &request
) const noexcept {
    qDebug() << "----------------------------\ngot for get tasks list";
    std::string email = request.value("email").toString().toStdString();
    std::string password = request.value("password").toString().toStdString();
    std::string user_role = request.value("user_role").toString().toStdString();

    messless::PrivateUserInfo sender{email, password, user_role};

    std::string project_name =
        request.value("project_name").toString().toStdString();

    int project_id = messless::DatabaseProject::get_project_id(
        *database, sender, project_name
    );
    std::vector<messless::Task> resp =
        messless::DatabaseProject::get_tasks(*database, project_id);
    std::string message;

    for (messless::Task task : resp) {
        message += task.task_name + '\n' + task.condition + '\n' +
                   task.deadline + '\n';
        message += '|';
    }

    QJsonObject jsonquery;
    jsonquery["status"] = "success";
    jsonquery["message"] = QString::fromStdString(message);
    QJsonDocument doc(jsonquery);

    qDebug() << "----------------------------";
    return doc;
}

QJsonDocument RequestHolder::send_message_to_company(const QJsonObject &request
) const noexcept {
    qDebug() << "----------------------------\ngot for send message";
    std::string email = request.value("email").toString().toStdString();
    std::string password = request.value("password").toString().toStdString();
    std::string user_role = request.value("user_role").toString().toStdString();
    messless::PrivateUserInfo sender{email, password, user_role};
    std::string message = request.value("message").toString().toStdString();

    qint32 id_company = 1;
    QJsonObject to_send;
    to_send["sender"] = QString::fromStdString(email);
    to_send["message"] = QString::fromStdString(message);
    to_send["id_company"] = id_company;
    QJsonDocument doc(to_send);

    QJsonObject json_query;
    try {
        owner->server->chat_m->send_message_to_company(doc, sender);
        json_query["status"] = "success";
    } catch (...) {
        json_query["status"] = "failed";
    }
    QJsonDocument ret_doc(json_query);
    qDebug() << "----------------------------";
    return ret_doc;
}

QJsonDocument RequestHolder::proccess_data(const QByteArray &incoming_data
) const noexcept {
    QJsonParseError json_data_error;
    QJsonDocument json_data =
        QJsonDocument::fromJson(incoming_data, &json_data_error);

    if (json_data_error.errorString().toInt() == QJsonParseError::NoError) {
        QString event_type = json_data.object().value("type").toString();
        qDebug() << "RH: got data";
        qDebug() << json_data;
        if (!event_type.size()) {
            QJsonObject jsonResponse;
            jsonResponse["status"] = "failed";
            jsonResponse["error_text"] = "missing request type";
            QJsonDocument response(jsonResponse);
            return response;
        }

        if (event_type == "authorization") {
            qDebug() << "RH: authorization";

            return validate_user(json_data.object());
        } else if (event_type == "registration") {
            qDebug() << "RH: registration";

            return register_company_with_admin(json_data.object());
        } else if (event_type == "add_project") {
            qDebug() << "RH: add_project";

            return create_project(json_data.object());
        } else if (event_type == "create_task") {
            qDebug() << "RH: create_task";

            return create_task(json_data.object());
        } else if (event_type == "get_projects") {
            qDebug() << "RH: get projects";

            return get_projects(json_data.object());
        } else if (event_type == "get_tasks") {
            qDebug() << "RH: get_tasks";

            return get_tasks(json_data.object());
        } else if (event_type == "send_message_to_company") {
            qDebug() << "RH: send message to company";

            return send_message_to_company(json_data.object());
        } else {
            qDebug() << "Got wrong request";
            QJsonObject jsonResponse;
            jsonResponse["status"] = "failed";
            jsonResponse["error_text"] = "Invalid JSON";
            QJsonDocument response(jsonResponse);
            return response;
        }
    }
    return json_data;
}
