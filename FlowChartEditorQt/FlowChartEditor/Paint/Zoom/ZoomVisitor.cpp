#include "ZoomVisitor.h"
#include "Zoom.h"
#include "../../Shapes/Symbols/Terminal.h"
#include "../../Shapes/Symbols/Preparation.h"
#include "../../Shapes/Symbols/InputOutput.h"
#include "../../Shapes/Symbols/Process.h"
#include "../../Shapes/Symbols/Decision.h"
#include "../../Shapes/Lines/Arrow.h"
#include "../../Shapes/Lines/LeftDown.h"
#include "../../Shapes/Lines/RightDown.h"
#include "../../Shapes/Lines/Join.h"
#include "../../Shapes/Lines/RightDownJoin.h"
#include "../../Shapes/Lines/RepeatTrue.h"
#include "../../Shapes/Lines/RepeatFalse.h"
#include "../../Shapes/Composite/Template.h"
#include "../../Shapes/Composite/FlowChart.h"
#include "../../Shapes/Others/A4Paper.h"
#include "../Coordinate/CoordinateConverter.h"

ZoomVisitor::ZoomVisitor(Zoom *zoom)
	: FlowChartVisitor() {
	this->zoom = zoom;
	this->converter = new CoordinateConverter;
}

ZoomVisitor::ZoomVisitor(const ZoomVisitor& source)
	: FlowChartVisitor() {
	this->zoom = source.zoom;
	this->converter = source.converter;
}

ZoomVisitor::~ZoomVisitor() {
	if (this->converter != NULL) {
		delete this->converter;
	}
}

ZoomVisitor& ZoomVisitor::operator=(const ZoomVisitor& source) {
	this->zoom = source.zoom;
	this->converter = source.converter;

	return *this;
}

void ZoomVisitor::Visit(Terminal *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	Long rate = this->zoom->GetRate();

	float centerX = x + width / 2;
	float centerY = y + height / 2;

	width = width * rate / 100;
	height = height * rate / 100;

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2.0F;
	y = realPoint.y() - height / 2.0F;

	element->Move(x, y);
}

void ZoomVisitor::Visit(Preparation *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	float centerX = x + width / 2;
	float centerY = y + height / 2;

	width = width * rate / 100;
	height = height * rate / 100;

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2.0F;
	y = realPoint.y() - height / 2.0F;

	element->Move(x, y);
}

void ZoomVisitor::Visit(InputOutput *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	float centerX = x + width / 2.0F;
	float centerY = y + height / 2.0F;

	width = width * rate / 100;
	height = height * rate / 100;

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2.0F;
	y = realPoint.y() - height / 2.0F;

	element->Move(x, y);
}

void ZoomVisitor::Visit(Process *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	float centerX = x + width / 2;
	float centerY = y + height / 2;

	width = width * rate / 100;
	height = height * rate / 100;

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2.0F;
	y = realPoint.y() - height / 2.0F;

	element->Move(x, y);
}

