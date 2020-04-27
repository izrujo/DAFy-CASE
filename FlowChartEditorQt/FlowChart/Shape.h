/******************************************************************
* 파일 이름 : NShape.h
* 기능 : 도형(기호,선)의 추상화 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/

#ifndef _NSHAPE_H
#define _NSHAPE_H

#include "String.h" //path 설정

#include <qpoint.h>
#include <qcolor.h>
#include <qpen.h>
#include <qcursor.h>

class ScrollController;

// 기호 관련 매크로들

#define ID_TERMINAL				40001
#define ID_PREPARATION			40002
#define ID_PUNCHEDCARD		40003
#define ID_PROCESS				40004
#define ID_DECISION				40005
#define ID_DOCUMENT			40006
#define ID_ARROW					40007
#define ID_LEFTDOWN				40008
#define ID_RIGHTDOWN			40009
#define ID_JOIN						40010
#define ID_REPEATTRUE			40011
#define ID_REPEATFALSE			40012
#define ID_RIGHTDOWNJOIN	40013
#define ID_INPUTOUTPUT     	40014

enum SHAPE {
	ALL = 0, SYMBOL = 1, LINE = 2, TERMINAL = 4, PREPARATION = 8, PUNCHEDCARD = 16, PROCESS = 32, DECISION = 64,
	DOCUMENT = 128, INPUTOUTPUT = 256, ARROW = 512, LEFTDOWN = 1024, RIGHTDOWN = 2048,
	JOIN = 4096, REPEATTRUE = 8196, REPEATFALSE = 16384, RIGHTDOWNJOIN = 32768
};

enum ATTRIBUTE { POINT_IN, POINT_OUT, POINT_TRUE, POINT_FALSE };

enum DECISION_ { NONE = 0, SELECTION = 1, ITERATION = 2 };

enum Direction { RIGHT = 0, LEFT = 1 };
enum PenStyle { SOLID, DASH, DOT, DASHDOT, DASHDOTDOT, INSIEDFRAME };

// 선택 관련 매크로들
#define HIT_NONE				   0
#define HIT_BODY					   1
#define HIT_TOPLEFT			       2
#define HIT_TOPMIDDLE		       3
#define HIT_TOPRIGHT			   4
#define HIT_BOTTOMLEFT		   5
#define HIT_BOTTOMMIDDLE	   6
#define HIT_BOTTOMRIGHT	   7
#define HIT_LEFTMIDDLE		   8
#define HIT_RIGHTMIDDLE		   9
#define HIT_IN                       10
#define HIT_OUT                    11
#define HIT_HANDLE               12
#define HIT_TRUE                   13
#define HIT_FALSE                  14

// ************* 디폴트 값들이 필요한가 ? ********************
// 속성 디폴트 값
#define BACKGROUNDCOLOR 10
#define BORDERLINE 0
#define BORDERCOLOR 10
#define FONT_HEIGHT 12

// 기호 디폴트 값
#define REPEATFALSE_WIDTH 30
#define REPEATFALSE_HEIGHT 40

#define REPEATTRUE_WIDTH 30
#define REPEATTRUE_HEIGHT 30

#define RIGHTDOWNJOIN_WIDTH 30
#define RIGHTDOWNJOIN_HEIGHT 30

#define ANNOTATION_WIDHT 30
#define DIRECTION RIGHT

// 화살표
#define ARROW_SIZE 5

// 라인두께
#define LINETHICKNESS 3

// 선택 박스
#define BOXLENGTH 6 // 박스의 테두리 길이
#define MARKLENGTH 5 // 색칠한 선택 박스 길이
#define BOXSCOPE 7 // 실질적 박스 선택 범위 CRgn 에서 테두리 영역을 못찾기 때문

// 선택박스 최대 개수
#define SELECTIONMARK 8

// 폼 너비 높이
#define FORMWIDTH 100
#define FORMHEIGHT 30

#define BOXVERTECIES 4 // Attribute 에서 사용

class GObject;
class FlowChartVisitor;

class Attribute {
public:
	Attribute();
	~Attribute();

	Attribute(const Attribute& source);
	Attribute& operator = (const Attribute& source);

	bool IsEqual(const Attribute& other);
	bool IsNotEqual(const Attribute& other);

	bool operator == (const Attribute& other);
	bool operator != (const Attribute& other);

	char GetVertexIn() const;
	char GetVertexOut() const;
	char GetVertexTrue() const;
	char GetVertexFalse() const;
	QPoint GetPointIn() const;
	QPoint GetPointOut() const;
	QPoint GetPointTrue() const;
	QPoint GetPointFalse() const;

public:
	char vertexIn;
	char vertexOut;
	char vertexTrue;
	char vertexFalse;
	QPoint pointIn;
	QPoint pointOut;
	QPoint pointTrue;
	QPoint pointFalse;
};

inline char Attribute::GetVertexIn() const {
	return this->vertexIn;
}

inline char Attribute::GetVertexOut() const {
	return this->vertexOut;
}

inline char Attribute::GetVertexTrue() const {
	return this->vertexTrue;
}

inline char Attribute::GetVertexFalse() const {
	return this->vertexFalse;
}

inline QPoint Attribute::GetPointIn() const {
	return this->pointIn;
}

inline QPoint Attribute::GetPointOut() const {
	return this->pointOut;
}

inline QPoint Attribute::GetPointTrue() const {
	return this->pointTrue;
}

inline QPoint Attribute::GetPointFalse() const {
	return this->pointFalse;
}

class NShape {
public:
	NShape();
	NShape(Long x, Long y, Long width, Long height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));

	virtual ~NShape() = 0;

	NShape(const NShape& source);
	NShape& operator=(const NShape& source);

	virtual bool IsEqual(const NShape& other);
	virtual bool IsNotEqual(const NShape& other);

	Long IsUpperThan(const NShape& other);
	Long IsDownThan(const NShape& other);
	Long IsFrontThan(const NShape& other);
	Long IsRearThan(const NShape& other);

	virtual bool operator ==(const NShape& other);
	virtual bool operator !=(const NShape& other);

	void Move(Long x, Long y);
	virtual void ReSize(Long width, Long height);
	void Rewrite(char(*text));

	void Paint(QColor backGroundColor, Qt::PenStyle borderLine, QColor borderColor); //색깔 속성 변경

	virtual void DrawActiveShape(GObject *painter); // 여러 도형 선택시는 이동만 필요함으로 선택박스를 그리지 않는다.

	// Visitor 패턴 적용
	virtual void Accept(FlowChartVisitor *draw) = 0;
	// Prototype 패턴 적용
	virtual NShape* Clone() = 0;

	//마우스 드래그로 여러 도형 한번에 선택시 사용
	virtual QRegion GetRegion() = 0;
	virtual QRegion GetRegion(Long thickness) = 0;

	virtual QRegion GetSelectionMarkerAllRegion();

	virtual void GetAttribute(Attribute *Attribute) {};

	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;
	QColor& GetBackGroundColor() const;
	Qt::PenStyle GetBorderLine() const;
	QColor& GetBorderColor() const;

	String& GetContents() const;

	Long GetLeft() const;
	Long GetTop() const;
	Long GetRight() const;
	Long GetBottom() const;

	// 선택 관련 
	virtual bool IsIncluded(QPoint point) { return false; };
	virtual bool IsIncluded(const QRect& rect) { return false; };

	virtual void Select(bool selected);
	virtual bool IsSelected() const;

	virtual int GetHitCode(QPoint point);
	virtual int GetHitCode(const QPoint& point, const QRegion& region);

	virtual QCursor GetCursor(int hit) const; //QCursor class 존재

	virtual void Copy(NShape *object);

	virtual void GetLine(char(*line)) {};

	virtual Long CenterOfGravityY() const;
	virtual Long CenterOfGravityX() const;

	virtual bool Identify(SHAPE identify) { return false; };
	virtual bool IsStyle(Long style);

	int GetSymbolID(); //190903 DrawingPaper.LButtonDown에서 Creator.Create 사용하기 위함
	int GetLineID(); //191227 Interpreter pattern 적용 중
public:
	static void MakeRectToPoint(QPoint point, QRect *rect);

protected:
	virtual void DrawSelectionMarkers(GObject *painter, ScrollController *scrollController); //painter, scroll 수정 후 고치기
	virtual void GetSelectionMarkerRect(int marker, QRect *rect); //marker - 전처리 선언된 매크로: int로 구분하자.

public: //Block virtual 선언
	virtual Long Attach(NShape *shape);
	virtual Long Insert(Long index, NShape *shape);
	virtual Long Detach(Long index);
	virtual Long Detach(SHAPE identify);
	virtual bool DetachSelectedAll();
	virtual NShape* GetAt(Long index);

	virtual Long Find(NShape* shape);
	virtual Long Find(QPoint point);
	virtual Long Find(Long x, Long y);
	virtual Long Find(QRect rect);
	virtual Long Find(SHAPE identify);
	virtual Long Find(Long fromIndex, SHAPE identify);
	virtual void Find(Long styles, Long* (*indexes), Long *count);

	virtual void Swap(Long toIndex, Long fromIndex);
	virtual void Swap(Long toIndex, NShape *shape);
	virtual void Clear();

	virtual void SelectAll();
	virtual void UnSelectAll();
	virtual void GetSelecteds(Long* (*indexes), Long *count);
	virtual Long CountSelecteds();
	virtual void AscendingSort();
	virtual void DescendingSort();

	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long GetCurrent() const;
protected:
	Long x;
	Long y;
	Long width;
	Long height;
	QColor backGroundColor;
	Qt::PenStyle borderLine;
	QColor borderColor;
	String contents;

	bool isSelected;
};

inline Long NShape::GetX() const {
	return this->x;
}

inline Long NShape::GetY() const {
	return this->y;
}

inline Long NShape::GetWidth() const {
	return this->width;
}

inline Long NShape::GetHeight() const {
	return this->height;
}

inline QColor& NShape::GetBackGroundColor() const {
	return const_cast<QColor&>(this->backGroundColor);
}

inline Qt::PenStyle NShape::GetBorderLine() const {
	return this->borderLine;
}

inline QColor& NShape::GetBorderColor() const {
	return const_cast<QColor&>(this->borderColor);
}

inline String& NShape::GetContents() const {
	return const_cast<String&>(this->contents);
}

inline Long NShape::GetLeft() const {
	return this->x;
}
inline Long NShape::GetTop() const {
	return this->y;
}

inline Long NShape::GetRight() const {
	return (this->x + this->width);
}

inline Long NShape::GetBottom() const {
	return (this->y + this->height);
}

inline bool NShape::IsSelected() const {
	return this->isSelected;
}

inline Long NShape::CenterOfGravityY() const {
	return this->y + this->height / 2;
}

inline Long NShape::CenterOfGravityX() const {
	return this->x + this->width / 2;
}

inline bool NShape::IsStyle(Long style) {
	return (style == ALL) ? (true) : (false);
}


#endif // _NSHAPE_H