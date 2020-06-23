#include "SketchBook.h"
#include "Shape.h"
#include "HistoryController.h"
#include "Registrar.h"
#include "VariableList.h"

SketchBook::SketchBook(Long capacity)
	: canvasList(capacity), flowChartList(capacity),
	fileOpenPathList(capacity), historyControllerList(capacity),
	registrarList(capacity), variableListList(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = 0;
}

SketchBook::SketchBook(const SketchBook& source)
	: canvasList(source.canvasList), flowChartList(source.flowChartList),
	fileOpenPathList(source.fileOpenPathList), historyControllerList(source.historyControllerList),
	registrarList(source.registrarList), variableListList(source.variableListList) {
	Long i = 0;
	while (i < source.length) {
		this->canvasList.Modify(i, (const_cast<SketchBook&>(source)).canvasList[i]->Clone());
		this->flowChartList.Modify(i, (const_cast<SketchBook&>(source)).flowChartList[i]->Clone());
		this->historyControllerList.Modify(i, new HistoryController(*const_cast<SketchBook&>(source).historyControllerList[i]));
		this->registrarList.Modify(i, new Registrar(*const_cast<SketchBook&>(source).registrarList[i]));
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
		if (this->historyControllerList[i] != 0) {
			delete this->historyControllerList[i];
		}
		if (this->registrarList[i] != 0) {
			delete this->registrarList[i];
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
	HistoryController *historyController;
	Registrar *registrar;
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
		historyController = this->historyControllerList.GetAt(i);
		if (historyController != 0) {
			delete historyController;
		}
		registrar = this->registrarList.GetAt(i);
		if (registrar != 0) {
			delete registrar;
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
	this->historyControllerList = source.historyControllerList;
	this->registrarList = source.registrarList;
	this->variableListList = source.variableListList;

	i = 0;
	while (i < source.GetLength()) {
		canvas = const_cast<SketchBook&>(source).canvasList.GetAt(i)->Clone();
		this->canvasList.Modify(i, canvas);
		flowChart = const_cast<SketchBook&>(source).flowChartList.GetAt(i)->Clone();
		this->flowChartList.Modify(i, flowChart);
		historyController = new HistoryController(*const_cast<SketchBook&>(source).historyControllerList.GetAt(i));
		this->historyControllerList.Modify(i, historyController);
		registrar = new Registrar(*const_cast<SketchBook&>(source).registrarList.GetAt(i));
		this->registrarList.Modify(i, registrar);
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
		this->historyControllerList.Store(this->length, new HistoryController);
		this->registrarList.Store(this->length, new Registrar);
		this->variableListList.Store(this->length, new VariableList);
	}
	else {
		this->current = this->canvasList.AppendFromRear(canvas);
		this->flowChartList.AppendFromRear(flowChart);
		this->fileOpenPathList.AppendFromRear(fileOpenPath);
		this->historyControllerList.AppendFromRear(new HistoryController);
		this->registrarList.AppendFromRear(new Registrar);
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
	this->historyControllerList.Insert(index, new HistoryController);
	this->registrarList.Insert(index, new Registrar);
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

		delete this->historyControllerList[index];
		this->historyControllerList.Delete(index);

		delete this->registrarList[index];
		this->registrarList.Delete(index);

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

HistoryController* SketchBook::GetHistoryController(Long index) {
	return this->historyControllerList.GetAt(index);
}

Registrar* SketchBook::GetRegistrar(Long index) {
	return this->registrarList.GetAt(index);
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

void SketchBook::Unfold(NShape *flowChart, HistoryController *historyController,
	Registrar *registrar, VariableList *variableList) {
	this->flowChartList[this->current] = flowChart;
	this->historyControllerList[this->current] = historyController;
	this->registrarList[this->current] = registrar;
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