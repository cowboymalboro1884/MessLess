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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton_2;
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
    QWidget *messages;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *messages_scroll;
    QHBoxLayout *horizontalLayout_4;
    QTextEdit *message;
    QPushButton *send_button;
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
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
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
        gridLayout = new QGridLayout(tab_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 0, 1, 1);

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
"	font: 63 8pt \"Yu Gothic UI Semibold\";\n"
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1098, 523));
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
        scrollArea_2->setStyleSheet(QString::fromUtf8("background-color:rgb(252, 252, 252)"));
        scrollArea_2->setWidgetResizable(true);
        messages = new QWidget();
        messages->setObjectName(QString::fromUtf8("messages"));
        messages->setGeometry(QRect(0, 0, 1098, 522));
        verticalLayout_5 = new QVBoxLayout(messages);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        messages_scroll = new QVBoxLayout();
        messages_scroll->setObjectName(QString::fromUtf8("messages_scroll"));

        verticalLayout_5->addLayout(messages_scroll);

        scrollArea_2->setWidget(messages);

        verticalLayout_3->addWidget(scrollArea_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        message = new QTextEdit(tab_3);
        message->setObjectName(QString::fromUtf8("message"));
        sizePolicy.setHeightForWidth(message->sizePolicy().hasHeightForWidth());
        message->setSizePolicy(sizePolicy);
        message->setMaximumSize(QSize(1000, 25));
        message->setStyleSheet(QString::fromUtf8("height:50px;\n"
"background-color:white;"));

        horizontalLayout_4->addWidget(message);

        send_button = new QPushButton(tab_3);
        send_button->setObjectName(QString::fromUtf8("send_button"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(200);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(send_button->sizePolicy().hasHeightForWidth());
        send_button->setSizePolicy(sizePolicy1);
        send_button->setMaximumSize(QSize(200, 25));
        send_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"background-color: rgb(80, 108, 200);\n"
"	color: white;\n"
"border: 1px black;\n"
"     border-radius: 4px;\n"
"	height:26px;\n"
"	width: 200px;\n"
"	font: 63 8pt \"Yu Gothic UI Semibold\";\n"
"}\n"
"\n"
"\n"
"QPushButton:hover{\n"
"border: 1px solid rgb(255, 255, 255);\n"
"}"));

        horizontalLayout_4->addWidget(send_button);


        verticalLayout_3->addLayout(horizontalLayout_4);

        tabWidget->addTab(tab_3, QString());

        verticalLayout_2->addWidget(tabWidget);

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


        verticalLayout_2->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Chat", nullptr));
        newProjetButton->setText(QApplication::translate("MainWindow", "Add new project", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Projects", nullptr));
        send_button->setText(QApplication::translate("MainWindow", "Send Message", nullptr));
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