void ZoomVisitor::Visit(Decision *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	float centerX = x + width / 2.0F;
	float centerY = y + height / 2.0F;

	width = width * rate / 100;
	height = height * rate / 100;

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ZoomVisitor::Visit(Arrow *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	//float centerX = x + width / 2;
	//float centerY = y + height / 2;

	width = width * rate / 100;
	height = height * rate / 100;

	element->ReSize(width, height);
	
	float arrowSize = element->GetArrowSize();
	arrowSize = arrowSize * rate / 100;
	element->ChangeArrowSize(arrowSize);

	//QPointF realPoint(centerX, centerY);
	QPointF realPoint(x, y);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	//x = realPoint.x() - width / 2;
	x = realPoint.x();
	//y = realPoint.y() - height / 2;
	y = realPoint.y();

	element->Move(x, y);
}

void ZoomVisitor::Visit(LeftDown *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	//float centerX = x + width / 2;
	//float centerY = y + height / 2;

	width = width * rate / 100;
	height = height * rate / 100;

	element->ReSize(width, height);
	
	float arrowSize = element->GetArrowSize();
	arrowSize = arrowSize * rate / 100;
	element->ChangeArrowSize(arrowSize);

	//QPointF realPoint(centerX, centerY);
	QPointF realPoint(x, y);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	//x = realPoint.x() - width / 2;
	x = realPoint.x();
	//y = realPoint.y() - height / 2;
	y = realPoint.y();

	element->Move(x, y);
}

void ZoomVisitor::Visit(RightDown *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	//float centerX = x + width / 2;
	//float centerY = y + height / 2;

	width = width * rate / 100;
	height = height * rate / 100;

	element->ReSize(width, height);
	
	float arrowSize = element->GetArrowSize();
	arrowSize = arrowSize * rate / 100;
	element->ChangeArrowSize(arrowSize);

	//QPointF realPoint(centerX, centerY);
	QPointF realPoint(x, y);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	//x = realPoint.x() - width / 2;
	x = realPoint.x();
	//y = realPoint.y() - height / 2;
	y = realPoint.y();

	element->Move(x, y);
}

void ZoomVisitor::Visit(Join *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	float height2 = element->GetHeight2();
	Long rate = this->zoom->GetRate();
	//float centerX = x + width / 2;
	//float centerY;

	//(height < 0) ? (centerY = y + height + (height2 - height) / 2) : (centerY = y + height2 / 2);

	width = width * rate / 100;
	(height > 0) ? (height = height * rate / 100) : (height = height * rate / 100);
	height2 = height2 * rate / 100;

	element->ReSize(width, height, height2);

	float arrowSize = element->GetArrowSize();
	arrowSize = arrowSize * rate / 100;
	element->ChangeArrowSize(arrowSize);

	//QPointF realPoint(centerX, centerY);
	QPointF realPoint(x, y);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	//x = realPoint.x() - width / 2;
	x = realPoint.x();
	//(height < 0) ? (y = realPoint.y() - (height2 - height) / 2 - height) : (y = realPoint.y() - height2 / 2);
	y = realPoint.y();

	element->Move(x, y);
}

void ZoomVisitor::Visit(RightDownJoin *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	float width2 = element->GetWidth2();
	float height2 = element->GetHeight2();
	Long rate = this->zoom->GetRate();\
	//float centerX = x + width2 - (width2 - width) / 2;
	//float centerY = y + (height + height2) / 2;

	width = width * rate / 100;
	height = height * rate / 100;
	width2 = width2 * rate / 100;
	height2 = height2 * rate / 100;

	element->ReSize(width, height, width2, height2);

	float arrowSize = element->GetArrowSize();
	arrowSize = arrowSize * rate / 100;
	element->ChangeArrowSize(arrowSize);

	//QPointF realPoint(centerX, centerY);
	QPointF realPoint(x, y);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	//x = realPoint.x() + (width2 - width) / 2 - width2;
	x = realPoint.x();
	//y = realPoint.y() - (height + height2) / 2;
	y = realPoint.y();

	element->Move(x, y);
}

void ZoomVisitor::Visit(RepeatTrue *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	float width2 = element->GetWidth2();
	float height2 = element->GetHeight2();
	Long rate = this->zoom->GetRate();
	//float centerX = x + width2 / 2;
	//float centerY = y + height2 + height / 2;

	width = width * rate / 100;
	height = height * rate / 100;
	width2 = width2 * rate / 100;
	height2 = height2 * rate / 100;

	element->ReSize(width, height, width2, height2);

	float arrowSize = element->GetArrowSize();
	arrowSize = arrowSize * rate / 100;
	element->ChangeArrowSize(arrowSize);

	//QPointF realPoint(centerX, centerY);
	QPointF realPoint(x, y);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	//x = realPoint.x() - width2 / 2;
	x = realPoint.x();
	//y = realPoint.y() - height / 2 - height2;
	y = realPoint.y();

	element->Move(x, y);
}

void ZoomVisitor::Visit(RepeatFalse *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	float width2 = element->GetWidth2();
	float height2 = element->GetHeight2();
	Long rate = this->zoom->GetRate();
	//float centerX = x + width2 - (width2 - width) / 2;
	//float centerY = y + height / 2;

	width = width * rate / 100;
	height = height * rate / 100;
	width2 = width2 * rate / 100;
	height2 = height2 * rate / 100;

	element->ReSize(width, height, width2, height2);

	float arrowSize = element->GetArrowSize();
	arrowSize = arrowSize * rate / 100;
	element->ChangeArrowSize(arrowSize);

	//QPointF realPoint(centerX, centerY);
	QPointF realPoint(x, y);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(virtualPoint.x() * rate / 100);
	virtualPoint.setY(virtualPoint.y() * rate / 100);

	realPoint = this->converter->ConvertReal(virtualPoint);

	//x = realPoint.x() + (width2 - width) / 2 - width2;
	x = realPoint.x();
	//y = realPoint.y() - height / 2;
	y = realPoint.y();

	element->Move(x, y);
}

void ZoomVisitor::Visit(FlowChart *element) {
	for (Long i = 0; i < element->GetLength(); i++) {
		element->GetAt(i)->Accept(this);
	}
}

void ZoomVisitor::Visit(Template *element) {
	for (Long i = 0; i < element->GetLength(); i++) {
		element->GetAt(i)->Accept(this);
	}
}

void ZoomVisitor::Visit(A4Paper *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	float centerX = element->CenterOfGravityX();
	float centerY = y + height / 2;

	width = width * rate / 100;
	height = height * rate / 100;

	element->ReSize(width, height);

	x = centerX - width / 2;
	y = centerY - height / 2;

	element->Move(x, y);

	float leftMargin = element->GetLeftMargin();
	float topMargin = element->GetTopMargin();
	float rightMargin = element->GetRightMargin();
	float bottomMargin = element->GetBottomMargin();

	leftMargin = leftMargin * rate / 100;
	topMargin = topMargin * rate / 100;
	rightMargin = rightMargin * rate / 100;
	bottomMargin = bottomMargin * rate / 100;

	element->ChangeMargin(leftMargin, topMargin, rightMargin, bottomMargin);

	this->converter->Update(element);
}