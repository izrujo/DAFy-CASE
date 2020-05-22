#include "FlowChartCommands.h"
#include "../FlowChartEditor.h"
#include "DrawingPaper.h"
#include "PreviewForm.h"
#include "A4Paper.h"
#include "FlowChart.h"
#include "../GObject/Painter.h"
#include "DrawVisitor.h"
#include "FlowChartTemplate.h"
#include "NumberBox.h"
#include "Template.h"
#include "Clipboard.h"
#include "Zoom.h"
#include "Tool.h"
#include "Shape.h"
#include "WindowTitle.h"
#include "VariableList.h"
#include "HistoryController.h"
#include "HistoryBook.h"
#include "Registrar.h"
#include "SheetManager.h"

#include "../GObject/QtPainter.h"
#include "../GObject/QtGObjectFactory.h"
#include "../GObject/GObject.h"

#include <qfiledialog.h>
#include <qtextstream.h>
#include <qfontdialog.h>
#include <qstring.h>
#include <qpixmap.h>
#include <QtPrintSupport/qpagesetupdialog.h>
#include <QtPrintSupport/qprinter.h>
#include <qmessagebox.h>
#include <qlabel.h>
#include <qstatusbar.h>
#include <qaction.h>

#include <windows.h>
#include <htmlhelp.h>

using namespace std;

//FlowChartCommand
FlowChartCommand::FlowChartCommand(FlowChartEditor *editor) {
	this->editor = editor;
}

FlowChartCommand::FlowChartCommand(const FlowChartCommand &source) {
	this->editor = source.editor;
}

FlowChartCommand::~FlowChartCommand() {
}

FlowChartCommand &FlowChartCommand::operator =(const FlowChartCommand &source) {
	this->editor = source.editor;

	return *this;
}

//SaveCommand
SaveCommand::SaveCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SaveCommand::SaveCommand(const SaveCommand &source)
	: FlowChartCommand(source) {

}

SaveCommand::~SaveCommand() {
}

SaveCommand &SaveCommand::operator =(const SaveCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SaveCommand::Execute() {
	Long current = this->editor->sheetManager->GetBinderCurrent();
	QString fileOpenPath = this->editor->sheetManager->GetFileOpenPath(current);
	if (fileOpenPath.isEmpty()) {
		NShape *canvasTitle = this->editor->sheetManager->GetTitle(current);
		QString fileName;
		QString fileName_(QString::fromLocal8Bit(canvasTitle->GetContents()));
		fileName_.remove(0, 1);

		fileName = QFileDialog::getSaveFileName((QWidget *)this->editor,
			QObject::tr("Save File"),
			fileName_,
			QObject::tr("Text files (*.txt)"));

		QFile file(fileName);
		bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);
		if (isOpen == true) {
			this->editor->sheetManager->ModifyFileOpenPath(fileName);
			(static_cast<DrawingPaper *>(this->editor->windows[0]))->Save(fileName);

			Long length = fileName.length();
			Long i = length - 1;
			while (i >= 0 && fileName[i] != '/') {
				length--;
				i--;
			}
			fileName.remove(0, length);
			fileName.remove(fileName.length() - 4, 4);
			fileName.insert(0, ' ');

			//파일이름이 10자가 넘으면 한 글자당 width 10씩 늘림
			float width = 186.0F;
			if (fileName.length() > 10) {
				width = width + (fileName.length() - 10) * 10;
				canvasTitle->ReSize(width, canvasTitle->GetHeight());
				this->editor->sheetManager->ModifyTitles();
				//캔버스 닫는거 옮기기
				float windowCloseX = canvasTitle->GetX() + canvasTitle->GetWidth() - 26 - 3; //24=사각형길이,3=여유공간
				float windowCloseY = canvasTitle->GetY() + 4;
				this->editor->windowClose->Move(windowCloseX, windowCloseY);
			}

			canvasTitle->Rewrite(fileName.toLocal8Bit().data());
		}
	}
	else {
		(static_cast<DrawingPaper *>(this->editor->windows[0]))->Save(fileOpenPath);
	}
	QString message = QString::fromLocal8Bit("    저장 성공");
	this->editor->messageStatus->setText(message);
	this->editor->statusBar->repaint();
}

