/********************************************************************************
** Form generated from reading UI file 'PreviewForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEWFORM_H
#define UI_PREVIEWFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>

QT_BEGIN_NAMESPACE

class Ui_PreviewFormClass
{
public:

    void setupUi(QFrame *PreviewFormClass)
    {
        if (PreviewFormClass->objectName().isEmpty())
			PreviewFormClass->setObjectName(QString::fromUtf8("PreviewFormClass"));
		PreviewFormClass->resize(1200, 875);

        retranslateUi(PreviewFormClass);

        QMetaObject::connectSlotsByName(PreviewFormClass);
    } // setupUi

    void retranslateUi(QFrame *PreviewFormClass)
    {
		PreviewFormClass->setWindowTitle(QApplication::translate("PreviewFormClass", "PreviewForm", nullptr));
    } // retranslateUi

};

namespace Ui_PreviewForm {
    class PreviewFormClass : public Ui_PreviewFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEWFORM_H
