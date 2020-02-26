/******************************************************************
* 파일 이름 : Terminal.h
* 기능 : 단말기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "Symbol.h"

class Terminal : public Symbol {
public:
	Terminal(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), QPen borderLine = QPen(Qt::SolidLine),
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~Terminal();

	Terminal(const Terminal& source);
	Terminal& operator =(const Terminal& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();

	virtual void GetRegion(QRegion *region);
	virtual void GetRegion(Long thickness, QRegion *region);

	virtual bool IsIncluded(QPoint point);
	virtual bool IsIncluded(const QRect& rect);

	void GetAttribute(Attribute *attribute);

	virtual void GetLine(char(*line));
	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual void DrawSelectionMarkers(GObject *painter, ScrollController *scrollController);
};

inline bool Terminal::Identify(SHAPE identify) {
	return (identify == SYMBOL || identify == TERMINAL) ? (true) : (false);
}

#endif //_THERMINAL_H