// _ERASINGKEY_H
#include "DeleteKey.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "MemoryController.h"

DeleteKey* DeleteKey::instance = 0;

DeleteKey* DeleteKey::Instance() {
	if (instance == 0) {
		instance = new DeleteKey;
	}
	return instance;
}

void DeleteKey::Destroy() {
	if (instance != 0) {
		delete instance;
		instance = 0;
	}
}

DeleteKey::DeleteKey() {}

void DeleteKey::OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long it;
	Shape *shape;

	Long count;
	Long(*indexes);
	dynamic_cast<FlowChart *>(canvas->flowChart)->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberRemove(indexes, count);

	it = dynamic_cast<FlowChart *>(canvas->flowChart)->GetLength() - 1;
	while (it >= 0) {
		shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(it);
		if (shape->IsSelected()) {
			dynamic_cast<FlowChart *>(canvas->flowChart)->Erase(it);
		}
		it--;
	}
	if (dynamic_cast<FlowChart *>(canvas->flowChart)->GetLength() < 1) {
		canvas->mode = DrawingPaper::IDLE;
	}

	if (indexes != 0) {
		delete[] indexes;
	}
}