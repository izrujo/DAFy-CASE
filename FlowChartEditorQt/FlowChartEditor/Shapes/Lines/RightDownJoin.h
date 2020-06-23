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
	RightDownJoin(float x, float y, float width, float height, float width2 = RIGHTDOWNJOIN_WIDTH, float height2 = RIGHTDOWNJOIN_HEIGHT,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~RightDownJoin();
	RightDownJoin(const RightDownJoin& source);
	RightDownJoin& operator =(const RightDownJoin& source);

	virtual bool IsEqual(const NShape& other);
	virtual bool IsNotEqual(const NShape& other);

	virtual bool operator ==(const NShape& other);
	virtual bool operator !=(const NShape& other);

	virtual void DrawActiveShape(GObject *painter);

	virtual void Accept(FlowChartVisitor *draw);

	virtual NShape* Clone();

	virtual QRegion GetRegion();
	virtual QRegion GetRegion(Long thickness);
	virtual QRegion GetSelectionMarkerAllRegion();

	void ReSize(float width, float height, float width2, float height2);

	virtual bool IsIncluded(QPointF point);
	virtual bool IsIncluded(const QRectF& rect);

	virtual int GetHitCode(const QPointF& point, const QRegion& region);

	virtual void Copy(NShape *object);

	float GetWidth2() const;
	float GetHeight2() const;

	virtual void GetLine(char(*line));
	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual float CenterOfGravityY() const;
	virtual float CenterOfGravityX() const;

	virtual void DrawSelectionMarkers(GObject *painter, ScrollController *scrollController);

	virtual void GetSelectionMarkerRect(int marker, QRectF *rect);
	void GetAttribute(Attribute *attribute);

private:
	float width2;
	float height2;
};

inline bool RightDownJoin::Identify(SHAPE identify) {
	return (identify == LINE || identify == RIGHTDOWNJOIN) ? (true) : (false);
}

inline float RightDownJoin::GetWidth2() const {
	return this->width2;
}

inline float RightDownJoin::GetHeight2() const {
	return this->height2;
}

inline float RightDownJoin::CenterOfGravityY() const {
	return this->y + this->height;
}

inline float RightDownJoin::CenterOfGravityX() const {
	return this->x + this->width;
}
#endif// _RIGHTDOWNJOIN_H