#include "SketchBook.h"
#include "NShape.h"

SketchBook::SketchBook(Long capacity)
	: canvasList(capacity), flowChartList(capacity) {
	this->capacity = capacity;
	this->length = length;
}
SketchBook(const SketchBook& source);
~SketchBook();
SketchBook& operator=(const SketchBook& source);

Long Add(NShape *canvas, NShape *flowChart);
Long Insert(Long index, NShape *canvas, NShape *flowChart);
Long Remove(Long index);

NShape* GetCanvas(Long index);
NShape* GetFlowChart(Long index);