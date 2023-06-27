#include "request_handler.hpp"

QJsonDocument RequestHandler::create_task(const QJsonObject &request
) const {  // DONE
    qDebug() << "----------------------------\ngot for create_task\n";

    std::string task_name = request.value("task_name").toString().toStdString();
    std::string description =
        request.value("description").toString().toStdString();
    std::string deadline = request.value("deadline").toString().toStdString();

    std::string project_name =
        request.value("project_name").toString().toStdString();

    PrivateUserInfo sender = extract_user_info_from_qjson(request);

    int project_id =
        DatabaseProject::get_project_id(*database, sender, project_name);

    std::vector<User> user_list =
        DatabaseProject::get_project_user_list(*database, project_id);

    int status = DatabaseProject::create_new_task(
        *database, project_id, task_name, description, deadline, user_list
    );

    if (status != 0) {
        TaskConditionUpdatedSignal response_to_send(project_name);
        QJsonArray recipients;
        for (auto user : user_list) {
            QJsonObject email;
            email["email"] = QString::fromStdString(user.email);
            recipients.append(email);
        }

        response_to_send.set_recipients(recipients);
        return response_to_send.to_qjson_document();
    } else {
        return UnableToCreateTask::get_instance().to_qjson_document();
    }
}

QJsonDocument RequestHandler::get_tasks(const QJsonObject &request
) const {  // DONE
    qDebug() << "get tasks list";

    PrivateUserInfo sender = extract_user_info_from_qjson(request);

    std::string project_name =
        request.value("project_name").toString().toStdString();

    int project_id =
        DatabaseProject::get_project_id(*database, sender, project_name);

    std::vector<Task> tasks_to_update =
        DatabaseProject::get_tasks(*database, project_id);

    GetTasksOfProjectResponse response(project_name);

    QJsonArray tasks_of_project;

    std::string message;
    for (const Task &task : tasks_to_update) {
        QJsonObject task_object;
        task_object["task_name"] = QString::fromStdString(task.task_name);
        task_object["task_condition"] = QString::fromStdString(task.condition);
        task_object["task_deadline"] = QString::fromStdString(task.deadline);
        tasks_of_project.append(task_object);
    }
    response.set_tasks_of_project(tasks_of_project);

    return response.to_qjson_document();
}

QJsonDocument RequestHandler::change_task_condition(const QJsonObject &request
) const {  // DONE
    PrivateUserInfo sender = extract_user_info_from_qjson(request);
    std::string task_name = request.value("task_name").toString().toStdString();

    std::string project_name =
        request.value("project_name").toString().toStdString();

    std::string new_condition =
        request.value("new_condition").toString().toStdString();

    int project_id =
        DatabaseProject::get_project_id(*database, sender, project_name);
    int task_id =
        DatabaseProject::get_task_id(*database, project_id, task_name);
    std::vector<User> user_list =
        DatabaseProject::get_project_user_list(*database, project_id);

    DatabaseProject::change_task_condition(*database, task_id, new_condition);

    int status = 1;
    if (status != 0) {
        TaskConditionUpdatedSignal response(project_name);
        QJsonArray recipients;

        for (auto user : user_list) {
            QJsonObject email;
            email["email"] = QString::fromStdString(user.email);
            recipients.append(email);
        }
        response.set_recipients(recipients);
        return response.to_qjson_document();
    } else {
        return UnableToChangTaskCondition::get_instance().to_qjson_document();
    }
}

QJsonDocument RequestHandler::delete_task(const QJsonObject &request) const {
    qDebug() << "create_task\n";

    std::string task_name = request.value("task_name").toString().toStdString();

    std::string project_name =
        request.value("project_name").toString().toStdString();

    PrivateUserInfo sender = extract_user_info_from_qjson(request);

    int project_id =
        DatabaseProject::get_project_id(*database, sender, project_name);

    std::vector<User> user_list =
        DatabaseProject::get_project_user_list(*database, project_id);

    int task_id =
        DatabaseProject::get_task_id(*database, project_id, task_name);

    DatabaseProject::delete_task(*database, task_id);

    int status = 1;
    if (status != 0) {
        TaskConditionUpdatedSignal response_to_send(project_name);
        QJsonArray recipients;
        for (auto user : user_list) {
            QJsonObject email;
            email["email"] = QString::fromStdString(user.email);
        }

        response_to_send.set_recipients(recipients);

    } else {
        return UnableToCreateTask::get_instance().to_qjson_document();
    }
}
