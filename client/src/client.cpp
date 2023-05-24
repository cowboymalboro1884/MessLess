#include "include/client.h"

namespace client {

Client::Client(QObject *parent) : m_window(new MainWindow()) {
  connect(m_window, SIGNAL(got_auth_data()), this, SLOT(got_auth_data()));
  connect(m_window, SIGNAL(got_register_data()), this,
          SLOT(got_register_data()));
  connect(m_window, SIGNAL(got_new_project_data()), this, SLOT(got_add_project_data()));
  connect(m_window, SIGNAL(got_project_tasks()), this, SLOT(got_project_tasks()));
  connect(m_window, SIGNAL(got_new_task_data()), this, SLOT(got_add_task_data()));
};

void Client::start() {
  m_window->display();
  m_socketwrapper = new network::SocketWrapper("194.87.210.109", 1339);
  m_socketwrapper->connect_to_host();

  connect(m_socketwrapper, SIGNAL(got_status_of_registration(client::network::PrivateUserInfo)), this, SLOT(got_status_of_registration_slot(client::network::PrivateUserInfo)));
  connect(m_socketwrapper, SIGNAL(got_status_of_authorization(client::network::PrivateUserInfo)), this, SLOT(got_status_of_authorization_slot(client::network::PrivateUserInfo)));
  connect(m_socketwrapper, SIGNAL(got_projects_to_update(std::vector<std::string>)), this, SLOT(got_projects_to_update_slot(std::vector<std::string>)));
  connect(m_socketwrapper, SIGNAL(somebody_updated_project()), this, SLOT(somebody_updated_project_slot()));
  connect(m_socketwrapper, SIGNAL(got_tasks_to_update(std::vector<client::network::Task>, QString)), this, SLOT(got_tasks_to_update_slot(std::vector<client::network::Task>, QString)));

}

// FIXME(to maxim): SIGNALS WITHOUT _slot - SEND DATA, with _slot - PROCESS RECIEVED FROM SERVER DATA

void Client::got_register_data() {
    m_socketwrapper->register_company_and_user_request(
    m_window->ui_Reg.getName(), m_window->ui_Reg.getSurname(),
    m_window->ui_Reg.getLogin(), m_window->ui_Reg.getPass(),
    m_window->ui_Reg.getCompName(), m_window->ui_Reg.getBio());
}


void Client::got_auth_data() {
  m_socketwrapper->validate_user_request(m_window->ui_Auth.getLogin(),
                                            m_window->ui_Auth.getPass());
}

void Client::got_add_project_data(){
    m_socketwrapper->create_project_request(user.email,user.password,user.user_role,m_window->project_name, m_window->project_description);
}

void Client::got_project_tasks(){
    m_socketwrapper->get_tasks_request(user.email, user.password, user.user_role, m_window->project_name);
}

void Client::got_add_task_data(){
    m_socketwrapper->create_task_request(user.email, user.password, user.user_role, m_window->task_name, m_window->task_description, m_window->task_deadline, m_window->project_name);
    got_project_tasks();
}

void Client::got_status_of_registration_slot(client::network::PrivateUserInfo new_user) {
    user = std::move(new_user);
    if (user.status == "success") {
      m_window->ui_Auth.close();
      m_window->ui_Reg.close();
      m_window->show();
    } else {
      //добавить ошибку
    }
}

void Client::got_status_of_authorization_slot(network::PrivateUserInfo new_user) {
    user = std::move(new_user);
    if (user.status == "success") {
      qDebug() << "name:" << user.email;
      m_window->ui_Auth.close();
      m_window->ui_Reg.close();
      m_window->show();
      m_socketwrapper->get_projects_request(user.email,user.password,user.user_role);
    } else {
      //добавить ошибку
    }
}


void Client::got_projects_to_update_slot(std::vector<std::string> projects_to_update) {
    m_window->projects = projects_to_update;
    m_window->update_projects();
    qDebug() << "проекты обновлены";
}

void Client::somebody_updated_project_slot() {
    m_window->flag = true;
    qDebug() << "flag: " << m_window->flag;
    m_socketwrapper->get_projects_request(user.email,user.password,user.user_role);
}

void Client::got_tasks_to_update_slot(std::vector<network::Task> tasks_to_update, QString project_name) {
    m_window->tasks = tasks_to_update;
    m_window->flag = true;
    // ....... !!!! обновление тасок для конкретного проекта
}

Client::~Client() { m_window->deleteLater(); }

} // namespace client
