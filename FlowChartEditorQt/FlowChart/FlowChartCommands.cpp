#include "FlowChartCommands.h"
#include "FlowChartEditor.h"
#include "DrawingPaper.h"
#include <afxdlgs.h>
#include "Memory.h"
#include "MemoryController.h"
#include "FlowChartFont.h"
#include "PreviewForm.h"
#include "A4Paper.h"
#include "FlowChart.h"
#include "Painter.h"
#include "DrawVisitor.h"
#include <atlimage.h>
#include "FlowChartTemplate.h"
#include "NumberBox.h"
#include "Template.h"
#include "resource.h"
#include "Clipboard.h"
#include "Zoom.h"
#include "Tool.h"
#include "TutorialForm.h"
#include <fstream>
#include "StatusBar.h"
#include "TutorialIntroForm.h"

using namespace std;
//FlowChartCommand
FlowChartCommand::FlowChartCommand(FlowChartEditor *editor) {
	this->editor = editor;
}

FlowChartCommand::FlowChartCommand(const FlowChartCommand& source) {
	this->editor = source.editor;
}

FlowChartCommand::~FlowChartCommand() {
}

FlowChartCommand& FlowChartCommand::operator =(const FlowChartCommand& source) {
	this->editor = source.editor;

	return *this;
}

//SaveCommand
SaveCommand::SaveCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SaveCommand::SaveCommand(const SaveCommand& source)
	: FlowChartCommand(source) {

}

SaveCommand::~SaveCommand() {
}

