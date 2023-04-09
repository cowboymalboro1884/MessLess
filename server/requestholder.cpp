#include "requestholder.h"

RequestHolder::RequestHolder(messless::Database *database_)
    : database(database_) {
  qDebug() << database->connection.is_open() << "RH\n";
}

QJsonDocument RequestHolder::validateUser(const QJsonObject &request) {
  qDebug() << "got for authorization" << request;
  QString entered_email = request.value("email").toString();
  QString entered_password = request.value("password").toString();
  qDebug() << "email: " << entered_email;
  qDebug() << "password: " << entered_password;
  messless::PrivateUserInfo is_login_success =
      messless::DatabaseUser::login_user(*database, entered_email.toStdString(),
                                         entered_password.toStdString());
  QJsonObject jsonResponse;
  jsonResponse["email"] = QString::fromStdString(is_login_success.email);
  jsonResponse["password"] = QString::fromStdString(is_login_success.password);
  jsonResponse["user_role"] =
      QString::fromStdString(is_login_success.user_role);

  if (is_login_success.email.empty() || is_login_success.password.empty() ||
      is_login_success.user_role.empty()) {
    jsonResponse["status"] = "success";
  } else {
    jsonResponse["status"] = "failed";
    jsonResponse["error_text"] = "couldn't authorize";
  }

  QJsonDocument response(jsonResponse);

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

  try {
    unsigned int company_id = messless::DatabaseCompany::create_company(
        *database, entered_company_name.toStdString(),
        entered_company_bio.toStdString());
    qDebug() << company_id;
    messless::PrivateUserInfo is_registration_success =
        messless::DatabaseCompany::create_user(
            *database, entered_email.toStdString(),
            entered_password.toStdString(), entered_name.toStdString(),
            entered_surname.toStdString(), company_id, "admin");
    qDebug() << "а мы сюда вообще зашли или зависли ты мне скажи";

    QJsonObject jsonResponse;
    jsonResponse["email"] =
        QString::fromStdString(is_registration_success.email);
    jsonResponse["password"] =
        QString::fromStdString(is_registration_success.password);
    jsonResponse["user_role"] =
        QString::fromStdString(is_registration_success.user_role);

    qDebug() << jsonResponse;

    if (is_registration_success.email.empty() ||
        is_registration_success.password.empty() ||
        is_registration_success.user_role.empty()) {
      jsonResponse["status"] = "failed";
      jsonResponse["error_text"] = "couldn't register";
    } else {
      jsonResponse["status"] = "success";
    }
    QJsonDocument response(jsonResponse);

    return response;

  } catch (...) {
    qDebug() << "failed(";
  }

  QJsonObject empty;
  empty["message"] = "ebanulsa?";
  QJsonDocument doc(empty);
  return doc;
}

QJsonDocument RequestHolder::createProject(const QJsonObject &request) {
  qDebug() << "got for create_project" << request;
  std::string email = request.value("email").toString().toStdString();
  std::string password = request.value("password").toString().toStdString();
  std::string user_role = request.value("user_role").toString().toStdString();
  messless::PrivateUserInfo sender{email, password, user_role};

  std::string project_name =
      request.value("project_name").toString().toStdString();
  std::string project_bio =
      request.value("project_bio").toString().toStdString();

  QJsonObject jsonResponse;
  if (!messless::DatabaseProject::is_project_exist(*database, sender,
                                                   project_name)) {
    unsigned int project_id = messless::DatabaseProject::create_project(
        *database, sender, project_name, project_bio);
    jsonResponse["status"] = "success";
    jsonResponse["project_id"] = QString::number(project_id);
    jsonResponse["project_name"] = QString::fromStdString(project_name);
    jsonResponse["project_bio"] = QString::fromStdString(project_bio);
  } else {
    jsonResponse["type"] = "failed";
    jsonResponse["error_text"] = "project with such name is already exist";
  }

  QJsonDocument response(jsonResponse);
  return response;
}

QJsonDocument RequestHolder::proccessData(const QByteArray &incoming_data) {
  QJsonParseError json_data_error;
  QJsonDocument json_data =
      QJsonDocument::fromJson(incoming_data, &json_data_error);

  if (json_data_error.errorString().toInt() == QJsonParseError::NoError) {
    QString event_type = json_data.object().value("type").toString();
    qDebug() << "RH: got data";
    qDebug() << json_data;
    if (!event_type.size()) {
      QJsonObject jsonResponse;
      jsonResponse["status"] = "error";
      jsonResponse["error_text"] = "missing request type";
      QJsonDocument response(jsonResponse);
      return response;
    }

    if (event_type == "authorization") {

      return validateUser(json_data.object());

    } else if (event_type == "registration") {
      qDebug() << "RH: registration";
      return registerCompanyWithAdmin(json_data.object());

    } else if (event_type == "add_project") {

      return createProject(json_data.object());

    } else {
      qDebug() << "Got wrong request";
      QJsonObject jsonResponse;
      jsonResponse["status"] = "failed";
      jsonResponse["error_text"] = "Invalid JSON";
      QJsonDocument response(jsonResponse);
      return response;
    }
  }
  return json_data;
}
