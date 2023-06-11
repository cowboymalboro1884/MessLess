/********************************************************************************
** Form generated from reading UI file 'reg_window.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REG_WINDOW_H
#define UI_REG_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_reg_window
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label_Confirm;
    QLabel *label_Name;
    QLabel *label_Password;
    QLineEdit *confirmLineEdit;
    QLabel *label_Welcome;
    QPushButton *pushButtonBack;
    QLabel *label_Surname;
    QLineEdit *emailLineEdit;
    QLabel *label_Email;
    QLineEdit *nameLineEdit;
    QLabel *label_Company_bio;
    QLineEdit *passwordLineEdit;
    QLineEdit *surnameLineEdit;
    QLineEdit *companyNameLineEdit;
    QLabel *label_Company_name;
    QLineEdit *companyBioLineEdit;
    QLabel *label_Error;
    QPushButton *pushButtonSignIn;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *reg_window)
    {
        if (reg_window->objectName().isEmpty())
            reg_window->setObjectName(QString::fromUtf8("reg_window"));
        reg_window->setWindowModality(Qt::NonModal);
        reg_window->resize(474, 300);
        reg_window->setMinimumSize(QSize(474, 300));
        reg_window->setMaximumSize(QSize(474, 301));
        reg_window->setStyleSheet(QString::fromUtf8("background-color:rgb(245, 245, 245);\n"
""));
        horizontalLayout = new QHBoxLayout(reg_window);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, -1, -1);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_Confirm = new QLabel(reg_window);
        label_Confirm->setObjectName(QString::fromUtf8("label_Confirm"));
        label_Confirm->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));

        gridLayout->addWidget(label_Confirm, 7, 0, 1, 1);

        label_Name = new QLabel(reg_window);
        label_Name->setObjectName(QString::fromUtf8("label_Name"));
        label_Name->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));

        gridLayout->addWidget(label_Name, 2, 0, 1, 1);

        label_Password = new QLabel(reg_window);
        label_Password->setObjectName(QString::fromUtf8("label_Password"));
        label_Password->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));

        gridLayout->addWidget(label_Password, 6, 0, 1, 1);

        confirmLineEdit = new QLineEdit(reg_window);
        confirmLineEdit->setObjectName(QString::fromUtf8("confirmLineEdit"));
        confirmLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(confirmLineEdit, 7, 1, 1, 2);

        label_Welcome = new QLabel(reg_window);
        label_Welcome->setObjectName(QString::fromUtf8("label_Welcome"));
        label_Welcome->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));
        label_Welcome->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_Welcome, 0, 1, 1, 2);

        pushButtonBack = new QPushButton(reg_window);
        pushButtonBack->setObjectName(QString::fromUtf8("pushButtonBack"));
        pushButtonBack->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     background-color: rgb(80, 108, 200);\n"
"	color: white;\n"
"border: 1px black;\n"
"\n"
"     border-radius: 4px;\n"
"	font: 63 8pt \"Yu Gothic UI Semibold\";\n"
"width:117px;\n"
"height:26px;\n"
"}\n"
"QPushButton:hover{\n"
"border: 1px solid rgb(255, 255, 255);\n"
"}"));

        gridLayout->addWidget(pushButtonBack, 9, 2, 1, 1);

        label_Surname = new QLabel(reg_window);
        label_Surname->setObjectName(QString::fromUtf8("label_Surname"));
        label_Surname->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));

        gridLayout->addWidget(label_Surname, 3, 0, 1, 1);

        emailLineEdit = new QLineEdit(reg_window);
        emailLineEdit->setObjectName(QString::fromUtf8("emailLineEdit"));
        emailLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(emailLineEdit, 1, 1, 1, 2);

        label_Email = new QLabel(reg_window);
        label_Email->setObjectName(QString::fromUtf8("label_Email"));
        label_Email->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));

        gridLayout->addWidget(label_Email, 1, 0, 1, 1);

        nameLineEdit = new QLineEdit(reg_window);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(nameLineEdit, 2, 1, 1, 2);

        label_Company_bio = new QLabel(reg_window);
        label_Company_bio->setObjectName(QString::fromUtf8("label_Company_bio"));
        label_Company_bio->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));

        gridLayout->addWidget(label_Company_bio, 5, 0, 1, 1);

        passwordLineEdit = new QLineEdit(reg_window);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(passwordLineEdit, 6, 1, 1, 2);

        surnameLineEdit = new QLineEdit(reg_window);
        surnameLineEdit->setObjectName(QString::fromUtf8("surnameLineEdit"));
        surnameLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(surnameLineEdit, 3, 1, 1, 2);

        companyNameLineEdit = new QLineEdit(reg_window);
        companyNameLineEdit->setObjectName(QString::fromUtf8("companyNameLineEdit"));
        companyNameLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(companyNameLineEdit, 4, 1, 1, 2);

        label_Company_name = new QLabel(reg_window);
        label_Company_name->setObjectName(QString::fromUtf8("label_Company_name"));
        label_Company_name->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));

        gridLayout->addWidget(label_Company_name, 4, 0, 1, 1);

        companyBioLineEdit = new QLineEdit(reg_window);
        companyBioLineEdit->setObjectName(QString::fromUtf8("companyBioLineEdit"));
        companyBioLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(companyBioLineEdit, 5, 1, 1, 2);

        label_Error = new QLabel(reg_window);
        label_Error->setObjectName(QString::fromUtf8("label_Error"));
        label_Error->setLayoutDirection(Qt::LeftToRight);
        label_Error->setStyleSheet(QString::fromUtf8("color: red;\n"
"font: 63 8pt \"Yu Gothic UI Semibold\";"));
        label_Error->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_Error, 8, 1, 1, 1);

        pushButtonSignIn = new QPushButton(reg_window);
        pushButtonSignIn->setObjectName(QString::fromUtf8("pushButtonSignIn"));
        pushButtonSignIn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        gridLayout->addWidget(pushButtonSignIn, 9, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 8, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(reg_window);

        QMetaObject::connectSlotsByName(reg_window);
    } // setupUi

    void retranslateUi(QWidget *reg_window)
    {
        reg_window->setWindowTitle(QApplication::translate("reg_window", "Form", nullptr));
        label_Confirm->setText(QApplication::translate("reg_window", "Confirm password:", nullptr));
        label_Name->setText(QApplication::translate("reg_window", "Name:", nullptr));
        label_Password->setText(QApplication::translate("reg_window", "Password:", nullptr));
        label_Welcome->setText(QApplication::translate("reg_window", "Registration", nullptr));
        pushButtonBack->setText(QApplication::translate("reg_window", "Back", nullptr));
        label_Surname->setText(QApplication::translate("reg_window", "Surname:", nullptr));
        label_Email->setText(QApplication::translate("reg_window", "Email:", nullptr));
        label_Company_bio->setText(QApplication::translate("reg_window", "Company bio:", nullptr));
        label_Company_name->setText(QApplication::translate("reg_window", "Company name:", nullptr));
        label_Error->setText(QString());
        pushButtonSignIn->setText(QApplication::translate("reg_window", "Sign In", nullptr));
    } // retranslateUi

};

namespace Ui {
    class reg_window: public Ui_reg_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REG_WINDOW_H
