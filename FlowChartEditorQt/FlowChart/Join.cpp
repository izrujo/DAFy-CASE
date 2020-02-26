/******************************************************************
* 파일 이름 : Join.cpp
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#include "Join.h"
#include "Painter.h"
#include "Join.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

#include "ScrollController.h"
#include "Scrolls.h"

#include "QtGObjectFactory.h"

Join::Join(Long x, Long y, Long width, Long height, Long height2, QColor backGroundColor,
	QPen borderLine, QColor borderColor, String contents)
	: Line(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
	this->height2 = height2;
}

Join::~Join() {

}

Join::Join(const Join& source) :Line(source) {
	this->height2 = source.height2;
}

Join& Join::operator =(const Join& source) {
	Line::operator=(source);
	this->height2 = source.height2;

	return *this;
}

bool Join::IsEqual(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<Join *>(const_cast<Shape *>(&other)) &&
		dynamic_cast<Join *>(const_cast<Shape *>(&other))->height2 == this->height2) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Join::IsNotEqual(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<Join *>(const_cast<Shape *>(&other)) ||
		dynamic_cast<Join *>(const_cast<Shape *>(&other))->height2 != this->height2) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool Join::operator ==(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<Join *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Join::operator !=(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<Join *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

Shape* Join::Clone() {
	return new Join(*this);
}

void Join::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

void Join::DrawActiveShape(GObject *painter) {
	QPoint points[4];
	points[0] = QPoint(this->x, this->y);
	points[1] = QPoint(this->x, this->y + this->height2);
	points[2] = QPoint(this->x + this->width, this->y + this->height2);
	points[3] = QPoint(this->x + this->width, this->y + this->height);

	painter->DrawPolyline(points, 4);
}

void Join::GetRegion(QRegion *region) {
	QRect rect;
	QRegion addRegion;

	rect.setCoords(this->x - LINETHICKNESS, this->y,
		this->x + LINETHICKNESS, this->y + this->height2);
	addRegion = QRegion(rect);
	*region += addRegion;

	rect.setCoords(this->x - LINETHICKNESS, this->y + this->height2 - LINETHICKNESS,
		this->x + this->width + LINETHICKNESS, this->y + this->height2 + LINETHICKNESS);
	addRegion = QRegion(rect);
	*region += addRegion;

	rect.setCoords(this->x + this->width - LINETHICKNESS, this->y + this->height2,
		this->x + this->width + LINETHICKNESS, this->y + this->height);
	addRegion = QRegion(rect);
	*region += addRegion;
}

void Join::GetRegion(Long thickness, QRegion *region) {
	QRect rect;
	QRegion addRegion;

	rect.setCoords(this->x - thickness, this->y,
		this->x + thickness, this->y + this->height2);
	addRegion = QRegion(rect);
	*region += addRegion;

	rect.setCoords(this->x - thickness, this->y + this->height2 - thickness,
		this->x + this->width + thickness, this->y + this->height2 + thickness);
	addRegion = QRegion(rect);
	*region += addRegion;

	rect.setCoords(this->x + this->width - thickness, this->y + this->height2,
		this->x + this->width + thickness, this->y + this->height);
	addRegion = QRegion(rect);
	*region += addRegion;
}

void Join::ReSize(Long width, Long height, Long height2) {
	this->width = width;
	this->height = height;
	this->height2 = height2;
}

bool Join::IsIncluded(QPoint point) {
	bool ret;

	QRegion region;
	QRect rect;
	QRegion addRegion;

	rect.setCoords(this->x - LINETHICKNESS, this->y,
		this->x + LINETHICKNESS, this->y + this->height2);
	addRegion = QRegion(rect);
	region += addRegion;

	rect.setCoords(this->x - LINETHICKNESS, this->y + this->height2 - LINETHICKNESS,
		this->x + this->width + LINETHICKNESS, this->y + this->height2 + LINETHICKNESS);
	addRegion = QRegion(rect);
	region += addRegion;

	rect.setCoords(this->x + this->width - LINETHICKNESS, this->y + this->height2,
		this->x + this->width + LINETHICKNESS, this->y + this->height);
	addRegion = QRegion(rect);
	region += addRegion;

	ret = region.contains(point);
	
	return ret;
}

bool Join::IsIncluded(const QRect& rect) {
	bool ret;

	QRegion region;
	QRect regionRect;
	QRegion addRegion;

	regionRect.setCoords(this->x - LINETHICKNESS, this->y,
		this->x + LINETHICKNESS, this->y + this->height2);
	addRegion = QRegion(regionRect);
	region += addRegion;

	regionRect.setCoords(this->x - LINETHICKNESS, this->y + this->height2 - LINETHICKNESS,
		this->x + this->width + LINETHICKNESS, this->y + this->height2 + LINETHICKNESS);
	addRegion = QRegion(regionRect);
	region += addRegion;

	regionRect.setCoords(this->x + this->width - LINETHICKNESS, this->y + this->height2,
		this->x + this->width + LINETHICKNESS, this->y + this->height);
	addRegion = QRegion(regionRect);
	region += addRegion;

	ret = region.contains(rect);

	return ret;
}

void Join::Copy(Shape *object) {
	this->x = object->GetX();
	this->y = object->GetY();
	this->width = object->GetWidth();
	this->height = object->GetHeight();
	this->backGroundColor = object->GetBackGroundColor();
	this->borderLine = object->GetBorderLine();
	this->borderColor = object->GetBorderColor();
	this->contents = object->GetContents();
	this->height2 = dynamic_cast<Join *>(object)->GetHeight2();
	this->isSelected = object->IsSelected();
}

void Join::GetSelectionMarkerRect(int marker, QRect *rect) {
	int x;
	int y;

	switch (marker) {
	case HIT_TRUE:
		x = this->x;
		y = this->y;
		break;

	case HIT_OUT:
		x = this->x + this->width / 2;
		y = this->y + this->height2;
		break;

	case HIT_FALSE:
		x = this->x + this->width;
		y = this->y + this->height;
		break;
	}

	rect->setCoords(x - 4, y - 4, x + 5, y + 5);
}

void Join::GetSelectionMarkerAllRegion(QRegion *region) {
	QRect rect;
	QRegion addRegion;

	Long x = this->x;
	Long y = this->y;
	rect.setCoords(x - 5, y - 5, x + 6, y + 6);
	addRegion = QRegion(rect);
	*region += addRegion;

	x = this->x + this->width / 2;
	y = this->y + this->height2;
	rect.setCoords(x - 5, y - 5, x + 6, y + 6);
	addRegion = QRegion(rect);
	*region += addRegion;

	x = this->x + this->width;
	y = this->y + this->height;
	rect.setCoords(x - 5, y - 5, x + 6, y + 6);
	addRegion = QRegion(rect);
	*region += addRegion;
}

int Join::GetHitCode(const QPoint& point, const QRegion& region) {
	int result = HIT_NONE;

	if (region.contains(point)) {
		result = HIT_BODY;
	}

	QRect rectSelect;
	this->GetSelectionMarkerRect(HIT_TRUE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_TRUE;
	}

	this->GetSelectionMarkerRect(HIT_OUT, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_OUT;
	}

	this->GetSelectionMarkerRect(HIT_FALSE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_FALSE;
	}

	return result;
}

void Join::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
	QRect rectSelect;

	QtGObjectFactory factory;
	GObject *brush = factory.MakeBrush(QColor(0, 0, 255), Qt::SolidPattern);
	GObject *oldBrush = painter->SelectObject(*brush);
	painter->Update();
	
	GetSelectionMarkerRect(HIT_TRUE, &rectSelect);
	Long positionX = scrollController->GetScroll(1)->GetPosition();
	Long positionY = scrollController->GetScroll(0)->GetPosition();
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_OUT, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_FALSE, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);
	
	painter->SelectObject(*oldBrush);
	painter->Update();
	if (brush != NULL) {
		delete brush;
	}
}

void Join::GetAttribute(Attribute *attribute) {
	attribute->vertexOut = 'Y';
	attribute->vertexTrue = 'Y';
	attribute->vertexFalse = 'Y';

	attribute->pointOut.setX(this->x + this->width / 2);
	attribute->pointOut.setY(this->y + this->height2);

	attribute->pointTrue.setX(this->x);
	attribute->pointTrue.setY(this->y);

	attribute->pointFalse.setX(this->x + this->width);
	attribute->pointFalse.setY(this->y + this->height);
}

void Join::GetLine(char(*line)) {
	sprintf(line, "%d\t%d\t%d\t%d\t%d\t\t%d\t%s\n", 
		ID_JOIN, this->x, this->y, this->width, this->height, this->height2, this->contents);
}


bool Join::IsStyle(Long style) {
	bool ret = false;
	if (Shape::IsStyle(style) || Line::IsStyle(style) || (style >> 12) % 2) {
		ret = true;
	}
	return ret;
}