#ifndef _RECTANGLEREGION_H
#define _RECTANGLEREGION_H

#include "Shape.h"

using FlowChartShape::Shape;

class RectangleRegion : public Shape {
public:
	RectangleRegion(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));

	virtual ~RectangleRegion();

	RectangleRegion(const RectangleRegion& source);
	RectangleRegion& operator =(const RectangleRegion& source);

	//void Draw(CDC *dc);
	//void Draw(Painter *painter);

	virtual void Accept(FlowChartVisitor *draw) {}; //Draw() 없애고 이거 만들기
	virtual Shape* Clone();

	virtual void GetRegion(QRegion *region) {};
	virtual void GetRegion(Long thickness, QRegion *region) {};

	virtual bool IsIncluded(QPoint point);
};

#endif //_RECTANGLEREGION_H