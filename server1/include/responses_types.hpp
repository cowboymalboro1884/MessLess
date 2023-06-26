#ifndef RESPONSES_TYPES_H
#define RESPONSES_TYPES_H

#include <QString>
#include <map>

enum RecipientType {
    TO_SENDER,
    TO_PROJECT_USER_LIST,
    TO_COMPANY,
    TO_CONCRETE_USER
};

enum ResponseTypes {
    ERROR,

    GOT_STATUS_OF_AUTHORIZATION,
    GOT_STATUS_OF_REGISTRATION,
    REGISTRATION_IS_SUCCESS,

    GOT_PROJECTS_TO_UPDATE,
    NEW_CONDITION_OF_PROJECTS,

    GOT_TASKS_TO_UPDATE,
    NEW_CONDITION_OF_TASKS,

    GOT_MESSAGE_TO_COMPANY_CHAT,
    GOT_MESSAGE_TO_PROJECT_CHAT,
};

inline std::map<ResponseTypes, QString> response_types = {
    {ERROR, "error"},
    {GOT_STATUS_OF_AUTHORIZATION, "got status of authorization user"},
    {GOT_STATUS_OF_REGISTRATION, "got status of registration user and company"},
    {REGISTRATION_IS_SUCCESS, "registration new user is success"},

    {GOT_PROJECTS_TO_UPDATE, "got projects to update"},
    {NEW_CONDITION_OF_PROJECTS, "new condition of projects"},

    {GOT_TASKS_TO_UPDATE, "got tasks to update"},
    {NEW_CONDITION_OF_TASKS, "new condition of tasks"},

    {GOT_MESSAGE_TO_COMPANY_CHAT, "got message to company chat"},
    {GOT_MESSAGE_TO_PROJECT_CHAT, "got message to project chat"}};

#endif  // RESPONSES_TYPES_H
