#ifndef _SKETCHBOOK_H
#define _SKETCHBOOK_H

#include "Array.h"
#include <qpoint.h>
#include <qstring.h>
class NShape;
class FlowChartVisitor;
class Memory;

class SketchBook {
public:
	SketchBook(Long capacity = 10);
	SketchBook(const SketchBook& source);
	~SketchBook();
	SketchBook& operator=(const SketchBook& source);

	//if New file added, flowchart would be empty.
	//if Open file added, flowchart would be not empty.
	//whenever Add or Insert called, memories would be empty.
	//memories will be changed only by selecting canvas.

	Long Add(NShape *canvas, NShape *flowChart, QString fileOpenPath = QString(""));
	Long Insert(Long index, NShape *canvas, NShape *flowChart, QString fileOpenPath = QString(""));
	Long Remove(Long index);

	Long Fold(QPoint point); //set current
	
	void Unfold(NShape *flowChart, Memory *undoMemory, Memory *redoMemory); //backup flowchart and memories on canvas window
	Long ModifyFileOpenPath(QString fileName); //set full file path name

	NShape* GetCanvas(Long index);
	NShape* GetFlowChart(Long index);
	QString& GetFileOpenPath(Long index);
	Memory* GetUndoMemory(Long index);
	Memory* GetRedoMemory(Long index);

	void Draw(FlowChartVisitor *visitor); //draw canvas title

	void Update(); //set color - current canvas : blue , other canvases : gray 
	void Arrange(Long x); //move - x : x of canvas window

	Long GetCapacity() const;
	Long GetLength() const;
	Long GetCurrent() const;
private:
	Array<NShape*> canvasList;
	Array<NShape*> flowChartList; //관리만! 변경 없음.
	Array<QString> fileOpenPathList;
	Array<Memory*> undoMemoryList; //관리만.
	Array<Memory*> redoMemoryList; //관리만.
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