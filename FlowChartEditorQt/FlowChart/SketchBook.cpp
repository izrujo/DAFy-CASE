#include "SketchBook.h"
#include "Shape.h"
#include "Memory.h"
#include "VariableList.h"

SketchBook::SketchBook(Long capacity)
	: canvasList(capacity), flowChartList(capacity),
	fileOpenPathList(capacity), undoMemoryList(capacity), redoMemoryList(capacity),
	variableListList(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = 0;
}

SketchBook::SketchBook(const SketchBook& source)
	: canvasList(source.canvasList), flowChartList(source.flowChartList),
	fileOpenPathList(source.fileOpenPathList), 
	undoMemoryList(source.undoMemoryList), redoMemoryList(source.redoMemoryList),
	variableListList(source.variableListList) {
	Long i = 0;
	while (i < source.length) {
		this->canvasList.Modify(i, (const_cast<SketchBook&>(source)).canvasList[i]->Clone());
		this->flowChartList.Modify(i, (const_cast<SketchBook&>(source)).flowChartList[i]->Clone());
		this->undoMemoryList.Modify(i, new Memory(*const_cast<SketchBook&>(source).undoMemoryList[i]));
		this->redoMemoryList.Modify(i, new Memory(*const_cast<SketchBook&>(source).redoMemoryList[i]));
		this->variableListList.Modify(i, new VariableList(*const_cast<SketchBook&>(source).variableListList[i]));
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

SketchBook::~SketchBook() {
	Long i = 0;
	while (i < this->length) {
		if (this->canvasList[i] != 0) {
			delete this->canvasList[i];
		}
		if (this->flowChartList[i] != 0) {
			delete this->flowChartList[i];
		}
		if (this->undoMemoryList[i] != 0) {
			delete this->undoMemoryList[i];
		}
		if (this->redoMemoryList[i] != 0) {
			delete this->redoMemoryList[i];
		}
		if (this->variableListList[i] != 0) {
			delete this->variableListList[i];
		}
		i++;
	}
}

SketchBook& SketchBook::operator=(const SketchBook& source) {
	NShape *canvas;
	NShape *flowChart;
	Memory *undoMemory;
	Memory *redoMemory;
	VariableList *variableList;

	Long i = 0;
	while (i < this->length) {
		canvas = this->canvasList.GetAt(i);
		if (canvas != 0) {
			delete canvas;
		}
		flowChart = this->flowChartList.GetAt(i);
		if (flowChart != 0) {
			delete flowChart;
		}
		undoMemory = this->undoMemoryList.GetAt(i);
		if (undoMemory != 0) {
			delete undoMemory;
		}
		redoMemory = this->redoMemoryList.GetAt(i);
		if (redoMemory != 0) {
			delete redoMemory;
		}
		variableList = this->variableListList.GetAt(i);
		if (variableList != 0) {
			delete variableList;
		}
		i++;
	}

	this->canvasList = source.canvasList;
	this->flowChartList = source.flowChartList;
	this->fileOpenPathList = source.fileOpenPathList;
	this->undoMemoryList = source.undoMemoryList;
	this->redoMemoryList = source.redoMemoryList;
	this->variableListList = source.variableListList;

	i = 0;
	while (i < source.GetLength()) {
		canvas = const_cast<SketchBook&>(source).canvasList.GetAt(i)->Clone();
		this->canvasList.Modify(i, canvas);
		flowChart = const_cast<SketchBook&>(source).flowChartList.GetAt(i)->Clone();
		this->flowChartList.Modify(i, flowChart);
		undoMemory = new Memory(*const_cast<SketchBook&>(source).undoMemoryList.GetAt(i));
		this->undoMemoryList.Modify(i, undoMemory);
		redoMemory = new Memory(*const_cast<SketchBook&>(source).redoMemoryList.GetAt(i));
		this->redoMemoryList.Modify(i, redoMemory);
		variableList = new VariableList(*const_cast<SketchBook&>(source).variableListList.GetAt(i));
		this->variableListList.Modify(i, variableList);
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	return *this;
}

Long SketchBook::Add(NShape *canvas, NShape *flowChart, QString fileOpenPath) {
	if (this->length < this->capacity) {
		this->current = this->canvasList.Store(this->length, canvas);
		this->flowChartList.Store(this->length, flowChart);
		this->fileOpenPathList.Store(this->length, fileOpenPath);
		this->undoMemoryList.Store(this->length, new Memory);
		this->redoMemoryList.Store(this->length, new Memory);
		this->variableListList.Store(this->length, new VariableList);
	}
	else {
		this->current = this->canvasList.AppendFromRear(canvas);
		this->flowChartList.AppendFromRear(flowChart);
		this->fileOpenPathList.AppendFromRear(fileOpenPath);
		this->undoMemoryList.AppendFromRear(new Memory);
		this->redoMemoryList.AppendFromRear(new Memory);
		this->variableListList.AppendFromRear(new VariableList);
		this->capacity++;
	}
	this->length++;

	return this->current;
}

Long SketchBook::Insert(Long index, NShape *canvas, NShape *flowChart, QString fileOpenPath) {
	this->current = -1;
	this->current = this->canvasList.Insert(index, canvas);
	this->flowChartList.Insert(index, flowChart);
	this->fileOpenPathList.Insert(index, fileOpenPath);
	this->undoMemoryList.Insert(index, new Memory);
	this->redoMemoryList.Insert(index, new Memory);
	this->variableListList.Insert(index, new VariableList);
	if (this->length >= this->capacity) {
		this->capacity += 1;
	}
	this->length++;

	return this->current;
}

Long SketchBook::Remove(Long index) {
	if (index >= 0 && index < this->GetLength()) {
		delete this->canvasList[index];
		this->current = this->canvasList.Delete(index);

		delete this->flowChartList[index];
		this->flowChartList.Delete(index);

		this->fileOpenPathList.Delete(index);

		delete this->undoMemoryList[index];
		this->undoMemoryList.Delete(index);

		delete this->redoMemoryList[index];
		this->redoMemoryList.Delete(index);

		delete this->variableListList[index];
		this->variableListList.Delete(index);

		this->length--;
	}
	return this->current;
}

Long SketchBook::ModifyFileOpenPath(QString fileName) {
	return this->fileOpenPathList.Modify(this->current, fileName);
}


NShape* SketchBook::GetCanvas(Long index) {
	return this->canvasList.GetAt(index);
}

NShape* SketchBook::GetFlowChart(Long index) {
	return this->flowChartList.GetAt(index);
}

QString& SketchBook::GetFileOpenPath(Long index) {
	return this->fileOpenPathList.GetAt(index);
}

Memory* SketchBook::GetUndoMemory(Long index) {
	return this->undoMemoryList.GetAt(index);
}

Memory* SketchBook::GetRedoMemory(Long index) {
	return this->redoMemoryList.GetAt(index);
}

VariableList* SketchBook::GetVariableList(Long index) {
	return this->variableListList.GetAt(index);
}

void SketchBook::Draw(FlowChartVisitor *visitor) {
	Long i = 0;
	while (i < this->length) {
		this->canvasList.GetAt(i)->Accept(visitor);
		i++;
	}
}

Long SketchBook::Fold(QPoint point) {
	Long i = 0;

	while (i < this->length) {
		if (this->canvasList[i]->IsIncluded(point)) {
			this->current = i;
		}
		i++;
	}

	return this->current;
}

void SketchBook::Unfold(NShape *flowChart, Memory *undoMemory, Memory *redoMemory, VariableList *variableList) {
	this->flowChartList[this->current] = flowChart;
	this->undoMemoryList[this->current] = undoMemory;
	this->redoMemoryList[this->current] = redoMemory;
	this->variableListList[this->current] = variableList;
}

void SketchBook::Update() {
	this->canvasList[this->current]->Paint(QColor(102, 204, 204), Qt::SolidLine, QColor(102, 204, 204));
	Long i = 0;
	while (i < this->length) {
		if (i != this->current) {
			this->canvasList[i]->Paint(QColor(235, 235, 235), Qt::SolidLine, QColor(235, 235, 235));
		}
		i++;
	}
}

void SketchBook::Arrange(float x) {
	NShape *current;
	float y = this->canvasList[0]->GetY();
	Long i = 0;
	while (i < this->length) {
		current = this->canvasList[i];
		current->Move(x, y);
		x += current->GetWidth();
		i++;
	}
}