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

std::map<ResponseTypes, QString> inline response_types = {
    {ERROR, "error"},
    {GOT_STATUS_OF_AUTHORIZATION, "got_status_of_authorization"},
    {GOT_STATUS_OF_REGISTRATION, "got_status_of_registration"},
    {REGISTRATION_IS_SUCCESS, "registration_is_success"},

    {GOT_PROJECTS_TO_UPDATE, "got_projects_to_update"},
    {NEW_CONDITION_OF_PROJECTS, "new_condition_of_projects"},

    {GOT_TASKS_TO_UPDATE, "got_tasks_to_update"},
    {NEW_CONDITION_OF_TASKS, "new_condition_of_tasks"},

    {GOT_MESSAGE_TO_COMPANY_CHAT, "got_message_to_company_chat"},
    {GOT_MESSAGE_TO_PROJECT_CHAT, "got_message_to_project_chat"}};

#endif  // RESPONSES_TYPES_H
