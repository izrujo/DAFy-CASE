/******************************************************************
* 파일 이름 : Preparation.h
* 기능 : 준비기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/

#ifndef _PREPARATION_H
#define _PREPARATION_H

#include "Symbol.h"

class Preparation : public Symbol {
public:
	Preparation(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~Preparation();
	Preparation(const Preparation& source);
	Preparation& operator =(const Preparation& source);

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

inline bool Preparation::Identify(SHAPE identify) {
	return (identify == SYMBOL || identify == PREPARATION) ? (true) : (false);
}

#endif //_PREPARATION_H