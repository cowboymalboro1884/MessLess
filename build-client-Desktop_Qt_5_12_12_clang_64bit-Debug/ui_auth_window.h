/********************************************************************************
** Form generated from reading UI file 'auth_window.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTH_WINDOW_H
#define UI_AUTH_WINDOW_H

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

class Ui_auth_window
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *errorMessage;
    QPushButton *showPassword;
    QSpacerItem *verticalSpacer;
    QLineEdit *loginLineEdit;
    QLabel *loginLabel;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QPushButton *loginPushButton;
    QPushButton *registerPushButton;
    QLabel *labelWelcome;

    void setupUi(QWidget *auth_window)
    {
        if (auth_window->objectName().isEmpty())
            auth_window->setObjectName(QString::fromUtf8("auth_window"));
        auth_window->resize(350, 192);
        auth_window->setMinimumSize(QSize(350, 192));
        auth_window->setMaximumSize(QSize(350, 192));
        auth_window->setStyleSheet(QString::fromUtf8("background-color:rgb(245, 245, 245);\n"
""));
        horizontalLayout = new QHBoxLayout(auth_window);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, -1, -1);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        errorMessage = new QLabel(auth_window);
        errorMessage->setObjectName(QString::fromUtf8("errorMessage"));
        errorMessage->setStyleSheet(QString::fromUtf8("color: red;\n"
"font: 63 8pt \"Yu Gothic UI Semibold\";"));
        errorMessage->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(errorMessage, 4, 1, 1, 1);

        showPassword = new QPushButton(auth_window);
        showPassword->setObjectName(QString::fromUtf8("showPassword"));
        showPassword->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     background-color: rgb(216, 216, 216);\n"
"border: 1px black;\n"
"     border-radius: 4px;\n"
"	font: 63 8pt \"Yu Gothic UI Semibold\";\n"
"width:93px;\n"
"height:21px;\n"
"}\n"
"QPushButton:hover{\n"
"border: 0.5px solid rgb(0, 170, 255);\n"
"}"));

        gridLayout->addWidget(showPassword, 2, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 23, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 2, 1, 1);

        loginLineEdit = new QLineEdit(auth_window);
        loginLineEdit->setObjectName(QString::fromUtf8("loginLineEdit"));
        loginLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(loginLineEdit, 1, 1, 1, 1);

        loginLabel = new QLabel(auth_window);
        loginLabel->setObjectName(QString::fromUtf8("loginLabel"));
        loginLabel->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));

        gridLayout->addWidget(loginLabel, 1, 0, 1, 1);

        passwordLabel = new QLabel(auth_window);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));

        gridLayout->addWidget(passwordLabel, 2, 0, 1, 1);

        passwordLineEdit = new QLineEdit(auth_window);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;"));

        gridLayout->addWidget(passwordLineEdit, 2, 1, 1, 1);

        loginPushButton = new QPushButton(auth_window);
        loginPushButton->setObjectName(QString::fromUtf8("loginPushButton"));
        loginPushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        gridLayout->addWidget(loginPushButton, 5, 0, 1, 3);

        registerPushButton = new QPushButton(auth_window);
        registerPushButton->setObjectName(QString::fromUtf8("registerPushButton"));
        registerPushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        gridLayout->addWidget(registerPushButton, 6, 0, 1, 3);

        labelWelcome = new QLabel(auth_window);
        labelWelcome->setObjectName(QString::fromUtf8("labelWelcome"));
        QFont font;
        font.setFamily(QString::fromUtf8("Yu Gothic UI Semibold"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(7);
        font.setKerning(true);
        labelWelcome->setFont(font);
        labelWelcome->setLayoutDirection(Qt::LeftToRight);
        labelWelcome->setStyleSheet(QString::fromUtf8("font: 63 8pt \"Yu Gothic UI Semibold\";"));
        labelWelcome->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelWelcome, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        QWidget::setTabOrder(loginPushButton, registerPushButton);

        retranslateUi(auth_window);

        QMetaObject::connectSlotsByName(auth_window);
    } // setupUi

    void retranslateUi(QWidget *auth_window)
    {
        auth_window->setWindowTitle(QApplication::translate("auth_window", "Form", nullptr));
        errorMessage->setText(QApplication::translate("auth_window", "error", nullptr));
        showPassword->setText(QApplication::translate("auth_window", "show", nullptr));
        loginLabel->setText(QApplication::translate("auth_window", "Login:", nullptr));
        passwordLabel->setText(QApplication::translate("auth_window", "Password:", nullptr));
        loginPushButton->setText(QApplication::translate("auth_window", "Log In", nullptr));
        registerPushButton->setText(QApplication::translate("auth_window", "Register", nullptr));
#ifndef QT_NO_TOOLTIP
        labelWelcome->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelWelcome->setText(QApplication::translate("auth_window", "Authorization", nullptr));
    } // retranslateUi

};

namespace Ui {
    class auth_window: public Ui_auth_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTH_WINDOW_H
