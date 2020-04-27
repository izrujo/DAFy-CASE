/******************************************************************
* 파일 이름 : Arrow.cpp
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#include "Arrow.h"
#include "../GObject/Painter.h"
#pragma warning (disable : 4996)
#include "FlowChartVisitor.h"

#include "ScrollController.h"
#include "Scroll.h"

#include "../GObject/QtGObjectFactory.h"

Arrow::Arrow(Long x, Long y, Long width, Long height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	:Line(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

Arrow::~Arrow() {

}

Arrow::Arrow(const Arrow& source) : Line(source) {

}

Arrow& Arrow::operator =(const Arrow& source) {
	Line::operator=(source);

	return *this;
}

bool Arrow::IsEqual(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<Arrow *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool Arrow::IsNotEqual(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<Arrow *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

bool Arrow::operator ==(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<Arrow *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool Arrow::operator !=(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<Arrow *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

void Arrow::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

void Arrow::DrawActiveShape(GObject *painter) {
	QPoint point1(this->x, this->y);
	QPoint point2(this->x + this->width, this->y + this->height);
	painter->DrawLine(point1, point2);
}

NShape* Arrow::Clone() {
	return new Arrow(*this);
}

QRegion Arrow::GetRegion() {
	QRect rect(this->x - LINETHICKNESS, this->y, LINETHICKNESS, this->height);
	QRegion region(rect);

	return region;
}

QRegion Arrow::GetRegion(Long thickness) {
	QRect rect(this->x - thickness, this->y, thickness, this->height);
	QRegion region(rect);

	return region;
}

bool Arrow::IsIncluded(QPoint point) {
	QRect rect(this->x - LINETHICKNESS, this->y, LINETHICKNESS, this->height);
	QRegion region(rect);
	bool ret;
	ret = region.contains(point);
	return ret;
}

bool Arrow::IsIncluded(const QRect& rect) {
	QRect regionRect(x - LINETHICKNESS, y, LINETHICKNESS, height);
	QRegion region(regionRect);
	bool ret;
	ret = region.contains(rect);
	return ret;
}

int Arrow::GetHitCode(const QPoint& point, const QRegion& region) {
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

void Arrow::GetSelectionMarkerRect(int marker, QRect *rect) {
	int x;
	int y;

	switch (marker) {
	case HIT_IN: // 매크로 LEFTTOP
		x = this->x;
		y = this->y;
		break;

	case HIT_OUT:
		x = this->x;
		y = this->y + this->height;
		break;
	}
	rect->setCoords(x - 4, y - 4, x + 5, y + 5);
}

QRegion Arrow::GetSelectionMarkerAllRegion() {
	QRegion region;
	QRect rect;

	Long x = this->x;
	Long y = this->y;
	rect.setCoords(x - 6, y - 6, 7, 7);
	region = QRegion(rect);

	x = this->x;
	y = this->y + this->height;
	rect.setCoords(x - 6, y - 6, 7, 7);
	region += QRegion(rect);
	
	return region;
}

void Arrow::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
	QRect rectSelect;

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

void Arrow::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x);
	attribute->pointOut.setY(this->y + this->height);
}

void Arrow::GetLine(char(*line)) {
	sprintf(line, "%d\t%d\t%d\t%d\t%d\t\t\t%s\n", 
		ID_ARROW, this->x, this->y, this->width, this->height, this->contents.GetString());
}

bool Arrow::IsStyle(Long style) {
	bool ret = false;
	if (NShape::IsStyle(style) || Line::IsStyle(style) || (style >> 9) % 2) {
		ret = true;
	}
	return ret;
}