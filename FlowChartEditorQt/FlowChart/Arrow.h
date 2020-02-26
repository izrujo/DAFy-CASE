/******************************************************************
* 파일 이름 : Arrow.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#ifndef _ARROW_H
#define _ARROW_H

#include "Line.h"

class Arrow : public Line {
public:
	Arrow(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), QPen borderLine = QPen(Qt::SolidLine),
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~Arrow();
	Arrow(const Arrow& source);
	Arrow& operator =(const Arrow& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	virtual void DrawActiveShape(GObject *painter);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();

	virtual void GetRegion(QRegion *region);
	virtual void GetRegion(Long thickness, QRegion *region);
	virtual void GetSelectionMarkerAllRegion(QRegion *region);

	virtual bool IsIncluded(QPoint point);
	virtual bool IsIncluded(const QRect& rect);

	virtual int GetHitCode(const QPoint& point, const QRegion& region);

	virtual void GetLine(char(*line));

	virtual bool Identify(SHAPE identify);

	virtual void DrawSelectionMarkers(GObject *painter, ScrollController *scrollController);
	virtual void GetSelectionMarkerRect(int marker, QRect *rect);

	void GetAttribute(Attribute *attribute);
	virtual bool IsStyle(Long style);
};

inline bool Arrow::Identify(SHAPE identify) {
	return (identify == LINE || identify == ARROW) ? (true) : (false);
}

#endif // _ARROW_H