#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include "include/mainwindow.h"
#include "include/reg_window.h"
#include "include/auth_window.h"

namespace client {
class WindowManager : public QObject {
    Q_OBJECT
    MainWindow* m_main;
    auth_window* m_auth;
    reg_window* m_reg;
public:
    WindowManager(QObject *parent = nullptr);
    ~WindowManager();
};
}

#endif // WINDOWMANAGER_H
