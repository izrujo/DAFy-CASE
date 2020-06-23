#include "WindowTitle.h"
#include "../../Paint/FlowChartVisitor.h"

WindowTitle::WindowTitle(float x, float y, float width, float height, QColor backGroundColor,
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

bool WindowTitle::IsIncluded(QPointF point) {
	bool ret;

	QRectF regionRect(this->x, this->y, this->width, this->height);
	QRegion region(regionRect.toRect());
	ret = region.contains(point.toPoint());

	return ret;
}