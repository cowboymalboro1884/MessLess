#include "request_handler.hpp"

using namespace templates::ResponseTemplate;

std::string RequestHandler::get_raw_projects_and_tasks(
    messless::PrivateUserInfo user
) const noexcept {
    std::vector<std::string> projects_to_update =
        messless::DatabaseProject::get_projects(*database, user);
    std::string message_to_send;

    for (const std::string &project : projects_to_update) {
        message_to_send += project + '|';
        int project_id =
            messless::DatabaseProject::get_project_id(*database, user, project);
        std::vector<messless::Task> tasks_of_project =
            messless::DatabaseProject::get_tasks(*database, project_id);

        for (const messless::Task &task : tasks_of_project) {
            message_to_send += task.task_name + '\n';
            message_to_send += task.condition + '\n';
            message_to_send += task.deadline + '\n';
            message_to_send += ':';
        }
    }
    return message_to_send;
}

QJsonDocument RequestHandler::get_projects(const QJsonObject &request
) const {
    qDebug() << "got for get project list";

    messless::PrivateUserInfo sender = extract_user_info_from_qjson(request);

    std::vector<std::string> projects_to_update =
        messless::DatabaseProject::get_projects(*database, sender);
    std::string message_to_send;

    for (const std::string &str : projects_to_update) {
        message_to_send += str + '|';
    }

    ProjectResponse response_to_send("got_projects_to_update");
    response_to_send.set_recipient("to sender");
    response_to_send.set_status("success");
    response_to_send.set_message(QString::fromStdString(message_to_send));

    qDebug() << response_to_send.message;
    qDebug() << "----------------------------";
    return response_to_send.to_qjson_document();
}

QJsonDocument RequestHandler::create_project(const QJsonObject &request) const {
    qDebug() << "----------------------------";
    qDebug() << "got for create project";

    messless::PrivateUserInfo sender = extract_user_info_from_qjson(request);

    std::string project_name =
        request.value("project_name").toString().toStdString();
    std::string project_bio =
        request.value("project_bio").toString().toStdString();

    qDebug() << "name_of_project" << QString::fromStdString(project_name);
    qDebug() << "bio_of_project" << QString::fromStdString(project_bio);

    ProjectResponse response_to_send("somebody_created_new_project");

    if (!messless::DatabaseProject::is_project_exist(
            *database, sender, project_name
        )) {
        unsigned int company_id =
            messless::DatabaseChats::get_company_id(*database, sender);
        unsigned int project_id = messless::DatabaseProject::create_project(
            *database, sender, project_name, project_bio
        );

        response_to_send.set_status("success");
        response_to_send.set_project_id(project_id);
        response_to_send.set_project_name(QString::fromStdString(project_name));
        response_to_send.set_project_bio(QString::fromStdString(project_bio));
        response_to_send.set_recipient("to company");
        response_to_send.set_company_id(company_id);

        qDebug() << "company id" << company_id;
        qDebug() << "project id " << project_id;

    } else {
        response_to_send.set_status("failed");
        response_to_send.set_recipient("to sender");
        response_to_send.set_error_text(
            "project with such name is already exist"
        );
    }
    qDebug() << "----------------------------";
    return response_to_send.to_qjson_document();
}

QJsonDocument RequestHandler::add_user_to_project(const QJsonObject &request
) const {
    qDebug() << "got for add user to project";

    messless::PrivateUserInfo sender = extract_user_info_from_qjson(request);

    std::string project_name =
        request.value("project_name").toString().toStdString();

    unsigned int project_id = messless::DatabaseProject::get_project_id(
        *database, sender, project_name
    );

    messless::DatabaseProject::add_user_in_project(
        *database, sender.email, project_id, sender.user_role
    );

    TaskResponse response_to_send("user_added_to_project");
    response_to_send.set_status("success");
    response_to_send.set_recipient("to concrete user");
    response_to_send.add_to_recipients(sender.email);

    return response_to_send.to_qjson_document();
};

QJsonDocument RequestHandler::delete_user_from_project(
    const QJsonObject &request
) const {
    // TODO
}
