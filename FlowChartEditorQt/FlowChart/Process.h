/******************************************************************
* 파일 이름 : Proess.h
* 기능 : 처리기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일 
*******************************************************************/

#ifndef _PROCESS_H
#define _PROCESS_H

#include "Symbol.h"

class Process : public Symbol{
public:
	Process(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
			PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));
	~Process();
	Process(const Process& source);
	Process operator =(const Process& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	//virtual void Draw(CDC *dc);
	//virtual void Draw(Painter *painter);

	virtual void Accept( FlowChartVisitor *draw);

	virtual Shape* Clone();

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
	virtual void DrawSelectionMarkers( Painter* painter, ScrollController *scrollController);
};

inline bool Process::Identify( SHAPE identify ){
	return ( identify == SYMBOL || identify == PROCESS )?( true ):( false );
}

#endif// _PROCESS_H