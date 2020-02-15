#ifndef _NUMBERBOX_H
#define _NUMBERBOX_H

#include "Shape.h"

class NumberBox : public Shape {
public:
	NumberBox(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), QPen borderLine = QPen(Qt::SolidLine),
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));

	virtual ~NumberBox();

	NumberBox(const NumberBox& source);
	NumberBox& operator =(const NumberBox& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();

	virtual void GetRegion(QRegion *region) {};
	virtual void GetRegion(Long thickness, QRegion *region) {};
};

#endif //_NUMBERBOX_H