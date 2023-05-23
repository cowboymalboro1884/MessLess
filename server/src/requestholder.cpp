#include "server.h"
#include "responsetemplate.h"

using namespace templates::ResponseTemplate;

RequestHolder::RequestHolder(messless::Database *database_)
    : database(database_) {}

QJsonDocument RequestHolder::validate_user(const QJsonObject &request) const noexcept {
    qDebug() << "got for authorization" << request;
    QString entered_email = request.value("email").toString();
    QString entered_password = request.value("password").toString();
    qDebug() << "---------";

    messless::PrivateUserInfo is_login_success =
        messless::DatabaseUser::login_user(
            *database, entered_email.toStdString(),
            entered_password.toStdString()
        );

    UserResponse auth_response("got_status_of_authorization", QString::fromStdString(is_login_success.email), \
                                        QString::fromStdString(is_login_success.password), \
                                     QString::fromStdString(is_login_success.user_role));

    if (!auth_response.is_success()) {
        auth_response.set_status("failed");
        auth_response.set_error_text("couldn't authorize");
    } else {
        qint32 company_id = messless::DatabaseChats::get_company_id(*database, is_login_success);
        qDebug() << company_id;
        auth_response.set_company_id(company_id);
        auth_response.set_status("success");
        auth_response.set_recipient("to sender");

        user = messless::PrivateUserInfo{
            is_login_success.email, is_login_success.password,
            is_login_success.user_role};
    }

    return auth_response.to_qjson_document();
}

