#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class ProjectWindow;
}

class ProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectWindow(QWidget *parent = nullptr, MainWindow *main_window = nullptr, QString project_name = "default");
    ~ProjectWindow();
    void update_tasks();
    QString name;
    QString description;
    QString deadline;
    void add_new_task();
    void clear_tasks();
private:
    Ui::ProjectWindow *ui;
    MainWindow *m_main_window;

signals:
    void open_project_settings();

private slots:
    void delete_and_update_tasks();
};

#endif // PROJECTWINDOW_H
