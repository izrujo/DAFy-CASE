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
	Process(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), QPen borderLine = QPen(Qt::SolidLine),
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));
	~Process();
	Process(const Process& source);
	Process& operator =(const Process& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	virtual void Accept( FlowChartVisitor *draw);

	virtual Shape* Clone();

	virtual void GetRegion(Painter *painter, QRegion *region);
	virtual void GetRegion(Painter *painter, Long thickness, QRegion *region);

	virtual bool IsIncluded(Painter *painter, QPoint point);
	virtual bool IsIncluded(Painter *painter, const QRect& rect);

	void GetAttribute(Attribute *attribute);

	virtual void GetLine(char (*line));

	virtual bool Identify( SHAPE identify );
	virtual bool IsStyle(Long style);

	//virtual void DrawSelectionMarkers( Painter* painter, ScrollController *scrollController);
};

inline bool Process::Identify( SHAPE identify ){
	return ( identify == SYMBOL || identify == PROCESS )?( true ):( false );
}

#endif// _PROCESS_H