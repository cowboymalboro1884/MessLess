/********************************************************************************
** Form generated from reading UI file 'add_task.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_TASK_H
#define UI_ADD_TASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddTask
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *task_name;
    QLineEdit *task_name_edit;
    QLabel *task_deadline;
    QLineEdit *task_description_edit;
    QPushButton *add_task;
    QLabel *task_description;
    QLineEdit *task_deadline_edit;

    void setupUi(QDialog *AddTask)
    {
        if (AddTask->objectName().isEmpty())
            AddTask->setObjectName(QString::fromUtf8("AddTask"));
        AddTask->resize(400, 233);
        AddTask->setStyleSheet(QString::fromUtf8("background-color:rgb(245, 245, 245);\n"
""));
        verticalLayout_2 = new QVBoxLayout(AddTask);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        task_name = new QLabel(AddTask);
        task_name->setObjectName(QString::fromUtf8("task_name"));
        task_name->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));
        task_name->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(task_name, 0, 0, 1, 1);

        task_name_edit = new QLineEdit(AddTask);
        task_name_edit->setObjectName(QString::fromUtf8("task_name_edit"));
        task_name_edit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(task_name_edit, 1, 0, 1, 1);

        task_deadline = new QLabel(AddTask);
        task_deadline->setObjectName(QString::fromUtf8("task_deadline"));
        task_deadline->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));
        task_deadline->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(task_deadline, 4, 0, 1, 1);

        task_description_edit = new QLineEdit(AddTask);
        task_description_edit->setObjectName(QString::fromUtf8("task_description_edit"));
        task_description_edit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(task_description_edit, 3, 0, 1, 1);

        add_task = new QPushButton(AddTask);
        add_task->setObjectName(QString::fromUtf8("add_task"));
        add_task->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        gridLayout->addWidget(add_task, 6, 0, 1, 1);

        task_description = new QLabel(AddTask);
        task_description->setObjectName(QString::fromUtf8("task_description"));
        task_description->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));
        task_description->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(task_description, 2, 0, 1, 1);

        task_deadline_edit = new QLineEdit(AddTask);
        task_deadline_edit->setObjectName(QString::fromUtf8("task_deadline_edit"));
        task_deadline_edit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(task_deadline_edit, 5, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        retranslateUi(AddTask);

        QMetaObject::connectSlotsByName(AddTask);
    } // setupUi

    void retranslateUi(QDialog *AddTask)
    {
        AddTask->setWindowTitle(QApplication::translate("AddTask", "Dialog", nullptr));
        task_name->setText(QApplication::translate("AddTask", "Task name", nullptr));
        task_deadline->setText(QApplication::translate("AddTask", "Deadline", nullptr));
        add_task->setText(QApplication::translate("AddTask", "Add new task", nullptr));
        task_description->setText(QApplication::translate("AddTask", "Descriprion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddTask: public Ui_AddTask {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_TASK_H
