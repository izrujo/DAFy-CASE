#include "A4Paper.h"
#include "FlowChartVisitor.h"

A4Paper::A4Paper(Long x, Long y, Long width, Long height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: Shape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
	this->isMarking = true;
	this->leftMargin = 40;
	this->topMargin = 40;
	this->rightMargin = 40;
	this->bottomMargin = 40;
}

A4Paper::~A4Paper() {
}

A4Paper::A4Paper(const A4Paper& source)
	:Shape(source) {
	this->isMarking = true;
	this->leftMargin = source.leftMargin;
	this->topMargin = source.topMargin;
	this->rightMargin = source.rightMargin;
	this->bottomMargin = source.bottomMargin;
}

A4Paper& A4Paper::operator =(const A4Paper& source) {
	Shape::operator=(source);
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

Shape* A4Paper::Clone() {
	return new A4Paper(*this);
}

void A4Paper::SetIsMarking(bool isMarking) {
	this->isMarking = isMarking;
}

void A4Paper::ChangeMargin(Long leftMargin, Long topMargin, Long rightMargin, Long bottomMargin) {
	this->leftMargin = leftMargin;
	this->topMargin = topMargin;
	this->rightMargin = rightMargin;
	this->bottomMargin = bottomMargin;
}