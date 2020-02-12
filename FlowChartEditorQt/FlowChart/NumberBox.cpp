#include "NumberBox.h"
#include "FlowChartVisitor.h"

NumberBox::NumberBox(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents, Direction direction)
	:Shape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

NumberBox::~NumberBox() {
}

NumberBox::NumberBox(const NumberBox& source)
	:Shape(source) {

}

NumberBox& NumberBox::operator =(const NumberBox& source) {
	Shape::operator=(source);
	
	return *this;
}

void NumberBox::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

Shape* NumberBox::Clone() {
	return new NumberBox(*this);
}