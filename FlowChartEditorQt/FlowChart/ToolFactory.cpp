#include "ToolFactory.h"
#include "DrawingTool.h"
#include "MovingTool.h"
#include "ResizingTool.h"
#include "SelectingTool.h"

#include "Shape.h"
#include "FlowChart.h"

#include "DrawingPaper.h"

#include "../FlowChartEditor.h"
#include "FlowChartTemplate.h"
#include "ScrollController.h"
#include "Scroll.h"
#include "Zoom.h"
#include "ZoomVisitor.h"
#include "CoordinateConverter.h"

#include <Windows.h>

ToolFactory::ToolFactory() {
}

Tool* ToolFactory::Create(DrawingPaper *canvas, QPointF point) {
	Tool *tool = 0;
	NShape *shape;
	FlowChartEditor* editor;
	bool isControlPressed;

	isControlPressed = ((::GetKeyState(VK_CONTROL) & 0x8000) != 0);

	// DRAWING 모드 결정
	editor = (FlowChartEditor*)canvas->parentWidget();
	if (static_cast<FlowChartTemplate*>(editor->windows[1])->shapeSelected != NULL) {
		canvas->templateSelected = static_cast<FlowChartTemplate *>(editor->windows[1])->shapeSelected->Clone();
		canvas->templateSelected->Move(0, 0);
		static_cast<FlowChartTemplate *>(editor->windows[1])->shapeSelected = NULL;

		tool = DrawingTool::Instance();
		canvas->mode = DrawingPaper::DRAWING;
	}
	else {
		if (!isControlPressed) {
			Long i = 0;
			Long(*indexes);
			Long count;

			canvas->flowChart->GetSelecteds(&indexes, &count);
			Long positionX = 0;
			Long positionY = 0;
			if (canvas->scrollController != NULL) {
				positionX = canvas->scrollController->GetScroll(1)->value();
				positionY = canvas->scrollController->GetScroll(0)->value();
			}
			point.setX(point.x() + positionX);
			point.setY(point.y() + positionY);

			NShape *holdA4Paper = canvas->a4Paper->Clone();
			FlowChartVisitor *zoomVisitor = new ZoomVisitor(canvas->zoom);
			holdA4Paper->Accept(zoomVisitor);

			QPointF currentReal(point.x(), point.y());
			QPointF currentVirtual = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertVirtual(currentReal);

			currentVirtual.setX(currentVirtual.x() * 100 / canvas->zoom->GetRate());
			currentVirtual.setY(currentVirtual.y() * 100 / canvas->zoom->GetRate());

			currentReal = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertReal(currentVirtual);

			point.setX(currentReal.x());
			point.setY(currentReal.y());

			while (i < count && tool == 0)
			{
				shape = canvas->flowChart->GetAt(indexes[i]);
				canvas->hitCode = shape->GetHitCode(point);

				if (canvas->hitCode == HIT_BODY) {
					tool = MovingTool::Instance();
					canvas->mode = DrawingPaper::MOVING;
				}

				if (!(canvas->hitCode == HIT_BODY || canvas->hitCode == HIT_NONE)) {
					canvas->indexOfSelected = indexes[i];
					tool = ResizingTool::Instance();
					canvas->mode = DrawingPaper::SIZING;
				}
				i++;
			}

			if (indexes != 0)
			{
				delete[] indexes;
			}
		}

		if (tool == 0) {
			tool = SelectingTool::Instance();
			canvas->mode = DrawingPaper::SELECT;
		}
	}
	canvas->repaint();
	return tool;
}