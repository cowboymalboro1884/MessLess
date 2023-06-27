#include "include/query_handler.h"

void QuerySender::check_credentials(
    const QString &email,
    const QString &password
) {
    QJsonObject json_query;
    json_query["type"] = "authorization";
    json_query["email"] = email;
    json_query["password"] = password;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::register_company_and_user(
    const QString &email,
    const QString &password,

    const QString &name,
    const QString &surname,

    const QString &company_name,
    const QString &company_bio
) {
    QJsonObject json_query;

    json_query["type"] = "registration";
    json_query["entered_email"] = email;
    json_query["entered_password"] = password;

    json_query["name"] = name;
    json_query["surname"] = surname;

    json_query["company_name"] = company_name;
    json_query["company_bio"] = company_bio;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::add_user_to_company(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role,

    const QString &email_to_add,
    const QString &password_to_add,
    const QString &user_role_to_add,

    const QString &name_to_add,
    const QString &surname_to_add
) {
    QJsonObject json_query;
    json_query["type"] = "add user to company";

    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    json_query["email_to_add"] = email_to_add;
    json_query["password_to_add"] = password_to_add;
    json_query["user_role_to_add"] = user_role_to_add;

    json_query["name"] = name_to_add;
    json_query["surname"] = surname_to_add;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::get_tasks_of_projects(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role,

    const QString &project_name
) {
    QJsonObject json_query;
    json_query["type"] = "get tasks";
    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    json_query["project_name"] = project_name;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::get_projects_of_company(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role
) {
    QJsonObject json_query;
    json_query["type"] = "get projects";
    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::create_project(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role,

    const QString &project_name,
    const QString &project_bio
) {
    QJsonObject json_query;
    json_query["type"] = "create project";
    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    json_query["project_name"] = project_name;
    json_query["project_bio"] = project_bio;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::add_user_to_project(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role,

    const QString &email_added,
    const QString &user_role_added,
    const QString &project_name
) {
    QJsonObject json_query;
    json_query["type"] = "add user to project";
    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    json_query["project_name"] = project_name;
    json_query["user_role_changed"] = user_role_added;
    json_query["user_email_changed"] = email_added;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::delete_user_to_project(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role,

    const QString &email_deleted,
    const QString &project_name
) {
    QJsonObject json_query;
    json_query["type"] = "delete user from project";
    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    json_query["project_name"] = project_name;
    json_query["user_email_changed"] = email_deleted;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::delete_project(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role,

    const QString &project_name
) {
    QJsonObject json_query;
    json_query["type"] = "delete project";
    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    json_query["project_name"] = project_name;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::create_task(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role,

    const QString &task_name,
    const QString &description,
    const QString &deadline,
    const QString &project_name
) {
    QJsonObject json_query;
    json_query["type"] = "create task";
    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    json_query["task_name"] = task_name;
    json_query["description"] = description;
    json_query["deadline"] = deadline;
    json_query["project_name"] = project_name;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::delete_task(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role,

    const QString &task_name,
    const QString &project_name
) {
    QJsonObject json_query;
    json_query["type"] = "delete task";
    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    json_query["task_name"] = task_name;
    json_query["project_name"] = project_name;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::change_task_condition(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role,

    const QString &task_name,
    const QString &project_name,
    const QString &new_condition
) {
    QJsonObject json_query;
    json_query["type"] = "change task condition";

    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    json_query["task_name"] = task_name;
    json_query["project_name"] = project_name;
    json_query["new_condition"] = new_condition;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::send_message_to_company(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role,

    const QString &message
) {
    QJsonObject json_query;
    json_query["type"] = "send message to company";
    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    json_query["message"] = message;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}

void QuerySender::send_message_to_project(
    const QString &sender_email,
    const QString &sender_password,
    const QString &sender_user_role,

    const QString &message,
    const QString &project_name
) {
    QJsonObject json_query;
    json_query["type"] = "send message to project";
    json_query["sender_email"] = sender_email;
    json_query["sender_password"] = sender_password;
    json_query["sender_user_role"] = sender_user_role;

    json_query["message"] = message;
    json_query["project_name"] = project_name;

    QJsonDocument doc_to_send(json_query);
    emit ready_to_write_data_to_socket(doc_to_send.toJson());
}
