/********************************************************************************
** Form generated from reading UI file 'add_user.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_USER_H
#define UI_ADD_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddUser
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *email;
    QGridLayout *gridLayout;
    QRadioButton *administrator;
    QRadioButton *employer;
    QPushButton *add_user;

    void setupUi(QWidget *AddUser)
    {
        if (AddUser->objectName().isEmpty())
            AddUser->setObjectName(QString::fromUtf8("AddUser"));
        AddUser->resize(420, 210);
        AddUser->setStyleSheet(QString::fromUtf8("background-color:rgb(245, 245, 245);\n"
""));
        verticalLayout = new QVBoxLayout(AddUser);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(AddUser);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 45));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 10pt \"Arial Black\";\n"
"height: 20px;"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        email = new QLineEdit(AddUser);
        email->setObjectName(QString::fromUtf8("email"));
        email->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        verticalLayout->addWidget(email);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        administrator = new QRadioButton(AddUser);
        administrator->setObjectName(QString::fromUtf8("administrator"));
        administrator->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 10pt \"Arial Black\";"));

        gridLayout->addWidget(administrator, 0, 0, 1, 1);

        employer = new QRadioButton(AddUser);
        employer->setObjectName(QString::fromUtf8("employer"));
        employer->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 10pt \"Arial Black\";"));

        gridLayout->addWidget(employer, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        add_user = new QPushButton(AddUser);
        add_user->setObjectName(QString::fromUtf8("add_user"));
        add_user->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     background-color: rgb(80, 108, 200);\n"
"	color: white;\n"
"border: 1px black;\n"
"\n"
"     border-radius: 4px;\n"
"	font: 63 10pt \"Yu Gothic UI Semibold\";\n"
"width:326px;\n"
"height:26px;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"border: 1px solid rgb(255, 255, 255);\n"
"}"));

        verticalLayout->addWidget(add_user);


        retranslateUi(AddUser);

        QMetaObject::connectSlotsByName(AddUser);
    } // setupUi

    void retranslateUi(QWidget *AddUser)
    {
        AddUser->setWindowTitle(QApplication::translate("AddUser", "Form", nullptr));
        label->setText(QApplication::translate("AddUser", "User email", nullptr));
        administrator->setText(QApplication::translate("AddUser", "Administrator", nullptr));
        employer->setText(QApplication::translate("AddUser", "Employer", nullptr));
        add_user->setText(QApplication::translate("AddUser", "Add user", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddUser: public Ui_AddUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_USER_H
