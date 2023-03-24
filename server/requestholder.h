#ifndef REQUESTHOLDER_H
#define REQUESTHOLDER_H

#include <QByteArray>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include "database.h"
#include <random>

class ClientSocket;

class RequestHolder {
messless::Database* database;
ClientSocket* owner;

public:
    RequestHolder(messless::Database* database_);

    void validateUser();
    QJsonDocument proccessData(QByteArray& incoming_data);
};

#endif // REQUESTHOLDER_H
