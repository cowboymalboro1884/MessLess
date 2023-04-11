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
    messless::PrivateUserInfo user;

public:
    RequestHolder(messless::Database *database_);
    QJsonDocument proccessData(const QByteArray &incoming_data);

    QJsonDocument validateUser(const QJsonObject &request);
    QJsonDocument registerCompanyWithAdmin(const QJsonObject &request);
    QJsonDocument createProject(const QJsonObject &request);
    QJsonDocument createTask(const QJsonObject &request);
    QJsonDocument getTasks(const QJsonObject &request);
    QJsonDocument getProjects(const QJsonObject &request);
};

#endif  // REQUESTHOLDER_H
