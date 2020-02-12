// SelectingTool.Cpp
#include "SelectingTool.h"

#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "Painter.h"
#include "Line.h"
#include "Arrow.h"
#include "Decision.h"
#include "ScrollController.h"
#include "Scrolls.h"
#include "ZoomVisitor.h"
#include "Zoom.h"
#include "CoordinateConverter.h"
#include "TutorialForm.h"
#include "Tutorials.h"
#include "FlowChartEditor.h"
#include "TutorialController.h"

SelectingTool* SelectingTool::instance = 0;

SelectingTool::SelectingTool() {
}

SelectingTool* SelectingTool::Instance() {
	if (instance == 0) {
		instance = new SelectingTool;
	}
	return instance;
}

void SelectingTool::Destroy() {
	if (instance != 0) {
		delete instance;
	}
	instance = 0;
}

void SelectingTool::OnLButtonDown(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	BOOL isControlPressed;
	isControlPressed = ((::GetKeyState(VK_CONTROL) & 0x8000) != 0);
	if (!isControlPressed) {
		dynamic_cast<FlowChart *>(canvas->flowChart)->UnSelectAll();
	}

	canvas->startX = point.x;
	canvas->startY = point.y;
	canvas->currentX = canvas->startX;
	canvas->currentY = canvas->startY;
}

void SelectingTool::OnMouseMove(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	BOOL isMouseLButtonPressed;
	isMouseLButtonPressed = ((::GetKeyState(VK_LBUTTON) & 0x8000) != 0);

	if (isMouseLButtonPressed) { // 왼쪽 마우스 버튼이 눌려져있을때
		canvas->DrawSelectingArea();
	}

	canvas->currentX = point.x;
	canvas->currentY = point.y;

	if (isMouseLButtonPressed) {
		canvas->DrawSelectingArea();
	}

}

void SelectingTool::OnLButtonUp(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	CRgn region;
	Shape *shape;
	Long i;
	Long it;
	Long index;
	Long quotient;
	Long remainder;

	Long positionX = 0;
	Long positionY = 0;
	if (canvas->scrollController != NULL) {
		positionX = canvas->scrollController->GetScroll(1)->GetPosition();
		positionY = canvas->scrollController->GetScroll(0)->GetPosition();
	}
	canvas->startX += positionX;
	canvas->startY += positionY;
	canvas->currentX += positionX;
	canvas->currentY += positionY;

	Shape *holdA4Paper = canvas->a4Paper->Clone();
	Shape *holdFlowChart = canvas->flowChart->Clone();
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(canvas->zoom);
	holdA4Paper->Accept(zoomVisitor);
	holdFlowChart->Accept(zoomVisitor);

	index = dynamic_cast<FlowChart *>(holdFlowChart)->Find(canvas->painter, canvas->currentX, canvas->currentY);
	if (canvas->startX == canvas->currentX && canvas->startY == canvas->currentY) {
		if (index > -1) {
			shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(index);
			(shape->IsSelected()) ? (shape->Select(false)) : (shape->Select(true));
		}
	}
	else {
		CRect rect = CRect(canvas->startX, canvas->startY, canvas->currentX, canvas->currentY);

		// 경계에 걸친 기호들을 빼기위한 영역		
		CRect top = CRect(canvas->startX, canvas->startY, canvas->currentX, canvas->currentY + 1);
		CRect bottom = CRect(canvas->startX, canvas->currentY - 1, canvas->currentX, canvas->currentY);
		CRect left = CRect(canvas->startX, canvas->startY, canvas->startX + 1, canvas->currentY);
		CRect right = CRect(canvas->currentX - 1, canvas->startY, canvas->currentX, canvas->currentY);

		i = 0;
		it = dynamic_cast<FlowChart *>(canvas->flowChart)->GetLength();
		for (i = 0; i < it; i++) {
			shape = dynamic_cast<FlowChart *>(holdFlowChart)->GetAt(i);
			shape->GetRegion(canvas->painter, &region);
			if (region.RectInRegion(rect) && (region.RectInRegion(top) || region.RectInRegion(left) || region.RectInRegion(right) || region.RectInRegion(bottom)))
			{
				dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(i)->Select(true);
			}
			region.DeleteObject();
		}

		TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(canvas->GetParent())->windows[2];
		if (tutorialForm != NULL) {
			tutorialForm->tutorialController->Update();
		}
	}

	if (holdFlowChart != 0) {
		delete holdFlowChart;
	}
	if (holdA4Paper != 0) {
		delete holdA4Paper;
	}

	Long count;
	Long(*indexes);
	(dynamic_cast<FlowChart *>(canvas->flowChart))->GetSelecteds(&indexes, &count);

	if (count > 0) {
		canvas->mode = DrawingPaper::SELECT;
	}
	else {
		canvas->mode = DrawingPaper::IDLE;
	}

	if (indexes != 0) {
		delete[] indexes;
	}

	canvas->RedrawWindow();
}