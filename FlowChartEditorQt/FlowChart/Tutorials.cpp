#include "Tutorials.h"
#include "FlowChartEditor.h"
#include "ToolTip.h"
#include "String.h"
#include "FlowChartTemplate.h"
#include "Template.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "ScrollController.h"
#include "Scrolls.h"

//Tutorial
Tutorial::Tutorial(FlowChartEditor *editor) {
	this->editor = editor;
}

Tutorial::Tutorial(const Tutorial& source) {
	this->editor = source.editor;
}

Tutorial::~Tutorial() {

}

Tutorial& Tutorial::operator=(const Tutorial& source) {
	this->editor = source.editor;

	return *this;
}

Long Tutorial::Add(Tutorial *tutorial) {
	return -1;
}

Tutorial* Tutorial::TakeOut() {
	return 0;
}

Tutorial* Tutorial::Top() {
	return 0;
}

Long Tutorial::GetCapacity() const {
	return 0;
}
Long Tutorial::GetLength() const {
	return 0;
}
Long Tutorial::GetTop() const {
	return -1;
}

//MacroTutorial
MacroTutorial::MacroTutorial(Long capacity)
	: tutorials(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->top = -1;
}

MacroTutorial::MacroTutorial(const MacroTutorial& source)
	: tutorials(source.tutorials) {
	Stack<Tutorial*> temp(source.capacity);
	Tutorial *tutorial;
	Long i = 0;
	while (i < source.length) {
		tutorial = this->tutorials.Pop();
		temp.Push(tutorial);
		i++;
	}

	i = 0;
	while (i < temp.GetLength()) {
		tutorial = temp.Pop();
		this->tutorials.Push(tutorial->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->top = source.top;
}

MacroTutorial::~MacroTutorial() {
	Tutorial *tutorial;
	Long i = 0;
	while (i < this->length) {
		tutorial = this->tutorials.Pop();
		if (tutorial != 0) {
			delete tutorial;
		}
		i++;
	}
}

MacroTutorial& MacroTutorial::operator=(const MacroTutorial& source) {
	Tutorial *tutorial;
	Long i = 0;
	while (i < this->length) {
		tutorial = this->tutorials.Pop();
		if (tutorial != 0) {
			delete tutorial;
		}
		i++;
	}

	this->tutorials = source.tutorials;

	Stack<Tutorial*> temp(source.capacity);
	i = 0;
	while (i < source.length) {
		tutorial = this->tutorials.Pop();
		temp.Push(tutorial);
		i++;
	}

	i = 0;
	while (i < temp.GetLength()) {
		tutorial = temp.Pop();
		this->tutorials.Push(tutorial->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->top = source.top;

	return *this;
}

Long MacroTutorial::Add(Tutorial *tutorial) {
	this->top = this->tutorials.Push(tutorial);
	this->length++;

	return this->top;
}

Tutorial* MacroTutorial::TakeOut() {
	Tutorial *tutorial = this->tutorials.Pop();
	this->top--;
	this->length--;

	return tutorial;
}

Tutorial* MacroTutorial::Top() {
	return this->tutorials.Top();
}

//================================Main=======================================
//MainTutorial
MainTutorial::MainTutorial(Long capacity)
	: MacroTutorial(capacity) {

}

MainTutorial::MainTutorial(const MainTutorial& source)
	: MacroTutorial(source) {

}

MainTutorial::~MainTutorial() {

}

MainTutorial& MainTutorial::operator=(const MainTutorial& source) {
	MacroTutorial::operator=(source);

	return *this;
}

void MainTutorial::Execute() {
	Tutorial *current = this->tutorials.Top();
	current->Execute();
}

Tutorial* MainTutorial::Clone() {
	return new MainTutorial(*this);
}

//SeveralTutorial
SeveralTutorial::SeveralTutorial(Long capacity)
	: MacroTutorial(capacity) {

}

SeveralTutorial::SeveralTutorial(const SeveralTutorial& source)
	: MacroTutorial(source) {

}

SeveralTutorial::~SeveralTutorial() {

}

SeveralTutorial& SeveralTutorial::operator=(const SeveralTutorial& source) {
	MacroTutorial::operator=(source);

	return *this;
}

void SeveralTutorial::Execute() {
	Tutorial *tutorial = this->tutorials.Top();
	tutorial->Execute();
	//if (tutorial != 0) {
	//	delete tutorial;
	//}
}

Tutorial* SeveralTutorial::Clone() {
	return new SeveralTutorial(*this);
}
//===========================================================================

//================================Detail=====================================
//SymbolSelectTutorial
SymbolSelectTutorial::SymbolSelectTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

SymbolSelectTutorial::SymbolSelectTutorial(const SymbolSelectTutorial& source)
	: Tutorial(source) {

}

SymbolSelectTutorial::~SymbolSelectTutorial() {

}

SymbolSelectTutorial& SymbolSelectTutorial::operator=(const SymbolSelectTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void SymbolSelectTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  마우스 클릭으로 기호를 선택하세요.  \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));
	Shape *firstSymbol = dynamic_cast<Template*>(dynamic_cast<FlowChartTemplate*>(editor->windows[1])->flowChartTemplate)->GetAt(0);
	Long left = firstSymbol->GetX() + firstSymbol->GetWidth() + 10;
	Long top = firstSymbol->GetY() - firstSymbol->GetHeight() - 30;
	Long right = left + 360;
	Long bottom = top + 63;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* SymbolSelectTutorial::Clone() {
	return new SymbolSelectTutorial(*this);
}

//DrawTutorial
DrawTutorial::DrawTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

DrawTutorial::DrawTutorial(const DrawTutorial& source)
	: Tutorial(source) {

}

DrawTutorial::~DrawTutorial() {

}

DrawTutorial& DrawTutorial::operator=(const DrawTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void DrawTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  마우스 클릭으로 그리세요. \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));

	Long left = 400;
	Long top = 50;
	Long right = left + 270;
	Long bottom = top + 63;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* DrawTutorial::Clone() {
	return new DrawTutorial(*this);
}

//EditContentsTutorial
EditContentsTutorial::EditContentsTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

EditContentsTutorial::EditContentsTutorial(const EditContentsTutorial& source)
	: Tutorial(source) {

}

EditContentsTutorial::~EditContentsTutorial() {

}

EditContentsTutorial& EditContentsTutorial::operator=(const EditContentsTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void EditContentsTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  기호를 더블 클릭하여  \r\n  내용을 편집하세요.  \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));
	FlowChart *flowChart = (FlowChart*)dynamic_cast<DrawingPaper*>(editor->windows[0])->flowChart;
	Shape *currentShape = flowChart->GetAt(flowChart->GetLength() - 1);
	Long positionX;
	Long positionY;
	if (dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController != NULL) {
		positionX = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(1)->GetPosition();
		positionY = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(0)->GetPosition();
	}
	Long right = currentShape->GetX() - positionX / 2 - 10;
	Long top = currentShape->GetY() - currentShape->GetHeight() - positionY;
	Long left = right - 230;
	Long bottom = top + 84;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* EditContentsTutorial::Clone() {
	return new EditContentsTutorial(*this);
}

//MoveTutorial
MoveTutorial::MoveTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

MoveTutorial::MoveTutorial(const MoveTutorial& source)
	: Tutorial(source) {

}

MoveTutorial::~MoveTutorial() {

}

MoveTutorial& MoveTutorial::operator=(const MoveTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void MoveTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  기호를 움직여 위치를 조정하세요.  \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));
	FlowChart *flowChart = (FlowChart*)dynamic_cast<DrawingPaper*>(editor->windows[0])->flowChart;
	Shape *currentShape = flowChart->GetAt(flowChart->GetLength() - 1);
	Long positionX;
	Long positionY;
	if (dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController != NULL) {
		positionX = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(1)->GetPosition();
		positionY = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(0)->GetPosition();
	}
	Long right = currentShape->GetX() - positionX / 2 - 10;
	Long top = currentShape->GetY() - positionY - 50;
	Long left = right - 340;
	Long bottom = top + 63;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* MoveTutorial::Clone() {
	return new MoveTutorial(*this);
}

