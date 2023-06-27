#ifndef ADD_USER_H
#define ADD_USER_H

#include <QWidget>
#include "projectwindow.h"

namespace Ui {
class AddUser;
}

class AddUser : public QWidget {
    Q_OBJECT

public:
    explicit AddUser(
        QWidget *parent = nullptr,
        ProjectWindow *project_window = nullptr
    );
    ~AddUser();

private:
    Ui::AddUser *ui;
    ProjectWindow *m_project_window;
    QString role;
};

#endif  // ADD_USER_H
