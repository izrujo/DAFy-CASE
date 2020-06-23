#ifndef _WINDOWPIN_H
#define _WINDOWPIN_H

#include "Shape.h"

class WindowPin : public NShape {
public:
	WindowPin(float x, float y, float width, float height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	virtual ~WindowPin();

	WindowPin(const WindowPin& source);
	WindowPin& operator =(const WindowPin& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual NShape* Clone();

	virtual QRegion GetRegion() { QRegion region; return region; };
	virtual QRegion GetRegion(Long thickness) { QRegion region; return region; };

	void SetIsPinned(bool isPinned);

	bool GetIsPinned() const;
private:
	bool isPinned;
};

inline bool WindowPin::GetIsPinned() const {
	return this->isPinned;
}

#endif //_WINDOWPIN_H