//SaveAsCommand
SaveAsCommand::SaveAsCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SaveAsCommand::SaveAsCommand(const SaveAsCommand &source)
	: FlowChartCommand(source) {

}

SaveAsCommand::~SaveAsCommand() {
}

SaveAsCommand &SaveAsCommand::operator =(const SaveAsCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SaveAsCommand::Execute() {
	Long current = this->editor->sheetManager->GetBinderCurrent();
	NShape *canvasTitle = this->editor->sheetManager->GetTitle(current);
	QString fileName;
	QString fileName_(QString::fromLocal8Bit(canvasTitle->GetContents()));
	fileName_.remove(0, 1);

	fileName = QFileDialog::getSaveFileName((QWidget *)this->editor,
		QObject::tr("Save File"),
		fileName_,
		QObject::tr("Text files (*.txt)"));
	QFile file(fileName);
	bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);
	if (isOpen == true) {
		this->editor->sheetManager->ModifyFileOpenPath(fileName);
		(static_cast<DrawingPaper *>(this->editor->windows[0]))->Save(fileName);

		Long length = fileName.length();
		Long i = length - 1;
		while (i >= 0 && fileName[i] != '/') {
			length--;
			i--;
		}
		fileName.remove(0, length);
		fileName.remove(fileName.length() - 4, 4);
		fileName.insert(0, ' ');

		//파일이름이 10자가 넘으면 한 글자당 width 10씩 늘림
		float width = 186.0F;
		if (fileName.length() > 10) {
			width = width + (fileName.length() - 10) * 10;
			canvasTitle->ReSize(width, canvasTitle->GetHeight());
			this->editor->sheetManager->ModifyTitles();
			//캔버스 닫는거 옮기기
			float windowCloseX = canvasTitle->GetX() + canvasTitle->GetWidth() - 26 - 3; //24=사각형길이,3=여유공간
			float windowCloseY = canvasTitle->GetY() + 4;
			this->editor->windowClose->Move(windowCloseX, windowCloseY);
		}

		canvasTitle->Rewrite(fileName.toLocal8Bit().data());

		QString message = QString::fromLocal8Bit("    저장 성공");
		this->editor->messageStatus->setText(message);
		this->editor->statusBar->repaint();
	}
}

//OpenCommand
OpenCommand::OpenCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

OpenCommand::OpenCommand(const OpenCommand &source)
	: FlowChartCommand(source) {

}

OpenCommand::~OpenCommand() {
}

