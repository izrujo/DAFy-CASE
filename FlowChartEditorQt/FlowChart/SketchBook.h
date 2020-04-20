#ifndef _SKETCHBOOK_H
#define _SKETCHBOOK_H

#include "Array.h"
#include <qpoint.h>
class NShape;
class FlowChartVisitor;

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

	void Draw(FlowChartVisitor *visitor);
	void Fold(QPoint point); //current canvas : blue , other canvases : gray 
	void Unfold(NShape *flowChart); //펼쳐져 있던 캔버스의 순서도를 저장하기.

	Long GetCapacity() const;
	Long GetLength() const;
	Long GetCurrent() const;

private:
	Array<NShape*> canvasList;
	Array<NShape*> flowChartList; //관리만! 변경 없음.
	Long capacity;
	Long length;
	Long current;
};

inline Long SketchBook::GetCapacity() const {
	return this->capacity;
}
inline Long SketchBook::GetLength() const {
	return this->length;
}
inline Long SketchBook::GetCurrent() const {
	return this->current;
}

#endif //_SKETCHBOOK_H