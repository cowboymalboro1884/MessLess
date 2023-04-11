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
  m_socketwrapper->connect();
}

void Client::got_register_data() {
  user = m_socketwrapper->registerCompanyAndUser(
      m_window->ui_Reg.getName(), m_window->ui_Reg.getSurname(),
      m_window->ui_Reg.getLogin(), m_window->ui_Reg.getPass(),
      m_window->ui_Reg.getCompName(), m_window->ui_Reg.getBio());
  if (user.status == "success") {
    m_window->ui_Auth.close();
    m_window->ui_Reg.close();
    m_window->show();

  } else {
    //добавить ошибку
  }
}

void Client::got_auth_data() {
  user = m_socketwrapper->validateUser(m_window->ui_Auth.getLogin(),
                                       m_window->ui_Auth.getPass());
  if (user.status == "success") {
    m_window->ui_Auth.close();
    m_window->ui_Reg.close();
    m_window->projects = m_socketwrapper->getProjects(user.email,user.password,user.user_role);
    m_window->show();
    m_window->update_projects();
  } else {
    //добавить ошибку
  }
}

void Client::got_add_project_data(){
    m_window->flag = m_socketwrapper->createProject(user.email,user.password,user.user_role,m_window->project_name, m_window->project_description);
    qDebug() << "flag: " << m_window->flag;
    m_window->projects = m_socketwrapper->getProjects(user.email,user.password,user.user_role);
    qDebug() << "проекты обновлены";
}

void Client::got_project_tasks(){
    m_window->tasks = m_socketwrapper->getTasks(user.email, user.password, user.user_role, m_window->project_name);

}

void Client::got_add_task_data(){
    m_window->flag = m_socketwrapper->createTask(user.email, user.password, user.user_role, m_window->task_name, m_window->task_description, m_window->task_deadline, m_window->project_name);
    got_project_tasks();
}

Client::~Client() { m_window->deleteLater(); }

} // namespace client
