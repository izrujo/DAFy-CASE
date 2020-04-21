#include "WindowClose.h"
#include "FlowChartVisitor.h"

WindowClose::WindowClose(Long x, Long y, Long width, Long height, QColor backGroundColor,
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