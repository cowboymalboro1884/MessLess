#ifndef RESPONSETEMPLATE_H
#define RESPONSETEMPLATE_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <string>
#include <vector>
#include "responses_types.hpp"

namespace templates::ResponseTemplate {

struct UserInfo {
    QString email;
    QString password;
    QString user_role;
};

struct Message {
    QString name_of_sender;
    QString surname_of_sender;
    QString user_role_of_sender;

    QString message_text;
    QString file_link;
};

struct AbstractJSONResponse {
    QString status;
    QString event_type;
    RecipientType recipient;
    QJsonObject main_data;

    AbstractJSONResponse(const QString &event_type_)
        : event_type(event_type_){};

    AbstractJSONResponse(
        const QString &event_type_,
        const QString &status_,
        RecipientType recipient_
    )
        : status(status_), event_type(event_type_), recipient(recipient_){};

    void set_recipient(RecipientType new_recipient_) {
        recipient = new_recipient_;
    }

    virtual ~AbstractJSONResponse() = default;

    virtual QJsonDocument to_qjson_document() {
        main_data["status"] = status;
        main_data["type"] = event_type;
        main_data["recipient"] = recipient;

        return QJsonDocument(main_data);
    }
};

struct SendActualGlobalConditionResponse : AbstractJSONResponse {
    QJsonArray projects_with_tasks;
    QJsonArray company_chat;
    QJsonArray projects_chats;
    UserInfo user_info;
    int company_id;

    SendActualGlobalConditionResponse(const QString &event_type_)
        : AbstractJSONResponse(event_type_, "success", TO_SENDER){};

    virtual ~SendActualGlobalConditionResponse() = default;

    void set_projects_with_tasks(const QJsonArray &projects_with_tasks_) {
        projects_with_tasks = std::move(projects_with_tasks_);
    }

    void set_company_chat(const QJsonArray &company_chat_) {
        company_chat = std::move(company_chat_);
    }

    void set_projects_chats(const QJsonArray &projects_chats_) {
        projects_chats = std::move(projects_chats_);
    }

    void set_company_id(int company_id_) {
        company_id = company_id_;
    }

    void set_user_info(
        const std::string &email,
        const std::string &password,
        const std::string &user_role
    ) {
        user_info = UserInfo{
            QString::fromStdString(email), QString::fromStdString(password),
            QString::fromStdString(user_role)};
    }

    QJsonDocument to_qjson_document() override {
        main_data["status"] = status;
        main_data["type"] = event_type;
        main_data["recipient"] = recipient;

        main_data["email"] = user_info.email;
        main_data["password"] = user_info.password;
        main_data["user_role"] = user_info.user_role;
        main_data["company_id"] = company_id;
        
        main_data["projects_with_tasks"] = projects_with_tasks;
        main_data["company_chat"] = company_chat;
        main_data["projects_chats"] = projects_chats;

        return QJsonDocument(main_data);
    }
};

struct GetTasksOfProjectResponse : AbstractJSONResponse {
    QJsonArray tasks_of_project;
    QString project_name;

    GetTasksOfProjectResponse(const std::string &project_name_)
        : AbstractJSONResponse(
              response_types[GOT_TASKS_TO_UPDATE],
              "success",
              TO_SENDER
          ),
          project_name(QString::fromStdString(project_name_)){};

    void set_tasks_of_project(const QJsonArray &tasks) {
        tasks_of_project = std::move(tasks);
    }

    QJsonDocument to_qjson_document() override {
        main_data["status"] = status;
        main_data["type"] = event_type;
        main_data["recipient"] = recipient;

        main_data["project_name"] = project_name;
        main_data["tasks_of_project"] = tasks_of_project;
        return QJsonDocument(main_data);
    }
};

struct GetProjectsWithUserResponse : AbstractJSONResponse {
    QJsonArray projects_of_company;

    GetProjectsWithUserResponse()
        : AbstractJSONResponse(
              response_types[GOT_PROJECTS_TO_UPDATE],
              "success",
              TO_SENDER
          ){};

    void set_projects_of_company(const QJsonArray &projects) {
        projects_of_company = std::move(projects);
    }

    QJsonDocument to_qjson_document() override {
        main_data["status"] = status;
        main_data["type"] = event_type;
        main_data["recipient"] = recipient;

        main_data["projects_with_tasks"] = projects_of_company;
        return QJsonDocument(main_data);
    }
};

struct RecievedMessageResponse : AbstractJSONResponse {
    Message message_to_send;
    QJsonArray recipients;
    QString project_name;
    int company_id;

    RecievedMessageResponse(
        const std::string &name_of_sender_,
        const std::string &surname_of_sender_,
        const std::string &user_role_of_sender_,
        const std::string &message_text_,
        const std::string &file_link_,
        int company_id_
    )
        : AbstractJSONResponse(
              response_types[GOT_MESSAGE_TO_COMPANY_CHAT],
              "success",
              TO_COMPANY
          ),
          company_id(company_id_) {
        message_to_send = {
            QString::fromStdString(name_of_sender_),
            QString::fromStdString(surname_of_sender_),
            QString::fromStdString(user_role_of_sender_),
            QString::fromStdString(message_text_),
            QString::fromStdString(file_link_)};
    }

