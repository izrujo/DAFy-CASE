/******************************************************************
* 파일 이름 : Shape.cpp
* 기능 : 도형(기호,선)의 추상화 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
* 수정 : Qt - 20.02.12
*******************************************************************/


#include "Shape.h"
#include "Painter.h"

#include "Document.h"
#include "InputOutput.h"
#include "Preparation.h"
#include "Terminal.h"
#include "Process.h"
#include "PunchedCard.h"
#include "Decision.h"
#include "ScrollController.h"
#include "Scrolls.h"
#include "Arrow.h"
#include "LeftDown.h"
#include "RightDown.h"
#include "Join.h"
#include "RepeatTrue.h"
#include "RepeatFalse.h"
#include "RightDownJoin.h"

//#include <qcursor.h>

Attribute::Attribute() {
	this->vertexIn = ' ';
	this->vertexOut = ' ';
	this->vertexTrue = ' ';
	this->vertexFalse = ' ';

	QPoint initPoint(0, 0);
	this->pointIn = initPoint;
	this->pointOut = initPoint;
	this->pointTrue = initPoint;
	this->pointFalse = initPoint;
}

Attribute::~Attribute() {
}

Attribute::Attribute(const Attribute& source) {
	this->vertexIn = source.vertexIn;
	this->vertexOut = source.vertexOut;
	this->vertexTrue = source.vertexTrue;
	this->vertexFalse = source.vertexFalse;

	this->pointIn = source.pointIn;
	this->pointOut = source.pointOut;
	this->pointTrue = source.pointTrue;
	this->pointFalse = source.pointFalse;
}

Attribute& Attribute::operator = (const Attribute& source) {
	this->vertexIn = source.vertexIn;
	this->vertexOut = source.vertexOut;
	this->vertexTrue = source.vertexTrue;
	this->vertexFalse = source.vertexFalse;

	this->pointIn = source.pointIn;
	this->pointOut = source.pointOut;
	this->pointTrue = source.pointTrue;
	this->pointFalse = source.pointFalse;

	return *this;
}

bool Attribute::IsEqual(const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn == other.vertexIn &&
		this->vertexOut == other.vertexOut &&
		this->vertexTrue == other.vertexTrue &&
		this->vertexFalse == other.vertexFalse &&
		this->pointIn.x() == other.pointIn.x() &&
		this->pointIn.y() == other.pointIn.y() &&
		this->pointOut.x() == other.pointOut.x() &&
		this->pointOut.y() == other.pointOut.y() &&
		this->pointTrue.x() == other.pointTrue.x() &&
		this->pointTrue.y() == other.pointTrue.y() &&
		this->pointFalse.x() == other.pointFalse.x() &&
		this->pointFalse.y() == other.pointFalse.y()) {
		retVO = true;
	}
	return retVO;
}

bool Attribute::IsNotEqual(const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn != other.vertexIn ||
		this->vertexOut != other.vertexOut ||
		this->vertexTrue != other.vertexTrue ||
		this->vertexFalse != other.vertexFalse ||
		this->pointIn.x() != other.pointIn.x() ||
		this->pointIn.y() != other.pointIn.y() ||
		this->pointOut.x() != other.pointOut.x() ||
		this->pointOut.y() != other.pointOut.y() ||
		this->pointTrue.x() != other.pointTrue.x() ||
		this->pointTrue.y() != other.pointTrue.y() ||
		this->pointFalse.x() != other.pointFalse.x() ||
		this->pointFalse.y() != other.pointFalse.y()) {
		retVO = true;
	}
	return retVO;
}

bool Attribute::operator == (const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn == other.vertexIn &&
		this->vertexOut == other.vertexOut &&
		this->vertexTrue == other.vertexTrue &&
		this->vertexFalse == other.vertexFalse &&
		this->pointIn.x() == other.pointIn.x() &&
		this->pointIn.y() == other.pointIn.y() &&
		this->pointOut.x() == other.pointOut.x() &&
		this->pointOut.y() == other.pointOut.y() &&
		this->pointTrue.x() == other.pointTrue.x() &&
		this->pointTrue.y() == other.pointTrue.y() &&
		this->pointFalse.x() == other.pointFalse.x() &&
		this->pointFalse.y() == other.pointFalse.y()) {
		retVO = true;
	}
	return retVO;
}

