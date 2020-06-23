/******************************************************************
* 파일 이름 : FlowCahrtTemplate.h
* 기능 : 순서도 작성자 컨트롤
* 작성자 : 송윤창
* 작성일자 : 2015년 4월 10일
*******************************************************************/

#ifndef _FLOWCHARTTEMPLATE_H
#define _FLOWCHARTTEMPLATE_H

#include <QtWidgets/QFrame>
#include "../Shapes/Shape.h"
class GObject;

typedef signed long int Long;

class FlowChartTemplate : public QFrame
{
	Q_OBJECT

public:
	enum { DRAWON, DRAWOFF };
public:
	FlowChartTemplate(QWidget *parent = Q_NULLPTR);
	~FlowChartTemplate();
public:
	NShape *shapeSelected;
	GObject *painter;
	int mode;
	NShape *flowChartTemplate;
	NShape *oldShapeSelected;
	
	NShape *windowTitle;
	QColor windowBorderColor;
	NShape *windowPin;
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event); //tracking 설정이 디폴트면 마우스 아무거나 눌렀을 때만 호출됨.
	void mouseReleaseEvent(QMouseEvent *event);
	void focusOutEvent(QFocusEvent *event);
	void focusInEvent(QFocusEvent *event);
	void leaveEvent(QEvent *event);
	void enterEvent(QEvent *event);
	void keyPressEvent(QKeyEvent *event); //DrawingMode, one, two, three, etc.
};

#endif // _FLOWCHARTTEMPLATE_H
