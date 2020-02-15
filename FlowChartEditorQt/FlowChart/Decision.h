/******************************************************************
* 파일 이름 : Decision.h
* 기능 : 판단기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/

#ifndef _DECISION_H
#define _DECISION_H

#include "Symbol.h"

class Decision : public Symbol {
public:
	Decision(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), QPen borderLine = QPen(Qt::SolidLine),
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~Decision();
	Decision(const Decision& source);
	Decision& operator =(const Decision& source);

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

	//virtual void DrawSelectionMarkers(Painter* painter, ScrollController *scrollController);
};

inline bool Decision::Identify(SHAPE identify) {
	return (identify == DECISION || identify == SYMBOL) ? (true) : (false);
}

#endif// _DECISION_H