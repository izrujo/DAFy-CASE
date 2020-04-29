#include "A4Paper.h"
#include "FlowChartVisitor.h"

A4Paper::A4Paper(float x, float y, float width, float height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: NShape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
	this->isMarking = true;
	this->leftMargin = 40.0;
	this->topMargin = 40.0;
	this->rightMargin = 40.0;
	this->bottomMargin = 40.0;
}

A4Paper::~A4Paper() {
}

A4Paper::A4Paper(const A4Paper& source)
	:NShape(source) {
	this->isMarking = true;
	this->leftMargin = source.leftMargin;
	this->topMargin = source.topMargin;
	this->rightMargin = source.rightMargin;
	this->bottomMargin = source.bottomMargin;
}

A4Paper& A4Paper::operator =(const A4Paper& source) {
	NShape::operator=(source);
	this->isMarking = true;
	this->leftMargin = source.leftMargin;
	this->topMargin = source.topMargin;
	this->rightMargin = source.rightMargin;
	this->bottomMargin = source.bottomMargin;
	return *this;
}

void A4Paper::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* A4Paper::Clone() {
	return new A4Paper(*this);
}

void A4Paper::SetIsMarking(bool isMarking) {
	this->isMarking = isMarking;
}

void A4Paper::ChangeMargin(float leftMargin, float topMargin, float rightMargin, float bottomMargin) {
	this->leftMargin = leftMargin;
	this->topMargin = topMargin;
	this->rightMargin = rightMargin;
	this->bottomMargin = bottomMargin;
}