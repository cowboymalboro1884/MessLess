#ifndef REQUESTHOLDER_H
#define REQUESTHOLDER_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <random>
#include "database.h"
#include "databaseproject.h"

class ClientSocket;

class RequestHolder {
    messless::Database *database;
    ClientSocket *owner;
    mutable messless::PrivateUserInfo user;

public:
    RequestHolder(messless::Database *database_);
    QJsonDocument proccess_data(const QByteArray &incoming_data) const noexcept;

    QJsonDocument validate_user(const QJsonObject &request) const noexcept;
    QJsonDocument register_company_with_admin(const QJsonObject &request) const noexcept;
    QJsonDocument create_project(const QJsonObject &request) const noexcept;
    QJsonDocument create_task(const QJsonObject &request) const noexcept;
    QJsonDocument get_tasks(const QJsonObject &request) const noexcept;
    QJsonDocument get_projects(const QJsonObject &request) const noexcept;
    QJsonDocument send_message_to_company(const QJsonObject &request) const noexcept;
};

#endif  // REQUESTHOLDER_H
