/******************************************************************
* 파일 이름 : Decision.cpp
* 기능 : 판단기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/

#include "Decision.h"
#include "../GObject/Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

Decision::Decision(Long x, Long y, Long width, Long height, QColor backGroundColor,
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
	Long halfWidth = (Long)this->width / 2;
	Long halfHeight = (Long)this->height / 2;
	
	QVector<QPoint> points(5);
	points.append(QPoint(this->x + halfWidth, this->y));
	points.append(QPoint(this->x + this->width, this->y + halfHeight));
	points.append(QPoint(this->x + halfWidth, this->y + this->height));
	points.append(QPoint(this->x, this->y + halfHeight));
	points.append(QPoint(this->x + halfWidth, this->y));
	QPolygon polygon(points);

	QRegion region(polygon);

	return region;
}

QRegion Decision::GetRegion(Long thickness) {
	Long x = this->x - thickness;
	Long y = this->y - thickness;
	Long width = this->width + thickness * 2;
	Long height = this->height + thickness * 2;
	Long halfWidth = width / 2;
	Long halfHeight = height / 2;

	QVector<QPoint> points(5);
	points.append(QPoint(x + halfWidth, y));
	points.append(QPoint(x + width, y + halfHeight));
	points.append(QPoint(x + halfWidth, y + height));
	points.append(QPoint(x, y + halfHeight));
	points.append(QPoint(x + halfWidth, y));
	QPolygon polygon(points);

	QRegion region(polygon);

	return region;
}

bool Decision::IsIncluded(QPoint point) {
	bool ret;
	Long halfWidth = (Long)this->width / 2;
	Long halfHeight = (Long)this->height / 2;

	QVector<QPoint> points(5);
	points.append(QPoint(this->x + halfWidth, this->y));
	points.append(QPoint(this->x + this->width, this->y + halfHeight));
	points.append(QPoint(this->x + halfWidth, this->y + this->height));
	points.append(QPoint(this->x, this->y + halfHeight));
	points.append(QPoint(this->x + halfWidth, this->y));
	QPolygon polygon(points);

	QRegion region(polygon);
	ret = region.contains(point);
	
	return ret;
}

bool Decision::IsIncluded(const QRect& rect) {
	bool ret;
	Long halfWidth = (Long)this->width / 2;
	Long halfHeight = (Long)this->height / 2;

	QVector<QPoint> points(5);
	points.append(QPoint(this->x + halfWidth, this->y));
	points.append(QPoint(this->x + this->width, this->y + halfHeight));
	points.append(QPoint(this->x + halfWidth, this->y + this->height));
	points.append(QPoint(this->x, this->y + halfHeight));
	points.append(QPoint(this->x + halfWidth, this->y));
	QPolygon polygon(points);

	QRegion region(polygon);
	ret = region.contains(rect);

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
	saveContents.Replace('\n', '\r');

	sprintf(line, "%d\t%d\t%d\t%d\t%d\t\t\t%s\n", 
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