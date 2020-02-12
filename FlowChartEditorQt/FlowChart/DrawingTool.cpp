#include "DrawingTool.h"

#include "DrawingPaper.h"
#include "FlowChartEditor.h"
#include "FlowChartTemplate.h"

#include "FlowChart.h"
#include "Shape.h"
#include "SelectingTool.h"

#include "ScrollController.h"
#include "Scrolls.h"

#include "MemoryController.h"

#include "Zoom.h"
#include "ZoomVisitor.h"
#include "CoordinateConverter.h"

#include "TutorialForm.h"
#include "Tutorials.h"
#include "ToolTip.h"

#include "Painter.h"
#include "TutorialController.h"

DrawingTool* DrawingTool::instance = 0;

DrawingTool::DrawingTool() {
}

DrawingTool* DrawingTool::Instance() {
	if (instance == 0) {
		instance = new DrawingTool;
	}
	return instance;
}

void DrawingTool::Destroy() {
	if (instance != 0) {
		delete instance;
		instance = 0;
	}
}

void DrawingTool::OnLButtonDown(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	(dynamic_cast<FlowChart*>(canvas->flowChart))->UnSelectAll();

	Long positionX = 0;
	Long positionY = 0;
	if (canvas->scrollController != NULL) {
		positionX = canvas->scrollController->GetScroll(1)->GetPosition();
		positionY = canvas->scrollController->GetScroll(0)->GetPosition();
	}

	canvas->startX = point.x + positionX;
	canvas->startY = point.y + positionY;

	canvas->currentX = point.x + positionX;
	canvas->currentY = point.y + positionY;

	Shape *holdA4Paper = canvas->a4Paper->Clone();
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(canvas->zoom);
	holdA4Paper->Accept(zoomVisitor);

	Long quotient;
	Long remainder;

	POINT startReal = { canvas->startX, canvas->startY };
	POINT startVirtual = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertVirtual(startReal);

	quotient = startVirtual.x * 100 / canvas->zoom->GetRate();
	remainder = startVirtual.x * 100 % canvas->zoom->GetRate();
	if (remainder >= 50) quotient++;
	startVirtual.x = quotient;

	quotient = startVirtual.y * 100 / canvas->zoom->GetRate();
	remainder = startVirtual.y * 100 % canvas->zoom->GetRate();
	if (remainder >= 50) quotient++;
	startVirtual.y = quotient;

	startReal = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertReal(startVirtual);

	POINT currentReal = { canvas->currentX, canvas->currentY };
	POINT currentVirtual = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertVirtual(currentReal);

	quotient = currentVirtual.x * 100 / canvas->zoom->GetRate();
	remainder = currentVirtual.x * 100 % canvas->zoom->GetRate();
	if (remainder >= 50) quotient++;
	currentVirtual.x = quotient;

	quotient = currentVirtual.y * 100 / canvas->zoom->GetRate();
	remainder = currentVirtual.y * 100 % canvas->zoom->GetRate();
	if (remainder >= 50) quotient++;
	currentVirtual.y = quotient;

	currentReal = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertReal(currentVirtual);

	canvas->startX = startReal.x;
	canvas->startY = startReal.y;

	canvas->currentX = currentReal.x;
	canvas->currentY = currentReal.y;

	canvas->templateSelected->Move(canvas->startX, canvas->startY);
	canvas->templateSelected->Select(true);
}

void DrawingTool::OnMouseMove(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	Long positionX = 0;
	Long positionY = 0;
	if (canvas->scrollController != NULL) {
		positionX = canvas->scrollController->GetScroll(1)->GetPosition();
		positionY = canvas->scrollController->GetScroll(0)->GetPosition();
	}

	canvas->currentX = point.x + positionX;
	canvas->currentY = point.y + positionY;

	Shape *holdA4Paper = canvas->a4Paper->Clone();
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(canvas->zoom);
	holdA4Paper->Accept(zoomVisitor);

	Long quotient;
	Long remainder;

	POINT currentReal = { canvas->currentX, canvas->currentY };
	POINT currentVirtual = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertVirtual(currentReal);

	quotient = currentVirtual.x * 100 / canvas->zoom->GetRate();
	remainder = currentVirtual.x * 100 % canvas->zoom->GetRate();
	if (remainder >= 50) quotient++;
	currentVirtual.x = quotient;

	quotient = currentVirtual.y * 100 / canvas->zoom->GetRate();
	remainder = currentVirtual.y * 100 % canvas->zoom->GetRate();
	if (remainder >= 50) quotient++;
	currentVirtual.y = quotient;

	currentReal = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertReal(currentVirtual);

	canvas->currentX = currentReal.x;
	canvas->currentY = currentReal.y;

	Long width = canvas->currentX - canvas->startX;
	Long height = canvas->currentY - canvas->startY;
	if (width >= 150 && height >= 50) {
		canvas->templateSelected->ReSize(width, height);
	}

	canvas->Invalidate(true);
}

void DrawingTool::OnLButtonUp(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	Long previousLength = dynamic_cast<FlowChart*>(canvas->flowChart)->GetLength();

	canvas->indexOfSelected= (dynamic_cast<FlowChart*>(canvas->flowChart))->Attach(canvas->templateSelected->Clone());

	Long currentLength = dynamic_cast<FlowChart*>(canvas->flowChart)->GetLength();
	if (currentLength != previousLength && dynamic_cast<FlowChartEditor*>(canvas->GetParent())->toolTip != NULL) {
		dynamic_cast<FlowChartEditor*>(canvas->GetParent())->toolTip->Destroy();
		dynamic_cast<FlowChartEditor*>(canvas->GetParent())->toolTip = NULL;
		TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(canvas->GetParent())->windows[2];
		if (tutorialForm != NULL) {
			tutorialForm->tutorialController->Update();
		}
	}

	Long(*indexes) = new Long[dynamic_cast<FlowChart*>(canvas->flowChart)->GetLength()];
	indexes[0] = canvas->indexOfSelected;
	canvas->memoryController->RememberAdd(indexes, 1);

	if (canvas->templateSelected != NULL) {
		delete canvas->templateSelected;
		canvas->templateSelected = NULL;
	}
	canvas->tool = SelectingTool::Instance();
	canvas->mode = DrawingPaper::SELECT;
	canvas->RedrawWindow();

	if (indexes != 0) {
		delete[] indexes;
	}
}