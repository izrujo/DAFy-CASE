/******************************************************************
* 파일 이름 : Decision.cpp
* 기능 : 판단기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/
#pragma warning (disable : 4996)

#include "Decision.h"
#include "../../Paint/FlowChartVisitor.h"

#include "../../../Graphic Objects/Composite/Painter.h"

Decision::Decision(float x, float y, float width, float height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: Symbol(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

Decision::~Decision() {

}

Decision::Decision(const Decision& source)
	: Symbol(source) {

}

Decision& Decision::operator =(const Decision& source) {
	Symbol::operator=(source);

	return *this;
}

bool Decision::IsEqual(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<Decision *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool Decision::IsNotEqual(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<Decision *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

bool Decision::operator ==(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<Decision *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool Decision::operator !=(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<Decision *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

NShape* Decision::Clone() {
	return new Decision(*this);
}

void Decision::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

QRegion Decision::GetRegion() {
	float halfWidth = this->width / 2;
	float halfHeight = this->height / 2;
	
	QVector<QPointF> points(5);
	points.append(QPointF(this->x + halfWidth, this->y));
	points.append(QPointF(this->x + this->width, this->y + halfHeight));
	points.append(QPointF(this->x + halfWidth, this->y + this->height));
	points.append(QPointF(this->x, this->y + halfHeight));
	points.append(QPointF(this->x + halfWidth, this->y));
	QPolygonF polygon(points);

	QRegion region(polygon.toPolygon());

	return region;
}

QRegion Decision::GetRegion(Long thickness) {
	float x = this->x - thickness;
	float y = this->y - thickness;
	float width = this->width + thickness * 2;
	float height = this->height + thickness * 2;
	float halfWidth = width / 2;
	float halfHeight = height / 2;

	QVector<QPointF> points(5);
	points.append(QPointF(x + halfWidth, y));
	points.append(QPointF(x + width, y + halfHeight));
	points.append(QPointF(x + halfWidth, y + height));
	points.append(QPointF(x, y + halfHeight));
	points.append(QPointF(x + halfWidth, y));
	QPolygonF polygon(points);

	QRegion region(polygon.toPolygon());

	return region;
}

bool Decision::IsIncluded(QPointF point) {
	bool ret;
	float halfWidth = this->width / 2;
	float halfHeight = this->height / 2;

	QVector<QPointF> points(5);
	points.append(QPointF(this->x + halfWidth, this->y));
	points.append(QPointF(this->x + this->width, this->y + halfHeight));
	points.append(QPointF(this->x + halfWidth, this->y + this->height));
	points.append(QPointF(this->x, this->y + halfHeight));
	points.append(QPointF(this->x + halfWidth, this->y));
	QPolygonF polygon(points);

	QRegion region(polygon.toPolygon());
	ret = region.contains(point.toPoint());
	
	return ret;
}

bool Decision::IsIncluded(const QRectF& rect) {
	bool ret;
	float halfWidth = this->width / 2;
	float halfHeight = this->height / 2;

	QVector<QPointF> points(5);
	points.append(QPointF(this->x + halfWidth, this->y));
	points.append(QPointF(this->x + this->width, this->y + halfHeight));
	points.append(QPointF(this->x + halfWidth, this->y + this->height));
	points.append(QPointF(this->x, this->y + halfHeight));
	points.append(QPointF(this->x + halfWidth, this->y));
	QPolygonF polygon(points);

	QRegion region(polygon.toPolygon());
	ret = region.contains(rect.toRect());

	return ret;
}

void Decision::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexTrue = 'Y';
	attribute->vertexFalse = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x + this->width / 2);
	attribute->pointIn.setY(this->y);

	attribute->pointTrue.setX(this->x);
	attribute->pointTrue.setY(this->y +this->height / 2);

	attribute->pointFalse.setX(this->x + this->width);
	attribute->pointFalse.setY(this->y + this->height / 2);

	attribute->pointOut.setX(this->x + this->width / 2);
	attribute->pointOut.setY(this->y + this->height);
}

void Decision::GetLine(char(*line)) {
	String saveContents(this->contents);

	sprintf(line, "%d\t%f\t%f\t%f\t%f\t\t\t%s;\n", 
		ID_DECISION, this->x, this->y, this->width, this->height, saveContents.GetString());
}

bool Decision::IsStyle(Long style) {
	bool ret = false;
	if (NShape::IsStyle(style) || Symbol::IsStyle(style) || (style >> 6) % 2) {
		ret = true;
	}
	return ret;
}

void Decision::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
	NShape::DrawSelectionMarkers(painter, scrollController);
}