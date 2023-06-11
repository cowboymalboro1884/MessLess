#ifndef RESPONSE_TYPES_H
#define RESPONSE_TYPES_H
#include <unordered_map>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "response_handler.h"




class Project {
public:
    QString project_name;
    QString project_bio;
    QString project_id;
};


class Message {
public:
    QString name_of_sender;
    QString surname_of_sender;
    QString message_as_it_is;
    QString user_role;
    QString file_path;
};

enum ResponseTypes {
    ERROR,

    GOT_STATUS_OF_AUTHORIZATION_USER,
    GOT_STATUS_OF_REGISTRATION_USER_AND_COMPANY,
    REGISTRATION_NEW_USER_IS_SUCCESS,

    GOT_PROJECTS_TO_UPDATE,
    NEW_CONDITION_OF_PROJECTS,

    GOT_TASKS_TO_UPDATE,
    NEW_CONDITION_OF_TASKS,

    GOT_MESSAGE_TO_COMPANY_CHAT,
    GOT_MESSAGE_TO_PROJECT_CHAT,
};

inline std::map<QString, ResponseTypes> response_types = {
    {"error", ERROR},
    {"got status of authorization user", GOT_STATUS_OF_AUTHORIZATION_USER},
    {"got status of registration user and company", GOT_STATUS_OF_REGISTRATION_USER_AND_COMPANY},
    {"registration new user is success", REGISTRATION_NEW_USER_IS_SUCCESS},

    {"got projects to update", GOT_PROJECTS_TO_UPDATE},
    {"new_condition_of_projects", NEW_CONDITION_OF_PROJECTS},

    {"got_tasks_to_update", GOT_TASKS_TO_UPDATE},
    {"new_condition_of_tasks", NEW_CONDITION_OF_TASKS},

    {"got_message_to_company_chat", GOT_MESSAGE_TO_COMPANY_CHAT},
    {"got_message_to_project_chat", GOT_MESSAGE_TO_PROJECT_CHAT}};


inline std::map<ResponseTypes, void (ResponseHandler::*) (const QJsonObject&) const> response_handlers = {

            {GOT_STATUS_OF_AUTHORIZATION_USER, &ResponseHandler::got_status_of_user_authorization},
            {GOT_STATUS_OF_REGISTRATION_USER_AND_COMPANY, &ResponseHandler::got_status_of_user_and_company_registration},
            {REGISTRATION_NEW_USER_IS_SUCCESS, &ResponseHandler::got_status_of_user_registration},

            {GOT_PROJECTS_TO_UPDATE, &ResponseHandler::update_projects},
            {NEW_CONDITION_OF_PROJECTS, &ResponseHandler::new_condition_of_projects},

            {GOT_TASKS_TO_UPDATE, &ResponseHandler::update_tasks},
            {NEW_CONDITION_OF_TASKS, &ResponseHandler::new_condition_of_tasks},

            {GOT_MESSAGE_TO_COMPANY_CHAT, &ResponseHandler::recieved_message_to_company},
            {GOT_MESSAGE_TO_PROJECT_CHAT, &ResponseHandler::recieved_message_to_project},
        };


#endif // RESPONSE_TYPES_H
