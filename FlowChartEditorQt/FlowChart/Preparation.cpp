/******************************************************************
* 파일 이름 : Preparation.cpp
* 기능 : 준비기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/

#include "Preparation.h"
#include "../GObject/Painter.h"
#include "Preparation.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)


Preparation::Preparation(float x, float y, float width, float height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: Symbol(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

Preparation::~Preparation() {

}

Preparation::Preparation(const Preparation& source) : Symbol(source) {
}

Preparation& Preparation::operator =(const Preparation& source) {
	Symbol::operator=(source);

	return *this;
}

bool Preparation::IsEqual(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<Preparation *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool Preparation::IsNotEqual(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<Preparation *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

bool Preparation::operator ==(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<Preparation *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool Preparation::operator !=(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<Preparation *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

void Preparation::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* Preparation::Clone() {
	return new Preparation(*this);
}

QRegion Preparation::GetRegion() {
	float halfHeight = this->height / 2;

	QVector<QPointF> points(7);
	points.append(QPointF(this->x + halfHeight, this->y));
	points.append(QPointF(this->x + this->width - halfHeight, this->y));
	points.append(QPointF(this->x + this->width, this->y + halfHeight));
	points.append(QPointF(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPointF(this->x + halfHeight, this->y + this->height));
	points.append(QPointF(this->x, this->y + halfHeight));
	points.append(QPointF(this->x + halfHeight, this->y));
	QPolygonF polygon(points);

	QRegion region(polygon.toPolygon());

	return region;
}

QRegion Preparation::GetRegion(Long thickness) {
	float x = this->x - thickness;
	float y = this->y - thickness;
	float width = this->width + thickness * 2.0F;
	float height = this->height + thickness * 2.0F;
	float halfHeight = this->height / 2.0F;

	QVector<QPointF> points(7);
	points.append(QPointF(this->x + halfHeight, this->y));
	points.append(QPointF(this->x + this->width - halfHeight, this->y));
	points.append(QPointF(this->x + this->width, this->y + halfHeight));
	points.append(QPointF(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPointF(this->x + halfHeight, this->y + this->height));
	points.append(QPointF(this->x, this->y + halfHeight));
	points.append(QPointF(this->x + halfHeight, this->y));
	QPolygonF polygon(points);

	QRegion region(polygon.toPolygon());

	return region;
}

bool Preparation::IsIncluded(QPointF point) {
	bool ret;
	float halfHeight = this->height / 2;

	QVector<QPointF> points(7);
	points.append(QPointF(this->x + halfHeight, this->y));
	points.append(QPointF(this->x + this->width - halfHeight, this->y));
	points.append(QPointF(this->x + this->width, this->y + halfHeight));
	points.append(QPointF(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPointF(this->x + halfHeight, this->y + this->height));
	points.append(QPointF(this->x, this->y + halfHeight));
	points.append(QPointF(this->x + halfHeight, this->y));
	QPolygonF polygon(points);

	QRegion region(polygon.toPolygon());
	ret = region.contains(point.toPoint());

	return ret;
}

bool Preparation::IsIncluded(const QRectF& rect) {
	bool ret;
	float halfHeight = this->height / 2;

	QVector<QPointF> points(7);
	points.append(QPointF(this->x + halfHeight, this->y));
	points.append(QPointF(this->x + this->width - halfHeight, this->y));
	points.append(QPointF(this->x + this->width, this->y + halfHeight));
	points.append(QPointF(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPointF(this->x + halfHeight, this->y + this->height));
	points.append(QPointF(this->x, this->y + halfHeight));
	points.append(QPointF(this->x + halfHeight, this->y));
	QPolygonF polygon(points);

	QRegion region(polygon.toPolygon());

	ret = region.contains(rect.toRect());

	return ret;
}

void Preparation::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x + this->width / 2.0F);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x + this->width / 2.0F);
	attribute->pointOut.setY(this->y + this->height);
}

void Preparation::GetLine(char(*line)) {
	String saveContents(this->contents);

	sprintf(line, "%d\t%f\t%f\t%f\t%f\t\t\t%s;\n", 
		ID_PREPARATION, this->x, this->y, this->width, this->height, saveContents.GetString());
}


bool Preparation::IsStyle(Long style) {
	bool ret = false;
	if (NShape::IsStyle(style) || Symbol::IsStyle(style) || (style >> 3) % 2) {
		ret = true;
	}
	return ret;
}

void Preparation::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
	NShape::DrawSelectionMarkers(painter, scrollController);
}