#ifndef _TUTORIALFORM_H
#define _TUTORIALFORM_H

#include <QtWidgets/QFrame>
#include "Array.h"
#include "Shape.h"
using namespace FlowChartShape;

class GObject;
class TextRegion;
class Tutorial;
class TutorialController;

class TutorialForm : public QFrame
{
	Q_OBJECT

public:
	TutorialForm(QWidget *parent = Q_NULLPTR);
protected:
	void closeEvent(QCloseEvent *event);
	void paintEvent(QPaintEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	void focusOutEvent(QFocusEvent *event);
	void focusInEvent(QFocusEvent *event);
public:
	FlowChartShape::Shape *lists;
	GObject *painter;
	FlowChartShape::Shape *sample;
	Tutorial *main;
	FlowChartShape::Shape *current;
	Tutorial *lastConcrete;
	TutorialController *tutorialController;
};

#endif //_TUTORIALFORM_H