SaveCommand& SaveCommand::operator =(const SaveCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SaveCommand::Execute() {
	if (this->editor->fileOpenPath.IsEmpty()) {
		CString fileName;
		CString fileName_;

		this->editor->GetWindowText(fileName);
		sscanf(fileName, "%s - FlowChart", fileName_);

		static char BASED_CODE szFilter[] = "txt Files (*.txt)|*.txt||";
		CFileDialog dlg(FALSE, "*.txt", fileName_, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

		if (dlg.DoModal() == IDOK) {
			(static_cast<DrawingPaper*>(this->editor->windows[0]))->Save(dlg.GetPathName());

			fileName_ = dlg.GetFileTitle() + " - FlowChart";
			this->editor->SetWindowText(fileName_);
		}
	}
	else {
		(static_cast<DrawingPaper*>(this->editor->windows[0]))->Save(this->editor->fileOpenPath);
	}
}

//SaveAsCommand
SaveAsCommand::SaveAsCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SaveAsCommand::SaveAsCommand(const SaveAsCommand& source)
	: FlowChartCommand(source) {

}

SaveAsCommand::~SaveAsCommand() {
}

SaveAsCommand& SaveAsCommand::operator =(const SaveAsCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SaveAsCommand::Execute() {
	CString fileName;
	CString fileName_;

	this->editor->GetWindowText(fileName);
	sscanf(fileName, "%s - FlowChart", fileName_);

	static char BASED_CODE szFilter[] = "txt Files (*.txt)|*.txt||";
	CFileDialog dlg(FALSE, "*.txt", fileName_, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	if (dlg.DoModal() == IDOK) {
		(static_cast<DrawingPaper *>(this->editor->windows[0]))->Save(dlg.GetPathName());

		fileName_ = dlg.GetFileTitle() + " - FlowChart";
		this->editor->SetWindowText(fileName_);
	}
}

//OpenCommand
OpenCommand::OpenCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

OpenCommand::OpenCommand(const OpenCommand& source)
	: FlowChartCommand(source) {

}

OpenCommand::~OpenCommand() {
}

OpenCommand& OpenCommand::operator =(const OpenCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void OpenCommand::Execute() {
	CString fileName;

	static char BASED_CODE szFilter[] = "txt Files (*.txt)|*.txt||";
	CFileDialog dlg(TRUE, "*.txt", "*.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	if (dlg.DoModal() == IDOK) {
		this->editor->fileOpenPath = dlg.GetPathName();
		(static_cast<DrawingPaper *>(this->editor->windows[0]))->Load(this->editor->fileOpenPath);
		fileName = this->editor->fileOpenPath + " - FlowChart";
		this->editor->SetWindowText(fileName);
		(static_cast<DrawingPaper *>(this->editor->windows[0]))->SetFocus();
		this->editor->RedrawWindow();
	}
}

//NewCommand
NewCommand::NewCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

NewCommand::NewCommand(const NewCommand& source)
	: FlowChartCommand(source) {

}

NewCommand::~NewCommand() {
}

NewCommand& NewCommand::operator =(const NewCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void NewCommand::Execute() {
	(static_cast<DrawingPaper *>(this->editor->windows[0]))->New();
	(static_cast<DrawingPaper *>(this->editor->windows[0]))->SetFocus();
	this->editor->RedrawWindow();
}

//UndoCommand
UndoCommand::UndoCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

UndoCommand::UndoCommand(const UndoCommand& source)
	: FlowChartCommand(source) {

}

UndoCommand::~UndoCommand() {
}

UndoCommand& UndoCommand::operator =(const UndoCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void UndoCommand::Execute() {
	if (static_cast<DrawingPaper*>(this->editor->windows[0])->memoryController->GetUndoMemory()->GetLength() > 0) {
		static_cast<DrawingPaper*>(this->editor->windows[0])->memoryController->RememberUndo();
		static_cast<DrawingPaper*>(this->editor->windows[0])->memoryController->Undo();
		this->editor->windows[0]->RedrawWindow();
	}
}

//RedoCommand
RedoCommand::RedoCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

RedoCommand::RedoCommand(const RedoCommand& source)
	: FlowChartCommand(source) {

}

RedoCommand::~RedoCommand() {
}

RedoCommand& RedoCommand::operator =(const RedoCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void RedoCommand::Execute() {
	if (static_cast<DrawingPaper*>(this->editor->windows[0])->memoryController->GetRedoMemory()->GetLength() > 0) {
		static_cast<DrawingPaper*>(this->editor->windows[0])->memoryController->RememberRedo();
		static_cast<DrawingPaper*>(this->editor->windows[0])->memoryController->Redo();
		this->editor->windows[0]->RedrawWindow();
	}
}

//FontSetCommand
FontSetCommand::FontSetCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

FontSetCommand::FontSetCommand(const FontSetCommand& source)
	: FlowChartCommand(source) {

}

FontSetCommand::~FontSetCommand() {
}

FontSetCommand& FontSetCommand::operator =(const FontSetCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void FontSetCommand::Execute() {
	LOGFONT logFont = this->editor->font->GetFont();
	COLORREF color;
	CFontDialog fontDialog(&logFont);
	int ret = fontDialog.DoModal();
	if (ret == IDOK) {
		//폰트 대화 상자에서 폰트 정보를 가져온다.
		fontDialog.GetCurrentFont(&logFont);
		color = fontDialog.GetColor();
		if (this->editor->font != NULL) {
			delete this->editor->font;
		}
		this->editor->font = new FlowChartFont(this->editor, logFont, color);

		this->editor->windows[0]->Invalidate();
	}
}

//PreviewCommand
PreviewCommand::PreviewCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

PreviewCommand::PreviewCommand(const PreviewCommand& source)
	: FlowChartCommand(source) {

}

PreviewCommand::~PreviewCommand() {
}

PreviewCommand& PreviewCommand::operator =(const PreviewCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void PreviewCommand::Execute() {
	Shape *flowChart = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->flowChart->Clone();
	PreviewForm *previewForm = new PreviewForm(this->editor, flowChart);
	previewForm->Create(NULL, "인쇄 미리 보기", 13565952UL, CRect(0, 0, 1200, 875));
	previewForm->ShowWindow(SW_NORMAL);
	previewForm->UpdateWindow();
}

//SaveAsImageCommand
SaveAsImageCommand::SaveAsImageCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SaveAsImageCommand::SaveAsImageCommand(const SaveAsImageCommand& source)
	: FlowChartCommand(source) {

}

SaveAsImageCommand::~SaveAsImageCommand() {
}

SaveAsImageCommand& SaveAsImageCommand::operator =(const SaveAsImageCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SaveAsImageCommand::Execute() {
	CString fileName;
	CString fileName_;

	this->editor->GetWindowText(fileName);
	sscanf(fileName, "%s - FlowChart", fileName_);

	static char BASED_CODE szFilter[] = "jpeg Files (*.jpg)|*.jpg||";
	CFileDialog dlg(FALSE, "*.jpg", fileName_, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	if (dlg.DoModal() == IDOK && dlg.GetPathName().GetLength() > 0) {
		FlowChart flowChart_(*(static_cast<FlowChart *>
			(dynamic_cast<DrawingPaper*>(this->editor->windows[0])->flowChart)));
		Shape *paper = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->a4Paper->Clone();

		flowChart_.UnSelectAll();

		Painter painter(dynamic_cast<DrawingPaper*>(this->editor->windows[0])->GetDC(), paper->GetWidth(), paper->GetHeight(), RGB(255, 255, 255), TRANSPARENT);
		DrawVisitor drawVisitor(&painter);

		HFONT hFont = this->editor->font->Create();
		painter.ChangeFont(hFont, this->editor->font->GetColor());

		Long x, y;
		for (Long i = 0; i < flowChart_.GetLength(); i++) {
			x = flowChart_.GetAt(i)->GetX();
			y = flowChart_.GetAt(i)->GetY();
			flowChart_.GetAt(i)->Move(x - paper->GetX(), y - paper->GetY());
		}

		flowChart_.Accept(&drawVisitor);

		CImage TempImageObj;
		TempImageObj.Attach(painter.GetCurrentBitmap());
		TempImageObj.Save(dlg.GetPathName());
		TempImageObj.Destroy();

		fileName_ = dlg.GetFileTitle() + " - FlowChart";
		this->editor->SetWindowText(fileName_);
	}
}

//DrawingModeCommand
DrawingModeCommand::DrawingModeCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

DrawingModeCommand::DrawingModeCommand(const DrawingModeCommand& source)
	: FlowChartCommand(source) {

}

DrawingModeCommand::~DrawingModeCommand() {
}

DrawingModeCommand& DrawingModeCommand::operator =(const DrawingModeCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void DrawingModeCommand::Execute() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWOFF) {
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode = FlowChartTemplate::DRAWON;

		Shape *one = new NumberBox(15, 85, 15, 15, RGB(230, 230, 230), DOT, 10, String("1"));
		Shape *two = new NumberBox(15, 155, 15, 15, RGB(230, 230, 230), DOT, 10, String("2"));
		Shape *three = new NumberBox(15, 225, 15, 15, RGB(230, 230, 230), DOT, 10, String("3"));
		Shape *four = new NumberBox(15, 295, 15, 15, RGB(230, 230, 230), DOT, 10, String("4"));
		Shape *five = new NumberBox(15, 365, 15, 15, RGB(230, 230, 230), DOT, 10, String("5"));
		Shape *six = new NumberBox(15, 435, 15, 15, RGB(230, 230, 230), DOT, 10, String("6"));
		Shape *seven = new NumberBox(15, 505, 15, 15, RGB(230, 230, 230), DOT, 10, String("7"));
		dynamic_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->Register(one);
		dynamic_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->Register(two);
		dynamic_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->Register(three);
		dynamic_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->Register(four);
		dynamic_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->Register(five);
		dynamic_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->Register(six);
		dynamic_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->Register(seven);

		this->editor->isUnModeMenuEnabled = TRUE; //모드가 설정되었으므로 모드 해제 메뉴를 활성화하고 모드 설정 모드를 비활성화한다.
	}
}

//DrawingUnModeCommand
DrawingUnModeCommand::DrawingUnModeCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

DrawingUnModeCommand::DrawingUnModeCommand(const DrawingUnModeCommand& source)
	: FlowChartCommand(source) {

}

DrawingUnModeCommand::~DrawingUnModeCommand() {
}

DrawingUnModeCommand& DrawingUnModeCommand::operator =(const DrawingUnModeCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void DrawingUnModeCommand::Execute() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode = FlowChartTemplate::DRAWOFF;
		Long i = dynamic_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetLength() - 1;
		while (i >= 7) { //numberBox만 없애기
			dynamic_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->UnRegister(i);
			i--;
		}
		this->editor->isUnModeMenuEnabled = FALSE; //모드가 해제되었으므로 모드 해제 메뉴를 비활성화하고 모드 설정 메뉴를 활성화한다.
	}
}

//CopyCommand
CopyCommand::CopyCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

CopyCommand::CopyCommand(const CopyCommand& source)
	: FlowChartCommand(source) {

}

CopyCommand::~CopyCommand() {
}

CopyCommand& CopyCommand::operator =(const CopyCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void CopyCommand::Execute() {
	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->clipboard->Copy(dynamic_cast<DrawingPaper*>(this->editor->windows[0]));
}

//PasteCommand
PasteCommand::PasteCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

PasteCommand::PasteCommand(const PasteCommand& source)
	: FlowChartCommand(source) {

}

PasteCommand::~PasteCommand() {
}

PasteCommand& PasteCommand::operator =(const PasteCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void PasteCommand::Execute() {
	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->clipboard->Paste(dynamic_cast<DrawingPaper*>(this->editor->windows[0]));
}

//CutCommand
CutCommand::CutCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

CutCommand::CutCommand(const CutCommand& source)
	: FlowChartCommand(source) {

}

CutCommand::~CutCommand() {
}

CutCommand& CutCommand::operator =(const CutCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void CutCommand::Execute() {
	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->clipboard->Cut(dynamic_cast<DrawingPaper*>(this->editor->windows[0]));
}

//DeleteCommand
DeleteCommand::DeleteCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

DeleteCommand::DeleteCommand(const DeleteCommand& source)
	: FlowChartCommand(source) {

}

DeleteCommand::~DeleteCommand() {
}

DeleteCommand& DeleteCommand::operator =(const DeleteCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void DeleteCommand::Execute() {
	Long it;
	Shape *shape;

	Long count;
	Long(*indexes);
	dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->editor->windows[0])->flowChart)->GetSelecteds(&indexes, &count);
	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->memoryController->RememberRemove(indexes, count);

	it = dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->editor->windows[0])->flowChart)->GetLength() - 1;
	while (it >= 0) {
		shape = dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->editor->windows[0])->flowChart)->GetAt(it);
		if (shape->IsSelected()) {
			dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->editor->windows[0])->flowChart)->Erase(it);
		}
		it--;
	}
	if (dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->editor->windows[0])->flowChart)->GetLength() < 1) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::IDLE;
	}

	if (indexes != 0) {
		delete[] indexes;
	}
}

//SelectAllCommand
SelectAllCommand::SelectAllCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SelectAllCommand::SelectAllCommand(const SelectAllCommand& source)
	: FlowChartCommand(source) {

}

SelectAllCommand::~SelectAllCommand() {
}

SelectAllCommand& SelectAllCommand::operator =(const SelectAllCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SelectAllCommand::Execute() {
	(dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->editor->windows[0])->flowChart))->SelectAll();
	if (dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->editor->windows[0])->flowChart)->GetLength() > 0) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::SELECT;
	}
}

