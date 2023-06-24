#ifndef RESPONSE_TYPES_H
#define RESPONSE_TYPES_H
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <unordered_map>

#include "response_handler.h"

class Project {
public:
  QString project_name;
  QString project_bio;
  QString project_id;
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
    {"got status of registration user and company",
     GOT_STATUS_OF_REGISTRATION_USER_AND_COMPANY},
    {"registration new user is success", REGISTRATION_NEW_USER_IS_SUCCESS},

    {"got projects to update", GOT_PROJECTS_TO_UPDATE},
    {"new condition of projects", NEW_CONDITION_OF_PROJECTS},

    {"got tasks to update", GOT_TASKS_TO_UPDATE},
    {"new condition of tasks", NEW_CONDITION_OF_TASKS},

    {"got message to company chat", GOT_MESSAGE_TO_COMPANY_CHAT},
    {"got message to project chat", GOT_MESSAGE_TO_PROJECT_CHAT}};

inline std::map<ResponseTypes,
                void (ResponseHandler::*)(const QJsonObject &) const>
    response_handlers = {
        {ERROR, &ResponseHandler::error},

        {GOT_STATUS_OF_AUTHORIZATION_USER,
         &ResponseHandler::got_status_of_user_authorization},
        {GOT_STATUS_OF_REGISTRATION_USER_AND_COMPANY,
         &ResponseHandler::got_status_of_user_and_company_registration},
        {REGISTRATION_NEW_USER_IS_SUCCESS,
         &ResponseHandler::got_status_of_user_registration},

        {GOT_PROJECTS_TO_UPDATE, &ResponseHandler::update_projects},
        {NEW_CONDITION_OF_PROJECTS,
         &ResponseHandler::new_condition_of_projects},

        {GOT_TASKS_TO_UPDATE, &ResponseHandler::update_tasks},
        {NEW_CONDITION_OF_TASKS, &ResponseHandler::new_condition_of_tasks},

        {GOT_MESSAGE_TO_COMPANY_CHAT,
         &ResponseHandler::recieved_message_to_company},
        {GOT_MESSAGE_TO_PROJECT_CHAT,
         &ResponseHandler::recieved_message_to_project},
};

#endif // RESPONSE_TYPES_H
