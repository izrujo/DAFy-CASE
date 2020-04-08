/******************************************************************
* 파일 이름 : RightDownJoin.cpp
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#include "RightDownJoin.h"
#include "../GObject/Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

#include "ScrollController.h"
#include "Scroll.h"

#include "../GObject/QtGObjectFactory.h"

RightDownJoin::RightDownJoin(Long x, Long y, Long width, Long height, Long width2, Long height2, 
	QColor backGroundColor, Qt::PenStyle borderLine, QColor borderColor, String contents) 
	: Line(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
	this->width2 = width2;
	this->height2 = height2;
}

RightDownJoin::~RightDownJoin() {

}

RightDownJoin::RightDownJoin(const RightDownJoin& source) 
	: Line(source) {
	this->width2 = source.width2;
	this->height2 = source.height2;
}

RightDownJoin& RightDownJoin::operator =(const RightDownJoin& source) {
	Line::operator=(source);
	this->width2 = source.width2;
	this->height2 = source.height2;
	
	return *this;
}

bool RightDownJoin::IsEqual(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<RightDownJoin *>(const_cast<NShape *>(&other)) &&
		dynamic_cast<RightDownJoin *>(const_cast<NShape *>(&other))->width2 == this->width2 &&
		dynamic_cast<RightDownJoin *>(const_cast<NShape *>(&other))->height2 == this->height2) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool RightDownJoin::IsNotEqual(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<RightDownJoin *>(const_cast<NShape *>(&other)) ||
		dynamic_cast<RightDownJoin *>(const_cast<NShape *>(&other))->width2 != this->width2 ||
		dynamic_cast<RightDownJoin *>(const_cast<NShape *>(&other))->height2 != this->height2) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

bool RightDownJoin::operator ==(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<RightDownJoin *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool RightDownJoin::operator !=(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<RightDownJoin *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

void RightDownJoin::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

void RightDownJoin::DrawActiveShape(GObject *painter) {
	QPoint points[5];
	points[0] = QPoint(this->x, this->y);
	points[1] = QPoint(this->x + this->width2, this->y);
	points[2] = QPoint(this->x + this->width2, this->y + this->height + this->height2);
	points[3] = QPoint(this->x + this->width, this->y + this->height + this->height2);
	points[4] = QPoint(this->x + this->width, this->y + this->height);
	painter->DrawPolyline(points, 5);
}

NShape* RightDownJoin::Clone() {
	return new RightDownJoin(*this);
}

void RightDownJoin::GetRegion(QRegion *region) {
	QRect rect;
	QRegion addRegion;

	rect.setCoords(this->x, this->y - LINETHICKNESS, 
		this->x + this->width2, this->y + LINETHICKNESS);
	addRegion = QRegion(rect);
	*region += addRegion;

	rect.setCoords(this->x + this->width2 - LINETHICKNESS, this->y, 
		this->x + this->width2 + LINETHICKNESS, this->y + this->height + this->height2);
	addRegion = QRegion(rect);
	*region += addRegion;

	rect.setCoords(this->x + this->width2, this->y + this->height + this->height2 - LINETHICKNESS, 
		this->x + this->width - this->width2, this->y + this->height + this->height2 + LINETHICKNESS);
	addRegion = QRegion(rect);
	*region += addRegion;

	rect.setCoords(this->x + this->width - LINETHICKNESS, this->y + this->height + this->height2, 
		this->x + this->width + LINETHICKNESS, this->y + this->height);
	addRegion = QRegion(rect);
	*region += addRegion;
}

void RightDownJoin::GetRegion(Long thickness, QRegion *region) {
	QRect rect;
	QRegion addRegion;

	rect.setCoords(this->x, this->y - thickness, 
		this->x + this->width2, this->y + thickness);
	addRegion = QRegion(rect);
	*region += addRegion;

	rect.setCoords(this->x + this->width2 - thickness, this->y, 
		this->x + this->width2 + thickness, this->y + this->height + this->height2);
	addRegion = QRegion(rect);
	*region += addRegion;

	rect.setCoords(this->x + this->width2, this->y + this->height + this->height2 - thickness, 
		this->x + this->width - this->width2, this->y + this->height + this->height2 + thickness);
	addRegion = QRegion(rect);
	*region += addRegion;
	
	rect.setCoords(this->x + this->width - thickness, this->y + this->height + this->height2, 
		this->x + this->width + thickness, this->y + this->height);
	addRegion = QRegion(rect);
	*region += addRegion;
}

void RightDownJoin::ReSize(Long width, Long height, Long width2, Long height2) {
	this->width = width;
	this->height = height;
	this->width2 = width2;
	this->height2 = height2;
}

bool RightDownJoin::IsIncluded(QPoint point) {
	bool ret;

	QRegion region;
	QRect regionRect;
	QRegion addRegion;

	regionRect.setCoords(this->x, this->y - LINETHICKNESS,
		this->x + this->width2, this->y + LINETHICKNESS);
	addRegion = QRegion(regionRect);
	region += addRegion;
	
	regionRect.setCoords(this->x + this->width2 - LINETHICKNESS, this->y,
		this->x + this->width2 + LINETHICKNESS, this->y + this->height + this->height2);
	addRegion = QRegion(regionRect);
	region += addRegion;

	regionRect.setCoords(this->x + this->width2, this->y + this->height + this->height2 - LINETHICKNESS,
		this->x + this->width - this->width2, this->y + this->height + this->height2 + LINETHICKNESS);
	addRegion = QRegion(regionRect);
	region += addRegion;

	regionRect.setCoords(this->x + this->width - LINETHICKNESS, this->y + this->height + this->height2,
		this->x + this->width + LINETHICKNESS, this->y + this->height);
	addRegion = QRegion(regionRect);
	region += addRegion;

	ret = region.contains(point);

	return ret;
}

bool RightDownJoin::IsIncluded(const QRect& rect) {
	bool ret;

	QRegion region;
	QRect regionRect;
	QRegion addRegion;

	regionRect.setCoords(this->x, this->y - LINETHICKNESS,
		this->x + this->width2, this->y + LINETHICKNESS);
	addRegion = QRegion(regionRect);
	region += addRegion;

	regionRect.setCoords(this->x + this->width2 - LINETHICKNESS, this->y,
		this->x + this->width2 + LINETHICKNESS, this->y + this->height + this->height2);
	addRegion = QRegion(regionRect);
	region += addRegion;

	regionRect.setCoords(this->x + this->width2, this->y + this->height + this->height2 - LINETHICKNESS,
		this->x + this->width - this->width2, this->y + this->height + this->height2 + LINETHICKNESS);
	addRegion = QRegion(regionRect);
	region += addRegion;

	regionRect.setCoords(this->x + this->width - LINETHICKNESS, this->y + this->height + this->height2,
		this->x + this->width + LINETHICKNESS, this->y + this->height);
	addRegion = QRegion(regionRect);
	region += addRegion;

	ret = region.contains(rect);

	return ret;
}

int RightDownJoin::GetHitCode(const QPoint& point, const QRegion& region) {
	int result = HIT_NONE;
	if (region.contains(point)) {
		result = HIT_BODY;
	}

	QRect rectSelect;
	GetSelectionMarkerRect(HIT_FALSE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_FALSE;
	}

	GetSelectionMarkerRect(HIT_HANDLE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_HANDLE;
	}

	GetSelectionMarkerRect(HIT_TRUE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_TRUE;
	}
	return result;
}

void RightDownJoin::Copy(NShape *object) {
	this->x = object->GetX();
	this->y = object->GetY();
	this->width = object->GetWidth();
	this->height = object->GetHeight();
	this->backGroundColor = object->GetBackGroundColor();
	this->borderLine = object->GetBorderLine();
	this->borderColor = object->GetBorderColor();
	this->contents = object->GetContents();
	this->width2 = dynamic_cast<RightDownJoin *>(object)->GetWidth2();
	this->height2 = dynamic_cast<RightDownJoin *>(object)->GetHeight2();

	this->isSelected = object->IsSelected();
}

void RightDownJoin::GetSelectionMarkerRect(int marker, QRect *rect) {
	int x;
	int y;

	switch (marker) {
	case HIT_FALSE:
		x = this->x;
		y = this->y;
		break;

	case HIT_HANDLE:
		x = this->x + this->width2;
		y = this->y + this->height + this->height2;
		break;

	case HIT_TRUE:
		x = this->x + this->width;
		y = this->y + this->height;
		break;
	}

	rect->setCoords(x - 4, y - 4, x + 5, y + 5);
}

void RightDownJoin::GetSelectionMarkerAllRegion(QRegion *region) {
	QRect rect;
	QRegion addRegion;

	Long x = this->x;
	Long y = this->y;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;

	x = this->x + this->width2;
	y = this->y + this->height + this->height2;
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;

	x = this->x + this->width;
	y = this->y + this->height; 
	rect.setCoords(x - 6, y - 6, x + 7, y + 7);
	addRegion = QRegion(rect);
	*region += addRegion;
}

void RightDownJoin::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
	QRect rectSelect;

	QtGObjectFactory factory;
	GObject *brush = factory.MakeBrush(QColor(0, 0, 255), Qt::SolidPattern);
	GObject *oldBrush = painter->SelectObject(*brush);
	painter->Update();

	GetSelectionMarkerRect(HIT_FALSE, &rectSelect);
	Long positionX = scrollController->GetScroll(1)->value();
	Long positionY = scrollController->GetScroll(0)->value();
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_HANDLE, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_TRUE, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	painter->SelectObject(*oldBrush);
	painter->Update();
	if (brush != NULL) {
		delete brush;
	}
}

void RightDownJoin::GetAttribute(Attribute *attribute) {
	attribute->vertexFalse = 'Y';
	attribute->vertexTrue = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointFalse.setX(this->x);
	attribute->pointFalse.setY(this->y);

	attribute->pointTrue.setX(this->x + this->width);
	attribute->pointTrue.setY(this->y + this->height);

	attribute->pointOut.setX(this->x + (this->width + this->width2) / 2);
	attribute->pointOut.setY(this->y + this->height + this->height2);
}

void RightDownJoin::GetLine(char(*line)) {
	sprintf(line, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n", 
		ID_RIGHTDOWNJOIN, this->x, this->y, this->width, this->height, this->width2, this->height2, this->contents);
}

bool RightDownJoin::IsStyle(Long style) {
	bool ret = false;
	if (NShape::IsStyle(style) || Line::IsStyle(style) || (style >> 15) % 2) {
		ret = true;
	}
	return ret;
}