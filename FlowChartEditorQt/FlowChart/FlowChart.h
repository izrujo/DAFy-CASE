/******************************************************************
* 파일 이름 : FlowChart.h
* 기능 : 순서도 컨트롤 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#ifndef _FLOWCHART_H
#define _FLOWCHART_H

#include "Block.h"

typedef signed long int Long;

class FlowChartVisitor;
class GObject;

class FlowChart : public Block {
public:
	FlowChart(Long capacity = 30);
	FlowChart(const FlowChart& source);
	virtual ~FlowChart();
	FlowChart& operator=(const FlowChart& source);

	virtual void DrawActiveShape(GObject *painter);
	virtual void Accept(FlowChartVisitor *draw);

	virtual NShape* Clone();

	virtual QRegion GetRegion() { QRegion region; return region; };
	virtual QRegion GetRegion(Long thickness) { QRegion region; return region; };

	QRect GetRange();
};

//Long CompareShapeAddress(void *one, void *other);
//Long CompareCoordinateForFlowChart(void *one, void *other);

#endif //_FLOWCHART_H
