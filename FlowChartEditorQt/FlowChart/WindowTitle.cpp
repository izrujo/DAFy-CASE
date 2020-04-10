#include "WindowTitle.h"
#include "FlowChartVisitor.h"

WindowTitle::WindowTitle(Long x, Long y, Long width, Long height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: NShape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
	this->isFocusedAndPinned = true;
}

WindowTitle::~WindowTitle() {

}

WindowTitle::WindowTitle(const WindowTitle& source)
	: NShape(source) {
	this->isFocusedAndPinned = true;
}

WindowTitle& WindowTitle::operator =(const WindowTitle& source) {
	NShape::operator=(source);
	this->isFocusedAndPinned = true;

	return *this;
}

void WindowTitle::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* WindowTitle::Clone() {
	return new WindowTitle(*this);
}

void WindowTitle::SetIsFocusedAndPinned(bool isFocusedAndPinned) {
	this->isFocusedAndPinned = isFocusedAndPinned;
}