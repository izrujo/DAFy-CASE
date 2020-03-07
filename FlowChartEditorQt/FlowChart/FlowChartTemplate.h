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
	LONG mode;
	FlowChartShape::Shape *flowChartTemplate;
	FlowChartShape::Shape *oldShapeSelected;
protected:
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnDestroy();
	//afx_msg void OnPaint();
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point); // 마우스 왼쪽 버튼 다운
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//DECLARE_MESSAGE_MAP()          //윈32에서 ON_COMMAND ON_NOTIFY 같은것을 정의
};

#endif // _FLOWCHARTTEMPLATE_H
