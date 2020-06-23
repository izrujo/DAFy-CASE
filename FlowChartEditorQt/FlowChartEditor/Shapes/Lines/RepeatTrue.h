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
	RepeatTrue(float x, float y, float width, float height, float width2 = REPEATTRUE_WIDTH, float height2 = REPEATTRUE_HEIGHT,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~RepeatTrue();
	RepeatTrue(const RepeatTrue& source);
	RepeatTrue& operator =(const RepeatTrue& source);

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

	float GetWidth2() const;
	float GetHeight2() const;

	virtual void Copy(NShape *object);
	virtual void GetSelectionMarkerRect(int marker, QRectF *rect);
	virtual int GetHitCode(const QPointF& point, const QRegion& region);

	virtual void GetLine(char(*line));
	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual float CenterOfGravityX() const;

	virtual void DrawSelectionMarkers(GObject *painter, ScrollController *scrollController);
	void GetAttribute(Attribute *attribute);

private:
	float width2;
	float height2;
};

inline bool RepeatTrue::Identify(SHAPE identify) {
	return (identify == LINE || identify == REPEATTRUE) ? (true) : (false);
}

inline float RepeatTrue::GetWidth2() const {
	return this->width2;
}

inline float RepeatTrue::GetHeight2() const {
	return this->height2;
}

inline float RepeatTrue::CenterOfGravityX() const {
	return this->x;
}
#endif _REPEATTRUE_H