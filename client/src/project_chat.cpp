#include "include/project_chat.h"
#include "ui_project_chat.h"

ProjectChat::ProjectChat(
    QWidget *parent,
    ProjectWindow *project_window,
    MainWindow *main_window
)
    : QWidget(parent),
      ui(new Ui::ProjectChat),
      m_project_window(project_window),
      m_main_window(main_window) {
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("MessLess");
    m_project_window->hide();
    m_project_window->setEnabled(false);
    QLayout *lay = ui->messages->layout();

    for (const auto &message :
         m_main_window
             ->all_messages[m_project_window->m_project_name.toStdString()]) {
        QPushButton *user = new QPushButton(
            message.name_of_sender + " " + message.surname_of_sender
        );
        QLabel *user_message = new QLabel(message.message_as_it_is);

        lay->addWidget(user);
        lay->addWidget(user_message);
    }
    connect(ui->send_button, &QPushButton::clicked, [&] {
        if (ui->message_edit->text().isEmpty()) {
            QMessageBox::warning(this, "Warning", "Enter message!");
        } else {
            m_main_window->send_project_message(
                m_project_window->m_project_name, ui->message_edit->text()
            );
            ui->message_edit->clear();
        }
    });

    connect(
        m_main_window, SIGNAL(got_project_message(Message)), this,
        SLOT(update_project_message(Message))
    );
}

void ProjectChat::update_project_message(Message message) {
    QLayout *lay = ui->messages->layout();
    QPushButton *user = new QPushButton(
        message.name_of_sender + " " + message.surname_of_sender
    );
    QLabel *user_message = new QLabel(message.message_as_it_is);
    lay->addWidget(user);
    lay->addWidget(user_message);
}

void ProjectChat::clear_chat() {
    QLayoutItem *child;
    while ((child = ui->messages->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
}

ProjectChat::~ProjectChat() {
    qDebug() << "окно чата удалилось";
    m_project_window->setEnabled(true);
    qDebug() << 5;
    m_project_window->show();
    qDebug() << 6;
    m_main_window->current_window = m_project_window->m_project_name;
      clear_chat();
    delete ui;
}
