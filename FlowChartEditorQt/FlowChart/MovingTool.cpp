#include "MovingTool.h"

#include "DrawingPaper.h"
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
#include "FlowChartEditor.h"
#include "TutorialController.h"

MovingTool* MovingTool::instance = 0;

MovingTool::MovingTool() {
}

MovingTool* MovingTool::Instance() {
	if (instance == 0) {
		instance = new MovingTool;
	}
	return instance;
}

void MovingTool::Destroy() {
	if (instance != 0) {
		delete instance;
		instance = 0;
	}
}

MovingTool::~MovingTool() {
}

void MovingTool::OnLButtonDown(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	canvas->currentX = point.x;
	canvas->currentY = point.y;

	Long count;
	Long(*indexes);
	dynamic_cast<FlowChart *>(canvas->flowChart)->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberOther(indexes, count);
	if (indexes != 0) {
		delete[] indexes;
	}
}

void MovingTool::OnMouseMove(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	Long i;
	Long count;
	Long(*indexes);
	Long x;
	Long y;
	int cx;
	int cy;

	if (canvas->mode == DrawingPaper::MOVING) {
		cx = point.x - canvas->currentX;
		cy = point.y - canvas->currentY;

		dynamic_cast<FlowChart *>(canvas->flowChart)->GetSelecteds(&indexes, &count);
		canvas->Invalidate(true);

		for (i = 0; i < count; i++) {
			x = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(indexes[i])->GetX();
			y = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(indexes[i])->GetY();

			dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(indexes[i])->Move(x + cx, y + cy);

		}
		canvas->Invalidate(true);

		canvas->currentX = point.x;
		canvas->currentY = point.y;

		if (indexes != 0) {
			delete[] indexes;
		}
	}
}

void MovingTool::OnLButtonUp(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	canvas->mode = DrawingPaper::SELECT;
	canvas->tool = SelectingTool::Instance();
	canvas->RedrawWindow();

	FlowChartEditor *editor = static_cast<FlowChartEditor*>(canvas->GetParent());
	TutorialForm *tutorialForm = static_cast<TutorialForm*>(editor->windows[2]);
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
}