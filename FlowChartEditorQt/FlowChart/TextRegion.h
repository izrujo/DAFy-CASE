#ifndef _TEXTREGION_H
#define _TEXTREGION_H

#include "Shape.h"

class TextRegion : public Shape {
public:
	TextRegion(Long x, Long y, Long width, Long height, 
		QColor backGroundColor = QColor(255, 255, 255), QPen borderLine = QPen(Qt::SolidLine),
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));

	virtual ~TextRegion();

	TextRegion(const TextRegion& source);
	TextRegion& operator =(const TextRegion& source);

	//void Draw(Painter *painter);

	virtual void Accept(FlowChartVisitor *draw) {};
	virtual Shape* Clone();

	virtual void GetRegion(Painter *painter, QRegion *region) {};
	virtual void GetRegion(Painter *painter, Long thickness, QRegion *region) {};

	virtual bool IsIncluded(Painter *painter, QPoint point);
};

#endif //_TEXTREGION_H