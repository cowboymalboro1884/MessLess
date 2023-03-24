#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QTcpSocket>
#include <QString>
#include <QScrollArea>
#include "auth_window.h"
#include "reg_window.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display(); // прототип пользовательской функции отображения
    QString get_username();
    QString get_password();
    Ui::MainWindow *get_ui() const;
    std::vector<std::string> projects;//нужен будет для сортировки
    bool is_auth = true;//надо будет изменить на false

private:
    Ui::MainWindow *ui_Main;
    auth_window ui_Auth; // экземпляры окна авторизации и окна регистрации
    reg_window ui_Reg; // принадлежат главному окну

private slots:
    void authorizeUser(); // пользовательские слоты
    void registerWindowShow();
    void registerUser();
    void check_auth();

signals:
    void got_auth_data();
};

#endif // MAINWINDOW_H
