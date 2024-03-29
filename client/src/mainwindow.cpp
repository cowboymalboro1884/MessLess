#include "include/mainwindow.h"
#include "include/add_project.h"
#include "include/add_user_window.h"
#include "include/projectwindow.h"
#include "ui_mainwindow.h"
#include <QScrollArea>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_Main(new Ui::MainWindow) {
  ui_Main->setupUi(this);
  this->current_window = "auth_window";
  this->setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("MessLess");
  ui_Main->tabWidget->setCurrentIndex(1);
  update_projects();
  connect(&ui_Auth, SIGNAL(login_button_clicked()), this,
          SLOT(authorizeUser()));
  connect(&ui_Auth, SIGNAL(register_button_clicked()), this,
          SLOT(registerWindowShow()));
  connect(&ui_Reg, SIGNAL(pushButtonBack_clicked()), this,
          SLOT(authorizeWindowShow()));
  connect(&ui_Reg, SIGNAL(register_button_clicked2()), this,
          SLOT(registerUser()));
  connect(ui_Main->newProjetButton, &QPushButton::clicked, [&] {
    add_project *chooseWindow = new add_project(nullptr, this);
    chooseWindow->show();
  });
  connect(ui_Main->add_user_button, &QPushButton::clicked, [&] {
    AddUserWindow *add_user_window = new AddUserWindow(nullptr, this);
    add_user_window->show();
  });
  connect(ui_Main->projectsButton, &QPushButton::clicked, [&] {
    ui_Main->tabWidget->setCurrentIndex(1);
    current_window = "main_window";
    clear_projects();
    update_projects();
  });
  connect(ui_Main->chatButton, &QPushButton::clicked, [&] {
    ui_Main->tabWidget->setCurrentIndex(2);
    current_window = "main_window_chat";
    if (update_company_chat_flag) {
      update_company_chat_flag = false;
      QLayout *lay = ui_Main->messages->layout();
      for (const auto &message : company_messages) {
        QPushButton *user = new QPushButton(message.name_of_sender + " " +
                                            message.surname_of_sender);
        QLabel *user_message = new QLabel(message.message_as_it_is);
        lay->addWidget(user);
        lay->addWidget(user_message);
      }
    } else {
      add_new_messages();
    }
  });
  connect(ui_Main->accButton, &QPushButton::clicked, [&] {
    ui_Main->tabWidget->setCurrentIndex(0);
    current_window = "main_window_account";
  });
  connect(ui_Main->send_message, &QPushButton::clicked, [&] {
    if (ui_Main->message_edit->text().isEmpty()) {
      QMessageBox::warning(this, "Warning", "Enter message!");
    } else {
      emit send_message(ui_Main->message_edit->text());
      ui_Main->message_edit->clear();
    }
  });
}

void MainWindow::authorizeUser() { emit got_auth_data(); }

void MainWindow::registerUser() { emit got_register_data(); }

void MainWindow::clear_projects() {
  QLayoutItem *child;
  while ((child = ui_Main->project_lay->takeAt(0)) != nullptr) {
    delete child->widget();
    delete child;
  }
}

void MainWindow::change_user_info(const QString &email, const QString &name,
                                  const QString &surname,
                                  const QString &company, const QString &role) {
  ui_Main->user_email_->setText(email);
  ui_Main->user_name_->setText(name);
  ui_Main->user_surname_->setText(surname);
  ui_Main->user_company_->setText(company);
  ui_Main->user_role_->setText(role);
}

void MainWindow::send_project_message(const QString &project_name,
                                      const QString &message) {
  emit send_project_message_signal(project_name, message);
}

void MainWindow::update_project_chat(const QString &project_name,
                                     Message message) {
  if (current_window == (project_name + "_chat")) {
    emit got_project_message(message);
  }
}

void MainWindow::add_new_messages() {
  if (current_window == "main_window_chat") {
    for (size_t index = company_messages.size() - message_counter;
         index < company_messages.size(); index++) {
      QLayout *lay = ui_Main->messages->layout();
      QPushButton *user =
          new QPushButton(company_messages[index].name_of_sender + " " +
                          company_messages[index].surname_of_sender);
      QLabel *user_message =
          new QLabel(company_messages[index].message_as_it_is);
      lay->addWidget(user);
      lay->addWidget(user_message);
    }
    message_counter = 0;
  }
}

void MainWindow::clear_messages() {
  QLayoutItem *child;
  while ((child = ui_Main->messages->takeAt(0)) != nullptr) {
    delete child->widget();
    delete child;
  }
}

void MainWindow::add_new_project(const QString &project_name,
                                 const QString &project_description) {
  emit got_new_project_data(project_name, project_description);
}

void MainWindow::add_new_task(const QString &task_name,
                              const QString &task_description,
                              const QString &task_deadline) {
  emit got_new_task_data(task_name, task_description, task_deadline);
}

void MainWindow::add_user_to_project(const QString &email,
                                     const QString &role) {
  emit got_project_user_data(email, role);
}

void MainWindow::add_user_to_company(const QString &email, const QString &name,
                                     const QString &surname,
                                     const QString &password,
                                     const QString &role) {
  emit add_new_user_to_company(email, name, surname, password, role);
}

void MainWindow::change_task_condition(const QString &name,
                                       const QString &condition) {
  emit update_task_condition(name, condition);
}

void MainWindow::update_projects() {
  QLayout *lay = ui_Main->project_lay->layout();
  for (const auto &i : all_tasks) {
    qDebug() << QString::fromStdString(i.first);
    QPushButton *button = new QPushButton(QString::fromStdString(i.first));
    project_name = button->text();
    connect(button, &QPushButton::clicked, [=] {
      project_name = button->text();
      ProjectWindow *project_window =
          new ProjectWindow(nullptr, this, project_name);
      project_window->show();
      if (user_role == "employee") {
        project_window->hide_settings();
      }
      current_window = project_name;
      update_tasks();
    });
    lay->addWidget(button);
  }
}

void MainWindow::delete_project(const QString &project) {
  qDebug() << 5;
  //    this->setEnabled(true);

  emit delete_project_signal(project);
  qDebug() << 6;
  //    this->setEnabled(false);
}

void MainWindow::delete_user(const QString &email) {
  emit delete_user_signal(email);
}

void MainWindow::update_tasks() { emit update_current_tasks(); }

void MainWindow::display() { ui_Auth.show(); }

void MainWindow::hide_button() { ui_Main->add_user_button->hide(); }

void MainWindow::registerWindowShow() {
  ui_Auth.hide();
  this->current_window = "reg_window";
  ui_Reg.show();
}

void MainWindow::authorizeWindowShow() {
  ui_Auth.show();
  this->current_window = "auth_window";
  ui_Reg.hide();
}

MainWindow::~MainWindow() {
  qDebug() << "MainWindow Destroyed";
  clear_projects();
  delete ui_Main;
  ui_Auth.~auth_window();
  ui_Reg.~reg_window();
  exit(0);
}
