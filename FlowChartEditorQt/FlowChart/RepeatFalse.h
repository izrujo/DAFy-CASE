/******************************************************************
* 파일 이름 : RepeatFalse.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#ifndef _REPEATFALSE_H
#define _REPEATFALSE_H

#include "Line.h"

class RepeatFalse : public Line {
public:
	RepeatFalse(Long x, Long y, Long width, Long height, Long width2 = REPEATFALSE_WIDTH, Long height2 = REPEATFALSE_HEIGHT,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~RepeatFalse();
	RepeatFalse(const RepeatFalse& source);
	RepeatFalse& operator =(const RepeatFalse& source);

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

	void ReSize(Long width, Long height, Long width2, Long height2);

	virtual bool IsIncluded(QPoint point);
	virtual bool IsIncluded(const QRect& rect);

	Long GetWidth2() const;
	Long GetHeight2() const;

	virtual void Copy(NShape *object);
	virtual void GetSelectionMarkerRect(int marker, QRect *rect);
	virtual int GetHitCode(const QPoint& point, const QRegion& region);

	virtual void GetLine(char(*line));
	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual Long CenterOfGravityY() const;
	virtual Long CenterOfGravityX() const;

	virtual void DrawSelectionMarkers(GObject *painter, ScrollController *scrollController);
	void GetAttribute(Attribute *attribute);

private:
	Long width2;
	Long height2;
};

inline bool RepeatFalse::Identify(SHAPE identify) {
	return (identify == LINE || identify == REPEATFALSE) ? (true) : (false);
}

inline Long RepeatFalse::GetWidth2() const
{
	return this->width2;
}

inline Long RepeatFalse::GetHeight2() const
{
	return this->height2;
}

inline Long RepeatFalse::CenterOfGravityY() const
{
	return this->y + this->height2 / 2;
}

inline Long RepeatFalse::CenterOfGravityX() const {
	return this->x + this->width;
}

#endif _REPEATFALSE_H