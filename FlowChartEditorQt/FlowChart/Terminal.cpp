/******************************************************************
* 파일 이름 : Terminal.cpp
* 기능 : 단말기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#include "Terminal.h"
#include "Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

Terminal::Terminal(Long x, Long y, Long width, Long height,
	QColor backGroundColor, QPen borderLine, QColor borderColor, String contents)
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

bool Terminal::IsEqual(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<Terminal *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Terminal::IsNotEqual(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<Terminal *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool Terminal::operator ==(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<Terminal *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Terminal::operator !=(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<Terminal *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

void Terminal::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

Shape* Terminal::Clone() {
	return new Terminal(*this);
}

void Terminal::GetRegion(QRegion *region) {
	Long halfHeight = (Long)this->height / 2;

	QRect ellipse;
	QRegion addRegion;

	ellipse = QRect(this->x, this->y, this->height, this->height);
	addRegion = QRegion(ellipse, QRegion::Ellipse);
	*region += addRegion;

	ellipse = QRect(this->x + this->width - this->height, this->y, this->height, this->height);
	addRegion = QRegion(ellipse, QRegion::Ellipse);
	*region += addRegion;

	QRect rectangle(this->x + halfHeight, this->y, this->width - this->height, this->height);
	addRegion = QRegion(rectangle, QRegion::Rectangle);
	*region += addRegion;
}


void Terminal::GetRegion(Long thickness, QRegion *region) {
	Long x = x - thickness;
	Long y = y - thickness;
	Long width = width + thickness * 2;
	Long height = height + thickness * 2;
	Long halfHeight = height / 2;

	QRect ellipse;
	QRegion addRegion;

	ellipse = QRect(x, y, height, height);
	addRegion = QRegion(ellipse, QRegion::Ellipse);
	*region += addRegion;

	ellipse = QRect(x + width - height, y, height, height);
	addRegion = QRegion(ellipse, QRegion::Ellipse);
	*region += addRegion;

	QRect rectangle(x + halfHeight, y, width - height, height);
	addRegion = QRegion(rectangle, QRegion::Rectangle);
	*region += addRegion;
}

bool Terminal::IsIncluded(QPoint point) {
	bool ret;
	
	Long halfHeight = (Long)this->height / 2;

	QRect ellipse;
	QRegion addRegion;
	QRegion region;

	ellipse = QRect(this->x, this->y, this->height, this->height);
	addRegion = QRegion(ellipse, QRegion::Ellipse);
	region += addRegion;

	ellipse = QRect(this->x + this->width - this->height, this->y, this->height, this->height);
	addRegion = QRegion(ellipse, QRegion::Ellipse);
	region += addRegion;

	QRect rectangle(this->x + halfHeight, this->y, this->width - this->height, this->height);
	addRegion = QRegion(rectangle, QRegion::Rectangle);
	region += addRegion;

	ret = region.contains(point);

	return ret;
}

bool Terminal::IsIncluded(const QRect& rect) {
	bool ret;

	Long halfHeight = (Long)this->height / 2;

	QRect ellipse;
	QRegion addRegion;
	QRegion region;

	ellipse = QRect(this->x, this->y, this->height, this->height);
	addRegion = QRegion(ellipse, QRegion::Ellipse);
	region += addRegion;

	ellipse = QRect(this->x + this->width - this->height, this->y, this->height, this->height);
	addRegion = QRegion(ellipse, QRegion::Ellipse);
	region += addRegion;

	QRect rectangle(this->x + halfHeight, this->y, this->width - this->height, this->height);
	addRegion = QRegion(rectangle, QRegion::Rectangle);
	region += addRegion;

	ret = region.contains(rect);
 
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
	saveContents.Replace('\n', '\r');

	sprintf(line, "%d\t%d\t%d\t%d\t%d\t\t\t%s\n", 
		ID_TERMINAL, this->x, this->y, this->width, this->height, saveContents);
}

bool Terminal::IsStyle(Long style) {
	bool ret = false;
	if (Shape::IsStyle(style) || Symbol::IsStyle(style) || (style >> 2) % 2) {
		ret = true;
	}
	return ret;
}

void Terminal::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
	Shape::DrawSelectionMarkers(painter, scrollController);
}