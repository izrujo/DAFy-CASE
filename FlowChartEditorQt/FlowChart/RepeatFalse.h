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
	RepeatFalse(Long x, Long y, Long width, Long height, Long width2 = REPEATFALSE_WIDTH, Long height2 = REPEATFALSE_HEIGHT, DWORD backGroundColor = BACKGROUNDCOLOR,
		PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));
	~RepeatFalse();
	RepeatFalse(const RepeatFalse& source);
	RepeatFalse& operator =(const RepeatFalse& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	//virtual void Draw(CDC *dc);
	//virtual void Draw(Painter *painter);
	virtual void DrawActiveShape(CDC *dc);
	virtual void DrawActiveShape(Painter *painter);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();

	//virtual void GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom);

	virtual void GetRegion(CDC *dc, CRgn *region);
	virtual void GetRegion(Painter *painter, CRgn *region);
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region);
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region);
	virtual void GetSelectionMarkerAllRegion(CRgn *region);

	void ReSize(Long _width, Long _height, Long _width2, Long _height2);

	virtual BOOL IsIncluded(CDC *dc, POINT point);
	virtual BOOL IsIncluded(Painter *painter, POINT point);
	virtual BOOL IsIncluded(Painter *painter, const RECT& rect);

	Long GetWidth2() const;
	Long GetHeight2() const;

	virtual void Copy(Shape *object);
	virtual void GetSelectionMarkerRect(UINT marker, CRect *rect);
	virtual int GetHitCode(Painter *painter, const CPoint& point, const CRgn& region);

	virtual void GetLine(char(*line));
	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual Long CenterOfGravityY() const;
	virtual Long CenterOfGravityX() const;

	virtual void DrawSelectionMarkers(CDC* dc, ScrollController *scrollController);
	virtual void DrawSelectionMarkers(Painter* painter, ScrollController *scrollController);
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
	return y + this->height2 / 2;
}

inline Long RepeatFalse::CenterOfGravityX() const {
	return x + width;
}

#endif _REPEATFALSE_H