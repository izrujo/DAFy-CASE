#ifndef _TUTORIALFORM_H
#define _TUTORIALFORM_H

#include <QtWidgets/QFrame>
#include "Array.h"

class Template;
class Painter;
class FlowChart;
class FlowChartFont;
class TextRegion;
class Tutorial;
class TutorialMark;
class TutorialController;

class TutorialForm : public QFrame
{
	Q_OBJECT

public:
	TutorialForm(QWidget *parent = Q_NULLPTR);
	~TutorialForm();
protected:
	void paintEvent(QPaintEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	void focusOutEvent(QFocusEvent *event);
	void focusInEvent(QFocusEvent *event);
public:
	Template *lists;
	Painter *painter;
	FlowChart *sample;
	Tutorial *main;
	TutorialMark *current;
	Tutorial *lastConcrete;
	TutorialController *tutorialController;
};

#endif //_TUTORIALFORM_H