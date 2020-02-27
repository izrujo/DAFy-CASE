/******************************************************************
* 파일 이름 : RepeatTure.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#ifndef _REPEATTRUE_H
#define _REPEATTRUE_H

#include "Line.h"

class RepeatTrue : public Line {
public:
	RepeatTrue(Long x, Long y, Long width, Long height, Long width2 = REPEATTRUE_WIDTH, Long height2 = REPEATTRUE_HEIGHT,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~RepeatTrue();
	RepeatTrue(const RepeatTrue& source);
	RepeatTrue& operator =(const RepeatTrue& source);

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

	void ReSize(Long width, Long height, Long width2, Long height2);

	virtual bool IsIncluded(QPoint point);
	virtual bool IsIncluded(const QRect& rect);

	Long GetWidth2() const;
	Long GetHeight2() const;

	virtual void Copy(Shape *object);
	virtual void GetSelectionMarkerRect(int marker, QRect *rect);
	virtual int GetHitCode(const QPoint& point, const QRegion& region);

	virtual void GetLine(char(*line));
	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual Long CenterOfGravityX() const;

	virtual void DrawSelectionMarkers(GObject *painter, ScrollController *scrollController);
	void GetAttribute(Attribute *attribute);

private:
	Long width2;
	Long height2;
};

inline bool RepeatTrue::Identify(SHAPE identify) {
	return (identify == LINE || identify == REPEATTRUE) ? (true) : (false);
}

inline Long RepeatTrue::GetWidth2() const {
	return this->width2;
}

inline Long RepeatTrue::GetHeight2() const {
	return this->height2;
}

inline Long RepeatTrue::CenterOfGravityX() const {
	return this->x;
}
#endif _REPEATTRUE_H