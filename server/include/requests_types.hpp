#ifndef REQUESTS_TYPES_H
#define REQUESTS_TYPES_H

#include <QString>
#include <map>
#include "request_handler.hpp"

enum REQUEST_TYPE {
    VALIDATE_USER,
    REGISTER_COMPANY_WITH_ADMIN,

    GET_PROJECTS_OF_COMPANY,
    GET_TASKS_OF_PROJECT,
    GET_COMPANY_CHAT,
    GET_PROJECT_CHAT,

    SEND_MESSAGE_TO_COMPANY_CHAT,
    SEND_MESSAGE_TO_PROJECT_CHAT,

    CREATE_PROJECT,
    ADD_USER_TO_PROJECT,
    DELETE_USER_FROM_PROJECT,
    DELETE_PROJECT,

    CREATE_TASK,
    ADD_USER_TO_TASK,
    CHANGE_TASK_CONDITION,
    DELETE_USER_FROM_TASK,
    DELETE_TASK
};

std::map<QString, REQUEST_TYPE> request_types = {
    {"authorization", VALIDATE_USER},
    {"registration", REGISTER_COMPANY_WITH_ADMIN},

    {"get_projects", GET_PROJECTS_OF_COMPANY},
    {"get_tasks", GET_TASKS_OF_PROJECT},
    {"get_company_chat", GET_COMPANY_CHAT},
    {"get_project_chat", GET_PROJECT_CHAT},

    {"send_message_to_company", SEND_MESSAGE_TO_COMPANY_CHAT},
    {"send_message_to_project", SEND_MESSAGE_TO_PROJECT_CHAT},

    {"add_project", CREATE_PROJECT},
    {"add_user_to_project", ADD_USER_TO_PROJECT},
    {"delete_user_from_project", DELETE_USER_FROM_PROJECT},
    {"delete_project", DELETE_PROJECT},

    {"create_task", CREATE_TASK},
    {"add_user_to_task", ADD_USER_TO_TASK},
    {"change_task_condition", CHANGE_TASK_CONDITION},
    {"delete_user_from_task", DELETE_USER_FROM_TASK},
    {"delete_task", DELETE_TASK}};

std::map<
    REQUEST_TYPE,
    QJsonDocument (RequestHandler::*)(const QJsonObject &) const>
    requests_handlers = {
        {VALIDATE_USER, &RequestHandler::send_message_to_project},
        {REGISTER_COMPANY_WITH_ADMIN,
         &RequestHandler::register_company_with_admin},

        {GET_PROJECTS_OF_COMPANY, &RequestHandler::get_projects},
        {GET_TASKS_OF_PROJECT, &RequestHandler::get_tasks},
        {GET_COMPANY_CHAT, &RequestHandler::get_company_chat},
        {GET_PROJECT_CHAT, &RequestHandler::get_project_chat},

        {SEND_MESSAGE_TO_COMPANY_CHAT,
         &RequestHandler::send_message_to_company},
        {SEND_MESSAGE_TO_PROJECT_CHAT,
         &RequestHandler::send_message_to_project},

        {CREATE_PROJECT, &RequestHandler::create_project},
        {ADD_USER_TO_TASK, &RequestHandler::add_user_to_task},
        {CHANGE_TASK_CONDITION, &RequestHandler::change_task_condition},
        {DELETE_USER_FROM_TASK, &RequestHandler::delete_user_from_task},
        {DELETE_TASK, &RequestHandler::delete_task}};

#endif  // REQUESTS_TYPES_H
