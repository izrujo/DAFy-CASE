/******************************************************************
* 파일 이름 : RepeatFalse.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/
#pragma warning (disable : 4996)

#include "RepeatFalse.h"
#include "../../Paint/FlowChartVisitor.h"

#include "../../Interface/Scroll.h"
#include "../../Observer/ScrollController.h"

#include "../../../Graphic Objects/Composite/Painter.h"
#include "../../../Graphic Objects/Factory/Qt/QtGObjectFactory.h"

RepeatFalse::RepeatFalse(float x, float y, float width, float height, float width2, float height2,
	QColor backGroundColor, Qt::PenStyle borderLine, QColor borderColor, String contents)
	: Line(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
	this->width2 = width2;
	this->height2 = height2;
}

RepeatFalse::~RepeatFalse() {}

RepeatFalse::RepeatFalse(const RepeatFalse& source)
	: Line(source) {
	this->width2 = source.width2;
	this->height2 = source.height2;
}

RepeatFalse& RepeatFalse::operator=(const RepeatFalse& source) {
	Line::operator=(source);

	this->width2 = source.width2;
	this->height2 = source.height2;

	return *this;
}

bool RepeatFalse::IsEqual(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<RepeatFalse *>(const_cast<NShape *>(&other)) &&
		dynamic_cast<RepeatFalse *>(const_cast<NShape *>(&other))->width2 == this->width2 &&
		dynamic_cast<RepeatFalse *>(const_cast<NShape *>(&other))->height2 == this->height2) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool RepeatFalse::IsNotEqual(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<RepeatFalse *>(const_cast<NShape *>(&other)) ||
		dynamic_cast<RepeatFalse *>(const_cast<NShape *>(&other))->width2 != this->width2 ||
		dynamic_cast<RepeatFalse *>(const_cast<NShape *>(&other))->height2 != this->height2) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

bool RepeatFalse::operator ==(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<RepeatFalse *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool RepeatFalse::operator !=(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<RepeatFalse *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

void RepeatFalse::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

void RepeatFalse::DrawActiveShape(GObject *painter) {
	QPointF points[5];
	points[0] = QPointF(this->x, this->y);
	points[1] = QPointF(this->x + this->width2, this->y);
	points[2] = QPointF(this->x + this->width2, this->y + this->height2);
	points[3] = QPointF(this->x + this->width, this->y + this->height2);
	points[4] = QPointF(this->x + this->width, this->y + this->height);
	painter->DrawPolyline(points, 5);

	QPointF arrow[3];
	arrow[0] = QPointF(this->x + this->width - ARROW_SIZE / 2.0F, this->y + this->height - ARROW_SIZE);
	arrow[0] = QPointF(this->x + this->width, this->y + this->height);
	arrow[0] = QPointF(this->x + this->width + ARROW_SIZE / 2.0F, this->y + this->height - ARROW_SIZE);
	painter->DrawPolygon(arrow, 3);
}

NShape* RepeatFalse::Clone() {
	return new RepeatFalse(*this);
}

QRegion RepeatFalse::GetRegion() {
	QRectF rect(this->x, this->y - LINETHICKNESS, this->width2 + 1, LINETHICKNESS * 2);
	QRegion region(rect.toRect());

	rect = QRect(this->x + this->width2 - LINETHICKNESS, this->y,
		LINETHICKNESS * 2, this->height2);
	region += QRegion(rect.toRect());

	rect = QRect(this->x + this->width, this->y + this->height2 - LINETHICKNESS,
		this->x + this->width + this->width2, LINETHICKNESS * 2);
	region += QRegion(rect.toRect());

	rect = QRect(this->x + this->width - LINETHICKNESS, this->y + this->height2 - 1,
		LINETHICKNESS * 2, this->height);
	region += QRegion(rect.toRect());

	return region;
}

QRegion RepeatFalse::GetRegion(Long thickness) {
	QRectF rect(this->x, this->y - thickness,
		this->width2 + 1, thickness * 2);
	QRegion region(rect.toRect());

	rect = QRectF(this->x + this->width2 - thickness, this->y,
		thickness * 2, this->height2);
	region += QRegion(rect.toRect());

	rect = QRectF(this->x + this->width, this->y + this->height2 - thickness,
		this->x + this->width + this->width2, thickness * 2);
	region += QRegion(rect.toRect());

	rect = QRectF(this->x + this->width - thickness, this->y + this->height2 - 1,
		thickness * 2, this->height);
	region += QRegion(rect.toRect());

	return region;
}

void RepeatFalse::ReSize(float width, float height, float width2, float height2) {
	this->width = width;
	this->height = height;
	this->width2 = width2;
	this->height2 = height2;
}

bool RepeatFalse::IsIncluded(QPointF point) {
	bool ret;

	QRegion region;
	QRectF regionRect(this->x, this->y - LINETHICKNESS,
		this->width2, LINETHICKNESS * 2);
	region = QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width2 - LINETHICKNESS, this->y,
		LINETHICKNESS * 2, this->height2);
	region += QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width, this->y + this->height2 - LINETHICKNESS,
		this->x + this->width + this->width2, LINETHICKNESS * 2);
	region += QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width - LINETHICKNESS, this->y + this->height2,
		LINETHICKNESS * 2, this->height);
	region += QRegion(regionRect.toRect());

	ret = region.contains(point.toPoint());

	return ret;
}

bool RepeatFalse::IsIncluded(const QRectF& rect) {
	bool ret;

	QRegion region;
	QRectF regionRect(this->x, this->y - LINETHICKNESS,
		this->width2, LINETHICKNESS * 2);
	region = QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width2 - LINETHICKNESS, this->y,
		LINETHICKNESS * 2, this->height2);
	region += QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width, this->y + this->height2 - LINETHICKNESS,
		this->x + this->width + this->width2, LINETHICKNESS * 2);
	region += QRegion(regionRect.toRect());

	regionRect = QRectF(this->x + this->width - LINETHICKNESS, this->y + this->height2,
		LINETHICKNESS * 2, this->height);
	region += QRegion(regionRect.toRect());

	ret = region.contains(rect.toRect());

	return ret;
}

void RepeatFalse::Copy(NShape *object) {
	x = object->GetX();
	y = object->GetY();
	width = object->GetWidth();
	height = object->GetHeight();
	backGroundColor = object->GetBackGroundColor();
	borderLine = object->GetBorderLine();
	borderColor = object->GetBorderColor();
	contents = object->GetContents();
	width2 = dynamic_cast<RepeatFalse *>(object)->GetWidth2();
	height2 = dynamic_cast<RepeatFalse *>(object)->GetHeight2();
	isSelected = object->IsSelected();
}

void RepeatFalse::GetSelectionMarkerRect(int marker, QRectF *rect) {
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

QRegion RepeatFalse::GetSelectionMarkerAllRegion() {
	float x = this->x;
	float y = this->y;
	QRectF rect(x - 6, y - 6, 7, 7);
	QRegion region(rect.toRect());

	x = this->x + this->width2;
	y = this->y + this->height2;
	rect = QRect(x - 6, y - 6, 7, 7);
	region += QRegion(rect.toRect());

	x = this->x + this->width;
	y = this->y + this->height;
	rect = QRect(x - 6, y - 6, 7, 7);
	region += QRegion(rect.toRect());

	return region;
}

int RepeatFalse::GetHitCode(const QPointF& point, const QRegion& region) {
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

void RepeatFalse::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
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

void RepeatFalse::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x + this->width);
	attribute->pointOut.setY(this->y + this->height);
}

void RepeatFalse::GetLine(char(*line)) {
	sprintf(line, "%d\t%f\t%f\t%f\t%f\t%f\t%f\t%s;\n",
		ID_REPEATFALSE, this->x, this->y, this->width, this->height, this->width2, this->height2,
		this->contents.GetString());
}

bool RepeatFalse::IsStyle(Long style) {
	bool ret = false;
	if (NShape::IsStyle(style) || Line::IsStyle(style) || (style >> 14) % 2) {
		ret = true;
	}
	return ret;
}