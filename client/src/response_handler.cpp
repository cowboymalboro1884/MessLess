#include "include/response_types.h"

std::unordered_map<std::string, std::vector<Task>>
extract_projects_with_tasks_from_json(const QJsonObject &request) {
    QJsonArray raw_projects_with_tasks =
        request["projects_with_tasks"].toArray();
    qDebug() << raw_projects_with_tasks;
    std::unordered_map<std::string, std::vector<Task>> projects_with_tasks;
    for (const auto &project : raw_projects_with_tasks) {
        QJsonObject project_obj = project.toObject();
        std::string project_name =
            project_obj["project_name"].toString().toStdString();

        QJsonArray tasks = project_obj["tasks_array"].toArray();
        projects_with_tasks[project_name] = {};
        for (const auto &task : tasks) {
            QJsonObject task_obj = task.toObject();
            projects_with_tasks[project_name].push_back(Task{
                task_obj["task_name"].toString(),
                task_obj["task_deadline"].toString(),
                task_obj["task_condition"].toString()});
        }
    }
    return projects_with_tasks;
}

std::vector<Message> extract_chat_from_json_array(
    const QJsonArray &message_array
) {
    std::vector<Message> chat;

    for (const auto &raw_message : message_array) {
        QJsonObject message_object = raw_message.toObject();
        Message message{
            message_object["name_of_sender"].toString(),
            message_object["surname_of_sender"].toString(),
            message_object["user_role_of_sender"].toString(),
            message_object["message_text"].toString(),
            message_object["file_link"].toString()};

        chat.push_back(std::move(message));
    }

    return chat;
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

    PrivateUserInfo sender{email, password, user_role};  // sender

    std::unordered_map<std::string, std::vector<Task>> projects_with_tasks =
        extract_projects_with_tasks_from_json(request);  // projects
    QJsonArray raw_company_chat = request["company_chat"].toArray();
    std::vector<Message> company_chat =
        extract_chat_from_json_array(raw_company_chat);  // company chat

    QJsonArray raw_project_chat = request["projects_chats"].toArray();

    std::unordered_map<std::string, std::vector<Message>>
        project_chats;  // projects chats

    for (const auto &raw_project_chat : raw_project_chat) {
        QJsonObject project_chat_object = raw_project_chat.toObject();
        QString project_name = project_chat_object["project_name"].toString();
        QJsonArray raw_chat = project_chat_object["raw_chat"].toArray();

        project_chats[project_name.toStdString()] =
            extract_chat_from_json_array(raw_chat);
    }
    QString name = request["name"].toString();
    QString surname = request["surname"].toString();
    QString company_name = request["company_name"].toString();

    emit got_status_of_authorization(sender);
    emit got_user_info(email, name, surname, company_name, user_role);
    emit got_projects_with_tasks(projects_with_tasks);
    emit got_company_messages(std::move(company_chat));
    emit got_project_chats(project_chats);
}

void ResponseHandler::got_status_of_user_and_company_registration(
    const QJsonObject &request
) const {
    QString email = request["email"].toString();
    QString password = request["password"].toString();
    QString user_role = request["user_role"].toString();

    PrivateUserInfo sender{email, password, user_role};  // sender

    std::unordered_map<std::string, std::vector<Task>> projects_with_tasks =
        extract_projects_with_tasks_from_json(request);  // projects

    QJsonArray raw_company_chat = request["company_chat"].toArray();
    std::vector<Message> company_chat =
        extract_chat_from_json_array(raw_company_chat);  // company chat

    QJsonArray raw_project_chat = request["projects_chats"].toArray();

    std::unordered_map<std::string, std::vector<Message>>
        project_chats;  // projects chats

    for (const auto &raw_project_chat : raw_project_chat) {
        QJsonObject project_chat_object = raw_project_chat.toObject();
        std::string project_name =
            project_chat_object["project_name"].toString().toStdString();
        QJsonArray raw_chat = project_chat_object["raw_chat"].toArray();

        project_chats[project_name] = extract_chat_from_json_array(raw_chat);
    }

    QString name = request["name"].toString();
    QString surname = request["surname"].toString();
    QString company_name = request["company_name"].toString();

    emit got_status_of_registration(sender);
    emit got_user_info(email, name, surname, company_name, user_role);
    emit got_projects_with_tasks(projects_with_tasks);
    emit got_company_messages(std::move(company_chat));
    emit got_project_chats(project_chats);
}

void ResponseHandler::got_status_of_user_registration(const QJsonObject &request
) const {
    qDebug() << "all okey =)";
}

void ResponseHandler::new_condition_of_projects(const QJsonObject &request
) const {
    emit get_new_condition_of_projects();
}

void ResponseHandler::new_condition_of_tasks(const QJsonObject &request) const {
    QString project_name = request["project_name"].toString();

    get_new_task_of_project(std::move(project_name));
}

void ResponseHandler::update_projects(const QJsonObject &request) const {
    QJsonArray raw_projects_with_tasks =
        request["projects_of_company"].toArray();

    std::unordered_map<std::string, std::vector<Task>> projects_with_tasks =
        extract_projects_with_tasks_from_json(request);

    for (auto i : projects_with_tasks)
        qDebug() << QString::fromStdString(i.first);

    emit got_projects_with_tasks(projects_with_tasks);
}

void ResponseHandler::update_tasks(const QJsonObject &request) const {
    QString project_name = request["project_name"].toString();
    QJsonArray tasks = request["tasks_of_project"].toArray();
    qDebug() << project_name;

    std::vector<Task> tasks_array;  // tasks we got

    for (const auto &raw_task : tasks) {
        QJsonObject task_obj = raw_task.toObject();
        qDebug() << task_obj["task_name"].toString();
        Task task{
            task_obj["task_name"].toString(),
            task_obj["task_deadline"].toString(),
            task_obj["task_condition"].toString()};
        tasks_array.push_back(std::move(task));
    }

    emit got_new_tasks_of_project(std::move(project_name), tasks_array);
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
    qDebug() << message.message_as_it_is;
    emit got_company_message(message);
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
        sender_name, sender_surname, sender_user_role, message_text,
        file_link};  // message we got

    emit got_project_message(project_name, message);
}

void ResponseHandler::error(const QJsonObject &request) const {
    // process error
    qDebug() << "error:";
    qDebug() << request["type"].toString();
    QString error = request["error_text"].toString();
    emit got_error(error);
}