QJsonDocument RequestHolder::register_company_with_admin(const QJsonObject &request
) const noexcept {
    qDebug() << "got for registration" << request;

    QString entered_email = request.value("email").toString();
    QString entered_password = request.value("password").toString();
    QString entered_name = request.value("name").toString();
    QString entered_surname = request.value("surname").toString();
    QString entered_company_bio = request.value("company_bio").toString();
    QString entered_company_name = request.value("company_name").toString();

    qint32 company_id = messless::DatabaseCompany::create_company(
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

    UserResponse reg_response("got_status_of_registration", QString::fromStdString(is_registration_success.email), \
                              QString::fromStdString(is_registration_success.password), \
                           QString::fromStdString(is_registration_success.user_role));

    if (!reg_response.is_success()) {
        reg_response.set_status("failed");
        reg_response.set_error_text("couldn't register");

    }else {
        unsigned int company_id = messless::DatabaseChats::get_company_id(*database, is_registration_success);

        reg_response.set_company_id(company_id);
        reg_response.set_status("success");
        reg_response.set_recipient("to sender");

        user = messless::PrivateUserInfo{
            is_registration_success.email, is_registration_success.password,
            is_registration_success.user_role};
    }

    return reg_response.to_qjson_document();
}

QJsonDocument RequestHolder::get_projects(const QJsonObject &request) const noexcept {
    qDebug() << "got for get project list";
    std::string email = request.value("email").toString().toStdString();
    std::string password = request.value("password").toString().toStdString();
    std::string user_role = request.value("user_role").toString().toStdString();
    messless::PrivateUserInfo sender{email, password, user_role};

    std::vector<std::string> projects_to_update =
        messless::DatabaseProject::get_projects(*database, sender);
    std::string message_to_send;

    for (const std::string &str : projects_to_update) {
        message_to_send += str + '|';
    }

    qDebug() << QString::fromStdString(message_to_send);

    QJsonObject json_response_object;

    json_response_object["type"] = "got_projects_to_update";
    json_response_object["status"] = "success";
    json_response_object["message"] = QString::fromStdString(message_to_send);
    json_response_object["recipient"] = "to sender";    
    QJsonDocument doc(json_response_object);

    qDebug() << "----------------------------";
    return doc;
}

QJsonDocument RequestHolder::create_project(const QJsonObject &request) const noexcept {
    qDebug() << "got for create project";

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

    QJsonObject json_response_object;
    if (!messless::DatabaseProject::is_project_exist(
            *database, sender, project_name
        )) {

        unsigned int company_id = messless::DatabaseChats::get_company_id(*database, sender);
        unsigned int project_id = messless::DatabaseProject::create_project(
            *database, sender, project_name, project_bio
        );

        json_response_object["type"] = "somebody_created_new_project";
        json_response_object["status"] = "success";
        json_response_object["project_id"] = QString::number(project_id);
        json_response_object["project_name"] = QString::fromStdString(project_name);
        json_response_object["project_bio"] = QString::fromStdString(project_bio);
        json_response_object["recipient"] = "to company";
        json_response_object["company_id"] = QString::number(company_id);
        qDebug() << "company id" << company_id;
        qDebug() << "project id " << project_id;

    } else {
        json_response_object["type"] = "somebody_created_new_project";
        json_response_object["status"] = "failed";
        json_response_object["recipient"] = "to sender";
        json_response_object["error_text"] = "project with such name is already exist";
    }

    QJsonDocument response_document(json_response_object);
    return response_document;
}

QJsonDocument RequestHolder::create_task(const QJsonObject &request) const noexcept {
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

    QJsonObject json_response_object;
    qDebug() << status;
    json_response_object["type"] = "somebody_created_new_task";
    if (status == 0) {
        json_response_object["status"] = "failed";
    } else {
        json_response_object["status"] = "success";
        json_response_object["task_id"] = status;

    }
    qDebug() << "----------------------------\n";
    return QJsonDocument(json_response_object);
}

QJsonDocument RequestHolder::get_tasks(const QJsonObject &request) const noexcept {
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

    // TODO: PROCCESS ERRORS
    std::vector<messless::Task> tasks_to_update =
        messless::DatabaseProject::get_tasks(*database, project_id);

    std::string message;

    for (const messless::Task& task : tasks_to_update) {
        message += task.task_name + '\n' + task.condition + '\n' +
                   task.deadline + '\n';
        message += '|';
    }

    QJsonObject json_response_object;

    json_response_object["status"] = "success";
    json_response_object["type"] = "got_tasks_to_update";
    json_response_object["project_name"] = QString::fromStdString(project_name);
    json_response_object["message"] = QString::fromStdString(message);
    json_response_object["recipient"] = "to sender";

    QJsonDocument doc(json_response_object);

    qDebug() << "----------------------------";
    return doc;
}

QJsonDocument RequestHolder::send_message_to_company(const QJsonObject &request) const noexcept {
    qDebug() << "----------------------------\ngot for send message";
    std::string email = request.value("email").toString().toStdString();
    std::string password = request.value("password").toString().toStdString();
    std::string user_role = request.value("user_role").toString().toStdString();
    messless::PrivateUserInfo sender{email, password, user_role};
    std::string message =
        request.value("message").toString().toStdString();
    std::string file_link =
        request.value("file_link").toString().toStdString();
    const unsigned int TO_COMPANY = 0;

    unsigned int company_id = messless::DatabaseChats::get_company_id(*database, sender);
    unsigned int chat_id = messless::DatabaseChats::get_chat_id(*database, company_id, TO_COMPANY);
    messless::DatabaseChats::send_message(*database, chat_id, sender, message, file_link);

    messless::User sender_user = messless::DatabaseChats::from_private_user_info_to_user(*database, sender);

    QJsonObject json_response_object;

    json_response_object["type"] = "got_new_message_to_company";
    json_response_object["message"] = QString::fromStdString(message);
    json_response_object["name_of_sender"] = QString::fromStdString(sender_user.name);
    json_response_object["surname_of_sender"] = QString::fromStdString(sender_user.surname);
    json_response_object["user_role"] = QString::fromStdString(user_role);
    json_response_object["file_link"] = QString::fromStdString(file_link);
    json_response_object["recipient"] = "to company";
    json_response_object["status"] = "success";

    QJsonDocument document_to_send(json_response_object);

    return document_to_send;
}

QJsonDocument RequestHolder::add_user_to_project(const QJsonObject &request) const noexcept {
    qDebug() << "----------------------------\ngot for add user to project";
    std::string email = request.value("email").toString().toStdString();
    std::string password = request.value("password").toString().toStdString();
    std::string user_role = request.value("user_role").toString().toStdString();
    messless::PrivateUserInfo sender{email, password, user_role};

    std::string project_name = request.value("project_name").toString().toStdString();

    unsigned int project_id = messless::DatabaseProject::get_project_id(*database, sender, project_name);

    messless::DatabaseProject::add_user_in_project(*database, email, project_id, user_role);

    QJsonObject json_response_object;
    json_response_object["type"] = "user_added_to_project";
    json_response_object["status"] = "success";
    json_response_object["recipient"] = "to concrete user";
    json_response_object["email"] = QString::fromStdString(email);

    return QJsonDocument(json_response_object);
};

QJsonDocument RequestHolder::proccess_data(const QByteArray &incoming_data) const noexcept {
    QJsonParseError json_data_error;
    QJsonDocument json_data =
        QJsonDocument::fromJson(incoming_data, &json_data_error);

    if (json_data_error.errorString().toInt() == QJsonParseError::NoError) {
        QString event_type = json_data.object().value("type").toString();
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
        } else if (event_type == "send_message_to_company"){
            qDebug() << "RH: send message to company";

            return send_message_to_company(json_data.object());
        } else if(event_type == "add_user_to_project"){
            qDebug() << "RH: add_user_to_project";

            return add_user_to_project(json_data.object());
        } else {
            qDebug() << "RH: Got wrong request";
            QJsonObject jsonResponse;
            jsonResponse["status"] = "failed";
            jsonResponse["error_text"] = "Invalid JSON";
            QJsonDocument response(jsonResponse);
            return response;
        }
    }
    return json_data;
}
