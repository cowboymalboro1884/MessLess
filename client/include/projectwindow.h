#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class ProjectWindow;
}

class ProjectWindow : public QDialog {
  Q_OBJECT

public:
  explicit ProjectWindow(QWidget *parent = nullptr,
                         MainWindow *main_window = nullptr,
                         QString project_name = "default");
  ~ProjectWindow();
  void update_tasks();
  void add_new_task(const QString &task_name, const QString &task_description,
                    const QString &task_deadline);
  void add_user_to_project(const QString &name, const QString &role);
  void clear_tasks();
  void hide_settings();
  void delete_project(const QString &project);
  void delete_user(const QString &email);
  QString m_project_name;

private:
  Ui::ProjectWindow *ui;
  MainWindow *m_main_window;

signals:
  void open_project_settings();

private slots:
  void delete_and_update_tasks();
};

#endif // PROJECTWINDOW_H
