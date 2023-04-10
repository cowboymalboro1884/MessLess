#ifndef PROJECT_BUTTON_H
#define PROJECT_BUTTON_H

#include <QString>
#include <QWidget>

class project_button : public QWidget {
  Q_OBJECT
public:
  project_button(const QString &name, const QString &deadline,
                 const QString &condition)
      : m_name(name), m_deadline(deadline), m_condition(condition) {}
  //    ~project_button();
  QString m_name;
  QString m_deadline;
  QString m_condition;

public slots:
  void on_project_button_clicked();

signals:
};

#endif // PROJECT_BUTTON_H
