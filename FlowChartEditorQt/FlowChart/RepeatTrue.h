/******************************************************************
* 파일 이름 : RepeatTure.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일 
*******************************************************************/

#ifndef _REPEATTRUE_H
#define _REPEATTRUE_H

#include "Line.h"

class RepeatTrue: public Line{
public:
	RepeatTrue(Long x, Long y, Long width, Long height, Long width2 = REPEATTRUE_WIDTH, Long height2 = REPEATTRUE_HEIGHT, DWORD backGroundColor = BACKGROUNDCOLOR, 
		PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));
	~RepeatTrue();
	RepeatTrue(const RepeatTrue& source);
	RepeatTrue& operator =(const RepeatTrue& source);

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
		
	void ReSize(Long _width, Long _height, Long _width2, Long _height2);
		
	virtual BOOL IsIncluded(CDC *dc, POINT point);
	virtual BOOL IsIncluded(Painter *painter, POINT point);
	virtual BOOL IsIncluded(Painter *painter, const RECT& rect);

	Long GetWidth2() const;
	Long GetHeight2() const;

	virtual void Copy(Shape *object);
	virtual void GetSelectionMarkerRect( UINT marker, CRect *rect );
	virtual int GetHitCode( Painter *painter, const CPoint& point, const CRgn& region );

	virtual void GetLine(char (*line));
	virtual bool Identify( SHAPE identify );
	virtual bool IsStyle(Long style);

	virtual Long CenterOfGravityX() const;

	virtual void DrawSelectionMarkers( CDC* dc, ScrollController *scrollController );
	virtual void DrawSelectionMarkers( Painter* painter, ScrollController *scrollController );
	void GetAttribute(Attribute *attribute);

private:
	Long width2;
	Long height2;
};

inline bool RepeatTrue::Identify( SHAPE identify){
	return ( identify == LINE || identify == REPEATTRUE)?( true ):( false );
}

inline Long RepeatTrue::GetWidth2() const{
	return this->width2;
}

inline Long RepeatTrue::GetHeight2() const{
	return this->height2;
}

inline Long RepeatTrue::CenterOfGravityX() const{
	return x;
}
#endif _REPEATTRUE_H