#ifndef _SKETCHBOOK_H
#define _SKETCHBOOK_H

#include "Array.h"
class NShape;

class SketchBook {
public:
	SketchBook(Long capacity = 10);
	SketchBook(const SketchBook& source);
	~SketchBook();
	SketchBook& operator=(const SketchBook& source);

	Long Add(NShape *canvas, NShape *flowChart);
	Long Insert(Long index, NShape *canvas, NShape *flowChart);
	Long Remove(Long index);

	NShape* GetCanvas(Long index);
	NShape* GetFlowChart(Long index);
	
	Long GetCapacity() const;
	Long GetLength() const;
	Long GetCurrent() const;

private:
	Array<NShape*> canvasList;
	Array<NShape*> flowChartList;
	Long capacity;
	Long length;
	Long current;
};

inline SketchBook::GetCapacity() const {
	return this->capacity;
}
inline SketchBook::GetLength() const {
	return this->length;
}
inline SketchBook::GetCurrent() const {
	return this->current;
}

#endif //_SKETCHBOOK_H