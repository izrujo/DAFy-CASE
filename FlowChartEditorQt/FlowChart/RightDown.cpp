/******************************************************************
* 파일 이름 : RightDown.cpp
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#include "RightDown.h"
#include "../GObject/Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

#include "ScrollController.h"
#include "Scroll.h"

#include "../GObject/QtGObjectFactory.h"

RightDown::RightDown(float x, float y, float width, float height,
	QColor backGroundColor, Qt::PenStyle borderLine, QColor borderColor, String contents)
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

bool RightDown::IsEqual(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<RightDown *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool RightDown::IsNotEqual(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<RightDown *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

bool RightDown::operator ==(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<RightDown *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool RightDown::operator !=(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<RightDown *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

void RightDown::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

void RightDown::DrawActiveShape(GObject *painter) {
	painter->DrawLine(QPointF(this->x, this->y), QPointF(this->x + this->width, this->y));
	painter->DrawLine(QPointF(this->x + this->width, this->y), QPointF(this->x + this->width, this->y + this->height - ARROW_SIZE));

	QPointF arrow[3];
	arrow[0] = QPointF(this->x + this->width, this->y + this->height);
	arrow[1] = QPointF(this->x + this->width - ARROW_SIZE / 2.0F, this->y + this->height - ARROW_SIZE);
	arrow[2] = QPointF(this->x + this->width + ARROW_SIZE / 2.0F, this->y + this->height - ARROW_SIZE);
	painter->DrawPolygon(arrow, 3);
}

NShape* RightDown::Clone() {
	return new RightDown(*this);
}

QRegion RightDown::GetRegion() {
	QRectF rect(this->x, this->y - LINETHICKNESS,
		this->width, LINETHICKNESS);
	QRegion region(rect.toRect());
	
	rect = QRectF(this->x + this->width - LINETHICKNESS, this->y,
		this->width + LINETHICKNESS, this->height);
	region += QRegion(rect.toRect());
	
	return region;
}

QRegion RightDown::GetRegion(Long thickness) {
	QRectF rect(this->x, this->y - thickness,
		this->width, thickness);
	QRegion region(rect.toRect());
	
	rect = QRectF(this->x + this->width - thickness, this->y,
		this->width + thickness, this->height);
	region += QRegion(rect.toRect());
	
	return region;
}

bool RightDown::IsIncluded(QPointF point) {
	bool ret;

	QRegion region;
	QRectF regionRect(this->x, this->y - LINETHICKNESS,
		this->width, LINETHICKNESS);
	region = QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width - LINETHICKNESS, this->y,
		this->width + LINETHICKNESS, this->height);
	region = QRegion(regionRect.toRect());

	ret = region.contains(point.toPoint());

	return ret;
}

bool RightDown::IsIncluded(const QRectF& rect) {
	bool ret;

	QRegion region;
	QRectF regionRect(this->x, this->y - LINETHICKNESS,
		this->width, LINETHICKNESS);
	region = QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width - LINETHICKNESS, this->y,
		this->width + LINETHICKNESS, this->height);
	region = QRegion(regionRect.toRect());

	ret = region.contains(rect.toRect());

	return ret;
}

void RightDown::GetSelectionMarkerRect(int marker, QRectF *rect) {
	float x;
	float y;

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

QRegion RightDown::GetSelectionMarkerAllRegion() {
	float x = this->x;
	float y = this->y;
	QRectF rect(x - 6, y - 6, 7, 7);
	QRegion region(rect.toRect());
	
	x = this->x + this->width;
	y = this->y + this->height;
	rect = QRectF(x - 6, y - 6, 7, 7);
	region += QRegion(rect.toRect());
	
	return region;
}

int RightDown::GetHitCode(const QPointF& point, const QRegion& region) {
	int result = HIT_NONE;

	if (region.contains(point.toPoint())) {
		result = HIT_BODY;
	}

	QRectF rectSelect;
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

void RightDown::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
	QRectF rectSelect;

	QtGObjectFactory factory;
	GObject *brush = factory.MakeBrush(QColor(0, 0, 255), Qt::SolidPattern);
	GObject *oldBrush = painter->SelectObject(*brush);
	painter->Update();

	GetSelectionMarkerRect(HIT_IN, &rectSelect);
	Long positionX = scrollController->GetScroll(1)->value();
	Long positionY = scrollController->GetScroll(0)->value();
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	GetSelectionMarkerRect(HIT_OUT, &rectSelect);
	rectSelect.setCoords(rectSelect.left() - positionX, rectSelect.top() - positionY,
		rectSelect.right() - positionX, rectSelect.bottom() - positionY);
	painter->DrawRect(rectSelect);

	painter->SelectObject(*oldBrush);
	painter->Update();
	if (brush != NULL) {
		delete brush;
	}
}

void RightDown::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x + this->width);
	attribute->pointOut.setY(this->y + this->height);
}

void RightDown::GetLine(char(*line)) {
	sprintf(line, "%d\t%f\t%f\t%f\t%f\t\t\t%s;\n", 
		ID_RIGHTDOWN, this->x, this->y, this->width, this->height, this->contents.GetString());
}


bool RightDown::IsStyle(Long style) {
	bool ret = false;
	if (NShape::IsStyle(style) || Line::IsStyle(style) || (style >> 11) % 2) {
		ret = true;
	}
	return ret;
}