//ReSizeTutorial
ReSizeTutorial::ReSizeTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

ReSizeTutorial::ReSizeTutorial(const ReSizeTutorial& source)
	: Tutorial(source) {

}

ReSizeTutorial::~ReSizeTutorial() {

}

ReSizeTutorial& ReSizeTutorial::operator=(const ReSizeTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void ReSizeTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  크기를 조정하세요.  \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));
	FlowChart *flowChart = (FlowChart*)dynamic_cast<DrawingPaper*>(editor->windows[0])->flowChart;
	Shape *currentShape = flowChart->GetAt(flowChart->GetLength() - 1);
	Long positionX;
	Long positionY;
	if (dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController != NULL) {
		positionX = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(1)->GetPosition();
		positionY = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(0)->GetPosition();
	}
	Long right = currentShape->GetX() - positionX / 2 - 10;
	Long top = currentShape->GetY() - positionY - 50;
	Long left = right - 200;
	Long bottom = top + 63;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* ReSizeTutorial::Clone() {
	return new ReSizeTutorial(*this);
}

//GroupTutorial
GroupTutorial::GroupTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

GroupTutorial::GroupTutorial(const GroupTutorial& source)
	: Tutorial(source) {

}

GroupTutorial::~GroupTutorial() {

}

GroupTutorial& GroupTutorial::operator=(const GroupTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void GroupTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  드래그해서 여러 기호를 선택하세요.  \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));
	
	Long left = 400;
	Long top = 50;
	Long right = left + 360;
	Long bottom = top + 63;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* GroupTutorial::Clone() {
	return new GroupTutorial(*this);
}

