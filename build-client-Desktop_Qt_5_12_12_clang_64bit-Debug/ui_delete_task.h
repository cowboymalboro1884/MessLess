/********************************************************************************
** Form generated from reading UI file 'delete_task.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETE_TASK_H
#define UI_DELETE_TASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeleteTask
{
public:

    void setupUi(QWidget *DeleteTask)
    {
        if (DeleteTask->objectName().isEmpty())
            DeleteTask->setObjectName(QString::fromUtf8("DeleteTask"));
        DeleteTask->resize(400, 300);

        retranslateUi(DeleteTask);

        QMetaObject::connectSlotsByName(DeleteTask);
    } // setupUi

    void retranslateUi(QWidget *DeleteTask)
    {
        DeleteTask->setWindowTitle(QApplication::translate("DeleteTask", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeleteTask: public Ui_DeleteTask {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETE_TASK_H
