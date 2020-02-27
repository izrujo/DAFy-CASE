#ifndef _TEXTREGION_H
#define _TEXTREGION_H

#include "Shape.h"

using FlowChartShape::Shape;

class TextRegion : public Shape {
public:
	TextRegion(Long x, Long y, Long width, Long height, 
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));

	virtual ~TextRegion();

	TextRegion(const TextRegion& source);
	TextRegion& operator =(const TextRegion& source);

	void Draw(GObject *painter);

	virtual void Accept(FlowChartVisitor *draw) {};
	virtual Shape* Clone();

	virtual void GetRegion(QRegion *region) {};
	virtual void GetRegion(Long thickness, QRegion *region) {};

	virtual bool IsIncluded(QPoint point);
};

#endif //_TEXTREGION_H