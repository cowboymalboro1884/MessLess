/********************************************************************************
** Form generated from reading UI file 'project_settings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECT_SETTINGS_H
#define UI_PROJECT_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectSettings
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *add_new_task;
    QPushButton *add_new_user;
    QPushButton *delete_task;
    QPushButton *delete_user;

    void setupUi(QWidget *ProjectSettings)
    {
        if (ProjectSettings->objectName().isEmpty())
            ProjectSettings->setObjectName(QString::fromUtf8("ProjectSettings"));
        ProjectSettings->resize(400, 300);
        ProjectSettings->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	background-color:rgb(245, 245, 245);\n"
"}\n"
"QPushButton {\n"
"     background-color: rgb(80, 108, 200);\n"
"	color: white;\n"
"border: 1px black;\n"
"\n"
"     border-radius: 4px;\n"
"	font: 63 8pt \"Yu Gothic UI Semibold\";\n"
"width:326px;\n"
"height:26px;\n"
"}\n"
"QPushButton:hover{\n"
"border: 1px solid rgb(255, 255, 255);\n"
"}"));
        gridLayout_2 = new QGridLayout(ProjectSettings);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        add_new_task = new QPushButton(ProjectSettings);
        add_new_task->setObjectName(QString::fromUtf8("add_new_task"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(36);
        sizePolicy.setHeightForWidth(add_new_task->sizePolicy().hasHeightForWidth());
        add_new_task->setSizePolicy(sizePolicy);
        add_new_task->setMinimumSize(QSize(0, 36));

        gridLayout_2->addWidget(add_new_task, 0, 0, 1, 1);

        add_new_user = new QPushButton(ProjectSettings);
        add_new_user->setObjectName(QString::fromUtf8("add_new_user"));
        sizePolicy.setHeightForWidth(add_new_user->sizePolicy().hasHeightForWidth());
        add_new_user->setSizePolicy(sizePolicy);
        add_new_user->setMinimumSize(QSize(0, 36));

        gridLayout_2->addWidget(add_new_user, 1, 0, 1, 1);

        delete_task = new QPushButton(ProjectSettings);
        delete_task->setObjectName(QString::fromUtf8("delete_task"));
        delete_task->setMinimumSize(QSize(0, 36));

        gridLayout_2->addWidget(delete_task, 0, 1, 1, 1);

        delete_user = new QPushButton(ProjectSettings);
        delete_user->setObjectName(QString::fromUtf8("delete_user"));
        delete_user->setMinimumSize(QSize(0, 36));

        gridLayout_2->addWidget(delete_user, 1, 1, 1, 1);


        retranslateUi(ProjectSettings);

        QMetaObject::connectSlotsByName(ProjectSettings);
    } // setupUi

    void retranslateUi(QWidget *ProjectSettings)
    {
        ProjectSettings->setWindowTitle(QApplication::translate("ProjectSettings", "Form", nullptr));
        add_new_task->setText(QApplication::translate("ProjectSettings", "Add new task", nullptr));
        add_new_user->setText(QApplication::translate("ProjectSettings", "Add new user", nullptr));
        delete_task->setText(QApplication::translate("ProjectSettings", "Delete task", nullptr));
        delete_user->setText(QApplication::translate("ProjectSettings", "Delete user", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectSettings: public Ui_ProjectSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT_SETTINGS_H