//StartCommand
StartCommand::StartCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

StartCommand::StartCommand(const StartCommand& source)
	: FlowChartCommand(source) {

}

StartCommand::~StartCommand() {
}

StartCommand& StartCommand::operator =(const StartCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void StartCommand::Execute() {
	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
		static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(0);
}

//PreparationCommand
PreparationCommand::PreparationCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

PreparationCommand::PreparationCommand(const PreparationCommand& source)
	: FlowChartCommand(source) {

}

PreparationCommand::~PreparationCommand() {
}

PreparationCommand& PreparationCommand::operator =(const PreparationCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void PreparationCommand::Execute() {
	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
		static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(1);
}

//InputCommand
InputCommand::InputCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

InputCommand::InputCommand(const InputCommand& source)
	: FlowChartCommand(source) {

}

InputCommand::~InputCommand() {
}

InputCommand& InputCommand::operator =(const InputCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void InputCommand::Execute() {
	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
		static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(2);
}

//ProcessCommand
ProcessCommand::ProcessCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

ProcessCommand::ProcessCommand(const ProcessCommand& source)
	: FlowChartCommand(source) {

}

ProcessCommand::~ProcessCommand() {
}

ProcessCommand& ProcessCommand::operator =(const ProcessCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void ProcessCommand::Execute() {
	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
		static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(3);
}

//DecisionCommand
DecisionCommand::DecisionCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

DecisionCommand::DecisionCommand(const DecisionCommand& source)
	: FlowChartCommand(source) {

}

DecisionCommand::~DecisionCommand() {
}

DecisionCommand& DecisionCommand::operator =(const DecisionCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void DecisionCommand::Execute() {
	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
		static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(4);
}

//OutputCommand
OutputCommand::OutputCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

OutputCommand::OutputCommand(const OutputCommand& source)
	: FlowChartCommand(source) {

}

OutputCommand::~OutputCommand() {
}

OutputCommand& OutputCommand::operator =(const OutputCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void OutputCommand::Execute() {
	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
		static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(5);
}

//StopCommand
StopCommand::StopCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

StopCommand::StopCommand(const StopCommand& source)
	: FlowChartCommand(source) {

}

StopCommand::~StopCommand() {
}

StopCommand& StopCommand::operator =(const StopCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void StopCommand::Execute() {
	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
	dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
		static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(6);
}

//PageSetCommand
PageSetCommand::PageSetCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

PageSetCommand::PageSetCommand(const PageSetCommand& source)
	: FlowChartCommand(source) {

}

PageSetCommand::~PageSetCommand() {
}

PageSetCommand& PageSetCommand::operator =(const PageSetCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void PageSetCommand::Execute() {
	CPageSetupDialog dlg(PSD_MARGINS | PSD_INHUNDREDTHSOFMILLIMETERS | PSD_DISABLEPAPER, this->editor);
	Shape *a4Paper = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->a4Paper;
	dlg.m_psd.rtMargin.left = dynamic_cast<A4Paper*>(a4Paper)->GetLeftMargin() * 210 / 1653 * 100;
	dlg.m_psd.rtMargin.top = dynamic_cast<A4Paper*>(a4Paper)->GetTopMargin() * 297 / 2338 * 100;
	dlg.m_psd.rtMargin.right = dynamic_cast<A4Paper*>(a4Paper)->GetRightMargin() * 210 / 1653 * 100;
	dlg.m_psd.rtMargin.bottom = dynamic_cast<A4Paper*>(a4Paper)->GetBottomMargin() * 297 / 2338 * 100;
	int message = dlg.DoModal();
	if (message == IDOK) {
		CRect marginRect;
		dlg.GetMargins(marginRect, NULL);

		Long paperWidth = a4Paper->GetWidth();
		Long paperHeight = a4Paper->GetHeight();

		Long leftMargin = marginRect.left / 100 * paperWidth / 210;
		Long rightMargin = marginRect.right / 100 * paperWidth / 210;
		Long topMargin = marginRect.top / 100 * paperHeight / 297;
		Long bottomMargin = marginRect.bottom / 100 * paperHeight / 297;

		dynamic_cast<A4Paper*>(a4Paper)->ChangeMargin(leftMargin, topMargin, rightMargin, bottomMargin);
	}
}

//PositionCommand
PositionCommand::PositionCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

PositionCommand::PositionCommand(const PositionCommand& source)
	: FlowChartCommand(source) {

}

PositionCommand::~PositionCommand() {
}

PositionCommand& PositionCommand::operator =(const PositionCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void PositionCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->tool->MoveMake(dynamic_cast<DrawingPaper*>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->RedrawWindow();
}

//SizeCommand
SizeCommand::SizeCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SizeCommand::SizeCommand(const SizeCommand& source)
	: FlowChartCommand(source) {

}

SizeCommand::~SizeCommand() {
}

SizeCommand& SizeCommand::operator =(const SizeCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SizeCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->tool->SizeMake(dynamic_cast<DrawingPaper*>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->RedrawWindow();
}

//IntervalCommand
IntervalCommand::IntervalCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

IntervalCommand::IntervalCommand(const IntervalCommand& source)
	: FlowChartCommand(source) {

}

IntervalCommand::~IntervalCommand() {
}

IntervalCommand& IntervalCommand::operator =(const IntervalCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void IntervalCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->tool->IntervalMake(dynamic_cast<DrawingPaper*>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->RedrawWindow();
}

//SequenceCommand
SequenceCommand::SequenceCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SequenceCommand::SequenceCommand(const SequenceCommand& source)
	: FlowChartCommand(source) {

}

SequenceCommand::~SequenceCommand() {
}

SequenceCommand& SequenceCommand::operator =(const SequenceCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SequenceCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->tool->SequenceMake(dynamic_cast<DrawingPaper*>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->RedrawWindow();
}

//IterationCommand
IterationCommand::IterationCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

IterationCommand::IterationCommand(const IterationCommand& source)
	: FlowChartCommand(source) {

}

IterationCommand::~IterationCommand() {
}

IterationCommand& IterationCommand::operator =(const IterationCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void IterationCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->tool->IterationMake(dynamic_cast<DrawingPaper*>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->RedrawWindow();
}

//SelectionCommand
SelectionCommand::SelectionCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

SelectionCommand::SelectionCommand(const SelectionCommand& source)
	: FlowChartCommand(source) {

}

SelectionCommand::~SelectionCommand() {
}

SelectionCommand& SelectionCommand::operator =(const SelectionCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void SelectionCommand::Execute() {
	float rate = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->GetRate();

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->tool->SelectionMake(dynamic_cast<DrawingPaper*>(this->editor->windows[0]));

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->Set(rate);

	dynamic_cast<DrawingPaper*>(this->editor->windows[0])->RedrawWindow();
}

//TutorialCommand
TutorialCommand::TutorialCommand(FlowChartEditor *editor)
	: FlowChartCommand(editor) {

}

TutorialCommand::TutorialCommand(const TutorialCommand& source)
	: FlowChartCommand(source) {

}

TutorialCommand::~TutorialCommand() {
}

TutorialCommand& TutorialCommand::operator =(const TutorialCommand& source) {
	FlowChartCommand::operator=(source);

	return *this;
}

void TutorialCommand::Execute() {
	this->editor->ShowWindow(SW_SHOWMAXIMIZED);

	CRect rect;
	this->editor->GetWindowRect(&rect);

	TutorialIntroForm *intro = new TutorialIntroForm;
	intro->Create(NULL, NULL, WS_POPUP | WS_VISIBLE | WS_CHILD,
		CRect(rect.left, rect.top, rect.Width(), rect.Height()), this->editor, NULL, WS_EX_LAYERED | WS_EX_CLIENTEDGE, NULL);
}