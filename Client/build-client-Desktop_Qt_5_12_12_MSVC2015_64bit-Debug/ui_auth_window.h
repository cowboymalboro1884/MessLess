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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_auth_window
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *labelWelcome;
    QPushButton *loginPushButton;
    QPushButton *registerPushButton;
    QLineEdit *lineEdit_2;
    QLabel *errorMessage;

    void setupUi(QWidget *auth_window)
    {
        if (auth_window->objectName().isEmpty())
            auth_window->setObjectName(QString::fromUtf8("auth_window"));
        auth_window->resize(350, 192);
        auth_window->setMinimumSize(QSize(350, 192));
        auth_window->setMaximumSize(QSize(350, 192));
        horizontalLayout = new QHBoxLayout(auth_window);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(auth_window);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        label_2 = new QLabel(auth_window);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit = new QLineEdit(auth_window);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        labelWelcome = new QLabel(auth_window);
        labelWelcome->setObjectName(QString::fromUtf8("labelWelcome"));
        QFont font;
        font.setKerning(true);
        labelWelcome->setFont(font);
        labelWelcome->setLayoutDirection(Qt::LeftToRight);
        labelWelcome->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelWelcome, 0, 1, 1, 1);

        loginPushButton = new QPushButton(auth_window);
        loginPushButton->setObjectName(QString::fromUtf8("loginPushButton"));

        gridLayout->addWidget(loginPushButton, 5, 0, 1, 2);

        registerPushButton = new QPushButton(auth_window);
        registerPushButton->setObjectName(QString::fromUtf8("registerPushButton"));

        gridLayout->addWidget(registerPushButton, 6, 0, 1, 2);

        lineEdit_2 = new QLineEdit(auth_window);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 1);

        errorMessage = new QLabel(auth_window);
        errorMessage->setObjectName(QString::fromUtf8("errorMessage"));
        errorMessage->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(errorMessage, 4, 0, 1, 2);


        horizontalLayout->addLayout(gridLayout);

        QWidget::setTabOrder(loginPushButton, registerPushButton);

        retranslateUi(auth_window);

        QMetaObject::connectSlotsByName(auth_window);
    } // setupUi

    void retranslateUi(QWidget *auth_window)
    {
        auth_window->setWindowTitle(QApplication::translate("auth_window", "Form", nullptr));
        label->setText(QApplication::translate("auth_window", "Password:", nullptr));
        label_2->setText(QApplication::translate("auth_window", "Login:", nullptr));
#ifndef QT_NO_TOOLTIP
        labelWelcome->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        labelWelcome->setText(QApplication::translate("auth_window", "Authorization", nullptr));
        loginPushButton->setText(QApplication::translate("auth_window", "Log In", nullptr));
        registerPushButton->setText(QApplication::translate("auth_window", "Register", nullptr));
        errorMessage->setText(QApplication::translate("auth_window", "eeee", nullptr));
    } // retranslateUi

};

namespace Ui {
    class auth_window: public Ui_auth_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTH_WINDOW_H
