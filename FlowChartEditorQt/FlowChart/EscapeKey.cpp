// EscapeKey.cpp
#include "EscapeKey.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "FlowChartEditor.h"
#include "FlowChartTemplate.h"
#include "Template.h"

EscapeKey* EscapeKey::instance = 0;

EscapeKey::EscapeKey() {}

EscapeKey* EscapeKey::Instance() {
	if (instance == 0) {
		instance = new EscapeKey;
	}
	return instance;
}

void EscapeKey::Destroy() {
	if (instance != 0) {
		delete instance;
		instance = 0;
	}
}

void EscapeKey::OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long count;
	Long(*indexes);

	dynamic_cast<FlowChart *>(canvas->flowChart)->GetSelecteds(&indexes, &count);
	for (Long i = 0; i < count; i++) {
		Shape *shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(indexes[i]);
		shape->Select(false);
	}

	FlowChartEditor* editor = (FlowChartEditor*)canvas->GetParent();
	FlowChartTemplate* flowChartTemplate = dynamic_cast<FlowChartTemplate*>(editor->windows[1]);

	if (flowChartTemplate->mode == FlowChartTemplate::DRAWON && canvas->mode != DrawingPaper::DRAWING) {
		flowChartTemplate->mode = FlowChartTemplate::DRAWOFF;
		Long i = dynamic_cast<Template*>(flowChartTemplate->flowChartTemplate)->GetLength() - 1;
		while (i >= 7) { //numberBox만 없애기
			dynamic_cast<Template*>(flowChartTemplate->flowChartTemplate)->UnRegister(i);
			i--;
		}
		editor->isUnModeMenuEnabled = FALSE;
	}

	if (canvas->mode == DrawingPaper::DRAWING) {
		canvas->templateSelected = NULL;
		flowChartTemplate->shapeSelected = NULL;
	}

	canvas->mode = DrawingPaper::IDLE;

	canvas->Invalidate(true);
	canvas->indexOfSelected = -1;


	if (indexes != 0) {
		delete[] indexes;
	}
}