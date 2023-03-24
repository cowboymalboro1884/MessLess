#include "project_button.h"

project_button::project_button(const std::string &name, bool is_it_my_project)
{
    button = new QPushButton(QString::fromStdString(name), nullptr);
    flag = is_it_my_project;
    button->setStyleSheet("QPushButton{background: red; border: 2px solid black; font: bold 40px;}"
                         "QPushButton:hover{background:  qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 red, stop:0.5 orange, stop:1 red); border:1px solid black;}");
        QObject::connect(button, SIGNAL(clicked()), this, SLOT(on_project_button_clicked()));
    }

project_button::~project_button(){
    delete button;
}

void project_button::on_project_button_clicked(){
    ////TODO
}
