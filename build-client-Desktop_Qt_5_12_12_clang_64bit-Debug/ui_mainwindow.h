/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout;
    QLabel *role;
    QLabel *name;
    QLabel *surname;
    QLabel *email;
    QLabel *email_;
    QLabel *role_;
    QLabel *company_;
    QLabel *name_;
    QLabel *company;
    QLabel *surname_;
    QPushButton *add_user_button;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QPushButton *newProjetButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QFormLayout *formLayout;
    QVBoxLayout *project_lay;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QFormLayout *formLayout_3;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *messages;
    QPushButton *pushButton;
    QLabel *label;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *message;
    QPushButton *send_message;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *chatButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *projectsButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *accButton;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1150, 700);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget:tab-bar\n"
"{\n"
"	background-color:rgb(176, 222, 240);\n"
"	alignment:center;\n"
"	height:0px;\n"
"	\n"
"}\n"
""));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tab_2->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));
        verticalLayout_6 = new QVBoxLayout(tab_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        role = new QLabel(tab_2);
        role->setObjectName(QString::fromUtf8("role"));
        role->setLayoutDirection(Qt::LeftToRight);
        role->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 20pt \"Arial Black\";"));
        role->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(role, 6, 0, 1, 1);

        name = new QLabel(tab_2);
        name->setObjectName(QString::fromUtf8("name"));
        name->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 20pt \"Arial Black\";"));
        name->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(name, 1, 0, 1, 1);

        surname = new QLabel(tab_2);
        surname->setObjectName(QString::fromUtf8("surname"));
        surname->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 20pt \"Arial Black\";"));
        surname->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(surname, 2, 0, 1, 1);

        email = new QLabel(tab_2);
        email->setObjectName(QString::fromUtf8("email"));
        email->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 20pt \"Arial Black\";"));
        email->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(email, 3, 0, 1, 1);

        email_ = new QLabel(tab_2);
        email_->setObjectName(QString::fromUtf8("email_"));
        email_->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 20pt \"Arial Black\";"));

        gridLayout->addWidget(email_, 3, 1, 1, 1);

        role_ = new QLabel(tab_2);
        role_->setObjectName(QString::fromUtf8("role_"));
        role_->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 20pt \"Arial Black\";"));

        gridLayout->addWidget(role_, 6, 1, 1, 1);

        company_ = new QLabel(tab_2);
        company_->setObjectName(QString::fromUtf8("company_"));
        company_->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 20pt \"Arial Black\";"));

        gridLayout->addWidget(company_, 5, 1, 1, 1);

        name_ = new QLabel(tab_2);
        name_->setObjectName(QString::fromUtf8("name_"));
        name_->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 20pt \"Arial Black\";"));

        gridLayout->addWidget(name_, 1, 1, 1, 1);

        company = new QLabel(tab_2);
        company->setObjectName(QString::fromUtf8("company"));
        company->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 20pt \"Arial Black\";"));
        company->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(company, 5, 0, 1, 1);

        surname_ = new QLabel(tab_2);
        surname_->setObjectName(QString::fromUtf8("surname_"));
        surname_->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 20pt \"Arial Black\";"));

        gridLayout->addWidget(surname_, 2, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout);

        add_user_button = new QPushButton(tab_2);
        add_user_button->setObjectName(QString::fromUtf8("add_user_button"));
        add_user_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     background-color: rgb(80, 108, 200);\n"
"	color: white;\n"
"border: 1px black;\n"
"\n"
"     border-radius: 4px;\n"
"	font: 63 20pt \"Yu Gothic UI Semibold\";\n"
"width:326px;\n"
"height:40px;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"border: 1px solid rgb(255, 255, 255);\n"
"}"));

        verticalLayout_6->addWidget(add_user_button);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        newProjetButton = new QPushButton(tab);
        newProjetButton->setObjectName(QString::fromUtf8("newProjetButton"));
        newProjetButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"background-color: rgb(80, 108, 200);\n"
"	color: white;\n"
"border: 1px black;\n"
"     border-radius: 4px;\n"
"	height:26px;\n"
"	font: 63 10pt \"Yu Gothic UI Semibold\";\n"
"}\n"
"\n"
"\n"
"QPushButton:hover{\n"
"border: 1px solid rgb(255, 255, 255);\n"
"}"));

        verticalLayout->addWidget(newProjetButton);

        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"background-color: rgb(255, 255, 255);\n"
