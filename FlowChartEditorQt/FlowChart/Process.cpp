/******************************************************************
* 파일 이름 : Process.cpp
* 기능 : 처리기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/

#include "Process.h"
#include "../GObject/Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

Process::Process(Long x, Long y, Long width, Long height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: Symbol(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

Process::~Process() {

}

Process::Process(const Process& source) :Symbol(source) {

}

Process& Process::operator =(const Process& source) {
	Symbol::operator=(source);

	return *this;
}

bool Process::IsEqual(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<Process *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool Process::IsNotEqual(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<Process *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

bool Process::operator ==(const NShape& other) {
	bool retVo = false;
	if (dynamic_cast<Process *>(const_cast<NShape *>(&other))) {
		retVo = NShape::IsEqual(other);
	}
	return retVo;
}

bool Process::operator !=(const NShape& other) {
	bool retVo = false;
	if (!dynamic_cast<Process *>(const_cast<NShape*>(&other))) {
		retVo = NShape::IsNotEqual(other);
	}
	return retVo;
}

void Process::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* Process::Clone() {
	return new Process(*this);
}

void Process::GetRegion(QRegion *region) {
	QRect rect;
	rect.setCoords(this->x, this->y, this->x + this->width, this->y + this->height);
	QRegion addRegion(rect);
	*region += addRegion;
}

void Process::GetRegion(Long thickness, QRegion *region) {
	Long x = this->x - thickness;
	Long y = this->y - thickness;
	Long width = this->width + thickness * 2;
	Long height = this->height + thickness * 2;

	QRect rect;
	rect.setCoords(this->x, this->y, this->x + this->width, this->y + this->height);
	QRegion addRegion(rect);
	*region += addRegion;
}

bool Process::IsIncluded(QPoint point) {
	bool ret;

	QRect rect;
	rect.setCoords(this->x, this->y, this->x + this->width, this->y + this->height);
	QRegion region(rect);
	ret = region.contains(point);
	
	return ret;
}

bool Process::IsIncluded(const QRect& rect) {
	bool ret;

	QRect regionRect;
	regionRect.setCoords(this->x, this->y, this->x + this->width, this->y + this->height);
	QRegion region(regionRect);
	ret = region.contains(rect);

	return ret;
}

void Process::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x + this->width / 2);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x + this->width / 2);
	attribute->pointOut.setY(this->y + this->height);
}

void Process::GetLine(char(*line)) {
	String saveContents(this->contents);
	saveContents.Replace('\n', '\r');

	sprintf(line, "%d\t%d\t%d\t%d\t%d\t\t\t%s\n", 
		ID_PROCESS, this->x, this->y, this->width, this->height, saveContents);
}

bool Process::IsStyle(Long style) {
	bool ret = false;
	if (NShape::IsStyle(style) || Symbol::IsStyle(style) || (style >> 5) % 2) {
		ret = true;
	}
	return ret;
}

void Process::DrawSelectionMarkers(GObject *painter, ScrollController *scrollController) {
	NShape::DrawSelectionMarkers(painter, scrollController);
}