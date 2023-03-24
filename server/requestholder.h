#ifndef REQUESTHOLDER_H
#define REQUESTHOLDER_H

#include <QByteArray>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include "database.h"
#include "databaseproject.h"
#include <random>

class ClientSocket;

class RequestHolder {
messless::Database* database;
ClientSocket* owner;

public:
    RequestHolder(messless::Database* database_);
    QJsonDocument proccessData(const QByteArray& incoming_data);

    QJsonDocument validateUser(const QJsonObject& request);
    QJsonDocument registerCompanyWithAdmin(const QJsonObject& request);
    QJsonDocument createProject(const QJsonObject& request);
};

#endif // REQUESTHOLDER_H
