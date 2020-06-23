#include "SheetManager.h"
#include "DrawingPaper.h"
#include "SheetBinder.h"
#include "Sheet.h"
#include "WindowTitle.h"
#include "HistoryController.h"
#include "HistoryBook.h"
#include "Registrar.h"
#include "VariableList.h"
#include "FlowChart.h"

SheetManager::SheetManager(DrawingPaper *canvas) {
	this->canvas = canvas;
	
	this->sheetBinder = new SheetBinder;
	float height = 26.0F;
	NShape *title = new WindowTitle(canvas->x(), canvas->y() - height - 4, 186.0F, height, QColor(102, 204, 204),
		Qt::SolidLine, QColor(102, 204, 204), String(" 제목없음"));

	Sheet *sheet = new Sheet(title, QString(""), this->canvas->flowChart,
		this->canvas->historyController->GetUndoHistoryBook(),
		this->canvas->historyController->GetRedoHistoryBook(),
		this->canvas->historyController->GetPreviousFlowChart(),
		this->canvas->registrar, this->canvas->variableList);
	this->sheetBinder->Add(sheet);
}

SheetManager::SheetManager(const SheetManager& source) {
	this->canvas = source.canvas;
	this->sheetBinder = new SheetBinder(*const_cast<SheetManager&>(source).sheetBinder);
}

SheetManager::~SheetManager() {
	if (this->sheetBinder != 0) {
		delete this->sheetBinder;
	}
}

SheetManager& SheetManager::operator=(const SheetManager& source) {
	this->canvas = source.canvas;
	this->sheetBinder = source.sheetBinder;

	return *this;
}

Long SheetManager::Select(QPoint point) {
	Long index = -1;
	
	Sheet *sheet;
	NShape *title;
	Long i = 0;
	while (i < this->sheetBinder->GetLength()) {
		sheet = this->sheetBinder->GetAt(i);
		title = sheet->GetTitle();
		if (title->IsIncluded(point)) {
			index = i;
		}
		i++;
	}

	return index;
}

Long SheetManager::Change(Long index) {
	Long current = this->sheetBinder->Move(index);
	Sheet *sheet = this->sheetBinder->GetAt(current);

	this->canvas->flowChart = sheet->GetFlowChart();
	HistoryBook *undoHistoryBook = sheet->GetUndoHistoryBook();
	HistoryBook *redoHistoryBook = sheet->GetRedoHistoryBook();
	NShape *previousFlowChart = sheet->GetPreviousFlowChart();
	this->canvas->historyController->ChangeAll(undoHistoryBook, redoHistoryBook,
		previousFlowChart);
	this->canvas->registrar = sheet->GetRegistrar();
	this->canvas->variableList = sheet->GetVariableList();

	return index;
}

Long SheetManager::New() {
	Sheet *previousSheet = this->sheetBinder->GetAt(this->sheetBinder->GetLength() - 1);
	NShape *previousTitle = previousSheet->GetTitle();
	
	NShape *title = new WindowTitle(previousTitle->GetX() + previousTitle->GetWidth(),
		previousTitle->GetY(), 186.0F, previousTitle->GetHeight(), QColor(102, 204, 204),
		Qt::SolidLine, QColor(102, 204, 204), String(" 제목없음"));
	QString fileOpenPath("");
	NShape *flowChart = new FlowChart;
	HistoryBook *undoHistoryBook = new HistoryBook;
	HistoryBook *redoHistoryBook = new HistoryBook;
	NShape *previousFlowChart = flowChart->Clone();
	Registrar *registrar = new Registrar;
	VariableList *variableList = new VariableList;

	Sheet *sheet = new Sheet(title, fileOpenPath, flowChart,
		undoHistoryBook, redoHistoryBook, previousFlowChart, registrar, variableList);
	Long index = this->sheetBinder->Add(sheet);

	return index;
}

Long SheetManager::Close() {
	Long current = this->sheetBinder->GetCurrent();
	return this->sheetBinder->Remove(current);
}

