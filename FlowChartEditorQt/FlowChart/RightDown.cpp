/******************************************************************
* 파일 이름 : RightDown.cpp
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#include "RightDown.h"
#include "Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

#include "ScrollController.h"
#include "Scrolls.h"

RightDown::RightDown(Long x, Long y, Long width, Long height,
	QColor backGroundColor, QPen borderLine, QColor borderColor, String contents)
	: Line(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

RightDown::~RightDown() {

}

RightDown::RightDown(const RightDown& source)
	: Line(source) {

}

RightDown& RightDown::operator =(const RightDown& source) {
	Line::operator=(source);

	return *this;
}

bool RightDown::IsEqual(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<RightDown *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool RightDown::IsNotEqual(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<RightDown *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool RightDown::operator ==(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<RightDown *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool RightDown::operator !=(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<RightDown *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

void RightDown::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}
/*
void RightDown::DrawActiveShape(Painter *painter) {
	painter->DrawLine(x, y, x + width, y);
	painter->DrawLine(x + width, y, x + width, y + height - ARROW_SIZE);

	POINT arrow[3];
	arrow[0].x = x + width;
	arrow[0].y = y + height;
	arrow[1].x = x + width - ARROW_SIZE / 2;
	arrow[1].y = y + height - ARROW_SIZE;
	arrow[2].x = x + width + ARROW_SIZE / 2;
	arrow[2].y = y + height - ARROW_SIZE;
	painter->DrawPolygon(arrow, 3);
}
*/

Shape* RightDown::Clone() {
	return new RightDown(*this);
}

void RightDown::GetRegion(QRegion *region) {
	QRect rect;
	QRegion addRegion;

	rect.setCoords(this->x, this->y - LINETHICKNESS,
		this->x + this->width, this->y + LINETHICKNESS);
	addRegion = QRegion(rect);
	*region += addRegion;

	rect.setCoords(this->x + this->width - LINETHICKNESS, this->y,
		this->x + this->width + LINETHICKNESS, this->y + this->height);
	addRegion = QRegion(rect);
	*region += addRegion;
}

void RightDown::GetRegion(Long thickness, QRegion *region) {
	QRect rect;
	QRegion addRegion;

	rect.setCoords(this->x, this->y - thickness,
		this->x + this->width, this->y + thickness);
	addRegion = QRegion(rect);
	*region += addRegion;

	rect.setCoords(this->x + this->width - thickness, this->y,
		this->x + this->width + thickness, this->y + this->height);
	addRegion = QRegion(rect);
	*region += addRegion;
}

bool RightDown::IsIncluded(QPoint point) {
	bool ret;

	QRegion region;
	QRect regionRect;
	QRegion addRegion;

	regionRect.setCoords(this->x, this->y - LINETHICKNESS,
		this->x + this->width, this->y + LINETHICKNESS);
	addRegion = QRegion(regionRect);
	region += addRegion;

	regionRect.setCoords(this->x + this->width - LINETHICKNESS, this->y,
		this->x + this->width + LINETHICKNESS, this->y + this->height);
	addRegion = QRegion(regionRect);
	region += addRegion;

	ret = region.contains(point);

	return ret;
}

bool RightDown::IsIncluded(const QRect& rect) {
	bool ret;

	QRegion region;
	QRect regionRect;
	QRegion addRegion;

	regionRect.setCoords(this->x, this->y - LINETHICKNESS,
		this->x + this->width, this->y + LINETHICKNESS);
	addRegion = QRegion(regionRect);
	region += addRegion;

	regionRect.setCoords(this->x + this->width - LINETHICKNESS, this->y,
		this->x + this->width + LINETHICKNESS, this->y + this->height);
	addRegion = QRegion(regionRect);
	region += addRegion;

	ret = region.contains(rect);

	return ret;
}

void RightDown::GetSelectionMarkerRect(int marker, QRect *rect) {
	int x;
	int y;

	switch (marker) {
	case HIT_IN:
		x = this->x;
		y = this->y;
		break;

	case HIT_OUT:
		x = this->x + this->width;
		y = this->y + this->height;
		break;
	}

	rect->setCoords(x - 4, y - 4, x + 5, y + 5);
}

void RightDown::GetSelectionMarkerAllRegion(QRegion *region) {
	QRect rect;
	QRegion addRegion;
	
	Long x = this->x;
	Long y = this->y;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;

	x = this->x + this->width;
	y = this->y + this->height;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;
}

int RightDown::GetHitCode(const QPoint& point, const QRegion& region) {
	int result = HIT_NONE;

	if (region.contains(point)) {
		result = HIT_BODY;
	}

	QRect rectSelect;
	this->GetSelectionMarkerRect(HIT_IN, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_IN;
	}

	this->GetSelectionMarkerRect(HIT_OUT, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_OUT;
	}

	return result;
}
/*
void RightDown::DrawSelectionMarkers(Painter* painter, ScrollController *scrollController) {
	CRect rectSelect;

	painter->ChangePlaneProperty(BS_SOLID, RGB(0, 0, 255));

	GetSelectionMarkerRect(HIT_IN, &rectSelect);
	Long positionX = scrollController->GetScroll(1)->GetPosition();
	Long positionY = scrollController->GetScroll(0)->GetPosition();
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_OUT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);
}
*/

void RightDown::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x + this->width);
	attribute->pointOut.setY(this->y + this->height);
}

void RightDown::GetLine(char(*line)) {
	sprintf(line, "%d\t%d\t%d\t%d\t%d\t\t\t%s\n", 
		ID_RIGHTDOWN, this->x, this->y, this->width, this->height, this->contents);
}


bool RightDown::IsStyle(Long style) {
	bool ret = false;
	if (Shape::IsStyle(style) || Line::IsStyle(style) || (style >> 11) % 2) {
		ret = true;
	}
	return ret;
}