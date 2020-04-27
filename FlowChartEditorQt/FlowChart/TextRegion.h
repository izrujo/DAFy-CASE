#ifndef _TEXTREGION_H
#define _TEXTREGION_H

#include "Shape.h"

class TextRegion : public NShape {
public:
	TextRegion(Long x, Long y, Long width, Long height, 
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));

	virtual ~TextRegion();

	TextRegion(const TextRegion& source);
	TextRegion& operator =(const TextRegion& source);

	void Draw(GObject *painter);

	virtual void Accept(FlowChartVisitor *draw) {};
	virtual NShape* Clone();

	virtual QRegion GetRegion() { QRegion region; return region; };
	virtual QRegion GetRegion(Long thickness) { QRegion region; return region; };

	virtual bool IsIncluded(QPoint point);
};

#endif //_TEXTREGION_H