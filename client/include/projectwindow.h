#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QWidget>

namespace Ui {
class projectWindow;
}

class projectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit projectWindow(QWidget *parent = nullptr);
    ~projectWindow();

private:
    Ui::projectWindow *ui;
};

#endif // PROJECTWINDOW_H
