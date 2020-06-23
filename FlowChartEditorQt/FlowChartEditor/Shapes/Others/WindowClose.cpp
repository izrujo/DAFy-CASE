#include "WindowClose.h"
#include "../../Paint/FlowChartVisitor.h"

WindowClose::WindowClose(float x, float y, float width, float height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: NShape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
	
}

WindowClose::~WindowClose() {

}

WindowClose::WindowClose(const WindowClose& source)
	: NShape(source) {

}

WindowClose& WindowClose::operator =(const WindowClose& source) {
	NShape::operator=(source);

	return *this;
}

void WindowClose::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* WindowClose::Clone() {
	return new WindowClose(*this);
}