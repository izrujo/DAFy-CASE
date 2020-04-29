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

	NShape *holdA4Paper = drawingPaper->a4Paper->Clone();
	NShape *holdFlowChart = drawingPaper->flowChart->Clone();
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(drawingPaper->zoom);
	holdA4Paper->Accept(zoomVisitor);
	holdFlowChart->Accept(zoomVisitor);

	NShape *shape = holdFlowChart->GetAt(drawingPaper->indexOfSelected);
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

	NShape *realShape= drawingPaper->flowChart->GetAt(drawingPaper->indexOfSelected);
	float realWidth = realShape->GetWidth();
	float realHeight = realShape->GetHeight();
	Long realLabelWidth;
	Long realLabelHeight;
	Long rate = drawingPaper->zoom->GetRate();

	float shapeX = this->label->GetX();
	float shapeY = this->label->GetY();
	float shapeWidth = shape->GetWidth();
	float shapeHeight = shape->GetHeight();
	float newY = shapeY + shapeHeight / 2 - height / 2;

	QRectF rect(shapeX - 5, shapeY - 5, shapeWidth + 5, shapeHeight + 5);
	if (width > shapeWidth) {
		rect.setRight(shapeX + width + 5);

		realLabelWidth = width * 100 / rate;
		realShape->ReSize(realHeight + realLabelWidth, realHeight);
	}
	if (height > shapeHeight) {
		rect.setBottom(shapeY + height + 5);
	
		realLabelHeight = height * 100 / rate;
		realShape->ReSize(realWidth, realLabelHeight);
	}

	this->label->move(this->label->GetX(), newY);
	this->label->resize(width, height);
	this->label->parentWidget()->repaint(rect.left(), rect.top(), rect.right(), rect.bottom());
}

SizeController& SizeController::operator=(const SizeController& source) {
	this->label = source.label;

	return *this;
}