bool Attribute::operator != (const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn != other.vertexIn ||
		this->vertexOut != other.vertexOut ||
		this->vertexTrue != other.vertexTrue ||
		this->vertexFalse != other.vertexFalse ||
		this->pointIn.x() != other.pointIn.x() ||
		this->pointIn.y() != other.pointIn.y() ||
		this->pointOut.x() != other.pointOut.x() ||
		this->pointOut.y() != other.pointOut.y() ||
		this->pointTrue.x() != other.pointTrue.x() ||
		this->pointTrue.y() != other.pointTrue.y() ||
		this->pointFalse.x() != other.pointFalse.x() ||
		this->pointFalse.y() != other.pointFalse.y()) {
		retVO = true;
	}
	return retVO;
}

Shape::Shape()
	: backGroundColor(QColor(255, 255, 255)),
	borderLine(QPen(Qt::SolidLine)),
	borderColor(QColor(0, 0, 0)),
	contents() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->isSelected = false;
}

Shape::Shape(Long x, Long y, Long width, Long height, QColor backGroundColor,
	QPen borderLine, QColor borderColor, String contents)
	: backGroundColor(backGroundColor),
	borderLine(borderLine),
	borderColor(borderColor),
	contents(contents) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->isSelected = false;
}

Shape::~Shape() {}

Shape::Shape(const Shape& source)
	: backGroundColor(source.backGroundColor),
	borderLine(source.borderLine),
	borderColor(source.borderColor),
	contents(source.contents) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->isSelected = source.isSelected;
}

Shape& Shape::operator=(const Shape& source)
{
	this->x = source.x;
	this->y = source.y;

	this->width = source.width;
	this->height = source.height;

	this->backGroundColor = source.backGroundColor;

	this->borderLine = source.borderLine;
	this->borderColor = source.borderColor;

	this->contents = source.contents;

	this->isSelected = source.isSelected;

	return *this;
}

bool Shape::IsEqual(const Shape& other) {
	bool retVo = false;

	if (this->x == other.x &&
		this->y == other.y &&
		this->width == other.width &&
		this->height == other.height &&
		this->backGroundColor == other.backGroundColor &&
		this->borderLine == other.borderLine &&
		this->borderColor == other.borderColor &&
		this->contents == other.contents) {
		retVo = true;
	}
	return retVo;
}

bool Shape::IsNotEqual(const Shape& other) {
	bool retVo = false;

	if (this->x != other.x ||
		this->y != other.y ||
		this->width != other.width ||
		this->height != other.height ||
		this->backGroundColor != other.backGroundColor ||
		this->borderLine != other.borderLine ||
		this->borderColor != other.borderColor ||
		this->contents != other.contents) {
		retVo = true;
	}
	return retVo;
}

