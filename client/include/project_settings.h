#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H

#include "projectwindow.h"
#include <QWidget>

namespace Ui {
class ProjectSettings;
}

class ProjectSettings : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectSettings(QWidget *parent = nullptr,
                             ProjectWindow *project_window = nullptr);
    ~ProjectSettings();

private:
    Ui::ProjectSettings *ui;
    ProjectWindow *m_project_window;
};

#endif // PROJECT_SETTINGS_H
