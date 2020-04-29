#include "NumberBox.h"
#include "FlowChartVisitor.h"

NumberBox::NumberBox(float x, float y, float width, float height, QColor backGroundColor,
	Qt::PenStyle borderLine, QColor borderColor, String contents)
	: NShape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

NumberBox::~NumberBox() {

}

NumberBox::NumberBox(const NumberBox& source)
	: NShape(source) {

}

NumberBox& NumberBox::operator =(const NumberBox& source) {
	NShape::operator=(source);

	return *this;
}

void NumberBox::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* NumberBox::Clone() {
	return new NumberBox(*this);
}