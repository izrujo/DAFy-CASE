#include "ResolutionVisitor.h"
#include "CoordinateConverter.h"
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

ResolutionVisitor::ResolutionVisitor(Long dpi, Long mmWidth, Long mmHeight) 
	: FlowChartVisitor() {
	this->converter = new CoordinateConverter;
	this->dpi = dpi;
	this->mmWidth = mmWidth;
	this->mmHeight = mmHeight;
	this->pixelWidth = 1653;
	this->pixelHeight = 2338;
}

ResolutionVisitor::ResolutionVisitor(const ResolutionVisitor& source)
	: FlowChartVisitor() {
	this->converter = source.converter;
	this->dpi = source.dpi;
	this->mmWidth = source.mmWidth;
	this->mmHeight = source.mmHeight;
	this->pixelWidth = source.pixelWidth;
	this->pixelHeight = source.pixelHeight;
}

ResolutionVisitor::~ResolutionVisitor() {
	if (this->converter != NULL) {
		delete this->converter;
	}
}

ResolutionVisitor& ResolutionVisitor::operator=(const ResolutionVisitor& source) {
	this->converter = source.converter;
	this->dpi = source.dpi;
	this->mmWidth = source.mmWidth;
	this->mmHeight = source.mmHeight;
	this->pixelWidth = source.pixelWidth;
	this->pixelHeight = source.pixelHeight;

	return *this;
}

