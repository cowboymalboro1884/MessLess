#include "include/add_user_window.h"
#include "ui_add_user_window.h"

AddUserWindow::AddUserWindow(QWidget *parent, MainWindow *main_window) :
    QWidget(parent),
    ui(new Ui::AddUserWindow), m_main_window(main_window)
{
    ui->setupUi(this);
    m_main_window->setEnabled(false);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("MessLess");
    connect(ui->moderator, &QPushButton::clicked, [&] {
      role = "moderator";
    });
    connect(ui->employer, &QPushButton::clicked, [&] {
      role = "employer";
    });
    connect(ui->add_user, &QPushButton::clicked, [&] {
        if(role.isEmpty() || ui->email1->text().isEmpty() || ui->name_1->text().isEmpty() || ui->surname_1->text().isEmpty() || ui->password_1->text().isEmpty()){
            QMessageBox::warning(this, "Warning" ,"All fields must be filled out!");
        }else{
            m_main_window->add_user_to_company(ui->email1->text(), ui->name_1->text(),ui->surname_1->text(),ui->password_1->text(),role);
            this->close();
        }
      });
}

AddUserWindow::~AddUserWindow()
{
    m_main_window->setEnabled(true);
    qDebug() << "окно добавления юзера удалилось";
    delete ui;
}
