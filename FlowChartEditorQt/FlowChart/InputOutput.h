// InputOutput.h

#ifndef _INPUTOUTPUT_H
#define _INPUTOUTPUT_H

#include "Symbol.h"

class InputOutput : public Symbol {
public:
	InputOutput(Long x, Long y, Long width, Long height, QColor backGroundColor,
		QPen borderLine, QColor borderColor, String contents = static_cast<String>(""));
	~InputOutput();
	InputOutput(const InputOutput& source);
	InputOutput& operator = (const InputOutput& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();

	virtual void GetRegion(Painter *painter, QRegion *region);
	virtual void GetRegion(Painter *painter, Long thickness, QRegion *region);

	virtual bool IsIncluded(Painter *painter, QPoint point);
	virtual bool IsIncluded(Painter *painter, const QRect& rect);

	void GetAttribute(Attribute *attribute);

	virtual void GetLine(char(*line));

	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	//virtual void DrawSelectionMarkers( Painter* painter, ScrollController *scrollController);
};

inline bool InputOutput::Identify(SHAPE identify) {
	return (identify == SYMBOL || identify == INPUTOUTPUT) ? (true) : (false);
}

#endif //_INPUTOUTPUT_H