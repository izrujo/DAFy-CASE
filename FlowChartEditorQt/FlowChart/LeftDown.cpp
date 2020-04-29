/******************************************************************
* 파일 이름 : LeftDown.cpp
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#include "LeftDown.h"
#include "../GObject/Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

#include "ScrollController.h"
#include "Scroll.h"

#include "../GObject/QtGObjectFactory.h"

LeftDown::LeftDown(float x, float y, float width, float height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: Line(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

LeftDown::~LeftDown() {

}

LeftDown::LeftDown(const LeftDown& source) : Line(source) {

}

LeftDown& LeftDown::operator =(const LeftDown& source) {
	Line::operator=(source);

	return *this;
}

bool LeftDown::IsEqual(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<LeftDown *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool LeftDown::IsNotEqual(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<LeftDown *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

bool LeftDown::operator ==(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<LeftDown *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool LeftDown::operator !=(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<LeftDown *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

void LeftDown::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* LeftDown::Clone() {
	return new LeftDown(*this);
}

void LeftDown::DrawActiveShape(GObject *painter) {
	painter->DrawLine(QPointF(this->x, this->y), QPointF(this->x + this->width, this->y));
	painter->DrawLine(QPointF(this->x + this->width, this->y), 
		QPointF(this->x + this->width, this->y + this->height - ARROW_SIZE));

	QPointF arrow[3];
	arrow[0] = QPointF(this->x + this->width, this->y + this->height);
	arrow[1] = QPointF(this->x + this->width - ARROW_SIZE / 2.0F, this->y + this->height - ARROW_SIZE);
	arrow[2] = QPointF(this->x + this->width + ARROW_SIZE / 2.0F, this->y + this->height - ARROW_SIZE);
	painter->DrawPolygon(arrow, 3);
}

QRegion LeftDown::GetRegion() {
	QRectF rect(this->x, this->y - LINETHICKNESS, this->width, LINETHICKNESS);
	QRegion region(rect.toRect());

	rect = QRectF(this->x + this->width - LINETHICKNESS, this->y, 
		this->width + LINETHICKNESS, this->height);
	region = QRegion(rect.toRect());

	return region;
}

QRegion LeftDown::GetRegion(Long thickness) {
	QRectF rect(this->x, this->y - thickness,this->width, thickness);
	QRegion region(rect.toRect());
	
	rect = QRectF(this->x + this->width - thickness, this->y, 
		this->width + thickness, this->height);
	region += QRegion(rect.toRect());
	
	return region;
}

bool LeftDown::IsIncluded(QPointF point) {
	bool ret;

	QRectF regionRect(this->x, this->y - LINETHICKNESS,
		this->width, LINETHICKNESS);
	QRegion region(regionRect.toRect());

	regionRect = QRectF(this->x + this->width - LINETHICKNESS, this->y,
		this->width + LINETHICKNESS, this->height);
	region += QRegion(regionRect.toRect());

	ret = region.contains(point.toPoint());

	return ret;
}

bool LeftDown::IsIncluded(const QRectF& rect) {
	bool ret;

	QRectF regionRect(this->x, this->y - LINETHICKNESS,
		this->width, LINETHICKNESS);
	QRegion region(regionRect.toRect());

	regionRect = QRectF(this->x + this->width - LINETHICKNESS, this->y,
		this->width + LINETHICKNESS, this->height);
	region += QRegion(regionRect.toRect());

	ret = region.contains(rect.toRect());

	return ret;
}

void LeftDown::GetSelectionMarkerRect(int marker, QRectF *rect) {
	float x;
	float y;

	switch (marker) {
	case HIT_IN:
		x = this->x;
		y = this->y;
		break;

	case HIT_OUT:
		x = this->x + width;
		y = this->y + height;
		break;
	}

	rect->setCoords(x - 4, y - 4, x + 5, y + 5);
}

QRegion LeftDown::GetSelectionMarkerAllRegion() {
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

int LeftDown::GetHitCode(const QPointF& point, const QRegion& region) {
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

void LeftDown::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
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

void LeftDown::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x + this->width);
	attribute->pointOut.setY(this->y + this->height);
}

void LeftDown::GetLine(char(*line)) {
	sprintf(line, "%d\t%f\t%f\t%f\t%f\t\t\t%s;\n", ID_LEFTDOWN, 
		this->x, this->y, this->width, this->height, this->contents.GetString());
}

bool LeftDown::IsStyle(Long style) {
	bool ret = false;
	if (NShape::IsStyle(style) || Line::IsStyle(style) || (style >> 10) % 2) {
		ret = true;
	}
	return ret;
}