/******************************************************************
* 파일 이름 : Terminal.cpp
* 기능 : 단말기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/
#pragma warning (disable : 4996)

#include "Terminal.h"
#include "../../Paint/FlowChartVisitor.h"

#include "../../../Graphic Objects/Composite/Painter.h"

Terminal::Terminal(float x, float y, float width, float height,
	QColor backGroundColor, Qt::PenStyle borderLine, QColor borderColor, String contents)
	: Symbol(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
}

Terminal::~Terminal() {

}

Terminal::Terminal(const Terminal& source) : Symbol(source) {

}

Terminal& Terminal::operator =(const Terminal& source) {
	Symbol::operator=(source);

	return *this;
}

bool Terminal::IsEqual(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<Terminal *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool Terminal::IsNotEqual(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<Terminal *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

bool Terminal::operator ==(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<Terminal *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool Terminal::operator !=(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<Terminal *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

void Terminal::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* Terminal::Clone() {
	return new Terminal(*this);
}

QRegion Terminal::GetRegion() {
	float halfHeight = this->height / 2.0F;

	QRectF ellipse;

	ellipse = QRectF(this->x, this->y, this->height, this->height);
	QRegion region(ellipse.toRect(), QRegion::Ellipse);
	
	ellipse = QRectF(this->x + this->width - this->height, this->y, this->height, this->height);
	region += QRegion(ellipse.toRect(), QRegion::Ellipse);
	
	QRectF rectangle(this->x + halfHeight, this->y, this->width - this->height, this->height);
	region += QRegion(rectangle.toRect(), QRegion::Rectangle);
	
	return region;
}


QRegion Terminal::GetRegion(Long thickness) {
	float x = this->x - thickness;
	float y = this->y - thickness;
	float width = this->width + thickness * 2;
	float height = this->height + thickness * 2;
	float halfHeight = height / 2;

	QRectF ellipse;

	ellipse = QRectF(x, y, height, height);
	QRegion region(ellipse.toRect(), QRegion::Ellipse);
	
	ellipse = QRectF(x + width - height, y, height, height);
	region += QRegion(ellipse.toRect(), QRegion::Ellipse);
	
	QRectF rectangle(x + halfHeight, y, width - height, height);
	region += QRegion(rectangle.toRect(), QRegion::Rectangle);
	
	return region;
}

bool Terminal::IsIncluded(QPointF point) {
	bool ret;
	
	float halfHeight = this->height / 2;

	QRectF ellipse(this->x, this->y, this->height, this->height);
	QRegion region(ellipse.toRect(), QRegion::Ellipse);

	ellipse = QRectF(this->x + this->width - this->height, this->y, this->height, this->height);
	region += QRegion(ellipse.toRect(), QRegion::Ellipse);

	QRectF rectangle(this->x + halfHeight, this->y, this->width - this->height, this->height);
	region += QRegion(rectangle.toRect(), QRegion::Rectangle);

	ret = region.contains(point.toPoint());

	return ret;
}

bool Terminal::IsIncluded(const QRectF& rect) {
	bool ret;

	float halfHeight = this->height / 2;

	QRectF ellipse(this->x, this->y, this->height, this->height);
	QRegion region(ellipse.toRect(), QRegion::Ellipse);

	ellipse = QRectF(this->x + this->width - this->height, this->y, this->height, this->height);
	region += QRegion(ellipse.toRect(), QRegion::Ellipse);

	QRectF rectangle(this->x + halfHeight, this->y, this->width - this->height, this->height);
	region += QRegion(rectangle.toRect(), QRegion::Rectangle);

	ret = region.contains(rect.toRect());
 
	return ret;
}

void Terminal::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x + this->width / 2);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x + this->width / 2);
	attribute->pointOut.setY(this->y + this->height);
}

void Terminal::GetLine(char(*line)) {
	String saveContents(this->contents);

	sprintf(line, "%d\t%f\t%f\t%f\t%f\t\t\t%s;\n", 
		ID_TERMINAL, this->x, this->y, this->width, this->height, saveContents.GetString());
}

bool Terminal::IsStyle(Long style) {
	bool ret = false;
	if (NShape::IsStyle(style) || Symbol::IsStyle(style) || (style >> 2) % 2) {
		ret = true;
	}
	return ret;
}

void Terminal::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
	NShape::DrawSelectionMarkers(painter, scrollController);
}