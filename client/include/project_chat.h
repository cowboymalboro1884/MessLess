#ifndef PROJECT_CHAT_H
#define PROJECT_CHAT_H

#include "include/mainwindow.h"
#include "include/projectwindow.h"
#include <QLabel>
#include <QWidget>

namespace Ui {
class ProjectChat;
}

class ProjectChat : public QWidget {
  Q_OBJECT

public:
  explicit ProjectChat(QWidget *parent = nullptr,
                       ProjectWindow *project_window = nullptr,
                       MainWindow *main_window = nullptr);
  ~ProjectChat();

private:
  Ui::ProjectChat *ui;
  ProjectWindow *m_project_window;
  MainWindow *m_main_window;
  void clear_chat();

private slots:
    void update_project_message(Message message);
};

#endif // PROJECT_CHAT_H
