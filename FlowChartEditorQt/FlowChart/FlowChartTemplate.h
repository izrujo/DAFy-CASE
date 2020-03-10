/******************************************************************
* 파일 이름 : FlowCahrtTemplate.h
* 기능 : 순서도 작성자 컨트롤
* 작성자 : 송윤창
* 작성일자 : 2015년 4월 10일
*******************************************************************/

#ifndef _FLOWCHARTTEMPLATE_H
#define _FLOWCHARTTEMPLATE_H

#include <QtWidgets/QFrame>
#include "Shape.h"
class Painter;

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
	FlowChartShape::Shape *shapeSelected;
	Painter *painter;
	int mode;
	FlowChartShape::Shape *flowChartTemplate;
	FlowChartShape::Shape *oldShapeSelected;
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event); //tracking 설정이 디폴트면 마우스 아무거나 눌렀을 때만 호출됨.
};

#endif // _FLOWCHARTTEMPLATE_H
