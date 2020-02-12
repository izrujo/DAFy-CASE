/******************************************************************
* 파일 이름 : Join.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일 
*******************************************************************/

#ifndef _JOIN_H
#define _JOIN_H

#include "Line.h"

class Join : public Line{
public:
	Join(Long x, Long y, Long width, Long height, Long height2, DWORD backGroundColor = BACKGROUNDCOLOR,
			PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));
	~Join();
	Join(const Join& source);
	Join& operator =(const Join& source);

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

	void ReSize( Long _width, Long _height, Long _height2);
				
	virtual BOOL IsIncluded(CDC *dc, POINT point);
	virtual BOOL IsIncluded(Painter *painter, POINT point);
	virtual BOOL IsIncluded(Painter *painter, const RECT& rect);

	Long GetHeight2() const;

	virtual void Copy(Shape *object);
	virtual void GetSelectionMarkerRect( UINT marker, CRect *rect );
	virtual int GetHitCode( Painter *painter, const CPoint& point, const CRgn& region );

	virtual void GetLine(char (*line));
	virtual bool Identify( SHAPE identify );
	virtual bool IsStyle(Long style);

	virtual Long CenterOfGravityY() const;
	virtual Long CenterOfGravityX() const;

	virtual void DrawSelectionMarkers( CDC* dc, ScrollController *scrollController);
	virtual void DrawSelectionMarkers( Painter* painter, ScrollController *scrollController);
	void GetAttribute(Attribute *attribute);
private:
	Long height2;
};

inline bool Join::Identify( SHAPE identify ){
	return ( identify == LINE || identify == JOIN )?( true ):( false );
}

inline Long Join::GetHeight2() const{
	return this->height2;
}

inline Long Join::CenterOfGravityY() const{	
	return ( height >= 0 )?(  y + height ):( y );
}

inline Long Join::CenterOfGravityX() const{
	//return ( height >= 0 )?( x ):( x + width);
	return x + width/2;
}

#endif // _JOIN_H