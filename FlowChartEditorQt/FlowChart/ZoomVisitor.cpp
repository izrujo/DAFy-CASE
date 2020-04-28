#include "ZoomVisitor.h"
#include "Zoom.h"
#include "Terminal.h"
#include "Preparation.h"
#include "InputOutput.h"
#include "Process.h"
#include "Arrow.h"
#include "LeftDown.h"
#include "RightDown.h"
#include "Join.h"
#include "RightDownJoin.h"
#include "RepeatTrue.h"
#include "RepeatFalse.h"
#include "Decision.h"
#include "Template.h"
#include "FlowChart.h"
#include "A4Paper.h"
#include "CoordinateConverter.h"

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
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width / 2;
	Long centerY = y + height / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	element->ReSize(width, height);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ZoomVisitor::Visit(Preparation *element) {
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width / 2;
	Long centerY = y + height / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	element->ReSize(width, height);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ZoomVisitor::Visit(InputOutput *element) {
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width / 2;
	Long centerY = y + height / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	element->ReSize(width, height);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ZoomVisitor::Visit(Process *element) {
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width / 2;
	Long centerY = y + height / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	element->ReSize(width, height);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ZoomVisitor::Visit(Decision *element) {
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width / 2;
	Long centerY = y + height / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	element->ReSize(width, height);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ZoomVisitor::Visit(Arrow *element) {
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width / 2;
	Long centerY = y + height / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	element->ReSize(width, height);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ZoomVisitor::Visit(LeftDown *element) {
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width / 2;
	Long centerY = y + height / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	element->ReSize(width, height);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ZoomVisitor::Visit(RightDown *element) {
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width / 2;
	Long centerY = y + height / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	element->ReSize(width, height);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ZoomVisitor::Visit(Join *element) {
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long height2 = element->GetHeight2();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width / 2;
	Long centerY;
	(height < 0) ? (centerY = y + height + (height2 - height) / 2) : (centerY = y + height2 / 2);

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	quotient = height2 * rate / 100;
	remainder = height2 * rate % 100;
	if (remainder >= 50) quotient++;
	height2 = quotient;

	element->ReSize(width, height, height2);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	(height < 0) ? (y = realPoint.y() - (height2 - height) / 2 - height) : (y = realPoint.y() - height2 / 2);

	element->Move(x, y);
}

void ZoomVisitor::Visit(RightDownJoin *element) {
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long width2 = element->GetWidth2();
	Long height2 = element->GetHeight2();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width2 - (width2 - width) / 2;
	Long centerY = y + (height + height2) / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	quotient = width2 * rate / 100;
	remainder = width2 * rate % 100;
	if (remainder >= 50) quotient++;
	width2 = quotient;

	quotient = height2 * rate / 100;
	remainder = height2 * rate % 100;
	if (remainder >= 50) quotient++;
	height2 = quotient;

	element->ReSize(width, height, width2, height2);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() + (width2 - width) / 2 - width2;
	y = realPoint.y() - (height + height2) / 2;

	element->Move(x, y);
}

void ZoomVisitor::Visit(RepeatTrue *element) {
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long width2 = element->GetWidth2();
	Long height2 = element->GetHeight2();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width2 / 2;
	Long centerY = y + height2 + height / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient--;
	width = quotient;

	quotient = height * (100 + 100 - rate) / 100; //À½¼ö : 0.4 -> 1.6
	remainder = height * rate % 100;
	if (remainder >= 50) quotient--;
	height = quotient;

	quotient = width2 * rate / 100;
	remainder = width2 * rate % 100;
	if (remainder >= 50) quotient++;
	width2 = quotient;

	quotient = height2 * rate / 100;
	remainder = height2 * rate % 100;
	if (remainder >= 50) quotient++;
	height2 = quotient;

	element->ReSize(width, height, width2, height2);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width2 / 2;
	y = realPoint.y() - height / 2 - height2;

	element->Move(x, y);
}

void ZoomVisitor::Visit(RepeatFalse *element) {
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long width2 = element->GetWidth2();
	Long height2 = element->GetHeight2();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = x + width2 - (width2 - width) / 2;
	Long centerY = y + height / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	quotient = width2 * rate / 100;
	remainder = width2 * rate % 100;
	if (remainder >= 50) quotient++;
	width2 = quotient;

	quotient = height2 * rate / 100;
	remainder = height2 * rate % 100;
	if (remainder >= 50) quotient++;
	height2 = quotient;

	element->ReSize(width, height, width2, height2);

	QPoint realPoint(centerX, centerY);
	QPoint virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = virtualPoint.x() * rate / 100;
	remainder = virtualPoint.x() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setX(quotient);

	quotient = virtualPoint.y() * rate / 100;
	remainder = virtualPoint.y() * rate % 100;
	if (remainder >= 50) quotient++;
	virtualPoint.setY(quotient);

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() + (width2 - width) / 2 - width2;
	y = realPoint.y() - height / 2;

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
	Long x = element->GetX();
	Long y = element->GetY();
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long rate = this->zoom->GetRate();
	Long quotient;
	Long remainder;
	Long centerX = element->CenterOfGravityX();
	Long centerY = y + height / 2;

	quotient = width * rate / 100;
	remainder = width * rate % 100;
	if (remainder >= 50) quotient++;
	width = quotient;

	quotient = height * rate / 100;
	remainder = height * rate % 100;
	if (remainder >= 50) quotient++;
	height = quotient;

	element->ReSize(width, height);

	x = centerX - width / 2;
	y = centerY - height / 2;

	element->Move(x, y);

	Long leftMargin = element->GetLeftMargin();
	Long topMargin = element->GetTopMargin();
	Long rightMargin = element->GetRightMargin();
	Long bottomMargin = element->GetBottomMargin();

	quotient = leftMargin * rate / 100;
	remainder = leftMargin * rate % 100;
	if (remainder >= 50) quotient++;
	leftMargin = quotient;

	quotient = topMargin * rate / 100;
	remainder = topMargin * rate % 100;
	if (remainder >= 50) quotient++;
	topMargin = quotient;

	quotient = rightMargin * rate / 100;
	remainder = rightMargin * rate % 100;
	if (remainder >= 50) quotient++;
	rightMargin = quotient;

	quotient = bottomMargin * rate / 100;
	remainder = bottomMargin * rate % 100;
	if (remainder >= 50) quotient++;
	bottomMargin = quotient;

	element->ChangeMargin(leftMargin, topMargin, rightMargin, bottomMargin);

	this->converter->Update(element);
}