#ifndef _NUMBERBOX_H
#define _NUMBERBOX_H

#include "Shape.h"

class NumberBox : public NShape {
public:
	NumberBox(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));

	virtual ~NumberBox();

	NumberBox(const NumberBox& source);
	NumberBox& operator =(const NumberBox& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual NShape* Clone();

	virtual QRegion GetRegion() { QRegion region; return region; };
	virtual QRegion GetRegion(Long thickness) { QRegion region; return region; };
};

#endif //_NUMBERBOX_H