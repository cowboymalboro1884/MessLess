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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_reg_window
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label_Password;
    QPushButton *pushButtonSignIn;
    QLineEdit *passwordLineEdit;
    QLineEdit *nameLineEdit;
    QLabel *label_Confirm;
    QLineEdit *confirmLineEdit;
    QLabel *label_Name;
    QLabel *label_Welcome;

    void setupUi(QWidget *reg_window)
    {
        if (reg_window->objectName().isEmpty())
            reg_window->setObjectName(QString::fromUtf8("reg_window"));
        reg_window->setWindowModality(Qt::NonModal);
        reg_window->resize(350, 192);
        reg_window->setMinimumSize(QSize(350, 192));
        reg_window->setMaximumSize(QSize(350, 192));
        horizontalLayout = new QHBoxLayout(reg_window);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_Password = new QLabel(reg_window);
        label_Password->setObjectName(QString::fromUtf8("label_Password"));

        gridLayout->addWidget(label_Password, 2, 0, 1, 1);

        pushButtonSignIn = new QPushButton(reg_window);
        pushButtonSignIn->setObjectName(QString::fromUtf8("pushButtonSignIn"));

        gridLayout->addWidget(pushButtonSignIn, 4, 0, 1, 3);

        passwordLineEdit = new QLineEdit(reg_window);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));

        gridLayout->addWidget(passwordLineEdit, 2, 1, 1, 2);

        nameLineEdit = new QLineEdit(reg_window);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        gridLayout->addWidget(nameLineEdit, 1, 1, 1, 2);

        label_Confirm = new QLabel(reg_window);
        label_Confirm->setObjectName(QString::fromUtf8("label_Confirm"));

        gridLayout->addWidget(label_Confirm, 3, 0, 1, 1);

        confirmLineEdit = new QLineEdit(reg_window);
        confirmLineEdit->setObjectName(QString::fromUtf8("confirmLineEdit"));

        gridLayout->addWidget(confirmLineEdit, 3, 1, 1, 2);

        label_Name = new QLabel(reg_window);
        label_Name->setObjectName(QString::fromUtf8("label_Name"));

        gridLayout->addWidget(label_Name, 1, 0, 1, 1);

        label_Welcome = new QLabel(reg_window);
        label_Welcome->setObjectName(QString::fromUtf8("label_Welcome"));
        label_Welcome->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_Welcome, 0, 1, 1, 2);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(reg_window);

        QMetaObject::connectSlotsByName(reg_window);
    } // setupUi

    void retranslateUi(QWidget *reg_window)
    {
        reg_window->setWindowTitle(QApplication::translate("reg_window", "Form", nullptr));
        label_Password->setText(QApplication::translate("reg_window", "Password:", nullptr));
        pushButtonSignIn->setText(QApplication::translate("reg_window", "Sign In", nullptr));
        label_Confirm->setText(QApplication::translate("reg_window", "Confirm password:", nullptr));
        label_Name->setText(QApplication::translate("reg_window", "Name:", nullptr));
        label_Welcome->setText(QApplication::translate("reg_window", "Registration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class reg_window: public Ui_reg_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REG_WINDOW_H
