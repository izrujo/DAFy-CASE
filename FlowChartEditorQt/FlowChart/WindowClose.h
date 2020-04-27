#ifndef _WINDOWCLOSE_H
#define _WINDOWCLOSE_H

#include "Shape.h"

class WindowClose : public NShape {
public:
	WindowClose(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	virtual ~WindowClose();

	WindowClose(const WindowClose& source);
	WindowClose& operator =(const WindowClose& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual NShape* Clone();

	virtual QRegion GetRegion() { QRegion region; return region; };
	virtual QRegion GetRegion(Long thickness) { QRegion region; return region; };
private:
	bool isPinned;
};

#endif //_WINDOWCLOSE_H