/********************************************************************************
** Form generated from reading UI file 'projectwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTWINDOW_H
#define UI_PROJECTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectWindow
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *TODO;
    QLabel *DONE;
    QVBoxLayout *task_in_progress;
    QScrollArea *task_in_progress_scroll_area;
    QWidget *scrollAreaWidgetContents_4;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *task_in_progress_layout;
    QVBoxLayout *task_to_do;
    QScrollArea *task_to_do_scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *task_to_do_layout;
    QPushButton *project_chat;
    QVBoxLayout *task_done;
    QScrollArea *task_done_scroll_area;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *task_done_layout;
    QLabel *INPROGRESS;
    QLabel *project_name;
    QPushButton *settings;

    void setupUi(QDialog *ProjectWindow)
    {
        if (ProjectWindow->objectName().isEmpty())
            ProjectWindow->setObjectName(QString::fromUtf8("ProjectWindow"));
        ProjectWindow->resize(689, 440);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProjectWindow->sizePolicy().hasHeightForWidth());
        ProjectWindow->setSizePolicy(sizePolicy);
        ProjectWindow->setMinimumSize(QSize(689, 440));
        ProjectWindow->setMaximumSize(QSize(689, 440));
        ProjectWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(251, 251, 251)"));
        gridLayout_2 = new QGridLayout(ProjectWindow);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        TODO = new QLabel(ProjectWindow);
        TODO->setObjectName(QString::fromUtf8("TODO"));
        TODO->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"background-color: white;\n"
"border-radius: 4px;\n"
"border: 0.5px solid  rgb(80, 108, 200);\n"
"font: 87 10pt \"Arial Black\";"));
        TODO->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(TODO, 2, 0, 1, 1);

        DONE = new QLabel(ProjectWindow);
        DONE->setObjectName(QString::fromUtf8("DONE"));
        DONE->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"background-color: white;\n"
"border-radius: 4px;\n"
"border: 0.5px solid  rgb(80, 108, 200);\n"
"font: 87 10pt \"Arial Black\";"));
        DONE->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(DONE, 2, 2, 1, 1);

        task_in_progress = new QVBoxLayout();
        task_in_progress->setObjectName(QString::fromUtf8("task_in_progress"));
        task_in_progress_scroll_area = new QScrollArea(ProjectWindow);
        task_in_progress_scroll_area->setObjectName(QString::fromUtf8("task_in_progress_scroll_area"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(208);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(task_in_progress_scroll_area->sizePolicy().hasHeightForWidth());
        task_in_progress_scroll_area->setSizePolicy(sizePolicy1);
        task_in_progress_scroll_area->setMinimumSize(QSize(208, 0));
        task_in_progress_scroll_area->setMaximumSize(QSize(16777215, 10000));
        task_in_progress_scroll_area->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-radius: 8px;\n"
"border: 0.5px solid rgb(80, 108, 200);\n"
""));
        task_in_progress_scroll_area->setWidgetResizable(true);
        task_in_progress_scroll_area->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 206, 340));
        scrollAreaWidgetContents_4->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);"));
        verticalLayoutWidget_2 = new QWidget(scrollAreaWidgetContents_4);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 211, 341));
        task_in_progress_layout = new QVBoxLayout(verticalLayoutWidget_2);
        task_in_progress_layout->setObjectName(QString::fromUtf8("task_in_progress_layout"));
        task_in_progress_layout->setContentsMargins(0, 0, 0, 0);
        task_in_progress_scroll_area->setWidget(scrollAreaWidgetContents_4);

        task_in_progress->addWidget(task_in_progress_scroll_area);


        gridLayout->addLayout(task_in_progress, 4, 1, 1, 1);

        task_to_do = new QVBoxLayout();
        task_to_do->setSpacing(1);
        task_to_do->setObjectName(QString::fromUtf8("task_to_do"));
        task_to_do_scrollArea = new QScrollArea(ProjectWindow);
        task_to_do_scrollArea->setObjectName(QString::fromUtf8("task_to_do_scrollArea"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(126);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(task_to_do_scrollArea->sizePolicy().hasHeightForWidth());
        task_to_do_scrollArea->setSizePolicy(sizePolicy2);
        task_to_do_scrollArea->setMaximumSize(QSize(10000, 16777215));
        task_to_do_scrollArea->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-radius: 8px;\n"
"border: 0.5px solid rgb(80, 108, 200);"));
        task_to_do_scrollArea->setWidgetResizable(true);
        task_to_do_scrollArea->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 206, 340));
        scrollAreaWidgetContents_2->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);"));
        verticalLayoutWidget = new QWidget(scrollAreaWidgetContents_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 211, 341));
        task_to_do_layout = new QVBoxLayout(verticalLayoutWidget);
        task_to_do_layout->setObjectName(QString::fromUtf8("task_to_do_layout"));
        task_to_do_layout->setContentsMargins(0, 0, 0, 0);
        task_to_do_scrollArea->setWidget(scrollAreaWidgetContents_2);

        task_to_do->addWidget(task_to_do_scrollArea);


        gridLayout->addLayout(task_to_do, 4, 0, 1, 1);

        project_chat = new QPushButton(ProjectWindow);
        project_chat->setObjectName(QString::fromUtf8("project_chat"));
        project_chat->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     background-color: rgb(80, 108, 200);\n"
"	color: white;\n"
"border: 1px black;\n"
"\n"
"     border-radius: 4px;\n"
"	font: 63 10pt \"Yu Gothic UI Semibold\";\n"
"width:210px;\n"
"height:26px;\n"
"}\n"
"QPushButton:hover{\n"
"border: 1px solid rgb(255, 255, 255);\n"
"}"));

        gridLayout->addWidget(project_chat, 0, 0, 1, 1);

        task_done = new QVBoxLayout();
        task_done->setSpacing(7);
        task_done->setObjectName(QString::fromUtf8("task_done"));
        task_done_scroll_area = new QScrollArea(ProjectWindow);
        task_done_scroll_area->setObjectName(QString::fromUtf8("task_done_scroll_area"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(task_done_scroll_area->sizePolicy().hasHeightForWidth());
        task_done_scroll_area->setSizePolicy(sizePolicy3);
        task_done_scroll_area->setMinimumSize(QSize(208, 0));
        task_done_scroll_area->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-radius: 8px;\n"
"border: 0.5px solid rgb(80, 108, 200);"));
        task_done_scroll_area->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 206, 340));
        scrollAreaWidgetContents_3->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);"));
        verticalLayoutWidget_3 = new QWidget(scrollAreaWidgetContents_3);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(0, 0, 211, 341));
        task_done_layout = new QVBoxLayout(verticalLayoutWidget_3);
        task_done_layout->setObjectName(QString::fromUtf8("task_done_layout"));
        task_done_layout->setContentsMargins(0, 0, 0, 0);
        task_done_scroll_area->setWidget(scrollAreaWidgetContents_3);

        task_done->addWidget(task_done_scroll_area);


        gridLayout->addLayout(task_done, 4, 2, 1, 1);

        INPROGRESS = new QLabel(ProjectWindow);
        INPROGRESS->setObjectName(QString::fromUtf8("INPROGRESS"));
        INPROGRESS->setMaximumSize(QSize(16777215, 20));
        INPROGRESS->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"background-color: white;\n"
"border-radius: 4px;\n"
"border: 0.5px solid  rgb(80, 108, 200);\n"
"font: 87 10pt \"Arial Black\";"));
        INPROGRESS->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(INPROGRESS, 2, 1, 1, 1);

        project_name = new QLabel(ProjectWindow);
        project_name->setObjectName(QString::fromUtf8("project_name"));
        project_name->setMaximumSize(QSize(16777215, 20));
        project_name->setStyleSheet(QString::fromUtf8("color: rgb(80, 108, 200);\n"
"font: 87 10pt \"Arial Black\";"));
        project_name->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(project_name, 0, 1, 1, 1);

        settings = new QPushButton(ProjectWindow);
        settings->setObjectName(QString::fromUtf8("settings"));
        settings->setMaximumSize(QSize(16777215, 40));
        settings->setStyleSheet(QString::fromUtf8("\n"
"background-color: transparent;\n"
"width:40px;\n"
"height:60px;\n"
"image: url(:img/settings.png);\n"
"background: none;\n"
"border: none;\n"
"background-repeat: none;\n"
""));

        gridLayout->addWidget(settings, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(ProjectWindow);

        QMetaObject::connectSlotsByName(ProjectWindow);
    } // setupUi

    void retranslateUi(QDialog *ProjectWindow)
    {
        ProjectWindow->setWindowTitle(QApplication::translate("ProjectWindow", "Dialog", nullptr));
        TODO->setText(QApplication::translate("ProjectWindow", "TO DO", nullptr));
        DONE->setText(QApplication::translate("ProjectWindow", "DONE", nullptr));
        project_chat->setText(QApplication::translate("ProjectWindow", "Chat", nullptr));
        INPROGRESS->setText(QApplication::translate("ProjectWindow", "IN PROGRESS", nullptr));
        project_name->setText(QApplication::translate("ProjectWindow", "Project Name", nullptr));
        settings->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ProjectWindow: public Ui_ProjectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTWINDOW_H
