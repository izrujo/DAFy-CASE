/********************************************************************************
** Form generated from reading UI file 'Notepad.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEPAD_H
#define UI_NOTEPAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>

namespace NotepadUi {

class Ui_NotepadClass
{
public:

    void setupUi(QFrame *NotepadUi__NotepadClass)
    {
        if (NotepadUi__NotepadClass->objectName().isEmpty())
            NotepadUi__NotepadClass->setObjectName(QString::fromUtf8("NotepadUi__NotepadClass"));
        NotepadUi__NotepadClass->resize(600, 400);
        NotepadUi__NotepadClass->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-color: rgba(255, 255, 255, 0);"));

        retranslateUi(NotepadUi__NotepadClass);

        QMetaObject::connectSlotsByName(NotepadUi__NotepadClass);
    } // setupUi

    void retranslateUi(QFrame *NotepadUi__NotepadClass)
    {
        NotepadUi__NotepadClass->setWindowTitle(QCoreApplication::translate("NotepadUi::NotepadClass", "Notepad", nullptr));
    } // retranslateUi

};

} // namespace NotepadUi

namespace NotepadUi {
namespace Ui {
    class NotepadClass: public Ui_NotepadClass {};
} // namespace Ui
} // namespace NotepadUi

#endif // UI_NOTEPAD_H