void ResolutionVisitor::Visit(Terminal *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	float centerX = x + width / 2;
	float centerY = y + height / 2;
	float inch;

	width = this->mmWidth * width / this->pixelWidth;
	inch = width / 25.4;
	width = round(inch * this->dpi);

	height = this->mmHeight * height / this->pixelHeight;
	inch = height / 25.4;
	height = round(inch * this->dpi);

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	virtualPoint.setX(this->mmWidth * virtualPoint.x() / this->pixelWidth);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(round(inch * this->dpi));

	virtualPoint.setY(this->mmHeight * virtualPoint.y() / this->pixelHeight);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(round(inch * this->dpi));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ResolutionVisitor::Visit(Preparation *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	
	
	float centerX = x + width / 2;
	float centerY = y + height / 2;
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = this->mmWidth * virtualPoint.x() / this->pixelWidth;
	remainder = this->mmWidth * virtualPoint.x() % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	virtualPoint.setX(quotient);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(static_cast<float>(round(inch * this->dpi)));

	quotient = this->mmHeight * virtualPoint.y() / this->pixelHeight;
	remainder = this->mmHeight * virtualPoint.y() % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	virtualPoint.setY(quotient);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(static_cast<float>(round(inch * this->dpi)));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ResolutionVisitor::Visit(InputOutput *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	
	
	float centerX = x + width / 2;
	float centerY = y + height / 2;
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = this->mmWidth * virtualPoint.x() / this->pixelWidth;
	remainder = this->mmWidth * virtualPoint.x() % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	virtualPoint.setX(quotient);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(static_cast<float>(round(inch * this->dpi)));

	quotient = this->mmHeight * virtualPoint.y() / this->pixelHeight;
	remainder = this->mmHeight * virtualPoint.y() % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	virtualPoint.setY(quotient);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(static_cast<float>(round(inch * this->dpi)));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ResolutionVisitor::Visit(Process *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	
	
	float centerX = x + width / 2;
	float centerY = y + height / 2;
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = this->mmWidth * virtualPoint.x() / this->pixelWidth;
	remainder = this->mmWidth * virtualPoint.x() % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	virtualPoint.setX(quotient);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(static_cast<float>(round(inch * this->dpi)));

	quotient = this->mmHeight * virtualPoint.y() / this->pixelHeight;
	remainder = this->mmHeight * virtualPoint.y() % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	virtualPoint.setY(quotient);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(static_cast<float>(round(inch * this->dpi)));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ResolutionVisitor::Visit(Decision *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	
	
	float centerX = x + width / 2;
	float centerY = y + height / 2;
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = this->mmWidth * virtualPoint.x() / this->pixelWidth;
	remainder = this->mmWidth * virtualPoint.x() % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	virtualPoint.setX(quotient);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(static_cast<float>(round(inch * this->dpi)));

	quotient = this->mmHeight * virtualPoint.y() / this->pixelHeight;
	remainder = this->mmHeight * virtualPoint.y() % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	virtualPoint.setY(quotient);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(static_cast<float>(round(inch * this->dpi)));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ResolutionVisitor::Visit(Arrow *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	
	
	float centerX = x + width / 2;
	float centerY = y + height / 2;
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = this->mmWidth * virtualPoint.x() / this->pixelWidth;
	remainder = this->mmWidth * virtualPoint.x() % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	virtualPoint.setX(quotient);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(static_cast<float>(round(inch * this->dpi)));

	quotient = this->mmHeight * virtualPoint.y() / this->pixelHeight;
	remainder = this->mmHeight * virtualPoint.y() % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	virtualPoint.setY(quotient);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(static_cast<float>(round(inch * this->dpi)));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ResolutionVisitor::Visit(LeftDown *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	
	
	float centerX = x + width / 2;
	float centerY = y + height / 2;
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = this->mmWidth * virtualPoint.x() / this->pixelWidth;
	remainder = this->mmWidth * virtualPoint.x() % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	virtualPoint.setX(quotient);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(static_cast<float>(round(inch * this->dpi)));

	quotient = this->mmHeight * virtualPoint.y() / this->pixelHeight;
	remainder = this->mmHeight * virtualPoint.y() % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	virtualPoint.setY(quotient);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(static_cast<float>(round(inch * this->dpi)));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ResolutionVisitor::Visit(RightDown *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	
	
	float centerX = x + width / 2;
	float centerY = y + height / 2;
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = this->mmWidth * virtualPoint.x() / this->pixelWidth;
	remainder = this->mmWidth * virtualPoint.x() % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	virtualPoint.setX(quotient);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(static_cast<float>(round(inch * this->dpi)));

	quotient = this->mmHeight * virtualPoint.y() / this->pixelHeight;
	remainder = this->mmHeight * virtualPoint.y() % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	virtualPoint.setY(quotient);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(static_cast<float>(round(inch * this->dpi)));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ResolutionVisitor::Visit(Join *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	float height2 = element->GetHeight2();
	
	
	float centerX = x + width / 2;
	float centerY;
	(height < 0) ? (centerY = y + height + (height2 - height) / 2) : (centerY = y + height2 / 2);
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height2 / this->pixelHeight;
	remainder = this->mmHeight * height2 % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height2 = quotient;
	inch = height2 / 25.4;
	height2 = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height, height2);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = this->mmWidth * virtualPoint.x() / this->pixelWidth;
	remainder = this->mmWidth * virtualPoint.x() % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	virtualPoint.setX(quotient);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(static_cast<float>(round(inch * this->dpi)));

	quotient = this->mmHeight * virtualPoint.y() / this->pixelHeight;
	remainder = this->mmHeight * virtualPoint.y() % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	virtualPoint.setY(quotient);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(static_cast<float>(round(inch * this->dpi)));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width / 2;
	(height < 0) ? (y = realPoint.y() - (height2 - height) / 2 - height) : (y = realPoint.y() - height2 / 2);

	element->Move(x, y);
}

void ResolutionVisitor::Visit(RightDownJoin *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	float width2 = element->GetWidth2();
	float height2 = element->GetHeight2();
	
	
	float centerX = x + width2 - (width2 - width) / 2;
	float centerY = y + (height + height2) / 2;
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmWidth * width2 / this->pixelWidth;
	remainder = this->mmWidth * width2 % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width2 = quotient;
	inch = width2 / 25.4;
	width2 = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height2 / this->pixelHeight;
	remainder = this->mmHeight * height2 % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height2 = quotient;
	inch = height2 / 25.4;
	height2 = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height, width2, height2);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = this->mmWidth * virtualPoint.x() / this->pixelWidth;
	remainder = this->mmWidth * virtualPoint.x() % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	virtualPoint.setX(quotient);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(static_cast<float>(round(inch * this->dpi)));

	quotient = this->mmHeight * virtualPoint.y() / this->pixelHeight;
	remainder = this->mmHeight * virtualPoint.y() % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	virtualPoint.setY(quotient);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(static_cast<float>(round(inch * this->dpi)));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() + (width2 - width) / 2 - width2;
	y = realPoint.y() - (height + height2) / 2;

	element->Move(x, y);
}

void ResolutionVisitor::Visit(RepeatTrue *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	float width2 = element->GetWidth2();
	float height2 = element->GetHeight2();
	
	
	float centerX = x + width2 / 2;
	float centerY = y + height2 + height / 2;
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmWidth * width2 / this->pixelWidth;
	remainder = this->mmWidth * width2 % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width2 = quotient;
	inch = width2 / 25.4;
	width2 = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height2 / this->pixelHeight;
	remainder = this->mmHeight * height2 % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height2 = quotient;
	inch = height2 / 25.4;
	height2 = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height, width2, height2);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = this->mmWidth * virtualPoint.x() / this->pixelWidth;
	remainder = this->mmWidth * virtualPoint.x() % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	virtualPoint.setX(quotient);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(static_cast<float>(round(inch * this->dpi)));

	quotient = this->mmHeight * virtualPoint.y() / this->pixelHeight;
	remainder = this->mmHeight * virtualPoint.y() % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	virtualPoint.setY(quotient);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(static_cast<float>(round(inch * this->dpi)));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() - width2 / 2;
	y = realPoint.y() - height / 2 - height2;

	element->Move(x, y);
}

void ResolutionVisitor::Visit(RepeatFalse *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	float width2 = element->GetWidth2();
	float height2 = element->GetHeight2();
	
	
	float centerX = x + width2 - (width2 - width) / 2;
	float centerY = y + height / 2;
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmWidth * width2 / this->pixelWidth;
	remainder = this->mmWidth * width2 % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width2 = quotient;
	inch = width2 / 25.4;
	width2 = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height2 / this->pixelHeight;
	remainder = this->mmHeight * height2 % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height2 = quotient;
	inch = height2 / 25.4;
	height2 = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height, width2, height2);

	QPointF realPoint(centerX, centerY);
	QPointF virtualPoint = this->converter->ConvertVirtual(realPoint);

	quotient = this->mmWidth * virtualPoint.x() / this->pixelWidth;
	remainder = this->mmWidth * virtualPoint.x() % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	virtualPoint.setX(quotient);
	inch = virtualPoint.x() / 25.4;
	virtualPoint.setX(static_cast<float>(round(inch * this->dpi)));

	quotient = this->mmHeight * virtualPoint.y() / this->pixelHeight;
	remainder = this->mmHeight * virtualPoint.y() % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	virtualPoint.setY(quotient);
	inch = virtualPoint.y() / 25.4;
	virtualPoint.setY(static_cast<float>(round(inch * this->dpi)));

	realPoint = this->converter->ConvertReal(virtualPoint);

	x = realPoint.x() + (width2 - width) / 2 - width2;
	y = realPoint.y() - height / 2;

	element->Move(x, y);
}

void ResolutionVisitor::Visit(FlowChart *element) {
	for (float i = 0; i < element->GetLength(); i++) {
		element->GetAt(i)->Accept(this);
	}
}

void ResolutionVisitor::Visit(Template *element) {
	for (float i = 0; i < element->GetLength(); i++) {
		element->GetAt(i)->Accept(this);
	}
}

void ResolutionVisitor::Visit(A4Paper *element) {
	float x = element->GetX();
	float y = element->GetY();
	float width = element->GetWidth();
	float height = element->GetHeight();
	this->pixelWidth = width;
	this->pixelHeight = height;
	
	
	float centerX = element->CenterOfGravityX();
	float centerY = y + height / 2;
	float inch;

	quotient = this->mmWidth * width / this->pixelWidth;
	remainder = this->mmWidth * width % this->pixelWidth;
	if (remainder >= this->pixelWidth / 2) quotient++;
	width = quotient;
	inch = width / 25.4;
	width = static_cast<float>(round(inch * this->dpi));

	quotient = this->mmHeight * height / this->pixelHeight;
	remainder = this->mmHeight * height % this->pixelHeight;
	if (remainder >= this->pixelHeight / 2) quotient++;
	height = quotient;
	inch = height / 25.4;
	height = static_cast<float>(round(inch * this->dpi));

	element->ReSize(width, height);

	x = centerX - width / 2;
	y = centerY - height / 2;

	element->Move(x, y);

	this->converter->Update(element);
}