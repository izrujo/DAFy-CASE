/********************************************************************************
** Form generated from reading UI file 'FlowChartEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLOWCHARTEDITOR_H
#define UI_FLOWCHARTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FlowChartEditorClass
{
public:

    void setupUi(QWidget *FlowChartEditorClass)
    {
        if (FlowChartEditorClass->objectName().isEmpty())
            FlowChartEditorClass->setObjectName(QString::fromUtf8("FlowChartEditorClass"));
		FlowChartEditorClass->setWindowState(Qt::WindowMaximized);
        FlowChartEditorClass->setStyleSheet(QString::fromUtf8("QMenuBar {\n"
"    background-color: white;\n"
"    spacing: 3px; /* spacing between menu bar items */\n"
"	border-bottom: 1px solid gray; \n"
"}\n"
"background-color: rgb(0, 0, 0);"));

        retranslateUi(FlowChartEditorClass);

        QMetaObject::connectSlotsByName(FlowChartEditorClass);
    } // setupUi

    void retranslateUi(QWidget *FlowChartEditorClass)
    {
        FlowChartEditorClass->setWindowTitle(QCoreApplication::translate("FlowChartEditorClass", "FlowChartEditor", nullptr));
    } // retranslateUi

};

namespace Ui_FlowChartEditor {
    class FlowChartEditorClass: public Ui_FlowChartEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLOWCHARTEDITOR_H
