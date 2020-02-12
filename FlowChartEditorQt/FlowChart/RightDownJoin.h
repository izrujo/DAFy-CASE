/******************************************************************
* 파일 이름 : RightDownJoin.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일 
*******************************************************************/

#ifndef _RIGHTDOWNJOIN_H
#define _RIGHTDOWNJOIN_H

#include "Line.h"

class RightDownJoin : public Line{
public:
	RightDownJoin(Long x, Long y, Long width, Long height,  Long width2 = RIGHTDOWNJOIN_WIDTH, Long height2 = RIGHTDOWNJOIN_HEIGHT, 
		DWORD backGroundColor = BACKGROUNDCOLOR, PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));
	~RightDownJoin();
	RightDownJoin(const RightDownJoin& source);
	RightDownJoin& operator =(const RightDownJoin& source);

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
	
	void ReSize( Long _width, Long _height, Long _width2, Long _height2);

	virtual BOOL IsIncluded(CDC *dc, POINT point);
	virtual BOOL IsIncluded(Painter *painter, POINT point);
	virtual BOOL IsIncluded(Painter *painter, const RECT& rect);

	virtual int GetHitCode( Painter *painter, const CPoint& point, const CRgn& region );

	virtual void Copy(Shape *object);

	Long GetWidth2() const;
	Long GetHeight2() const;

	virtual void GetLine(char (*line));
	virtual bool Identify( SHAPE identify );
	virtual bool IsStyle(Long style);

	virtual Long CenterOfGravityY() const;
	virtual Long CenterOfGravityX() const;

	virtual void DrawSelectionMarkers( CDC* dc, ScrollController *scrollController);
	virtual void DrawSelectionMarkers( Painter* painter, ScrollController *scrollController);

	virtual void GetSelectionMarkerRect( UINT marker, CRect *rect);
	void GetAttribute(Attribute *attribute);

private:
	Long width2;
	Long height2;
};

inline bool RightDownJoin::Identify( SHAPE identify ){
	return ( identify == LINE || identify == RIGHTDOWNJOIN)?( true ):( false );
}

inline Long RightDownJoin::GetWidth2() const{
	return this->width2;
}

inline Long RightDownJoin::GetHeight2() const{
	return this->height2;
}

inline Long RightDownJoin::CenterOfGravityY() const{	
	return y + height;
}

inline Long RightDownJoin::CenterOfGravityX() const{
	return x + width;
}
#endif// _RIGHTDOWNJOIN_H