#ifndef ADD_PROJECT_H
#define ADD_PROJECT_H

#include "mainwindow.h"
#include <QMainWindow>
#include <QWidget>

namespace Ui {
class add_project;
}

class add_project : public QWidget {
  Q_OBJECT

public:
  explicit add_project(QWidget *parent = nullptr,
                       MainWindow *main_wind = nullptr);
  ~add_project();

  // signals:
  //   void create_project();

private:
  Ui::add_project *ui;
  MainWindow *main_wind;
};

#endif // ADD_PROJECT_H
