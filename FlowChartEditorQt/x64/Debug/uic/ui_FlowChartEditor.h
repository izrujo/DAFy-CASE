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

namespace FlowChartEditorUi {

	class Ui_FlowChartEditorClass
	{
	public:

		void setupUi(QWidget *FlowChartEditorUi__FlowChartEditorClass)
		{
			if (FlowChartEditorUi__FlowChartEditorClass->objectName().isEmpty())
				FlowChartEditorUi__FlowChartEditorClass->setObjectName(QString::fromUtf8("FlowChartEditorUi__FlowChartEditorClass"));
			FlowChartEditorUi__FlowChartEditorClass->resize(600, 400);
			FlowChartEditorUi__FlowChartEditorClass->setStyleSheet(QString::fromUtf8("QMenuBar {\n"
				"    background-color: white;\n"
				"    spacing: 3px; /* spacing between menu bar items */\n"
				"	border-bottom: 1px solid gray; \n"
				"}\n"
				"background-color: rgb(0, 0, 0);"));

			retranslateUi(FlowChartEditorUi__FlowChartEditorClass);

			QMetaObject::connectSlotsByName(FlowChartEditorUi__FlowChartEditorClass);
		} // setupUi

		void retranslateUi(QWidget *FlowChartEditorUi__FlowChartEditorClass)
		{
			FlowChartEditorUi__FlowChartEditorClass->setWindowTitle(QCoreApplication::translate("FlowChartEditorUi::FlowChartEditorClass", "FlowChartEditor", nullptr));
		} // retranslateUi

	};

} // namespace FlowChartEditorUi

namespace FlowChartEditorUi {
	namespace Ui {
		class FlowChartEditorClass : public Ui_FlowChartEditorClass {};
	} // namespace Ui
} // namespace FlowChartEditorUi

#endif // UI_FLOWCHARTEDITOR_H