Long Shape::IsUpperThan(const Shape& other) {
	Long retVo;

	if (this->y < other.y)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

Long Shape::IsDownThan(const Shape& other) {
	Long retVo;

	if (this->y > other.y)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

Long Shape::IsFrontThan(const Shape& other) {
	Long retVo;

	if (this->x < other.x)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

Long Shape::IsRearThan(const Shape& other) {
	Long retVo;

	if (this->x > other.x)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

bool Shape::operator ==(const Shape& other) {
	bool retVo = false;

	if (this->x == other.x &&
		this->y == other.y &&
		this->width == other.width &&
		this->height == other.height &&
		this->backGroundColor == other.backGroundColor &&
		this->borderLine == other.borderLine &&
		this->borderColor == other.borderColor &&
		this->contents == other.contents) {
		retVo = true;
	}
	return retVo;
}
bool Shape::operator !=(const Shape& other) {
	bool retVo = false;

	if (this->x != other.x ||
		this->y != other.y ||
		this->width != other.width ||
		this->height != other.height ||
		this->backGroundColor != other.backGroundColor ||
		this->borderLine != other.borderLine ||
		this->borderColor != other.borderColor ||
		this->contents != other.contents) {
		retVo = true;
	}
	return retVo;
}

void Shape::Move(Long x, Long y) {
	this->x = x;
	this->y = y;
}

void Shape::ReSize(Long width, Long height) {
	this->width = width;
	this->height = height;
}

void Shape::Paint(QColor backGroundColor, QPen borderLine, QColor borderColor) {
	this->backGroundColor = backGroundColor;
	this->borderLine = borderLine;
	this->borderColor = borderColor;
}

/*
void Shape::DrawActiveShape(Painter *painter) {
	POINT point[4];
	point[0].x = x - LINETHICKNESS;
	point[0].y = y - LINETHICKNESS;
	point[1].x = x + width + LINETHICKNESS;
	point[1].y = y - LINETHICKNESS;
	point[2].x = x + width + LINETHICKNESS;
	point[2].y = y + height + LINETHICKNESS;
	point[3].x = x - LINETHICKNESS;
	point[3].y = y + height + LINETHICKNESS;

	painter->DrawPolygon(point, BOXVERTECIES);
}
*/

//////////////////////////////////////////////////////////////////////////
// 선택 관련 : 2015-11-23

void Shape::Select(bool selected) {
	this->isSelected = selected;
}

int Shape::GetHitCode(Painter *painter, QPoint point) {
	QRegion region;
	this->GetRegion(painter, &region);
	return GetHitCode(painter, point, region);
}

int Shape::GetHitCode(Painter *painter, const QPoint& point, const QRegion& region) {
	int result = HIT_NONE;
	if (region.contains(point)) {
		result = HIT_BODY;
	}

	QRect rectSelect;
	GetSelectionMarkerRect(HIT_TOPLEFT, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_TOPLEFT;
	}
	GetSelectionMarkerRect(HIT_TOPMIDDLE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_TOPMIDDLE;
	}
	GetSelectionMarkerRect(HIT_TOPRIGHT, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_TOPRIGHT;
	}
	GetSelectionMarkerRect(HIT_BOTTOMLEFT, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_BOTTOMLEFT;
	}
	GetSelectionMarkerRect(HIT_BOTTOMMIDDLE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_BOTTOMMIDDLE;
	}
	GetSelectionMarkerRect(HIT_BOTTOMRIGHT, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_BOTTOMRIGHT;
	}
	GetSelectionMarkerRect(HIT_LEFTMIDDLE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_LEFTMIDDLE;
	}
	GetSelectionMarkerRect(HIT_RIGHTMIDDLE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_RIGHTMIDDLE;
	}
	return result;
}

void Shape::GetSelectionMarkerRect(int marker, QRect *rect)
{
	int x;
	int y;
	switch (marker) {
	case HIT_TOPLEFT:
		x = this->x;
		y = this->y;
		break;
	case HIT_TOPMIDDLE:
		x = this->x + this->width / 2;
		y = this->y;
		break;
	case HIT_TOPRIGHT:
		x = this->x + this->width;
		y = this->y;
		break;
	case HIT_LEFTMIDDLE:
		x = this->x;
		y = this->y + this->height / 2;
		break;
	case HIT_RIGHTMIDDLE:
		x = this->x + this->width;
		y = this->y + this->height / 2;
		break;
	case HIT_BOTTOMLEFT:
		x = this->x;
		y = this->y + this->height;
		break;
	case HIT_BOTTOMMIDDLE:
		x = this->x + this->width / 2;
		y = this->y + this->height;
		break;
	case HIT_BOTTOMRIGHT:
		x = this->x + this->width;
		y = this->y + this->height;
		break;
	}

	rect->setCoords(x - 4, y - 4, x + 5, y + 5);
}

void Shape::GetSelectionMarkerAllRegion(QRegion *region) {
	QRect rect;
	QRegion addRegion;

	Long x = this->x;
	Long y = this->y;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;

	x = this->x + this->width / 2;
	y = this->y;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;


	x = this->x + this->width;
	y = this->y;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;

	x = this->x;
	y = this->y + this->height / 2;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;

	x = this->x + this->width;
	y = this->y + this->height / 2;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;

	x = this->x;
	y = this->y + this->height;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;

	x = this->x + this->width / 2;
	y = this->y + this->height;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;

	x = this->x + this->width;
	y = this->y + this->height;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;
}

QCursor Shape::GetCursor(int hit) const {
	QCursor cursor;
	switch (hit) {
	case HIT_BODY:
		cursor.setShape(Qt::SizeAllCursor);
		break;
	case HIT_TOPLEFT:
		cursor.setShape(Qt::SizeFDiagCursor);
		break;
	case HIT_TOPMIDDLE:
		cursor.setShape(Qt::SizeBDiagCursor);
		break;
	case HIT_TOPRIGHT:
		cursor.setShape(Qt::SizeBDiagCursor);
		break;
	case HIT_BOTTOMLEFT:
		cursor.setShape(Qt::SizeBDiagCursor);
		break;
	case HIT_BOTTOMMIDDLE:
		cursor.setShape(Qt::SizeBDiagCursor);
		break;
	case HIT_BOTTOMRIGHT:
		cursor.setShape(Qt::SizeFDiagCursor);
		break;
	case HIT_LEFTMIDDLE:
		cursor.setShape(Qt::SizeHorCursor);
		break;
	case HIT_RIGHTMIDDLE:
		cursor.setShape(Qt::SizeHorCursor);
		break;
	}

	return cursor;
}

void Shape::Copy(Shape *object) {
	this->x = object->GetX();
	this->y = object->GetY();
	this->width = object->GetWidth();
	this->height = object->GetHeight();
	this->backGroundColor = object->GetBackGroundColor();
	this->borderLine = object->GetBorderLine();
	this->borderColor = object->GetBorderColor();
	this->contents = object->GetContents();

	this->isSelected = object->IsSelected();
}

/*
void Shape::DrawSelectionMarkers(Painter* painter, ScrollController *scrollController)
{
	QRect rectSelect;

	painter->ChangePlaneProperty(BS_SOLID, RGB(0, 0, 255));

	GetSelectionMarkerRect(HIT_TOPLEFT, &rectSelect);
	Long positionX = scrollController->GetScroll(1)->GetPosition();
	Long positionY = scrollController->GetScroll(0)->GetPosition();
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_TOPMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_TOPRIGHT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_BOTTOMLEFT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_BOTTOMMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_BOTTOMRIGHT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_RIGHTMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_LEFTMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);
}
*/

void Shape::MakeRectToPoint(QPoint point, QRect *rect) {
	Long left = point.x() - BOXSCOPE;
	Long top = point.y() - BOXSCOPE;
	Long right = point.x() + BOXSCOPE;
	Long bottom = point.y() + BOXSCOPE;
	rect->setCoords(left, top, right, bottom);
}

void Shape::Rewrite(char(*text)) {
	this->contents = text;
}

int Shape::GetSymbolID() {
	int id = 0;
	if (dynamic_cast<Document*>(this)) {
		id = ID_DOCUMENT;
	}
	else if (dynamic_cast<InputOutput*>(this)) {
		id = ID_INPUTOUTPUT;
	}
	else if (dynamic_cast<Preparation*>(this)) {
		id = ID_PREPARATION;
	}
	else if (dynamic_cast<Terminal*>(this)) {
		id = ID_TERMINAL;
	}
	else if (dynamic_cast<Process*>(this)) {
		id = ID_PROCESS;
	}
	else if (dynamic_cast<PunchedCard*>(this)) {
		id = ID_PUNCHEDCARD;
	}
	else if (dynamic_cast<Decision*>(this)) {
		id = ID_DECISION;
	}

	return id;
}

int Shape::GetLineID() {
	int id = 0;
	if (dynamic_cast<Arrow*>(this)) {
		id = ID_ARROW;
	}
	else if (dynamic_cast<LeftDown*>(this)) {
		id = ID_LEFTDOWN;
	}
	else if (dynamic_cast<RightDown*>(this)) {
		id = ID_RIGHTDOWN;
	}
	else if (dynamic_cast<Join*>(this)) {
		id = ID_JOIN;
	}
	else if (dynamic_cast<RepeatTrue*>(this)) {
		id = ID_REPEATTRUE;
	}
	else if (dynamic_cast<RepeatFalse*>(this)) {
		id = ID_REPEATFALSE;
	}
	else if (dynamic_cast<RightDownJoin*>(this)) {
		id = ID_RIGHTDOWNJOIN;
	}

	return id;
}