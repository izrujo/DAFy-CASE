/******************************************************************
* 파일 이름 : Process.cpp
* 기능 : 처리기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/
#pragma warning (disable : 4996)

#include "Process.h"
#include "../../Paint/FlowChartVisitor.h"

#include "../../../Graphic Objects/Composite/Painter.h"

Process::Process(float x, float y, float width, float height, QColor backGroundColor,
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

QRegion Process::GetRegion() {
	QRectF rect(this->x, this->y, this->width, this->height);
	QRegion region(rect.toRect());
	
	return region;
}

QRegion Process::GetRegion(Long thickness) {
	float x = this->x - thickness;
	float y = this->y - thickness;
	float width = this->width + thickness * 2.0F;
	float height = this->height + thickness * 2.0F;

	QRectF rect(this->x, this->y, width, height);
	QRegion region(rect.toRect());
	
	return region;
}

bool Process::IsIncluded(QPointF point) {
	bool ret;

	QRectF rect(this->x, this->y, this->width, this->height);
	QRegion region(rect.toRect());
	ret = region.contains(point.toPoint());
	
	return ret;
}

bool Process::IsIncluded(const QRectF& rect) {
	bool ret;

	QRectF regionRect(this->x, this->y, this->width, this->height);
	QRegion region(regionRect.toRect());
	ret = region.contains(rect.toRect());

	return ret;
}

void Process::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.setX(this->x + this->width / 2.0F);
	attribute->pointIn.setY(this->y);

	attribute->pointOut.setX(this->x + this->width / 2.0F);
	attribute->pointOut.setY(this->y + this->height);
}

void Process::GetLine(char(*line)) {
	String saveContents(this->contents);

	sprintf(line, "%d\t%f\t%f\t%f\t%f\t\t\t%s;\n", 
		ID_PROCESS, this->x, this->y, this->width, this->height, saveContents.GetString());
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