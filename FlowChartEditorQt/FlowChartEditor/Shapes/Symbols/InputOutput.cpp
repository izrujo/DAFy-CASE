// InputOutput.cpp

/******************************************************************
* 파일 이름 : InputOutput.cpp
* 기능 : 입력출력기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2016년 2월 22일
*******************************************************************/
#pragma warning (disable : 4996)

#include "InputOutput.h"
#include "../../Paint/FlowChartVisitor.h"

#include "../../../Graphic Objects/Composite/Painter.h"

InputOutput::InputOutput(float x, float y, float width, float height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: Symbol(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

InputOutput::~InputOutput() {

}

InputOutput::InputOutput(const InputOutput& source) 
	: Symbol(source) {

}

InputOutput& InputOutput::operator=(const InputOutput& source) {
	Symbol::operator=(source);

	return *this;
}

bool InputOutput::IsEqual(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<InputOutput *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool InputOutput::IsNotEqual(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<InputOutput *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

bool InputOutput::operator ==(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<InputOutput *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool InputOutput::operator !=(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<InputOutput *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

void InputOutput::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* InputOutput::Clone() {
	return new InputOutput(*this);
}

QRegion InputOutput::GetRegion() {
	float halfWidth = this->width / 2.0F;
	float halfHeight = this->height / 2.0F;

	QVector<QPointF> points(5);
	points.append(QPointF(this->x + halfHeight, this->y));
	points.append(QPointF(this->x + this->width, this->y));
	points.append(QPointF(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPointF(this->x, this->y + this->height));
	points.append(QPointF(this->x + halfHeight, this->y));
	QPolygonF polygon(points);
	
	QRegion region(polygon.toPolygon());

	return region;
}

QRegion InputOutput::GetRegion(Long thickness) {
	float x = this->x - thickness;
	float y = this->y - thickness;
	float width = this->width + thickness * 2.0F;
	float height = this->height + thickness * 2.0F;
	float halfWidth = this->width / 2.0F;
	float halfHeight = this->height / 2.0F;

	QVector<QPointF> points(5);
	points.append(QPointF(this->x + halfHeight, this->y));
	points.append(QPointF(this->x + this->width, this->y));
	points.append(QPointF(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPointF(this->x, this->y + this->height));
	points.append(QPointF(this->x + halfHeight, this->y));
	QPolygonF polygon(points);

	QRegion region(polygon.toPolygon());

	return region;
}

bool InputOutput::IsIncluded(QPointF point) {
	bool ret;
	float halfWidth = this->width / 2.0F;
	float halfHeight = this->height / 2.0F;

	QVector<QPointF> points(5);
	points.append(QPointF(this->x + halfHeight, this->y));
	points.append(QPointF(this->x + this->width, this->y));
	points.append(QPointF(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPointF(this->x, this->y + this->height));
	points.append(QPointF(this->x + halfHeight, this->y));
	QPolygonF polygon(points);

	QRegion region(polygon.toPolygon());
	ret = region.contains(point.toPoint());

	return ret;
}

bool InputOutput::IsIncluded(const QRectF& rect) {
	bool ret;
	float halfWidth = this->width / 2.0F;
	float halfHeight = this->height / 2.0F;

	QVector<QPointF> points(5);
	points.append(QPointF(this->x + halfHeight, this->y));
	points.append(QPointF(this->x + this->width, this->y));
	points.append(QPointF(this->x + this->width - halfHeight, this->y + this->height));
	points.append(QPointF(this->x, this->y + this->height));
	points.append(QPointF(this->x + halfHeight, this->y));
	QPolygonF polygon(points);

	QRegion region(polygon.toPolygon());
	ret = region.contains(rect.toRect());

	return ret;
}

void InputOutput::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x + this->width / 2.0F);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x + this->width / 2.0F);
	attribute->pointOut.setY(this->y + this->height);
}

void InputOutput::GetLine(char(*line)) {
	String saveContents(this->contents);

	sprintf(line, "%d\t%f\t%f\t%f\t%f\t\t\t%s;\n", 
		ID_INPUTOUTPUT, this->x, this->y, this->width, this->height, saveContents.GetString());
}

bool InputOutput::IsStyle(Long style) {
	bool ret = false;
	if (NShape::IsStyle(style) || Symbol::IsStyle(style) || (style >> 8) % 2) {
		ret = true;
	}
	return ret;
}

void InputOutput::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
	NShape::DrawSelectionMarkers(painter, scrollController);
}