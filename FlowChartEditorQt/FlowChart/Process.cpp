/******************************************************************
* 파일 이름 : Process.cpp
* 기능 : 처리기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/

#include "Process.h"
#include "Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

Process::Process(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
	:Symbol(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
}

Process::~Process() {};

Process::Process(const Process& source) :Symbol(source) {
}

Process Process::operator =(const Process& source) {
	Symbol::operator=(source);
	return *this;
}

bool Process::IsEqual(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<Process *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Process::IsNotEqual(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<Process *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool Process::operator ==(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<Process *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Process::operator !=(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<Process *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

void Process::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

Shape* Process::Clone() {
	return new Process(*this);
}

void Process::GetRegion(CDC *dc, CRgn *region) {
	region->CreateRectRgn(x, y, x + width, y + height);
}

void Process::GetRegion(Painter *painter, CRgn *region) {
	region->CreateRectRgn(x, y, x + width, y + height);
}

void Process::GetRegion(CDC *dc, Long thickness, CRgn *region) {
	Long x_, y_, width_, height_;
	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness * 2;
	height_ = height + thickness * 2;
	region->CreateRectRgn(x_, y_, x_ + width_, y_ + height_);
}

void Process::GetRegion(Painter *painter, Long thickness, CRgn *region) {
	Long x_, y_, width_, height_;
	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness * 2;
	height_ = height + thickness * 2;
	region->CreateRectRgn(x_, y_, x_ + width_, y_ + height_);
}

BOOL Process::IsIncluded(CDC *dc, POINT point) {
	CRgn region;
	BOOL ret;
	region.CreateRectRgn(x, y, x + width, y + height);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Process::IsIncluded(Painter *painter, POINT point) {
	CRgn region;
	BOOL ret;
	region.CreateRectRgn(x, y, x + width, y + height);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Process::IsIncluded(Painter *painter, const RECT& rect) {
	CRgn region;
	BOOL ret;
	region.CreateRectRgn(x, y, x + width, y + height);
	ret = region.RectInRegion(&rect);
	region.DeleteObject();
	return ret;
}

void Process::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.x = x + width / 2;
	attribute->pointIn.y = y;

	attribute->pointOut.x = x + width / 2;
	attribute->pointOut.y = y + height;
}

void Process::GetLine(char(*line)) {
	String saveContents(contents);
	saveContents.Replace('\n', '\r');

	sprintf(line, "%d\t%d\t%d\t%d\t%d\t\t\t%s\n", ID_PROCESS, x, y, width, height, saveContents);
}

bool Process::IsStyle(Long style) {
	bool ret = false;
	if (Shape::IsStyle(style) || Symbol::IsStyle(style) || (style >> 5) % 2) {
		ret = true;
	}
	return ret;
}

void Process::DrawSelectionMarkers(CDC* dc, ScrollController *scrollController) {
	Shape::DrawSelectionMarkers(dc, scrollController);
}

void Process::DrawSelectionMarkers(Painter* painter, ScrollController *scrollController) {
	Shape::DrawSelectionMarkers(painter, scrollController);
}