#include "include/add_user_window.h"
#include "ui_add_user_window.h"

AddUserWindow::AddUserWindow(QWidget *parent, MainWindow *main_window)
    : QWidget(parent), ui(new Ui::AddUserWindow), m_main_window(main_window) {
    ui->setupUi(this);
    m_main_window->setEnabled(false);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("MessLess");
    connect(ui->moderator, &QPushButton::clicked, [&] { role = "moderator"; });
    connect(ui->employer, &QPushButton::clicked, [&] { role = "employee"; });
    connect(ui->add_user_button, &QPushButton::clicked, [&] {
        if (role.isEmpty() || ui->email_->text().isEmpty() ||
            ui->name_->text().isEmpty() || ui->surname_->text().isEmpty() ||
            ui->password_->text().isEmpty()) {
            QMessageBox::warning(
                this, "Warning", "All fields must be filled out!"
            );
        } else {
            m_main_window->add_user_to_company(
                ui->email_->text(), ui->name_->text(), ui->surname_->text(),
                ui->password_->text(), role
            );
            this->close();
        }
    });
}

AddUserWindow::~AddUserWindow() {
    m_main_window->setEnabled(true);
    qDebug() << "окно добавления юзера удалилось";
    delete ui;
}