"	color: rgb(80, 108, 200);\n"
"border: 1px solid rgb(80, 108, 200);\n"
"     border-radius: 4px;\n"
"	height:26px;\n"
"	font: 63 8pt \"Yu Gothic UI Semibold\";\n"
"\n"
"}\n"
"QPushButton:hover{\n"
"border: 1px solid rgb(102, 137, 254)\n"
"}"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1078, 501));
        formLayout = new QFormLayout(scrollAreaWidgetContents);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignCenter);
        project_lay = new QVBoxLayout();
        project_lay->setObjectName(QString::fromUtf8("project_lay"));

        formLayout->setLayout(0, QFormLayout::SpanningRole, project_lay);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tab_3->setStyleSheet(QString::fromUtf8("background-color:rgb(247, 247, 247)"));
        verticalLayout_3 = new QVBoxLayout(tab_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scrollArea_2 = new QScrollArea(tab_3);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollArea_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 1078, 503));
        scrollAreaWidgetContents_3->setStyleSheet(QString::fromUtf8("QLabel{\n"
"color: rgb(80, 108, 200);\n"
"font:13px;\n"
"qproperty-alignment: AlignCenter;\n"
"}\n"
"QPushButton{\n"
"color: rgb(80, 108, 200);\n"
"font:13px \"Arial Black\";;\n"
"background-color: white;\n"
"border-radius: 4px;\n"
"border: 0.5px solid  rgb(80, 108, 200);\n"
"\n"
"\n"
"}\n"
"\n"
""));
        formLayout_3 = new QFormLayout(scrollAreaWidgetContents_3);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_3->setItem(0, QFormLayout::LabelRole, verticalSpacer);

        messages = new QVBoxLayout();
        messages->setObjectName(QString::fromUtf8("messages"));
        pushButton = new QPushButton(scrollAreaWidgetContents_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        messages->addWidget(pushButton);

        label = new QLabel(scrollAreaWidgetContents_3);
        label->setObjectName(QString::fromUtf8("label"));

        messages->addWidget(label);


        formLayout_3->setLayout(1, QFormLayout::SpanningRole, messages);

        scrollArea_2->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_3->addWidget(scrollArea_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        message = new QLineEdit(tab_3);
        message->setObjectName(QString::fromUtf8("message"));
        message->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"     border-radius: 4px;\n"
"background-color: white;\n"
"height:24px;\n"
""));

        horizontalLayout_4->addWidget(message);

        send_message = new QPushButton(tab_3);
        send_message->setObjectName(QString::fromUtf8("send_message"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(200);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(send_message->sizePolicy().hasHeightForWidth());
        send_message->setSizePolicy(sizePolicy1);
        send_message->setMaximumSize(QSize(200, 25));
        send_message->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"background-color: rgb(80, 108, 200);\n"
"	color: white;\n"
"border: 1px black;\n"
"     border-radius: 4px;\n"
"	height:26px;\n"
"	width: 200px;\n"
"	font: 63 10pt \"Yu Gothic UI Semibold\";\n"
"}\n"
"\n"
"\n"
"QPushButton:hover{\n"
"border: 1px solid rgb(255, 255, 255);\n"
"}"));

        horizontalLayout_4->addWidget(send_message);


        verticalLayout_3->addLayout(horizontalLayout_4);

        tabWidget->addTab(tab_3, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        chatButton = new QPushButton(centralwidget);
        chatButton->setObjectName(QString::fromUtf8("chatButton"));
        chatButton->setStyleSheet(QString::fromUtf8("\n"
"background-color: transparent;\n"
"width:10px;\n"
"height:60px;\n"
"image: url(:img/chat.png);\n"
"background: none;\n"
"border: none;\n"
"background-repeat: none;\n"
""));

        horizontalLayout_2->addWidget(chatButton);

        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        projectsButton = new QPushButton(centralwidget);
        projectsButton->setObjectName(QString::fromUtf8("projectsButton"));
        projectsButton->setStyleSheet(QString::fromUtf8("\n"
"background-color: transparent;\n"
"width:40px;\n"
"height:60px;\n"
"image: url(:img/project.png);\n"
"background: none;\n"
"border: none;\n"
"background-repeat: none;\n"
""));

        horizontalLayout_2->addWidget(projectsButton);

        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        accButton = new QPushButton(centralwidget);
        accButton->setObjectName(QString::fromUtf8("accButton"));
        accButton->setStyleSheet(QString::fromUtf8("\n"
"background-color: transparent;\n"
"width:40px;\n"
"height:60px;\n"
"image: url(:img/ls1.png);\n"
"background: none;\n"
"border: none;\n"
"background-repeat: none;\n"
""));

        horizontalLayout_2->addWidget(accButton);

        horizontalSpacer_4 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        role->setText(QApplication::translate("MainWindow", "Role:", nullptr));
        name->setText(QApplication::translate("MainWindow", "Name:", nullptr));
        surname->setText(QApplication::translate("MainWindow", "Surname:", nullptr));
        email->setText(QApplication::translate("MainWindow", "Email:", nullptr));
        email_->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        role_->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        company_->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        name_->setText(QApplication::translate("MainWindow", "t", nullptr));
        company->setText(QApplication::translate("MainWindow", "Company name:", nullptr));
        surname_->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        add_user_button->setText(QApplication::translate("MainWindow", "Add user to company", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Chat", nullptr));
        newProjetButton->setText(QApplication::translate("MainWindow", "Add new project", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Projects", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        label->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        message->setText(QString());
        send_message->setText(QApplication::translate("MainWindow", "Send Message", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", nullptr));
        chatButton->setText(QString());
        projectsButton->setText(QString());
        accButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
