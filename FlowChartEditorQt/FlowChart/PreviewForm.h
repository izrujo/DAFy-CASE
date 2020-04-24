#ifndef _PREVIEWFORM_H
#define _PREVIEWFORM_H

#include <QtWidgets/QFrame>
#include "ui_PreviewForm.h"
#include "Shape.h"

class FlowChartEditor;
class GObject;
class QToolBar;
class QAction;

class PreviewForm : public QFrame 
{
	Q_OBJECT

public:
	PreviewForm(QWidget *parent = Q_NULLPTR, NShape *flowChart = 0);
private:
	Ui_PreviewForm::PreviewFormClass ui;
	
protected:
	void closeEvent(QCloseEvent *event);
	void paintEvent(QPaintEvent *event);

	void CommandRange(string text);
	//void mousePressEvent(QMouseEvent *event);
	//afx_msg void OnCommandRange(UINT uID);
public:
	FlowChartEditor *editor;
	NShape *flowChart;
	NShape *a4Paper;
	GObject *painter;
	
public:
	void CreateToolBar();

	QToolBar *toolBar;
	QAction *print;
	QAction *exit;
};

#endif //_PREVIEWFORM_H