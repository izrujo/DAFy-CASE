/******************************************************************
* 파일 이름 : RightDownJoin.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#ifndef _RIGHTDOWNJOIN_H
#define _RIGHTDOWNJOIN_H

#include "Line.h"

class RightDownJoin : public Line {
public:
	RightDownJoin(Long x, Long y, Long width, Long height, Long width2 = RIGHTDOWNJOIN_WIDTH, Long height2 = RIGHTDOWNJOIN_HEIGHT,
		QColor backGroundColor = QColor(255, 255, 255), QPen borderLine = QPen(Qt::SolidLine),
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~RightDownJoin();
	RightDownJoin(const RightDownJoin& source);
	RightDownJoin& operator =(const RightDownJoin& source);

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

	virtual int GetHitCode(const QPoint& point, const QRegion& region);

	virtual void Copy(Shape *object);

	Long GetWidth2() const;
	Long GetHeight2() const;

	virtual void GetLine(char(*line));
	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual Long CenterOfGravityY() const;
	virtual Long CenterOfGravityX() const;

	virtual void DrawSelectionMarkers(GObject *painter, ScrollController *scrollController);

	virtual void GetSelectionMarkerRect(int marker, QRect *rect);
	void GetAttribute(Attribute *attribute);

private:
	Long width2;
	Long height2;
};

inline bool RightDownJoin::Identify(SHAPE identify) {
	return (identify == LINE || identify == RIGHTDOWNJOIN) ? (true) : (false);
}

inline Long RightDownJoin::GetWidth2() const {
	return this->width2;
}

inline Long RightDownJoin::GetHeight2() const {
	return this->height2;
}

inline Long RightDownJoin::CenterOfGravityY() const {
	return this->y + this->height;
}

inline Long RightDownJoin::CenterOfGravityX() const {
	return this->x + this->width;
}
#endif// _RIGHTDOWNJOIN_H