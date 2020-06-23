// InputOutput.h

#ifndef _INPUTOUTPUT_H
#define _INPUTOUTPUT_H

#include "Symbol.h"

class InputOutput : public Symbol {
public:
	InputOutput(float x, float y, float width, float height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~InputOutput();
	InputOutput(const InputOutput& source);
	InputOutput& operator = (const InputOutput& source);

	virtual bool IsEqual(const NShape& other);
	virtual bool IsNotEqual(const NShape& other);

	virtual bool operator ==(const NShape& other);
	virtual bool operator !=(const NShape& other);

	virtual void Accept(FlowChartVisitor *draw);

	virtual NShape* Clone();

	virtual QRegion GetRegion();
	virtual QRegion GetRegion(Long thickness);

	virtual bool IsIncluded(QPointF point);
	virtual bool IsIncluded(const QRectF& rect);

	void GetAttribute(Attribute *attribute);

	virtual void GetLine(char(*line));

	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual void DrawSelectionMarkers(GObject *painter, ScrollController *scrollController);
};

inline bool InputOutput::Identify(SHAPE identify) {
	return (identify == SYMBOL || identify == INPUTOUTPUT) ? (true) : (false);
}

#endif //_INPUTOUTPUT_H