Long SheetManager::Open(QString fileOpenPath) {
	Long length = fileOpenPath.length();
	Long i = length - 1;
	while (i >= 0 && fileOpenPath[i] != '/') {
		length--;
		i--;
	}
	QString fileName = fileOpenPath;
	fileName.remove(0, length);
	fileName.remove(fileName.length() - 4, 4);
	fileName.insert(0, ' ');
	//파일이름이 10자가 넘으면 한 글자당 width 10씩 늘림
	float width = 186.0F;
	if (fileName.length() > 10) {
		width = width + (fileName.length() - 10) * 10;
	}

	Sheet *previousSheet = this->sheetBinder->GetAt(this->sheetBinder->GetLength() - 1);
	NShape *previousTitle = previousSheet->GetTitle();

	NShape *title = new WindowTitle(previousTitle->GetX() + previousTitle->GetWidth(),
		previousTitle->GetY(), width, previousTitle->GetHeight(), QColor(102, 204, 204),
		Qt::SolidLine, QColor(102, 204, 204), String(fileName.toLocal8Bit().data()));
	NShape *flowChart = canvas->flowChart;
	HistoryBook *undoHistoryBook = new HistoryBook;
	HistoryBook *redoHistoryBook = new HistoryBook;
	NShape *previousFlowChart = flowChart->Clone();
	Registrar *registrar = canvas->registrar;
	VariableList *variableList = canvas->variableList;

	Sheet *sheet = new Sheet(title, fileOpenPath, flowChart,
		undoHistoryBook, redoHistoryBook, previousFlowChart, registrar, variableList);
	Long index = this->sheetBinder->Add(sheet);

	return index;
}

void SheetManager::ModifyFileOpenPath(QString fileOpenPath) {
	Sheet *sheet = this->sheetBinder->GetAt(this->sheetBinder->GetCurrent());
	sheet->fileOpenPath = fileOpenPath;
}

void SheetManager::ModifyTitles() {
	Sheet *sheet = this->sheetBinder->GetAt(this->sheetBinder->GetCurrent());

	NShape *title = sheet->GetTitle();
	title->Paint(QColor(102, 204, 204), Qt::SolidLine, QColor(102, 204, 204));
	
	float x = this->canvas->x();
	float y = title->GetY();
	float width = title->GetWidth();
	
	Long i = 0;
	while (i < this->sheetBinder->GetLength()) {
		sheet = this->sheetBinder->GetAt(i);
		title = sheet->GetTitle();
		title->Move(x, y);
		x += width;
	
		if (i != this->sheetBinder->GetCurrent()) {
			title->Paint(QColor(235, 235, 235), Qt::SolidLine, QColor(235, 235, 235));
		}
		
		i++;
	}
}

void SheetManager::ModifyPreviousFlowChart(NShape *previousFlowChart) {
	Sheet *sheet = this->sheetBinder->GetAt(this->sheetBinder->GetCurrent());
	sheet->previousFlowChart = previousFlowChart;
}

void SheetManager::ModifyVariableList(VariableList *variableList) {
	Sheet *sheet = this->sheetBinder->GetAt(this->sheetBinder->GetCurrent());
	sheet->variableList = variableList;
}

void SheetManager::Draw(FlowChartVisitor *draw) {
	Long i = 0;
	while (i < this->sheetBinder->GetLength()) {
		this->sheetBinder->GetAt(i)->GetTitle()->Accept(draw);
		i++;
	}
}

NShape* SheetManager::GetTitle(Long index) {
	Sheet *sheet = this->sheetBinder->GetAt(index);
	NShape *title = sheet->GetTitle();

	return title;
}

QString& SheetManager::GetFileOpenPath(Long index) {
	Sheet *sheet = this->sheetBinder->GetAt(index);

	return sheet->GetFileOpenPath();
}

Long SheetManager::GetBinderLength() {
	return this->sheetBinder->GetLength();
}

Long SheetManager::GetBinderCurrent() {
	return this->sheetBinder->GetCurrent();
}