//ContextMenuTutorial
ContextMenuTutorial::ContextMenuTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

ContextMenuTutorial::ContextMenuTutorial(const ContextMenuTutorial& source)
	: Tutorial(source) {

}

ContextMenuTutorial::~ContextMenuTutorial() {

}

ContextMenuTutorial& ContextMenuTutorial::operator=(const ContextMenuTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void ContextMenuTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  마우스 오른쪽 클릭으로  \r\n  메뉴를 확인하세요.  \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));
	
	FlowChart *flowChart = (FlowChart*)dynamic_cast<DrawingPaper*>(editor->windows[0])->flowChart;
	Long count;
	Long(*indexes);
	flowChart->GetSelecteds(&indexes, &count);

	Shape *currentShape = flowChart->GetAt(indexes[count-1]);
	Long positionX;
	Long positionY;
	if (dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController != NULL) {
		positionX = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(1)->GetPosition();
		positionY = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(0)->GetPosition();
	}
	Long right = currentShape->GetX() - positionX - 10;
	Long top = currentShape->GetY() - currentShape->GetHeight() - positionY;
	Long left = right - 250;
	Long bottom = top + 84;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* ContextMenuTutorial::Clone() {
	return new ContextMenuTutorial(*this);
}

//PositionTutorial
PositionTutorial::PositionTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

PositionTutorial::PositionTutorial(const PositionTutorial& source)
	: Tutorial(source) {

}

PositionTutorial::~PositionTutorial() {

}

PositionTutorial& PositionTutorial::operator=(const PositionTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void PositionTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  '기호 위치 같게'를 누르세요.  \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));
	FlowChart *flowChart = (FlowChart*)dynamic_cast<DrawingPaper*>(editor->windows[0])->flowChart;
	Long count;
	Long(*indexes);
	flowChart->GetSelecteds(&indexes, &count);

	Shape *currentShape = flowChart->GetAt(indexes[count - 1]);
	Long positionX;
	Long positionY;
	if (dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController != NULL) {
		positionX = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(1)->GetPosition();
		positionY = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(0)->GetPosition();
	}
	Long right = currentShape->GetX() - positionX - 10;
	Long top = currentShape->GetY() - currentShape->GetHeight() - positionY;
	Long left = right - 280;
	Long bottom = top + 63;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* PositionTutorial::Clone() {
	return new PositionTutorial(*this);
}

//IntervalTutorial
IntervalTutorial::IntervalTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

IntervalTutorial::IntervalTutorial(const IntervalTutorial& source)
	: Tutorial(source) {

}

IntervalTutorial::~IntervalTutorial() {

}

IntervalTutorial& IntervalTutorial::operator=(const IntervalTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void IntervalTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  '기호 간격 같게'를 누르세요.  \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));
	FlowChart *flowChart = (FlowChart*)dynamic_cast<DrawingPaper*>(editor->windows[0])->flowChart;
	Long count;
	Long(*indexes);
	flowChart->GetSelecteds(&indexes, &count);

	Shape *currentShape = flowChart->GetAt(indexes[count - 1]);
	Long positionX;
	Long positionY;
	if (dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController != NULL) {
		positionX = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(1)->GetPosition();
		positionY = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(0)->GetPosition();
	}
	Long right = currentShape->GetX() - positionX - 10;
	Long top = currentShape->GetY() - currentShape->GetHeight() - positionY;
	Long left = right - 280;
	Long bottom = top + 63;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* IntervalTutorial::Clone() {
	return new IntervalTutorial(*this);
}

