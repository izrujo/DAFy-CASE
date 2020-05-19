#include "MovingTool.h"

#include "DrawingPaper.h"
#include "Shape.h"
#include "SelectingTool.h"
#include "ScrollController.h"
#include "Scroll.h"
#include "Zoom.h"
#include "ZoomVisitor.h"
#include "CoordinateConverter.h"
#include "../FlowChartEditor.h"

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

void MovingTool::OnLButtonDown(DrawingPaper *canvas, QPointF point) {
	canvas->currentX = point.x();
	canvas->currentY = point.y();

	Long count;
	Long(*indexes);
	canvas->flowChart->GetSelecteds(&indexes, &count);
	if (indexes != 0) {
		delete[] indexes;
	}
}

void MovingTool::OnMouseMove(DrawingPaper *canvas, QPointF point) {
	Long i;
	Long count;
	Long(*indexes);
	float x;
	float y;
	float cx;
	float cy;

	if (canvas->mode == DrawingPaper::MOVING) {
		cx = point.x() - canvas->currentX;
		cy = point.y() - canvas->currentY;

		canvas->flowChart->GetSelecteds(&indexes, &count);
		canvas->repaint();

		for (i = 0; i < count; i++) {
			x = canvas->flowChart->GetAt(indexes[i])->GetX();
			y = canvas->flowChart->GetAt(indexes[i])->GetY();

			canvas->flowChart->GetAt(indexes[i])->Move(x + cx, y + cy);

		}
		canvas->repaint();

		canvas->currentX = point.x();
		canvas->currentY = point.y();

		if (indexes != 0) {
			delete[] indexes;
		}
	}
}

void MovingTool::OnLButtonUp(DrawingPaper *canvas, QPointF point) {
	canvas->mode = DrawingPaper::SELECT;
	canvas->tool = SelectingTool::Instance();
	canvas->repaint();
}