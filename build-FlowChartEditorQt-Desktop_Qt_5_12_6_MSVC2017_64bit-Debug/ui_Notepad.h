/********************************************************************************
** Form generated from reading UI file 'Notepad.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEPAD_H
#define UI_NOTEPAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>

QT_BEGIN_NAMESPACE

class Ui_NotepadClass
{
public:

    void setupUi(QFrame *NotepadClass)
    {
        if (NotepadClass->objectName().isEmpty())
            NotepadClass->setObjectName(QString::fromUtf8("NotepadClass"));
        NotepadClass->resize(600, 400);
        NotepadClass->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));

        retranslateUi(NotepadClass);

        QMetaObject::connectSlotsByName(NotepadClass);
    } // setupUi

    void retranslateUi(QFrame *NotepadClass)
    {
        NotepadClass->setWindowTitle(QApplication::translate("NotepadClass", "Notepad", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NotepadClass: public Ui_NotepadClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEPAD_H
