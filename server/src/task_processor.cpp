#include "request_handler.hpp"

using namespace templates::ResponseTemplate;

QJsonDocument RequestHandler::create_task(const QJsonObject &request) const {
    qDebug() << "----------------------------\ngot for create_task\n";

    std::string task_name = request.value("task_name").toString().toStdString();
    std::string description =
        request.value("description").toString().toStdString();
    std::string deadline = request.value("deadline").toString().toStdString();

    std::string project_name =
        request.value("project_name").toString().toStdString();

    messless::PrivateUserInfo sender = extract_user_info_from_qjson(request);

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

    TaskResponse response_to_send("somebody_created_new_task");
    response_to_send.set_recipient("to array of users");

    qDebug() << status;
    if (status != 0) {
        response_to_send.set_status("success");
        response_to_send.set_task_id(status);

        for (auto user : user_list) {
            response_to_send.add_to_recipients(user.email);
        }

    } else {
        response_to_send.set_status("failed");
        response_to_send.set_error_text(
            "something went wrong in creating task =("
        );
    }
    qDebug() << "----------------------------\n";

    return response_to_send.to_qjson_document();
}

QJsonDocument RequestHandler::get_tasks(const QJsonObject &request) const {
    qDebug() << "----------------------------\ngot for get tasks list";

    messless::PrivateUserInfo sender = extract_user_info_from_qjson(request);

    std::string project_name =
        request.value("project_name").toString().toStdString();

    int project_id = messless::DatabaseProject::get_project_id(
        *database, sender, project_name
    );

    std::vector<messless::Task> tasks_to_update =
        messless::DatabaseProject::get_tasks(*database, project_id);

    std::string message;
    for (const messless::Task &task : tasks_to_update) {
        message += task.task_name + '\n' + task.condition + '\n' +
                   task.deadline + '\n';
        message += '|';
    }

    ProjectResponse response_to_send("got_tasks_to_update");

    response_to_send.set_status("success");
    response_to_send.set_message(QString::fromStdString(message));
    response_to_send.set_project_name(QString::fromStdString(project_name));
    response_to_send.set_recipient("to sender");
    response_to_send.set_project_id(project_id);

    qDebug() << "----------------------------";
    return response_to_send.to_qjson_document();
}

QJsonDocument RequestHandler::change_task_condition(const QJsonObject &request
) const {
    // TODO
}

QJsonDocument RequestHandler::add_user_to_task(const QJsonObject &request
) const {
    // TODO
}

QJsonDocument RequestHandler::delete_user_from_task(const QJsonObject &request
) const {
    // TODO
}

QJsonDocument RequestHandler::delete_task(const QJsonObject &request) const {
    //TODO
}
