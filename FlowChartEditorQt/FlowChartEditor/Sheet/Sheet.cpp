#include "Sheet.h"

Sheet::Sheet(NShape *title, QString fileOpenPath, NShape *flowChart,
	HistoryBook *undoHistoryBook, HistoryBook *redoHistoryBook, NShape *previousFlowChart,
	Registrar *registrar, VariableList *variableList) {
	this->title = title;
	this->fileOpenPath = fileOpenPath;
	this->flowChart = flowChart;
	this->undoHistoryBook = undoHistoryBook;
	this->redoHistoryBook = redoHistoryBook;
	this->previousFlowChart = previousFlowChart;
	this->registrar = registrar;
	this->variableList = variableList;
}

Sheet::Sheet(const Sheet& source) {
	this->title = source.title;
	this->fileOpenPath = source.fileOpenPath;
	this->flowChart = source.flowChart;
	this->undoHistoryBook = source.undoHistoryBook;
	this->redoHistoryBook = source.redoHistoryBook;
	this->previousFlowChart = source.previousFlowChart;
	this->registrar = source.registrar;
	this->variableList = source.variableList;
}

Sheet::~Sheet() {
	if (this->title != 0) {
		delete this->title;
	}
	if (this->flowChart != 0) {
		delete this->flowChart;
	}
	if (this->undoHistoryBook != 0) {
		delete this->undoHistoryBook;
	}
	if (this->redoHistoryBook != 0) {
		delete this->redoHistoryBook;
	}
	if (this->previousFlowChart != 0) {
		delete this->previousFlowChart;
	}
	if (this->registrar != 0) {
		delete this->registrar;
	}
	if (this->variableList != 0) {
		delete this->variableList;
	}
}

Sheet& Sheet::operator=(const Sheet& source) {
	this->title = source.title;
	this->fileOpenPath = source.fileOpenPath;
	this->flowChart = source.flowChart;
	this->undoHistoryBook = source.undoHistoryBook;
	this->redoHistoryBook = source.redoHistoryBook;
	this->previousFlowChart = source.previousFlowChart;
	this->registrar = source.registrar;
	this->variableList = source.variableList;

	return *this;
}

Sheet* Sheet::Clone() {
	return new Sheet(*this);
}

NShape* Sheet::GetTitle() const {
	return this->title;
}

QString& Sheet::GetFileOpenPath() const {
	return const_cast<QString&>(this->fileOpenPath);
}

NShape* Sheet::GetFlowChart() const {
	return this->flowChart;
}

HistoryBook* Sheet::GetUndoHistoryBook() const {
	return this->undoHistoryBook;
}

HistoryBook* Sheet::GetRedoHistoryBook() const {
	return this->redoHistoryBook;
}

NShape* Sheet::GetPreviousFlowChart() const {
	return this->previousFlowChart;
}

Registrar* Sheet::GetRegistrar() const {
	return this->registrar;
}

VariableList* Sheet::GetVariableList() const {
	return this->variableList;
}