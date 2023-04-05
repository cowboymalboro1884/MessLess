#ifndef PROJECT_BUTTON_H
#define PROJECT_BUTTON_H

#include <QWidget>
#include <QPushButton>

class project_button : public QWidget
{
    Q_OBJECT
public:
    explicit project_button(const std::string &name, bool is_it_my_project);
    ~project_button();

private:
    QPushButton *button;
    bool flag;

public slots:
    void on_project_button_clicked();

signals:

};

#endif // PROJECT_BUTTON_H
