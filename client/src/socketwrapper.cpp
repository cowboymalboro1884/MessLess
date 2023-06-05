#include "include/socketwrapper.h"
#include <QDataStream>
#include <sstream>

namespace client::network {

SocketWrapper::SocketWrapper(QString ip_, qint16 port_) {
  m_socket_wrap = new QTcpSocket(this);
  ip = ip_;
  port = port_;
}

void SocketWrapper::connect_to_host() {
  m_socket_wrap->connectToHost(ip, port);
  if (m_socket_wrap->waitForConnected()) {
    qDebug() << "Connected, i think...";
    connect(m_socket_wrap, SIGNAL(readyRead()), this, SLOT(update()));
  }
}

void SocketWrapper::update() {
  qDebug() << "Got new data to update!";
  QDataStream in(&(*m_socket_wrap));
  quint16 block_size;
  in >> block_size;
  m_socket_wrap->read(sizeof(quint32));
  QByteArray response = m_socket_wrap->read(block_size);
  qDebug() << block_size;
  qDebug() << response;

  QJsonParseError json_data_error;
  QJsonDocument json_data = QJsonDocument::fromJson(response, &json_data_error);
  if (json_data_error.errorString().toInt() == QJsonParseError::NoError) {
    QString event_type = json_data.object().value("type").toString();
    qDebug() << json_data.object().value("status").toString();
    qDebug() << event_type;
    if (event_type == "got_status_of_authorization") { ////DONE

      QString status = json_data.object().value("status").toString();
      QString got_email = json_data.object().value("email").toString();
      QString got_password = json_data.object().value("password").toString();
      QString got_user_role = json_data.object().value("user_role").toString();
      user = PrivateUserInfo{status, got_email, got_password, got_user_role};

      std::unordered_map<std::string, std::vector<Task>> projects_w_tasks;

      std::string raw_data =
          json_data.object().value("message").toString().toStdString();
      std::stringstream ss1(raw_data);
      std::string project_with_task;
      while (std::getline(ss1, project_with_task, '|')) {
        std::string project_name;
        std::stringstream ss2(project_with_task);
        std::getline(ss2, project_name, ';');
        std::string task_string;
        while (std::getline(ss2, task_string, ':')) {
          std::string task_name;
          std::string task_condition;
          std::string task_deadline;
          std::getline(ss2, task_name, '\n');
          std::getline(ss2, task_condition, '\n');
          std::getline(ss2, task_deadline, '\n');

          projects_w_tasks[project_name].push_back(
              Task{task_name, task_condition, task_deadline});
        }
      }

      emit got_status_of_authorization(user, projects_w_tasks);

    } else if (event_type == "got_status_of_registration") { ////DONE

      QString got_email = json_data.object().value("email").toString();
      QString got_password = json_data.object().value("password").toString();
      QString got_user_role = json_data.object().value("user_role").toString();
      QString status = json_data.object().value("status").toString();
      user = PrivateUserInfo{status, got_email, got_password, got_user_role};

      std::unordered_map<std::string, std::vector<Task>> projects_w_tasks;

      std::string raw_data =
          json_data.object().value("message").toString().toStdString();
      std::stringstream ss1(raw_data);
      std::string project_with_task;
      while (std::getline(ss1, project_with_task, '|')) {
        std::string project_name;
        std::stringstream ss2(project_with_task);
        std::getline(ss2, project_name, ';');
        std::string task_string;
        while (std::getline(ss2, task_string, ':')) {
          std::string task_name;
          std::string task_condition;
          std::string task_deadline;
          std::getline(ss2, task_name, '\n');
          std::getline(ss2, task_condition, '\n');
          std::getline(ss2, task_deadline, '\n');

          projects_w_tasks[project_name].push_back(
              Task{task_name, task_condition, task_deadline});
        }
      }

      emit got_status_of_registration(user, projects_w_tasks);

    } else if (event_type == "got_projects_to_update") { ////DONE
      std::vector<std::string> projects_to_update;
      std::string projects =
          json_data.object().value("message").toString().toStdString();
      std::stringstream ss(projects);
      std::string proj;
      while (std::getline(ss, proj, '|')) {
        projects_to_update.push_back(proj);
      }

      emit got_projects_to_update(projects_to_update);

    } else if (event_type == "got_tasks_to_update") {
      std::string tasks =
          json_data.object().value("message").toString().toStdString();
      std::vector<Task> tasks_to_update;
      std::stringstream ss1(tasks);
      std::string task;
      QString project_name =
          json_data.object().value("project_name").toString();
      while (std::getline(ss1, task, '|')) {
        std::stringstream ss2(task);
        std::string condition;
        std::string deadline;
        std::string task_name;
        std::getline(ss2, task_name, '\n');
        std::getline(ss2, condition, '\n');
        std::getline(ss2, deadline, '\n');
        tasks_to_update.push_back(Task{task_name, deadline, condition});

        qDebug() << QString::fromStdString(task_name)
                 << QString::fromStdString(deadline)
                 << QString::fromStdString(condition);
      }

      emit got_tasks_to_update(tasks_to_update, project_name);

    } else if (event_type == "somebody_created_new_task") {
      QString project_name =
          json_data.object().value("project_name").toString();

      //             emit somebody_created_new_task(project_name);

    } else if (event_type == "got_new_message_to_company") {
      std::string message =
          json_data.object().value("message").toString().toStdString();

      std::string name_of_sender =
          json_data.object().value("name_of_sender").toString().toStdString();

      std::string surname_of_sender = json_data.object()
                                          .value("surname_of_sender")
                                          .toString()
                                          .toStdString();
      std::string user_role =
          json_data.object().value("user_role").toString().toStdString();

      std::string file_link =
          json_data.object().value("file_link").toString().toStdString();

      Message new_message{QString::fromStdString(name_of_sender),
                          QString::fromStdString(surname_of_sender),
                          QString::fromStdString(message),
                          QString::fromStdString(user_role),
                          QString::fromStdString(file_link)};

      // emit got_new_message_to_company(new_message);

    } else if (event_type == "somebody_created_new_project") { ////DONE
      emit somebody_updated_project();

    } else if (event_type == "got_messages_of_company") {
      std::string raw_messages =
          json_data.object().value("message").toString().toStdString();

      std::vector<Message> messages_to_update;
      std::stringstream ss1(raw_messages);
      std::string message;
      while (std::getline(ss1, message, '|')) {
        std::stringstream ss2(message);
        std::string text_of_message;
        std::string name_of_sender;
        std::string surname_of_sender;
        std::string user_role;
        std::string file_path;

        std::getline(ss2, text_of_message, '\n');
        std::getline(ss2, name_of_sender, '\n');
        std::getline(ss2, surname_of_sender, '\n');
        std::getline(ss2, user_role, '\n');
        std::getline(ss2, file_path, '\n');

        messages_to_update.push_back(Message{
            QString::fromStdString(name_of_sender),
            QString::fromStdString(surname_of_sender),
            QString::fromStdString(message), QString::fromStdString(user_role),
            QString::fromStdString(file_path)});
      }

      // emit got_all_message_of_company(messages_to_update);

    } else if (event_type == "got_all_messages_of_project") {
      std::string raw_messages =
          json_data.object().value("message").toString().toStdString();
      QString project_name = json_data.object().value("message").toString();

      std::vector<Message> messages_to_update;
      std::stringstream ss1(raw_messages);
      std::string message;
      while (std::getline(ss1, message, '|')) {
        std::stringstream ss2(message);
        std::string text_of_message;
        std::string name_of_sender;
        std::string surname_of_sender;
        std::string user_role;
        std::string file_path;

        std::getline(ss2, text_of_message, '\n');
        std::getline(ss2, name_of_sender, '\n');
        std::getline(ss2, surname_of_sender, '\n');
        std::getline(ss2, user_role, '\n');
        std::getline(ss2, file_path, '\n');

        messages_to_update.push_back(Message{
            QString::fromStdString(name_of_sender),
            QString::fromStdString(surname_of_sender),
            QString::fromStdString(message), QString::fromStdString(user_role),
            QString::fromStdString(file_path)});
      }

      // emit got_all_messages_of_project(messages_to_update,
      // project_name);
    }

  } else {
    qDebug() << "ERROR: Invalid JSON format";
  }
}

bool SocketWrapper::send_data(const QByteArray &data) {
  m_socket_wrap->write(data);
  return m_socket_wrap->waitForBytesWritten();
}

bool SocketWrapper::add_user_to_project(const QString &email_sender,
                                        const QString &password_sender,
                                        const QString &user_role_sender,
                                        const QString &project_name) {
  QJsonObject jsonquery;
  jsonquery["type"] = "add_user_to_project";
  jsonquery["email"] = email_sender;
  jsonquery["password"] = password_sender;
  jsonquery["user_role"] = user_role_sender;

  jsonquery["project_name"] = project_name;

  QJsonDocument doc_to_send(jsonquery);
  bool status = send_data(doc_to_send.toJson());

  return status;
}

bool SocketWrapper::get_projects_request(const QString &email,
                                         const QString &password,
                                         const QString &user_role) {
  QJsonObject jsonquery;
  jsonquery["type"] = "get_projects";
  jsonquery["email"] = email;
  jsonquery["password"] = password;
  jsonquery["user_role"] = user_role;

  QJsonDocument doc_to_send(jsonquery);
  bool status = send_data(doc_to_send.toJson());

  return status;
}

bool SocketWrapper::get_tasks_request(const QString &email,
                                      const QString &password,
                                      const QString &user_role,
                                      const QString &project_name) {
  QJsonObject jsonquery;
  jsonquery["type"] = "get_tasks";
  jsonquery["email"] = email;
  jsonquery["password"] = password;
  jsonquery["project_name"] = project_name;
  jsonquery["user_role"] = user_role;

  QJsonDocument doc_to_send(jsonquery);

  bool status = send_data(doc_to_send.toJson());

  return status;
}

bool SocketWrapper::create_task_request(
    const QString &email, const QString &password, const QString &user_role,
    const QString &task_name, const QString &description,
    const QString &deadline, const QString &project_name) {
  QJsonObject jsonquery;
  jsonquery["type"] = "create_task";
  jsonquery["task_name"] = task_name;
  jsonquery["description"] = description;
  jsonquery["deadline"] = deadline;
  jsonquery["project_name"] = project_name;

  jsonquery["email"] = email;
  jsonquery["password"] = password;
  jsonquery["user_role"] = user_role;

  QJsonDocument doc_to_send(jsonquery);
  bool status = send_data(doc_to_send.toJson());

  return status;
}

bool SocketWrapper::register_company_and_user_request(
    const QString &name, const QString &surname, const QString &email,
    const QString &password, const QString &company_name,
    const QString &company_bio) {
  QJsonObject jsonquery;
  jsonquery["type"] = "registration";
  jsonquery["name"] = name;
  jsonquery["surname"] = surname;
  jsonquery["company_bio"] = company_bio;
  jsonquery["company_name"] = company_name;
  jsonquery["email"] = email;
  jsonquery["password"] = password;

  QJsonDocument doc_to_send(jsonquery);
  bool status = send_data(doc_to_send.toJson());
  wait_for_data();

  return status;
}

bool SocketWrapper::create_project_request(const QString &email,
                                           const QString &password,
                                           const QString &user_role,
                                           const QString &project_name,
                                           const QString &project_bio) {
  QJsonObject jsonquery;
  jsonquery["type"] = "add_project";
  jsonquery["email"] = email;
  jsonquery["password"] = password;
  jsonquery["user_role"] = user_role;
  jsonquery["project_name"] = project_name;
  jsonquery["project_bio"] = project_bio;

  QJsonDocument doc_to_send(jsonquery);
  bool status = send_data(doc_to_send.toJson());

  return status;
}

bool SocketWrapper::validate_user_request(const QString &email,
                                          const QString &password) {
  QJsonObject jsonquery;
  jsonquery["type"] = "authorization";
  jsonquery["email"] = email;
  jsonquery["password"] = password;

  QJsonDocument doc_to_send(jsonquery);
  bool status = send_data(doc_to_send.toJson());
  //    wait_for_data();

  return status;
}

bool SocketWrapper::send_message_to_company_request(const QString &email,
                                                    const QString &password,
                                                    const QString &user_role,
                                                    const QString &message) {
  QJsonObject jsonquery;
  jsonquery["type"] = "send_message_to_company";
  jsonquery["email"] = email;
  jsonquery["password"] = password;
  jsonquery["user_role"] = user_role;
  jsonquery["message"] = message;
  QJsonDocument doc_to_send(jsonquery);

  bool status = send_data(doc_to_send.toJson());

  return status;
}

bool SocketWrapper::get_all_message_of_company_request(
    const QString &email, const QString &password, const QString &user_role) {
  QJsonObject jsonquery;
  jsonquery["type"] = "get_all_message_of_company";
  jsonquery["email"] = email;
  jsonquery["password"] = password;
  jsonquery["user_role"] = user_role;

  QJsonDocument doc_to_send(jsonquery);

  bool status = send_data(doc_to_send.toJson());

  return status;
}

SocketWrapper::~SocketWrapper() { m_socket_wrap->deleteLater(); }

} // namespace client::network
