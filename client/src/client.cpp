#include "include/client.h"

namespace client {

Client::Client(QObject *parent)
    : m_window(new MainWindow()){
            connect(m_window, SIGNAL(got_auth_data()), this,
            SLOT(got_auth_data()));
            connect(m_window, SIGNAL(got_register_data()), this,
                    SLOT(got_register_data()));
            connect(m_window, SIGNAL(got_new_project_data()), this,
            SLOT(got_add_project_data()));
            connect(m_window, SIGNAL(got_project_tasks()), this,
            SLOT(got_project_tasks()));
            connect(m_window, SIGNAL(got_new_task_data()), this,
            SLOT(got_add_task_data()));
      };

void Client::start() {
    m_window->display();

    try {
        m_network_manager = new NetworkManager(this, "194.87.210.109", 1339);
        network_thread = new QThread();
        connect(
            network_thread, &QThread::started, m_network_manager,
            &NetworkManager::run
        );
        m_network_manager->moveToThread(network_thread);
        network_thread->start();
    } catch (...) {
        // need to delete
    }

      connect(m_network_manager->m_response_handler,
      SIGNAL(got_status_of_registration(PrivateUserInfo)),
      this,
      SLOT(got_status_of_registration_slot(PrivateUserInfo)));
      connect(m_network_manager->m_response_handler,
      SIGNAL(got_status_of_authorization(PrivateUserInfo)),
      this,
      SLOT(got_status_of_authorization_slot(PrivateUserInfo)));
      connect(m_network_manager->m_response_handler, SIGNAL(get_new_condition_of_projects()), this,SLOT(somebody_updated_project_slot()));

      //сообщение для будущего меня, пытаюсь законнектить сигналы и слоты уже на получение инфы, но происходит беда хз


//      connect(m_network_manager->m_response_handler,
//      SIGNAL(got_projects_to_update(std::vector<std::string>)), this,
//      SLOT(got_projects_to_update_slot(std::vector<std::string>)));
//      connect(m_network_manager->m_response_handler, SIGNAL(somebody_updated_project()), this,
//      SLOT(somebody_updated_project_slot())); connect(m_network_manager->m_response_handler,
//      SIGNAL(got_tasks_to_update(std::vector<client::network::Task>,
//      QString)), this,
//      SLOT(got_tasks_to_update_slot(std::vector<client::network::Task>,
//      QString)));


}

void Client::got_register_data() {
    m_network_manager->m_query_sender->register_company_and_user(
        m_window->ui_Reg.getName(), m_window->ui_Reg.getSurname(),
        m_window->ui_Reg.getLogin(), m_window->ui_Reg.getPass(),
        m_window->ui_Reg.getCompName(), m_window->ui_Reg.getBio()
    );
}

void Client::got_auth_data() {
    m_network_manager->m_query_sender->check_credentials(
        m_window->ui_Auth.getLogin(), m_window->ui_Auth.getPass()
    );
}

void Client::got_add_project_data() {
    m_network_manager->m_query_sender->create_project(user.email, user.password, user.user_role, m_window->project_name,
                                                      m_window->project_description);
}

void Client::got_project_tasks() {
    m_network_manager->m_query_sender->get_tasks_of_projects(user.email, user.password, user.user_role, m_window->project_name);

}

void Client::got_add_task_data() {
    m_network_manager->m_query_sender->create_task(user.email, user.password, user.user_role, m_window->task_name,
                                                   m_window->task_description, m_window->task_deadline,
                                                   m_window->project_name);

//    got_project_tasks();
}

void Client::got_status_of_registration_slot(PrivateUserInfo new_user) {
    user = std::move(new_user);
//    if (user.status == "success") {
        m_window->ui_Auth.close();
        m_window->ui_Reg.close();
        m_window->show();
//    } else {
//        // добавить ошибку
//    }
}

void Client::got_status_of_authorization_slot(PrivateUserInfo new_user) {
    user = std::move(new_user);
//    if (user.status == "success") {
        qDebug() << "name:" << user.email;
        m_window->ui_Auth.close();
        m_window->ui_Reg.close();

        m_window->show();
        m_window->current_window = "main_window";
        // TODO:обработать ошибку
        //       m_socketwrapper->get_projects_request(user.email,user.password,user.user_role);
//    } else {
//        // добавить ошибку
//    }
}

void Client::got_projects_to_update_slot(
    std::vector<std::string> projects_to_update
) {
    m_window->projects = projects_to_update;
    m_window->clear_projects();
    m_window->update_projects();
    qDebug() << "проекты обновлены";
}

void Client::somebody_updated_project_slot() {
    m_window->flag = true;
    qDebug() << "flag: " << m_window->flag;
//        m_socketwrapper->get_projects_request(user.email,user.password,user.user_role);
    m_network_manager->m_query_sender->get_projects_of_company(user.email, user.password, user.user_role);
}

void Client::got_tasks_to_update_slot(
    std::vector<Task> tasks_to_update,
    QString project_name
) {
    m_window->tasks = tasks_to_update;
    m_window->flag = true;
    m_window->all_tasks[project_name.toStdString()] = tasks_to_update;
    // ....... !!!! обновление тасок для конкретного проекта
    if (m_window->current_window == project_name) {
        m_window->update_tasks();
    }
}

Client::~Client() {
    m_window->deleteLater();
    network_thread->quit();
    network_thread->wait();
    network_thread->deleteLater();
}

}  // namespace client