    void change_to_project_chat(
        const QJsonArray &recipients_,
        const QString &project_name_
    ) {
        response_types[GOT_MESSAGE_TO_PROJECT_CHAT],
            recipient = TO_PROJECT_USER_LIST;
        recipients = std::move(recipients_);
        project_name = project_name_;
    }

    QJsonDocument to_qjson_document() override {
        main_data["status"] = status;
        main_data["type"] = event_type;
        main_data["recipient"] = recipient;

        main_data["name_of_sender"] = message_to_send.name_of_sender;
        main_data["surname_of_sender"] = message_to_send.surname_of_sender;
        main_data["user_role_of_sender"] = message_to_send.user_role_of_sender;
        main_data["message_text"] = message_to_send.message_text;
        main_data["file_link"] = message_to_send.file_link;

        main_data["company_id"] = company_id;
        main_data["emails_of_recipients"] = recipients;
        main_data["project_name"] = project_name;
        return QJsonDocument(main_data);
    }
};

struct ProjectUserDeletedOrAdded final : AbstractJSONResponse {
    QString recipient_email;
    QString project_name;
    QString project_bio;
    int project_id;

    ProjectUserDeletedOrAdded(
        const std::string &project_name_,
        const std::string &project_bio_,
        int project_id_
    )
        : AbstractJSONResponse(
              response_types[NEW_CONDITION_OF_PROJECTS],
              "success",
              TO_CONCRETE_USER
          ),
          project_name(QString::fromStdString(project_name_)),
          project_bio(QString::fromStdString(project_bio_)),
          project_id(project_id_){};

    ProjectUserDeletedOrAdded(const std::string &project_name_)
        : AbstractJSONResponse(
              response_types[NEW_CONDITION_OF_PROJECTS],
              "success",
              TO_CONCRETE_USER
          ),
          project_name(QString::fromStdString(project_name_)){};

    void set_recipient(const QString &recipient_email_) {
        recipient_email = std::move(recipient_email_);
    }

    QJsonDocument to_qjson_document() override {
        main_data["status"] = status;
        main_data["type"] = event_type;
        main_data["recipient"] = recipient;

        main_data["reciever_email"] = recipient_email;
        main_data["project_name"] = project_name;
        main_data["project_bio"] = project_bio;
        main_data["project_id"] = project_id;
        return QJsonDocument(main_data);
    }
};

struct TaskConditionUpdatedSignal : AbstractJSONResponse {
    QJsonArray recipients;
    QString project_name;
    TaskConditionUpdatedSignal(const std::string &project_name_)
        : AbstractJSONResponse(
              response_types[NEW_CONDITION_OF_TASKS],
              "success",
              TO_PROJECT_USER_LIST
          ),
          project_name(QString::fromStdString(project_name_)){};

    void set_recipients(const QJsonArray &recipients_) {
        recipients = std::move(recipients_);
    }

    QJsonDocument to_qjson_document() override {
        main_data["status"] = status;
        main_data["type"] = event_type;
        main_data["recipient"] = recipient;

        main_data["emails_of_recipients"] = recipients;
        main_data["project_name"] = project_name;
        return QJsonDocument(main_data);
    }
};

struct ProjectIsDeleted final : AbstractJSONResponse {
    QString project_name;
    QJsonArray recipients;

    ProjectIsDeleted(const std::string &project_name_)
        : AbstractJSONResponse(
              response_types[NEW_CONDITION_OF_PROJECTS],
              "success",
              TO_PROJECT_USER_LIST
          ),
          project_name(QString::fromStdString(project_name_)){};

    void set_recipients(const QJsonArray &recipients_) {
        recipients = std::move(recipients_);
    }

    QJsonDocument to_qjson_document() override {
        main_data["status"] = status;
        main_data["type"] = event_type;
        main_data["recipient"] = recipient;

        main_data["emails_of_recipients"] = recipients;
        main_data["project_name"] = project_name;
        return QJsonDocument(main_data);
    }
};

struct ProjectCreationIsSuccess final : AbstractJSONResponse {
    ProjectCreationIsSuccess(const std::string &project_name)
        : AbstractJSONResponse(
              response_types[NEW_CONDITION_OF_PROJECTS],
              "success",
              TO_SENDER
          ){};
};

struct AuthorizationIsSuccess final : SendActualGlobalConditionResponse {
    AuthorizationIsSuccess()
        : SendActualGlobalConditionResponse(
              response_types[GOT_STATUS_OF_AUTHORIZATION]
          ){};
};

struct RegistrationCompanyIsSuccess final : SendActualGlobalConditionResponse {
    RegistrationCompanyIsSuccess()
        : SendActualGlobalConditionResponse(
              response_types[GOT_STATUS_OF_REGISTRATION]
          ){};
};

struct RegistrationUserIsSuccess final : AbstractJSONResponse {
    RegistrationUserIsSuccess()
        : AbstractJSONResponse(
              response_types[REGISTRATION_IS_SUCCESS],
              "success",
              TO_SENDER
          ){};
};

}  // namespace templates::ResponseTemplate

#endif  // RESPONSETEMPLATE_H
