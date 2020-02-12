/******************************************************************
* 파일 이름 : PunchedCard.h
* 기능 : 입력기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일 
*******************************************************************/

#ifndef _PUNCHEDCARD_H
#define _PUNCHEDCARD_H

#include "Symbol.h"


class PunchedCard : public Symbol{
public:
	PunchedCard(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
			PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));
	~PunchedCard();

	PunchedCard(const PunchedCard& source);
	PunchedCard& operator =(const PunchedCard& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	//virtual void Draw(CDC *dc);
	//virtual void Draw(Painter *painter);

	virtual void Accept( FlowChartVisitor *draw);

	virtual Shape* Clone();

	//virtual void GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom);
	//virtual void GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom);
	//virtual void GetFormattingArea(Long *left, Long *right);

	virtual void GetRegion(CDC *dc, CRgn *region);
	virtual void GetRegion(Painter *painter, CRgn *region);
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region);
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region);

	virtual BOOL IsIncluded(CDC *dc, POINT point);
	virtual BOOL IsIncluded(Painter *painter, POINT point);
	virtual BOOL IsIncluded(Painter *painter, const RECT& rect);

	void GetAttribute(Attribute *attribute);

	virtual void GetLine(char (*line));
	virtual bool Identify( SHAPE identify );
	virtual bool IsStyle(Long style);

	virtual void DrawSelectionMarkers( CDC* dc , ScrollController *scrollController);
	virtual void DrawSelectionMarkers( Painter* painter, ScrollController *scrollController );
};

inline bool PunchedCard::Identify( SHAPE identify ){
	return ( identify == SYMBOL || identify == PUNCHEDCARD)?( true ):( false );
}

#endif //_PUNCHEDCARD_H
