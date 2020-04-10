#ifndef _WINDOWPIN_H
#define _WINDOWPIN_H

#include "Shape.h"

class WindowPin : public NShape {
public:
	WindowPin(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	virtual ~WindowPin();

	WindowPin(const WindowPin& source);
	WindowPin& operator =(const WindowPin& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual NShape* Clone();

	virtual void GetRegion(QRegion *region) {};
	virtual void GetRegion(Long thickness, QRegion *region) {};

	void SetIsPinned(bool isPinned);

	bool GetIsPinned() const;
private:
	bool isPinned;
};

inline bool WindowPin::GetIsPinned() const {
	return this->isPinned;
}

#endif //_WINDOWPIN_H