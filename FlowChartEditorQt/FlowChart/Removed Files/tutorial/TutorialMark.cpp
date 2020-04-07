#include "TutorialMark.h"
#include "FlowChartVisitor.h"

TutorialMark::TutorialMark(Long x, Long y, Long width, Long height, 
	QColor backGroundColor, QPen borderLine, QColor borderColor, String contents)
	: Shape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

TutorialMark::~TutorialMark() {

}

TutorialMark::TutorialMark(const TutorialMark& source)
	: Shape(source) {

}

TutorialMark& TutorialMark::operator =(const TutorialMark& source) {
	Shape::operator=(source);

	return *this;
}

void TutorialMark::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

Shape* TutorialMark::Clone() {
	return new TutorialMark(*this);
}