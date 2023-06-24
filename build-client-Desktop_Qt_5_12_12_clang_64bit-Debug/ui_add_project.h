/********************************************************************************
** Form generated from reading UI file 'add_project.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_PROJECT_H
#define UI_ADD_PROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_add_project
{
public:
    QGridLayout *gridLayout;
    QLabel *name_label;
    QLineEdit *name_lineEdit;
    QPushButton *addProject;
    QLabel *description_label;
    QLineEdit *description_lineEdit;

    void setupUi(QWidget *add_project)
    {
        if (add_project->objectName().isEmpty())
            add_project->setObjectName(QString::fromUtf8("add_project"));
        add_project->resize(420, 210);
        add_project->setStyleSheet(QString::fromUtf8("background-color:rgb(245, 245, 245);\n"
""));
        gridLayout = new QGridLayout(add_project);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        name_label = new QLabel(add_project);
        name_label->setObjectName(QString::fromUtf8("name_label"));
        name_label->setMaximumSize(QSize(16777215, 15));
        name_label->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 10pt \"Arial Black\";"));
        name_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(name_label, 0, 0, 1, 1);

        name_lineEdit = new QLineEdit(add_project);
        name_lineEdit->setObjectName(QString::fromUtf8("name_lineEdit"));
        name_lineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(name_lineEdit, 1, 0, 1, 1);

        addProject = new QPushButton(add_project);
        addProject->setObjectName(QString::fromUtf8("addProject"));
        addProject->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     background-color: rgb(80, 108, 200);\n"
"	color: white;\n"
"border: 1px black;\n"
"\n"
"     border-radius: 4px;\n"
"	font: 63 8pt \"Yu Gothic UI Semibold\";\n"
"width:326px;\n"
"height:26px;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"border: 1px solid rgb(255, 255, 255);\n"
"}"));

        gridLayout->addWidget(addProject, 4, 0, 1, 1);

        description_label = new QLabel(add_project);
        description_label->setObjectName(QString::fromUtf8("description_label"));
        description_label->setMaximumSize(QSize(16777215, 15));
        description_label->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 10pt \"Arial Black\";"));
        description_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(description_label, 2, 0, 1, 1);

        description_lineEdit = new QLineEdit(add_project);
        description_lineEdit->setObjectName(QString::fromUtf8("description_lineEdit"));
        description_lineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(description_lineEdit, 3, 0, 1, 1);


        retranslateUi(add_project);

        QMetaObject::connectSlotsByName(add_project);
    } // setupUi

    void retranslateUi(QWidget *add_project)
    {
        add_project->setWindowTitle(QApplication::translate("add_project", "Form", nullptr));
        name_label->setText(QApplication::translate("add_project", "Project name", nullptr));
        addProject->setText(QApplication::translate("add_project", "Add project", nullptr));
        description_label->setText(QApplication::translate("add_project", "Description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class add_project: public Ui_add_project {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_PROJECT_H
