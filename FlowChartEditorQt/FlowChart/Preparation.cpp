/******************************************************************
* 파일 이름 : Preparation.cpp
* 기능 : 준비기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/

#include "Preparation.h"
#include "Painter.h"
#include "Preparation.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)


Preparation::Preparation(Long x, Long y, Long width, Long height, QColor backGroundColor,
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

bool Preparation::IsEqual(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<Preparation *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Preparation::IsNotEqual(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<Preparation *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool Preparation::operator ==(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<Preparation *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Preparation::operator !=(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<Preparation *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

void Preparation::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

Shape* Preparation::Clone() {
	return new Preparation(*this);
}

void Preparation::GetRegion(QRegion *region) {
	Long halfHeight = (Long)this->height / 2;

	QVector<QPoint> points(7);
	points.append(QPoint(this->x + halfHeight, this->y));
	points.append(QPoint(this->x + this->width - halfHeight, this->y));
	points.append(QPoint(this->x + this->width, this->y + halfHeight));
	points.append(QPoint(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPoint(this->x + halfHeight, this->y + this->height));
	points.append(QPoint(this->x, this->y + halfHeight));
	points.append(QPoint(this->x + halfHeight, this->y));
	QPolygon polygon(points);

	*region += QRegion(polygon);
}

void Preparation::GetRegion(Long thickness, QRegion *region) {
	Long x = this->x - thickness;
	Long y = this->y - thickness;
	Long width = this->width + thickness * 2;
	Long height = this->height + thickness * 2;
	Long halfHeight = this->height / 2;

	QVector<QPoint> points(7);
	points.append(QPoint(this->x + halfHeight, this->y));
	points.append(QPoint(this->x + this->width - halfHeight, this->y));
	points.append(QPoint(this->x + this->width, this->y + halfHeight));
	points.append(QPoint(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPoint(this->x + halfHeight, this->y + this->height));
	points.append(QPoint(this->x, this->y + halfHeight));
	points.append(QPoint(this->x + halfHeight, this->y));
	QPolygon polygon(points);

	*region += QRegion(polygon);
}

bool Preparation::IsIncluded(QPoint point) {
	bool ret;
	Long halfHeight = (Long)this->height / 2;

	QVector<QPoint> points(7);
	points.append(QPoint(this->x + halfHeight, this->y));
	points.append(QPoint(this->x + this->width - halfHeight, this->y));
	points.append(QPoint(this->x + this->width, this->y + halfHeight));
	points.append(QPoint(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPoint(this->x + halfHeight, this->y + this->height));
	points.append(QPoint(this->x, this->y + halfHeight));
	points.append(QPoint(this->x + halfHeight, this->y));
	QPolygon polygon(points);

	QRegion region(polygon);
	ret = region.contains(point);

	return ret;
}

bool Preparation::IsIncluded(const QRect& rect) {
	bool ret;
	Long halfHeight = (Long)this->height / 2;

	QVector<QPoint> points(7);
	points.append(QPoint(this->x + halfHeight, this->y));
	points.append(QPoint(this->x + this->width - halfHeight, this->y));
	points.append(QPoint(this->x + this->width, this->y + halfHeight));
	points.append(QPoint(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPoint(this->x + halfHeight, this->y + this->height));
	points.append(QPoint(this->x, this->y + halfHeight));
	points.append(QPoint(this->x + halfHeight, this->y));
	QPolygon polygon(points);

	QRegion region(polygon);

	ret = region.contains(rect);

	return ret;
}

void Preparation::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x + this->width / 2);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x + this->width / 2);
	attribute->pointOut.setY(this->y + this->height);
}

void Preparation::GetLine(char(*line)) {
	String saveContents(this->contents);
	saveContents.Replace('\n', '\r');

	sprintf(line, "%d\t%d\t%d\t%d\t%d\t\t\t%s\n", 
		ID_PREPARATION, this->x, this->y, this->width, this->height, saveContents);
}


bool Preparation::IsStyle(Long style) {
	bool ret = false;
	if (Shape::IsStyle(style) || Symbol::IsStyle(style) || (style >> 3) % 2) {
		ret = true;
	}
	return ret;
}

void Preparation::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
	Shape::DrawSelectionMarkers(painter, scrollController);
}