OpenCommand &OpenCommand::operator =(const OpenCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void OpenCommand::Execute() {
	QString fileName = QFileDialog::getOpenFileName((QWidget *)this->editor,
		QObject::tr("Load"), "",
		QObject::tr("(*.txt);;All Files (*)"));
	QFile file(fileName);
	bool isOpen = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (isOpen == true) {
		//너무 많이 열지 못하게 방지하는 기능
		NShape *last = this->editor->sheetManager->GetTitle(this->editor->sheetManager->GetBinderLength() - 1);
		Long lastRight = last->GetX() + last->GetWidth();

		DrawingPaper *canvas = static_cast<DrawingPaper *>(this->editor->windows[0]);
		//마지막 캔버스 타이틀의 오른쪽이 윈도우의 오른쪽보다 작을 때만 추가로 열 수 있다.
		if (lastRight + 186 < canvas->x() + canvas->width()) { //186은 캔버스 타이틀의 최소 너비
			//제일 끝에 있는 캔버스 타이틀 뒤에 새로운 캔버스 타이틀 붙이기
			//열기
			(static_cast<DrawingPaper *>(this->editor->windows[0]))->Load(fileName);
			//새로운 캔버스 타이틀 만들기
			Long current = this->editor->sheetManager->Open(fileName);
			this->editor->sheetManager->Change(current);
			//스케치북을 펼친다 : 캔버스 타이틀 색깔 바꾸기
			this->editor->sheetManager->ModifyTitles();
			//캔버스 닫는거 옮기기
			NShape *canvasTitle = this->editor->sheetManager->GetTitle(current);
			float windowCloseX = canvasTitle->GetX() + canvasTitle->GetWidth() - 26 - 3; //24=사각형길이,3=여유공간
			float windowCloseY = canvasTitle->GetY() + 4;
			this->editor->windowClose->Move(windowCloseX, windowCloseY);

			canvas->setFocus();
			this->editor->repaint();
		}
		else {
			//메시지 박스
			QMessageBox messageBox(QMessageBox::Warning, QString::fromLocal8Bit("경고"),
				QString::fromLocal8Bit("더 열 수 없습니다. 파일을 닫은 후 여십시오."),
				QMessageBox::Ok, this->editor);
			int ret = messageBox.exec();
		}
	}
}

//NewCommand
NewCommand::NewCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

NewCommand::NewCommand(const NewCommand &source)
	: FlowChartCommand(source) {

}

NewCommand::~NewCommand() {
}

NewCommand &NewCommand::operator =(const NewCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void NewCommand::Execute() {
	(static_cast<DrawingPaper *>(this->editor->windows[0]))->New();
	(static_cast<DrawingPaper *>(this->editor->windows[0]))->setFocus();
	this->editor->repaint();
}

//UndoCommand
UndoCommand::UndoCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

UndoCommand::UndoCommand(const UndoCommand &source)
	: FlowChartCommand(source) {

}

UndoCommand::~UndoCommand() {
}

UndoCommand &UndoCommand::operator =(const UndoCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void UndoCommand::Execute() {
	if (static_cast<DrawingPaper *>(this->editor->windows[0])
		->historyController->GetUndoHistoryBook()->GetLength() > 0) {
		static_cast<DrawingPaper *>(this->editor->windows[0])->historyController->Undo();
		this->editor->windows[0]->repaint();
	}
}

//RedoCommand
RedoCommand::RedoCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

RedoCommand::RedoCommand(const RedoCommand &source)
	: FlowChartCommand(source) {

}

RedoCommand::~RedoCommand() {
}

RedoCommand &RedoCommand::operator =(const RedoCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void RedoCommand::Execute() {
	if (static_cast<DrawingPaper *>(this->editor->windows[0])
		->historyController->GetRedoHistoryBook()->GetLength() > 0) {
		static_cast<DrawingPaper *>(this->editor->windows[0])->historyController->Redo();
		this->editor->windows[0]->repaint();
	}
}

//FontSetCommand
FontSetCommand::FontSetCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

FontSetCommand::FontSetCommand(const FontSetCommand &source)
	: FlowChartCommand(source) {

}

FontSetCommand::~FontSetCommand() {
}

FontSetCommand &FontSetCommand::operator =(const FontSetCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void FontSetCommand::Execute() {
	//QFontDialog 로 QFont 객체 얻어서 그것의 정보로 GObject 만들어서 Select - Update 하기
	//따라서 FlowChartFont는 필요 없음.

	//취소 눌렀을 때 설정할 원래 폰트
	GObject *oldFont = static_cast<DrawingPaper *>(this->editor->windows[0])->painter->CurrentObject("Font");
	QString family = oldFont->GetFamily();
	Long weight = oldFont->GetWeight();
	Long pointSize = oldFont->GetPointSize();
	bool italic = oldFont->GetItalic();
	QFont cancelFont(family, weight, pointSize, italic);

	bool ok;
	QFont userfont = QFontDialog::getFont(&ok, cancelFont, this->editor);

	if (ok == true) {
		QtGObjectFactory factory;
		GObject *font = factory.MakeFont(userfont.family(), userfont.pointSize(), userfont.weight(), userfont.italic());
		static_cast<DrawingPaper *>(this->editor->windows[0])->painter->SelectObject(*font);
		static_cast<DrawingPaper *>(this->editor->windows[0])->painter->Update();
		this->editor->windows[0]->repaint();
	}
}

//PreviewCommand
PreviewCommand::PreviewCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

PreviewCommand::PreviewCommand(const PreviewCommand &source)
	: FlowChartCommand(source) {

}

PreviewCommand::~PreviewCommand() {
}

PreviewCommand &PreviewCommand::operator =(const PreviewCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void PreviewCommand::Execute() {
	NShape *flowChart = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->flowChart->Clone();
	PreviewForm *previewForm = new PreviewForm(this->editor, flowChart);
	previewForm->show();
	//previewForm->Create(NULL, "인쇄 미리 보기", 13565952UL, CRect(0, 0, 1200, 875));
	//previewForm->ShowWindow(SW_NORMAL);
	//previewForm->UpdateWindow();
}

//SaveAsImageCommand
SaveAsImageCommand::SaveAsImageCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SaveAsImageCommand::SaveAsImageCommand(const SaveAsImageCommand &source)
	: FlowChartCommand(source) {

}

SaveAsImageCommand::~SaveAsImageCommand() {
}

SaveAsImageCommand &SaveAsImageCommand::operator =(const SaveAsImageCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SaveAsImageCommand::Execute() {
	NShape *canvasTitle = this->editor->sheetManager->GetTitle(this->editor->sheetManager->GetBinderCurrent());
	QString fileName;
	QString fileName_(QString::fromLocal8Bit(canvasTitle->GetContents()));
	fileName_.remove(0, 1);

	fileName = QFileDialog::getSaveFileName((QWidget *)this->editor,
		QObject::tr("Save File"),
		fileName_,
		QObject::tr("Image files (*.jpg)"));

	QFile file(fileName);
	bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);
	if (isOpen == true && fileName.length() > 0) {
		NShape *flowChart = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->flowChart->Clone();
		NShape *paper = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->a4Paper->Clone();

		flowChart->UnSelectAll();

		GObject *painter = new QtPainter(paper->GetWidth(), paper->GetHeight());
		DrawVisitor drawVisitor(painter);

		GObject *font = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->painter->CurrentObject("Font");
		painter->SelectObject(*(font->Clone()));
		painter->Update();

		float x;
		float y;
		Long i;
		for (i = 0; i < flowChart->GetLength(); i++) {
			x = flowChart->GetAt(i)->GetX();
			y = flowChart->GetAt(i)->GetY();
			flowChart->GetAt(i)->Move(x - paper->GetX(), y - paper->GetY());
		}

		flowChart->Accept(&drawVisitor);

		dynamic_cast<QtPainter *>(painter)->qPixmap->save(fileName, "png");

		if (flowChart != NULL) {
			delete flowChart;
		}
		if (paper != NULL) {
			delete paper;
		}
		if (painter != NULL) {
			delete painter;
		}
	}
}

//DrawingModeCommand
DrawingModeCommand::DrawingModeCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

DrawingModeCommand::DrawingModeCommand(const DrawingModeCommand &source)
	: FlowChartCommand(source) {

}

DrawingModeCommand::~DrawingModeCommand() {
}

DrawingModeCommand &DrawingModeCommand::operator =(const DrawingModeCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void DrawingModeCommand::Execute() {
	if (dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWOFF) {
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->mode = FlowChartTemplate::DRAWON;

		NShape *terminal = dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->GetAt(0);
		float x = terminal->GetX() - 5;
		float y = terminal->GetY() - 5;
		float size = 20.0F;
		QColor backgroundColor(0, 0, 0);
		QColor borderColor(255, 255, 255);

		NShape *one = new NumberBox(x, y, size, size, backgroundColor, Qt::SolidLine, borderColor, String("1"));
		y += 70.0F;
		NShape *two = new NumberBox(x, y, size, size, backgroundColor, Qt::SolidLine, borderColor, String("2"));
		y += 70.0F;
		NShape *three = new NumberBox(x, y, size, size, backgroundColor, Qt::SolidLine, borderColor, String("3"));
		y += 70.0F;
		NShape *four = new NumberBox(x, y, size, size, backgroundColor, Qt::SolidLine, borderColor, String("4"));
		y += 70.0F;
		NShape *five = new NumberBox(x, y, size, size, backgroundColor, Qt::SolidLine, borderColor, String("5"));
		y += 70.0F;
		NShape *six = new NumberBox(x, y, size, size, backgroundColor, Qt::SolidLine, borderColor, String("6"));
		y += 70.0F;
		NShape *seven = new NumberBox(x, y, size, size, backgroundColor, Qt::SolidLine, borderColor, String("7"));
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->Attach(one);
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->Attach(two);
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->Attach(three);
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->Attach(four);
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->Attach(five);
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->Attach(six);
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->Attach(seven);

		this->editor->drawingModeAction->setChecked(true);
	}
	else {
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->mode = FlowChartTemplate::DRAWOFF;
		Long i = dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->GetLength() - 1;
		while (i >= 7) { //numberBox만 없애기
			dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->Detach(i);
			i--;
		}

		this->editor->drawingModeAction->setChecked(false);
	}
}

//CopyCommand
CopyCommand::CopyCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

CopyCommand::CopyCommand(const CopyCommand &source)
	: FlowChartCommand(source) {

}

CopyCommand::~CopyCommand() {
}

CopyCommand &CopyCommand::operator =(const CopyCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void CopyCommand::Execute() {
	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->clipboard->Copy(dynamic_cast<DrawingPaper *>(this->editor->windows[0]));
}

//PasteCommand
PasteCommand::PasteCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

PasteCommand::PasteCommand(const PasteCommand &source)
	: FlowChartCommand(source) {

}

PasteCommand::~PasteCommand() {
}

PasteCommand &PasteCommand::operator =(const PasteCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void PasteCommand::Execute() {
	DrawingPaper *drawingPaper = static_cast<DrawingPaper *>(this->editor->windows[0]);
	drawingPaper->clipboard->Paste(drawingPaper);

	drawingPaper->Notify();
}

//CutCommand
CutCommand::CutCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

CutCommand::CutCommand(const CutCommand &source)
	: FlowChartCommand(source) {

}

CutCommand::~CutCommand() {
}

CutCommand &CutCommand::operator =(const CutCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void CutCommand::Execute() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	canvas->clipboard->Cut(canvas);

	canvas->Notify();
}

//DeleteCommand
DeleteCommand::DeleteCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

DeleteCommand::DeleteCommand(const DeleteCommand &source)
	: FlowChartCommand(source) {

}

DeleteCommand::~DeleteCommand() {
}

DeleteCommand &DeleteCommand::operator =(const DeleteCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void DeleteCommand::Execute() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);

	Long it;
	NShape *shape;

	Long count;
	Long(*indexes);
	canvas->flowChart->GetSelecteds(&indexes, &count);

	it = canvas->flowChart->GetLength() - 1;
	while (it >= 0) {
		shape = canvas->flowChart->GetAt(it);
		if (shape->IsSelected()) {
			canvas->flowChart->Detach(it);
		}
		it--;
	}
	if (canvas->flowChart->GetLength() < 1) {
		canvas->mode = DrawingPaper::IDLE;
	}

	if (indexes != 0) {
		delete[] indexes;
	}

	canvas->Notify();
}

//SelectAllCommand
SelectAllCommand::SelectAllCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SelectAllCommand::SelectAllCommand(const SelectAllCommand &source)
	: FlowChartCommand(source) {

}

SelectAllCommand::~SelectAllCommand() {
}

SelectAllCommand &SelectAllCommand::operator =(const SelectAllCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SelectAllCommand::Execute() {
	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->flowChart->SelectAll();
	if (dynamic_cast<DrawingPaper *>(this->editor->windows[0])->flowChart->GetLength() > 0) {
		dynamic_cast<DrawingPaper *>(this->editor->windows[0])->mode = DrawingPaper::SELECT;
	}
}

//StartCommand
StartCommand::StartCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

StartCommand::StartCommand(const StartCommand &source)
	: FlowChartCommand(source) {

}

StartCommand::~StartCommand() {
}

StartCommand &StartCommand::operator =(const StartCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void StartCommand::Execute() {
	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->shapeSelected =
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->GetAt(0);
}

//PreparationCommand
PreparationCommand::PreparationCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

PreparationCommand::PreparationCommand(const PreparationCommand &source)
	: FlowChartCommand(source) {

}

PreparationCommand::~PreparationCommand() {
}

PreparationCommand &PreparationCommand::operator =(const PreparationCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void PreparationCommand::Execute() {
	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->shapeSelected =
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->GetAt(1);
}

//InputCommand
InputCommand::InputCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

InputCommand::InputCommand(const InputCommand &source)
	: FlowChartCommand(source) {

}

InputCommand::~InputCommand() {
}

InputCommand &InputCommand::operator =(const InputCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void InputCommand::Execute() {
	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->shapeSelected =
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->GetAt(2);
}

//ProcessCommand
ProcessCommand::ProcessCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

ProcessCommand::ProcessCommand(const ProcessCommand &source)
	: FlowChartCommand(source) {

}

ProcessCommand::~ProcessCommand() {
}

ProcessCommand &ProcessCommand::operator =(const ProcessCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void ProcessCommand::Execute() {
	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->shapeSelected =
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->GetAt(3);
}

//DecisionCommand
DecisionCommand::DecisionCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

DecisionCommand::DecisionCommand(const DecisionCommand &source)
	: FlowChartCommand(source) {

}

DecisionCommand::~DecisionCommand() {
}

DecisionCommand &DecisionCommand::operator =(const DecisionCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void DecisionCommand::Execute() {
	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->shapeSelected =
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->GetAt(4);
}

//OutputCommand
OutputCommand::OutputCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

OutputCommand::OutputCommand(const OutputCommand &source)
	: FlowChartCommand(source) {

}

OutputCommand::~OutputCommand() {
}

OutputCommand &OutputCommand::operator =(const OutputCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void OutputCommand::Execute() {
	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->shapeSelected =
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->GetAt(5);
}

//StopCommand
StopCommand::StopCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

StopCommand::StopCommand(const StopCommand &source)
	: FlowChartCommand(source) {

}

StopCommand::~StopCommand() {
}

StopCommand &StopCommand::operator =(const StopCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void StopCommand::Execute() {
	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->shapeSelected =
		dynamic_cast<FlowChartTemplate *>(this->editor->windows[1])->flowChartTemplate->GetAt(6);
}

//PageSetCommand
PageSetCommand::PageSetCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

PageSetCommand::PageSetCommand(const PageSetCommand &source)
	: FlowChartCommand(source) {

}

PageSetCommand::~PageSetCommand() {
}

PageSetCommand &PageSetCommand::operator =(const PageSetCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void PageSetCommand::Execute() {
	//페이지 방향 설정 못하게 막는 방법 찾기

	QPageSetupDialog dlg((QWidget *)this->editor);
	QPrinter *printer = dlg.printer();
	printer->setFullPage(true); //must be before setmargin
	NShape *a4Paper = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->a4Paper;
	qreal left = dynamic_cast<A4Paper *>(a4Paper)->GetLeftMargin() * 210 / 1653;
	qreal top = dynamic_cast<A4Paper *>(a4Paper)->GetTopMargin() * 297 / 2338;
	qreal right = dynamic_cast<A4Paper *>(a4Paper)->GetRightMargin() * 210 / 1653;
	qreal bottom = dynamic_cast<A4Paper *>(a4Paper)->GetBottomMargin() * 297 / 2338;
	printer->setPageMargins(QMarginsF(left, top, right, bottom), QPageLayout::Millimeter);
	int dialogCode = dlg.exec();
	if (dialogCode == QDialog::Accepted) {
		printer->getPageMargins(&left, &top, &right, &bottom, QPrinter::Millimeter);
		if (left >= 6 && top >= 6 && right >= 6 && bottom >= 6) {
			float paperWidth = a4Paper->GetWidth();
			float paperHeight = a4Paper->GetHeight();

			float leftMargin = left / 100 * paperWidth / 210;
			float rightMargin = right / 100 * paperWidth / 210;
			float topMargin = top / 100 * paperHeight / 297;
			float bottomMargin = bottom / 100 * paperHeight / 297;

			dynamic_cast<A4Paper *>(a4Paper)->ChangeMargin(leftMargin, topMargin, rightMargin, bottomMargin);
		}
		else {
			//메시지 박스
			QMessageBox messageBox(QMessageBox::Warning, QString::fromLocal8Bit("경고"),
				QString::fromLocal8Bit("여백 지정 실패. 최소 여백은 6mm입니다."),
				QMessageBox::Ok, this->editor);
			messageBox.exec();
		}
	}

}

//PositionCommand
PositionCommand::PositionCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

PositionCommand::PositionCommand(const PositionCommand &source)
	: FlowChartCommand(source) {

}

PositionCommand::~PositionCommand() {
}

PositionCommand &PositionCommand::operator =(const PositionCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void PositionCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->tool->MoveMake(dynamic_cast<DrawingPaper *>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->repaint();
}

//SizeCommand
SizeCommand::SizeCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SizeCommand::SizeCommand(const SizeCommand &source)
	: FlowChartCommand(source) {

}

SizeCommand::~SizeCommand() {
}

SizeCommand &SizeCommand::operator =(const SizeCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SizeCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->tool->SizeMake(dynamic_cast<DrawingPaper *>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->repaint();
}

//IntervalCommand
IntervalCommand::IntervalCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

IntervalCommand::IntervalCommand(const IntervalCommand &source)
	: FlowChartCommand(source) {

}

IntervalCommand::~IntervalCommand() {
}

IntervalCommand &IntervalCommand::operator =(const IntervalCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void IntervalCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->tool->IntervalMake(dynamic_cast<DrawingPaper *>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->repaint();
}

//SequenceCommand
SequenceCommand::SequenceCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SequenceCommand::SequenceCommand(const SequenceCommand &source)
	: FlowChartCommand(source) {

}

SequenceCommand::~SequenceCommand() {
}

SequenceCommand &SequenceCommand::operator =(const SequenceCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SequenceCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->tool->SequenceMake(dynamic_cast<DrawingPaper *>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->repaint();
}

//IterationCommand
IterationCommand::IterationCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

IterationCommand::IterationCommand(const IterationCommand &source)
	: FlowChartCommand(source) {

}

IterationCommand::~IterationCommand() {
}

IterationCommand &IterationCommand::operator =(const IterationCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void IterationCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->tool->IterationMake(dynamic_cast<DrawingPaper *>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->repaint();
}

//SelectionCommand
SelectionCommand::SelectionCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SelectionCommand::SelectionCommand(const SelectionCommand &source)
	: FlowChartCommand(source) {

}

SelectionCommand::~SelectionCommand() {
}

SelectionCommand &SelectionCommand::operator =(const SelectionCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SelectionCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->tool->SelectionMake(dynamic_cast<DrawingPaper *>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper *>(this->editor->windows[0])->repaint();
}

//CloseCommand
CloseCommand::CloseCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

CloseCommand::CloseCommand(const CloseCommand &source)
	: FlowChartCommand(source) {

}

CloseCommand::~CloseCommand() {
}

CloseCommand &CloseCommand::operator =(const CloseCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void CloseCommand::Execute() {
	this->editor->close();
}

//RuleKeepCommand
RuleKeepCommand::RuleKeepCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

RuleKeepCommand::RuleKeepCommand(const RuleKeepCommand &source)
	: FlowChartCommand(source) {

}

RuleKeepCommand::~RuleKeepCommand() {
}

RuleKeepCommand &RuleKeepCommand::operator =(const RuleKeepCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void RuleKeepCommand::Execute() {
	DrawingPaper *canvas = static_cast<DrawingPaper *>(this->editor->windows[0]);
	if (canvas->variableList != NULL) {
		if (canvas->flowChart->GetLength() > 0) {
			QString message = QString::fromLocal8Bit("    규칙 검사를 사용 해제할 수 없습니다. 빈 파일이어야 합니다.");
			this->editor->messageStatus->setText(message);
			this->editor->statusBar->repaint();
			this->editor->ruleKeepAction->setChecked(true);
		}
		else {
			if (canvas->variableList != NULL) {
				delete canvas->variableList;
				canvas->variableList = NULL;
			}
			QString message = QString::fromLocal8Bit("    규칙 검사 사용 해제");
			this->editor->messageStatus->setText(message);
			this->editor->statusBar->repaint();
		}
	}
	else {
		if (canvas->flowChart->GetLength() > 0) {
			QString message = QString::fromLocal8Bit("    규칙 검사를 사용할 수 없습니다. 빈 파일이어야 합니다.");
			this->editor->messageStatus->setText(message);
			this->editor->statusBar->repaint();
			this->editor->ruleKeepAction->setChecked(false);
		}
		else {
			canvas->variableList = new VariableList;
			QString message = QString::fromLocal8Bit("    규칙 검사 사용 설정");
			this->editor->messageStatus->setText(message);
			this->editor->statusBar->repaint();
		}
	}
}

//HelpCommand
HelpCommand::HelpCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

HelpCommand::HelpCommand(const HelpCommand &source)
	: FlowChartCommand(source) {

}

HelpCommand::~HelpCommand() {
}

HelpCommand &HelpCommand::operator =(const HelpCommand &source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void HelpCommand::Execute() {
	QString helpFile("dafycasehelpdoc.chm::/dafycasehelpdoc.htm");
	HWND hWnd = ::HtmlHelp(GetDesktopWindow(),
		helpFile.toStdWString().c_str(),
		HH_DISPLAY_TOPIC, NULL);
	DWORD e = ::GetLastError();
	Long i = 0;
}