#ifndef REG_WINDOW_H
#define REG_WINDOW_H

#include <QWidget>

namespace Ui {
class reg_window;
}

class reg_window : public QWidget {
    Q_OBJECT

public:
    explicit reg_window(QWidget *parent = nullptr);
    ~reg_window();
    QString getName();
    QString getSurname();
    QString getLogin();
    QString getPass();
    QString getConfPass();
    QString getBio();
    QString getCompName();
    bool checkPass();

signals:
    void register_button_clicked2();
    void pushButtonSignIn_clicked();
    void pushButtonBack_clicked();

private slots:
    void on_pushButtonSignIn_clicked();

    void on_pushButtonBack_clicked();

private:
    Ui::reg_window *ui;
};

#endif  // REG_WINDOW_H