//SequenceMakeTutorial
SequenceMakeTutorial::SequenceMakeTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

SequenceMakeTutorial::SequenceMakeTutorial(const SequenceMakeTutorial& source)
	: Tutorial(source) {

}

SequenceMakeTutorial::~SequenceMakeTutorial() {

}

SequenceMakeTutorial& SequenceMakeTutorial::operator=(const SequenceMakeTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void SequenceMakeTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  순차구조를 만드세요.  \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));
	FlowChart *flowChart = (FlowChart*)dynamic_cast<DrawingPaper*>(editor->windows[0])->flowChart;
	Long count;
	Long(*indexes);
	flowChart->GetSelecteds(&indexes, &count);

	Shape *currentShape = flowChart->GetAt(indexes[count - 1]);
	Long positionX;
	Long positionY;
	if (dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController != NULL) {
		positionX = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(1)->GetPosition();
		positionY = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(0)->GetPosition();
	}
	Long right = currentShape->GetX() - positionX - 10;
	Long top = currentShape->GetY() - currentShape->GetHeight() - positionY;
	Long left = right - 250;
	Long bottom = top + 63;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* SequenceMakeTutorial::Clone() {
	return new SequenceMakeTutorial(*this);
}

//SelectionMakeTutorial
SelectionMakeTutorial::SelectionMakeTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

SelectionMakeTutorial::SelectionMakeTutorial(const SelectionMakeTutorial& source)
	: Tutorial(source) {

}

SelectionMakeTutorial::~SelectionMakeTutorial() {

}

SelectionMakeTutorial& SelectionMakeTutorial::operator=(const SelectionMakeTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void SelectionMakeTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  선택구조를 만드세요.  \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));
	FlowChart *flowChart = (FlowChart*)dynamic_cast<DrawingPaper*>(editor->windows[0])->flowChart;
	Long count;
	Long(*indexes);
	flowChart->GetSelecteds(&indexes, &count);

	Shape *currentShape = flowChart->GetAt(indexes[0]);
	Long positionX;
	Long positionY;
	if (dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController != NULL) {
		positionX = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(1)->GetPosition();
		positionY = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(0)->GetPosition();
	}
	Long right = currentShape->GetX() - positionX - 10;
	Long top = currentShape->GetY() - currentShape->GetHeight() - positionY;
	Long left = right - 250;
	Long bottom = top + 63;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* SelectionMakeTutorial::Clone() {
	return new SelectionMakeTutorial(*this);
}

//IterationMakeTutorial
IterationMakeTutorial::IterationMakeTutorial(FlowChartEditor *editor)
	: Tutorial(editor) {

}

IterationMakeTutorial::IterationMakeTutorial(const IterationMakeTutorial& source)
	: Tutorial(source) {

}

IterationMakeTutorial::~IterationMakeTutorial() {

}

IterationMakeTutorial& IterationMakeTutorial::operator=(const IterationMakeTutorial& source) {
	Tutorial::operator=(source);

	return *this;
}

void IterationMakeTutorial::Execute() {
	if (editor->toolTip != NULL) {
		editor->toolTip->Destroy();
	}
	char *tip = (char*)"\r\n  반복구조를 만드세요.  \r\n";
	this->editor->toolTip = ToolTip::Instance(tip, RGB(255, 255, 204));
	FlowChart *flowChart = (FlowChart*)dynamic_cast<DrawingPaper*>(editor->windows[0])->flowChart;
	Long count;
	Long(*indexes);
	flowChart->GetSelecteds(&indexes, &count);

	Shape *currentShape = flowChart->GetAt(indexes[2]);
	Long positionX;
	Long positionY;
	if (dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController != NULL) {
		positionX = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(1)->GetPosition();
		positionY = dynamic_cast<DrawingPaper*>(editor->windows[0])->scrollController->GetScroll(0)->GetPosition();
	}
	Long right = currentShape->GetX() - positionX - 10;
	Long top = currentShape->GetY() - currentShape->GetHeight() - positionY;
	Long left = right - 250;
	Long bottom = top + 63;
	this->editor->toolTip->Open(left, top, right - left, bottom - top, tip);
	this->editor->toolTip->Create(NULL, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), editor, -1);
}

Tutorial* IterationMakeTutorial::Clone() {
	return new IterationMakeTutorial(*this);
}