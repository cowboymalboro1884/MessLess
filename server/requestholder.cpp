#include "requestholder.h"

RequestHolder::RequestHolder(messless::Database *database_)
    : database(database_) {}

QJsonDocument RequestHolder::validateUser(const QJsonObject &request) {
  qDebug() << "got for authorization" << request;
  QString entered_email = request.value("email").toString();
  QString entered_password = request.value("password").toString();
  qDebug() << "email: " << entered_email;
  qDebug() << "password: " << entered_password;
  messless::PrivateUserInfo is_check_success =
      messless::DatabaseUser::login_user(*database, entered_email.toStdString(),
                                         entered_password.toStdString());
  QJsonObject jsonResponse;
  jsonResponse["email"] = QString::fromStdString(is_check_success.email);
  jsonResponse["password"] = QString::fromStdString(is_check_success.password);
  jsonResponse["user_role"] =
      QString::fromStdString(is_check_success.user_role);
  QJsonDocument response(jsonResponse);

  //// Return {"", "", ""} if authorization is failed, {email, password,
  ///user_role} else
  return response;
}

QJsonDocument
RequestHolder::registerCompanyWithAdmin(const QJsonObject &request) {
  qDebug() << "got for registration" << request;

  QString entered_email = request.value("email").toString();
  QString entered_password = request.value("password").toString();
  QString entered_name = request.value("name").toString();
  QString entered_surname = request.value("surname").toString();
  QString entered_company_bio = request.value("company_bio").toString();
  QString entered_company_name = request.value("company_name").toString();

  unsigned int company_id = messless::DatabaseCompany::create_company(
      *database, entered_company_name.toStdString(),
      entered_company_bio.toStdString());

  messless::PrivateUserInfo is_registration_success =
      messless::DatabaseCompany::create_user(
          *database, entered_email.toStdString(),
          entered_password.toStdString(), entered_name.toStdString(),
          entered_surname.toStdString(), company_id, "admin");

  QJsonObject jsonResponse;
  jsonResponse["email"] = QString::fromStdString(is_registration_success.email);
  jsonResponse["password"] =
      QString::fromStdString(is_registration_success.password);
  jsonResponse["user_role"] =
      QString::fromStdString(is_registration_success.user_role);
  QJsonDocument response(jsonResponse);

  //// Return {"", "", ""} if authorization is failed, {email, password,
  ///user_role} else
  return response;
}

QJsonDocument RequestHolder::proccessData(const QByteArray &incoming_data) {
  QJsonParseError json_data_error;
  QJsonDocument json_data =
      QJsonDocument::fromJson(incoming_data, &json_data_error);

  if (json_data_error.errorString().toInt() == QJsonParseError::NoError) {
    QString event_type = json_data.object().value("type").toString();

    if (!event_type.size()) {
      QJsonObject jsonResponse;
      jsonResponse["type"] = "error";
      jsonResponse["text"] = "missing request type";
      QJsonDocument response(jsonResponse);
      return response;
    }

    if (event_type == "authorization") {

      return validateUser(json_data.object());

    } else if (event_type == "registration") {

      return registerCompanyWithAdmin(json_data.object());

    } else {
      qDebug() << "Got wrong request";
      QJsonObject jsonResponse;
      jsonResponse["type"] = "error";
      jsonResponse["text"] = "Invalid JSON";
      QJsonDocument response(jsonResponse);
      return response;
    }
  }
  return json_data;
}
