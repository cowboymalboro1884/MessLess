#ifndef PROJECT_CHAT_H
#define PROJECT_CHAT_H

#include <QWidget>

namespace Ui {
  class ProjectChat;
}

class ProjectChat : public QWidget
{
  Q_OBJECT

public:
  explicit ProjectChat(QWidget *parent = nullptr);
  ~ProjectChat();

private:
  Ui::ProjectChat *ui;
};

#endif // PROJECT_CHAT_H
