#include "SizeController.h"
#include "Label.h"
#include "../Notepad/CharacterMetrics.h"
#include "../Notepad/Note.h"
#include "Shape.h"

#include "DrawingPaper.h"
#include "FlowChart.h"
#include "ZoomVisitor.h"
#include "Zoom.h"

SizeController::SizeController(Label *label) {
	this->label = label;
	this->label->AttachObserver(this);
}

SizeController::SizeController(const SizeController& source) {
	this->label = source.label;
}

SizeController::~SizeController() {
	this->label->DetachObserver(this);
}

void SizeController::Update() {
	DrawingPaper *drawingPaper = (DrawingPaper*)this->label->parentWidget();

	Shape *holdA4Paper = drawingPaper->a4Paper->Clone();
	Shape *holdFlowChart = drawingPaper->flowChart->Clone();
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(drawingPaper->zoom);
	holdA4Paper->Accept(zoomVisitor);
	holdFlowChart->Accept(zoomVisitor);

	Shape *shape = holdFlowChart->GetAt(drawingPaper->indexOfSelected);
	Long height = this->label->characterMetrics->GetY(this->label->note->GetLength());

	Long width = 0;
	Long i = 0;
	while (i < this->label->note->GetLength()) {
		Glyph *line = this->label->note->GetAt(i);
		Long x = this->label->characterMetrics->GetX(line, line->GetLength());
		if (x > width) {
			width = x;
		}
		i++;
	}

	Shape *realShape= drawingPaper->flowChart->GetAt(drawingPaper->indexOfSelected);
	Long realWidth = realShape->GetWidth();
	Long realHeight = realShape->GetHeight();
	Long realLabelWidth;
	Long realLabelHeight;
	Long rate = drawingPaper->zoom->GetRate();
	Long quotient;
	Long remainder;

	Long shapeX = this->label->GetX();
	Long shapeY = this->label->GetY();
	Long shapeWidth = shape->GetWidth();
	Long shapeHeight = shape->GetHeight();
	Long newY = shapeY + shapeHeight / 2 - height / 2;

	RECT rect = { shapeX - 5, shapeY - 5, shapeX + shapeWidth + 5, shapeY + shapeHeight + 5 };
	if (width > shapeWidth) {
		rect.right = shapeX + width + 5;

		quotient = width * 100 / rate;
		remainder = width * 100 % rate;
		if (remainder >= 50) quotient++;
		realLabelWidth = quotient;
		realShape->ReSize(realHeight + realLabelWidth, realHeight);
	}
	if (height > shapeHeight) {
		rect.bottom = shapeY + height + 5;
		
		quotient = height * 100 / rate;
		remainder = height * 100 % rate;
		if (remainder >= 50) quotient++;
		realLabelHeight = quotient;
		realShape->ReSize(realWidth, realLabelHeight);
	}

	this->label->move(this->label->GetX(), newY);
	this->label->resize(width, height);
	this->label->parentWidget()->repaint(rect.left, rect.top, rect.right, rect.bottom);
}

SizeController& SizeController::operator=(const SizeController& source) {
	this->label = source.label;

	return *this;
}