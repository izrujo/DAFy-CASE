/******************************************************************
* 파일 이름 : Arrow.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일 
*******************************************************************/

#ifndef _ARROW_H
#define _ARROW_H

#include "Line.h"

class Arrow : public Line{
public:
	Arrow(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
			PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));
	~Arrow();
	Arrow(const Arrow& source);
	Arrow& operator =(const Arrow& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	//virtual void Draw(CDC *dc);
	//virtual void Draw(Painter *painter);
	virtual void DrawActiveShape(CDC *dc);
	virtual void DrawActiveShape(Painter *painter);

	virtual void Accept( FlowChartVisitor *draw);

	virtual Shape* Clone();
	
	//virtual void GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom);

	virtual void GetRegion(CDC *dc, CRgn *region);
	virtual void GetRegion(Painter *painter, CRgn *region);
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region);
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region);
	virtual void GetSelectionMarkerAllRegion( CRgn *region );

	virtual BOOL IsIncluded(CDC *dc, POINT point);
	virtual BOOL IsIncluded(Painter *painter, POINT point);
	virtual BOOL IsIncluded(Painter *painter, const RECT& rect);
		
	virtual int GetHitCode( Painter *painter, const CPoint& point, const CRgn& region );

	virtual void GetLine(char (*line));
		
	virtual bool Identify( SHAPE identify );

	virtual void DrawSelectionMarkers( CDC* dc, ScrollController *scrollController);
	virtual void DrawSelectionMarkers( Painter* painter, ScrollController *scrollController);
	virtual void GetSelectionMarkerRect( UINT marker, CRect *rect );

	void GetAttribute(Attribute *attribute);
	virtual bool IsStyle(Long style);
};

inline bool Arrow::Identify(SHAPE identify){
	return ( identify == LINE || identify == ARROW )?( true ):( false );
}

#endif // _ARROW_H