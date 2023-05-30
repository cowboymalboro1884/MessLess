#include "include/response_types.h"

std::unordered_map<QString, std::vector<Task>>
extract_projects_with_tasks_from_json(const QJsonObject &request) {
    QJsonArray raw_projects_with_tasks =
        request["projects_with_tasks"].toArray();
    std::unordered_map<QString, std::vector<Task>> projects_with_tasks;
    for (const auto &project : raw_projects_with_tasks) {
        QJsonObject project_obj = project.toObject();
        QString project_name = project_obj["project_name"].toString();
        QJsonArray tasks = project_obj["tasks_array"].toArray();
        for (const auto &task : tasks) {
            QJsonObject task_obj = task.toObject();
            projects_with_tasks[project_name].push_back(Task{
                task_obj["task_name"].toString(),
                task_obj["task_condition"].toString(),
                task_obj["task_deadline"].toString()});
        }
    }
    return projects_with_tasks;
}

void ResponseHandler::proccess_data(const QByteArray &incoming_data) {
    QJsonParseError json_data_error;
    QJsonDocument json_data =
        QJsonDocument::fromJson(incoming_data, &json_data_error);

    if (json_data_error.errorString().toInt() == QJsonParseError::NoError) {
        QString event_type = json_data.object().value("type").toString();

        if (!event_type.size()) {
            qDebug() << "RH: Missing response type";
            return;
        }

        if (response_types.find(event_type) == response_types.end()) {
            qDebug() << "RH: Got wrong request";
            return;
        }

        ResponseTypes request_type = response_types[event_type];
        qDebug() << event_type;

        return (this->*response_handlers[request_type])(json_data.object());
    } else {
        qDebug() << "RH: Got invalid JSON";
        return;
    }
}

void ResponseHandler::got_status_of_user_authorization(
    const QJsonObject &request
) const {
    QString email = request["email"].toString();
    QString password = request["password"].toString();
    QString user_role = request["user_role"].toString();

    // get projects with tasks
    QJsonArray raw_projects_with_tasks =
        request["projects_with_tasks"].toArray();
    std::unordered_map<QString, std::vector<Task>> projects_with_tasks =
        extract_projects_with_tasks_from_json(request);
    // get projects with tasks

    QJsonArray raw_company_chat = request["company_chat"].toArray();
    // std::vector<Message> chat;
    for (const auto &raw_message : raw_company_chat) {
        QJsonObject message_object = raw_message.toObject();
        Message message{
            message_object["name_of_sender"].toString(),
            message_object["surname_of_sender"].toString(),
            message_object["user_role_of_sender"].toString(),
            message_object["message_text"].toString(),
            message_object["file_link"].toString()};

        // append ...
    }

    QJsonArray raw_project_chat = request["projects_chats"].toArray();
    // std::vector<Message> chat;
    for (const auto &raw_project_chat : raw_company_chat) {
        QJsonObject project_chat_object = raw_project_chat.toObject();
        QString project_name = project_chat_object["project_name"].toString();
        QJsonArray project_chat = project_chat_object["raw_chat"].toArray();
        for (const auto &raw_message : project_chat) {
            QJsonObject message_object = raw_message.toObject();
            Message message{
                message_object["name_of_sender"].toString(),
                message_object["surname_of_sender"].toString(),
                message_object["user_role_of_sender"].toString(),
                message_object["message_text"].toString(),
                message_object["file_link"].toString()};
            // append ...
        }
        // append ...
    }

    // emit smth
}

void ResponseHandler::got_status_of_user_and_company_registration(
    const QJsonObject &request
) const {
    // the same
}

void ResponseHandler::got_status_of_user_registration(const QJsonObject &request
) const {
    // success: emit good =)
    // else : emit bad =)
}

void ResponseHandler::new_condition_of_projects(const QJsonObject &request
) const {
    // just emit smth
}

void ResponseHandler::new_condition_of_tasks(const QJsonObject &request) const {
    // just emit smth
}

void ResponseHandler::update_projects(const QJsonObject &request) const {
    QJsonArray raw_projects_with_tasks =
        request["projects_of_company"].toArray();

    std::unordered_map<QString, std::vector<Task>> projects_with_tasks =
        extract_projects_with_tasks_from_json(request);

    // emit smth
}

void ResponseHandler::update_tasks(const QJsonObject &request) const {
    QString project_name = request["project_name"].toString();
    QJsonArray tasks = request["tasks_of_project"].toArray();

    for (const auto &raw_task : tasks) {
        QJsonObject task_obj = raw_task.toObject();
        Task task{
            task_obj["task_name"].toString(),
            task_obj["task_condition"].toString(),
            task_obj["task_deadline"].toString()};
        // append ...
    }
}

void ResponseHandler::recieved_message_to_company(const QJsonObject &request
) const {
    QString sender_name = request["name_of_sender"].toString();
    QString sender_surname = request["surname_of_sender"].toString();
    QString sender_user_role = request["user_role_of_sender"].toString();
    QString message_text = request["message_text"].toString();
    QString file_link = request["file_link"].toString();

    Message message{
        sender_name, sender_surname, sender_user_role, message_text, file_link};
    // emit smth
}

void ResponseHandler::recieved_message_to_project(const QJsonObject &request
) const {
    QString project_name = request["project_name"].toString();

    QString sender_name = request["name_of_sender"].toString();
    QString sender_surname = request["surname_of_sender"].toString();
    QString sender_user_role = request["user_role_of_sender"].toString();
    QString message_text = request["message_text"].toString();
    QString file_link = request["file_link"].toString();

    Message message{
        sender_name, sender_surname, sender_user_role, message_text, file_link};

    // emit smth
}
