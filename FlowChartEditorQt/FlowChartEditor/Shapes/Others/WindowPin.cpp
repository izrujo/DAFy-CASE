#include "WindowPin.h"
#include "FlowChartVisitor.h"

WindowPin::WindowPin(float x, float y, float width, float height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: NShape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
	this->isPinned = true;
}

WindowPin::~WindowPin() {

}

WindowPin::WindowPin(const WindowPin& source)
	: NShape(source) {
	this->isPinned = source.isPinned;
}

WindowPin& WindowPin::operator =(const WindowPin& source) {
	NShape::operator=(source);
	this->isPinned = source.isPinned;

	return *this;
}

void WindowPin::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* WindowPin::Clone() {
	return new WindowPin(*this);
}

void WindowPin::SetIsPinned(bool isPinned) {
	this->isPinned = isPinned;
}