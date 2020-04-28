/******************************************************************
* 파일 이름 : RepeatTure.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#include "RepeatTrue.h"
#include "../GObject/Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

#include "ScrollController.h"
#include "Scroll.h"

#include "../GObject/QtGObjectFactory.h"

RepeatTrue::RepeatTrue(float x, float y, float width, float height, float width2, float height2,
	QColor backGroundColor, Qt::PenStyle borderLine, QColor borderColor, String contents)
	: Line(x, y, width, height, backGroundColor, borderLine, borderColor, contents)
{
	this->width2 = width2;
	this->height2 = height2;
}

RepeatTrue::~RepeatTrue() {

}

RepeatTrue::RepeatTrue(const RepeatTrue& source)
	: Line(source)
{
	this->width2 = source.width2;
	this->height2 = source.height2;
}

RepeatTrue& RepeatTrue::operator=(const RepeatTrue& source) {
	Line::operator=(source);
	this->width2 = source.width2;
	this->height2 = source.height2;

	return *this;
}

bool RepeatTrue::IsEqual(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<RepeatTrue *>(const_cast<NShape *>(&other)) &&
		dynamic_cast<RepeatTrue *>(const_cast<NShape *>(&other))->width2 == this->width2 &&
		dynamic_cast<RepeatTrue *>(const_cast<NShape *>(&other))->height2 == this->height2) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool RepeatTrue::IsNotEqual(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<RepeatTrue *>(const_cast<NShape *>(&other)) ||
		dynamic_cast<RepeatTrue *>(const_cast<NShape *>(&other))->width2 != this->width2 ||
		dynamic_cast<RepeatTrue *>(const_cast<NShape *>(&other))->height2 != this->height2) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

bool RepeatTrue::operator ==(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<RepeatTrue *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool RepeatTrue::operator !=(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<RepeatTrue *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

void RepeatTrue::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

void RepeatTrue::DrawActiveShape(GObject *painter) {
	QPointF points[5];
	points[0] = QPointF(this->x, this->y);
	points[1] = QPointF(this->x, this->y + this->height2);
	points[2] = QPointF(this->x + this->width2, this->y + this->height2);
	points[3] = QPointF(this->x + this->width2, this->y + this->height);
	points[4] = QPointF(this->x + this->width, this->y + this->height);
	painter->DrawPolyline(points, 5);

	QPointF arrow[3];
	arrow[0] = QPointF(this->x + this->width - ARROW_SIZE, this->y + this->height - ARROW_SIZE / 2.0F);
	arrow[1] = QPointF(this->x + this->width, this->y + this->height);
	arrow[2] = QPointF(this->x + this->width - ARROW_SIZE, this->y + this->height + ARROW_SIZE / 2.0F);
	painter->DrawPolygon(arrow, 3);
}

NShape* RepeatTrue::Clone() {
	return new RepeatTrue(*this);
}

QRegion RepeatTrue::GetRegion() {
	QRectF rect(this->x - LINETHICKNESS, this->y, LINETHICKNESS, this->height2);
	QRegion region(rect.toRect());

	rect = QRectF(this->x + 1, this->y + this->height2 - LINETHICKNESS,
		this->width2, this->height2 + LINETHICKNESS);
	region += QRegion(rect.toRect());

	rect = QRectF(this->x + this->width2 - LINETHICKNESS, this->y + this->height2,
		this->width2 + LINETHICKNESS, this->height);
	region += QRegion(rect.toRect());

	rect = QRectF(this->x + this->width2 - 1, this->y + this->height - LINETHICKNESS,
		this->width, this->height + LINETHICKNESS);
	region += QRegion(rect.toRect());

	return region;
}

QRegion RepeatTrue::GetRegion(Long thickness) {
	QRectF rect(this->x - thickness, this->y, thickness, this->height2);
	QRegion region(rect.toRect());
	
	rect = QRectF(this->x + 1, this->y + this->height2 - thickness, 
		this->width2, this->height2 + thickness);
	region += QRegion(rect.toRect());
	
	rect = QRectF(this->x + this->width2 - thickness, this->y + this->height2, 
		this->width2 + thickness, this->height);
	region += QRegion(rect.toRect());

	rect = QRectF(this->x + this->width2 - 1, this->y + this->height - thickness, 
		this->width, this->height + thickness);
	region += QRegion(rect.toRect());
	
	return region;
}

void RepeatTrue::ReSize(float width, float height, float width2, float height2) {
	width = width;
	height = height;
	this->width2 = width2;
	this->height2 = height2;
}

bool RepeatTrue::IsIncluded(QPointF point) {
	bool ret;

	QRectF regionRect(this->x - LINETHICKNESS, this->y, 
		LINETHICKNESS, this->height2);
	QRegion region(regionRect.toRect());

	regionRect = QRectF(this->x, this->y + this->height2 - LINETHICKNESS, 
		this->width2, this->height2 + LINETHICKNESS);
	region = QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width2 - LINETHICKNESS, this->y + this->height2, 
		this->width2 + LINETHICKNESS, this->height);
	region += QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width2, this->y + this->height - LINETHICKNESS, 
		this->width, this->height + LINETHICKNESS);
	region += QRegion(regionRect.toRect());
	
	ret = region.contains(point.toPoint());
	
	return ret;
}

bool RepeatTrue::IsIncluded(const QRectF& rect) {
	bool ret;

	QRectF regionRect(this->x - LINETHICKNESS, this->y,
		LINETHICKNESS, this->height2);
	QRegion region(regionRect.toRect());

	regionRect = QRectF(this->x, this->y + this->height2 - LINETHICKNESS,
		this->width2, this->height2 + LINETHICKNESS);
	region = QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width2 - LINETHICKNESS, this->y + this->height2,
		this->width2 + LINETHICKNESS, this->height);
	region += QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width2, this->y + this->height - LINETHICKNESS,
		this->width, this->height + LINETHICKNESS);
	region += QRegion(regionRect.toRect());

	ret = region.contains(rect.toRect());

	return ret;
}

void RepeatTrue::Copy(NShape *object) {
	x = object->GetX();
	y = object->GetY();
	width = object->GetWidth();
	height = object->GetHeight();
	backGroundColor = object->GetBackGroundColor();
	borderLine = object->GetBorderLine();
	borderColor = object->GetBorderColor();
	contents = object->GetContents();
	width2 = dynamic_cast<RepeatTrue *>(object)->GetWidth2();
	height2 = dynamic_cast<RepeatTrue *>(object)->GetHeight2();
	isSelected = object->IsSelected();
}

void RepeatTrue::GetSelectionMarkerRect(int marker, QRectF *rect) {
	float x;
	float y;

	switch (marker) {
	case HIT_IN:
		x = this->x;
		y = this->y;
		break;

	case HIT_HANDLE:
		x = this->x + this->width2;
		y = this->y + this->height2;
		break;

	case HIT_OUT:
		x = this->x + this->width;
		y = this->y + this->height;
		break;
	}

	rect->setCoords(x - 4, y - 4, x + 5, y + 5);
}

QRegion RepeatTrue::GetSelectionMarkerAllRegion() {
	float x = this->x;
	float y = this->y;
	QRectF rect(x - 5, y - 5, 6, 6);
	QRegion region(rect.toRect());
	
	x = this->x + this->width2;
	y = this->y + this->height2;
	rect = QRectF(x - 5, y - 5, 6, 6);
	region += QRegion(rect.toRect());
	
	x = this->x + this->width;
	y = this->y + this->height;
	rect = QRectF(x - 5, y - 5, 6, 6);
	region += QRegion(rect.toRect());
	
	return region;
}

int RepeatTrue::GetHitCode(const QPointF& point, const QRegion& region) {
	int result = HIT_NONE;

	if (region.contains(point.toPoint())) {
		result = HIT_BODY;
	}

	QRectF rectSelect;
	GetSelectionMarkerRect(HIT_IN, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_IN;
	}

	GetSelectionMarkerRect(HIT_HANDLE, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_HANDLE;
	}

	GetSelectionMarkerRect(HIT_OUT, &rectSelect);
	if (rectSelect.contains(point)) {
		result = HIT_OUT;
	}
	return result;
}

void RepeatTrue::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
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

	GetSelectionMarkerRect(HIT_HANDLE, &rectSelect);
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

void RepeatTrue::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x + this->width);
	attribute->pointOut.setY(this->y + this->height);
}

void RepeatTrue::GetLine(char(*line)) {
	sprintf(line, "%d\t%f\t%f\t%f\t%f\t%f\t%f\t%s\n", 
		ID_REPEATTRUE, this->x, this->y, this->width, this->height, this->width2, this->height2, 
		this->contents.GetString());
}

bool RepeatTrue::IsStyle(Long style) {
	bool ret = false;
	if (NShape::IsStyle(style) || Line::IsStyle(style) || (style >> 13) % 2) {
		ret = true;
	}
	return ret;
}