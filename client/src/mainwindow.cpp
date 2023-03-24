#include "include/mainwindow.h"
#include "include/auth_window.h"
#include "include/reg_window.h"
#include "ui_mainwindow.h"
#include "include/add_project.h"
#include
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_Main(new Ui::MainWindow) {
  ui_Main->setupUi(this);
  connect(&ui_Auth, SIGNAL(login_button_clicked()), this,
          SLOT(authorizeUser()));
  connect(&ui_Auth, SIGNAL(destroyed()), this, SLOT(show()));
  connect(&ui_Auth, SIGNAL(register_button_clicked()), this,
          SLOT(registerWindowShow()));
  connect(&ui_Reg, SIGNAL(register_button_clicked2()), this,
          SLOT(registerUser()));
  connect(&ui_Reg, SIGNAL(destroyed()), &ui_Auth, SLOT(show()));
  connect(&ui_Auth, SIGNAL(auth_check()), this, SLOT(check_auth()));
  connect(ui_Main->newProjetButton, &QPushButton::clicked, [this] {
    add_project *chooseWindow = new add_project(nullptr, this);
    chooseWindow->show();
  });

  QScrollArea *scroll = new QScrollArea(ui_Main->tab);
  scroll->setBackgroundRole(QPalette::Window);
  scroll->setFrameShadow(QFrame::Plain);
  scroll->setFrameShape(QFrame::NoFrame);
  scroll->setWidgetResizable(true);

  QWidget *techArea = new QWidget(ui_Main->tabWidget);
  techArea->setObjectName("techarea");
  techArea->setSizePolicy(QSizePolicy::MinimumExpanding,
                          QSizePolicy::MinimumExpanding);
  techArea->setLayout(new QVBoxLayout(techArea));
  scroll->setWidget(techArea);
}

void MainWindow::authorizeUser() { emit got_auth_data(); }

QString MainWindow::get_username() { return ui_Auth.getLogin(); }

QString MainWindow::get_password() { return ui_Auth.getPass(); }

void MainWindow::registerUser() {
  /// TODO
}

void MainWindow::update_projects(){
    QLayout *lay = techArea->layout();
    for(const auto &i:projects){
        lay->addWidget()
    }
}

void MainWindow::display() { ui_Auth.show(); }

Ui::MainWindow *MainWindow::get_ui() const { return ui_Main; }

void MainWindow::check_auth() {
  qDebug() << "показалось";
  if (is_auth) {
    this->show();
    ui_Auth.close();
  }
}

void MainWindow::registerWindowShow() {
  ui_Auth.hide();
  ui_Reg.show();
}


MainWindow::~MainWindow() {
  qDebug() << "MainWindow Destroyed";
  delete ui_Main;

  //Возможно нужно будет поудалять все
  exit(0);
}
