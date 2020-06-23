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
	LeftDown(float x, float y, float width, float height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~LeftDown();
	LeftDown(const LeftDown& source);
	LeftDown& operator =(const LeftDown& source);

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

	virtual bool IsIncluded(QPointF point);
	virtual bool IsIncluded(const QRectF& rect);

	virtual void GetSelectionMarkerRect(int marker, QRectF *rect);
	virtual int GetHitCode(const QPointF& point, const QRegion& region);

	virtual void GetLine(char(*line));
	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual float CenterOfGravityX() const;

	virtual void DrawSelectionMarkers(GObject *painter, ScrollController *scrollController);

	void GetAttribute(Attribute *attribute);
};

inline bool LeftDown::Identify(SHAPE identify) {
	return (identify == LINE || identify == LEFTDOWN) ? (true) : (false);
}

inline float LeftDown::CenterOfGravityX() const {
	return this->x;
}

#endif // _LEFTDOWN_H