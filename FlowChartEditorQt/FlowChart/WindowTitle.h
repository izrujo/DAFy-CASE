#ifndef _WINDOWTITLE_H
#define _WINDOWTITLE_H

#include "Shape.h"

class WindowTitle : public NShape {
public:
	WindowTitle(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	virtual ~WindowTitle();

	WindowTitle(const WindowTitle& source);
	WindowTitle& operator =(const WindowTitle& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual NShape* Clone();

	virtual QRegion GetRegion() { QRegion region; return region; };
	virtual QRegion GetRegion(Long thickness) { QRegion region; return region; };

	virtual bool IsIncluded(QPoint point);

	void SetIsFocusedAndPinned(bool isFocusedAndPinned);

	bool GetIsFocusedAndPinned() const;
private:
	bool isFocusedAndPinned;
};

inline bool WindowTitle::GetIsFocusedAndPinned() const {
	return this->isFocusedAndPinned;
}

#endif //_WINDOWTITLE_H