/******************************************************************
* 파일 이름 : LeftDown.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#ifndef _LEFTDOWN_H
#define _LEFTDOWN_H

#include "Line.h"

class LeftDown : public Line {
public:
	LeftDown(Long x, Long y, Long width, Long height, QColor backGroundColor,
		QPen borderLine, QColor borderColor, String contents = static_cast<String>(""));
	~LeftDown();
	LeftDown(const LeftDown& source);
	LeftDown& operator =(const LeftDown& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	//virtual void DrawActiveShape(Painter *painter);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();

	virtual void GetRegion(Painter *painter, QRegion *region);
	virtual void GetRegion(Painter *painter, Long thickness, QRegion *region);
	virtual void GetSelectionMarkerAllRegion(QRegion *region);

	virtual bool IsIncluded(Painter *painter, QPoint point);
	virtual bool IsIncluded(Painter *painter, const QRect& rect);

	virtual void GetSelectionMarkerRect(int marker, QRect *rect);
	virtual int GetHitCode(Painter *painter, const QPoint& point, const QRegion& region);

	virtual void GetLine(char(*line));
	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual Long CenterOfGravityX() const;

	//virtual void DrawSelectionMarkers(Painter* painter, ScrollController *scrollController);

	void GetAttribute(Attribute *attribute);
};

inline bool LeftDown::Identify(SHAPE identify) {
	return (identify == LINE || identify == LEFTDOWN) ? (true) : (false);
}

inline Long LeftDown::CenterOfGravityX() const {
	return this->x;
}

#endif // _LEFTDOWN_H