#include "FlowChartKeyActions.h"
#include "../FlowChartEditor.h"
#include "FlowChartTemplate.h"
#include "DrawingPaper.h"
#include "Template.h"
#include "Shape.h"
#include "NumberBox.h"
#include "Zoom.h"
#include "MemoryController.h"
#include "ScrollController.h"
#include "FlowChart.h"
#include "../GObject/Painter.h"
#include "Clipboard.h"
#include "Memory.h"

FlowChartKeyAction::FlowChartKeyAction(FlowChartEditor *editor) {
	this->editor = editor;
}

FlowChartKeyAction::FlowChartKeyAction(const FlowChartKeyAction& source) {
	this->editor = source.editor;
}

FlowChartKeyAction::~FlowChartKeyAction() {

}

FlowChartKeyAction& FlowChartKeyAction::operator=(const FlowChartKeyAction& source) {
	this->editor = source.editor;

	return *this;
}

//FDeleteKeyAction
FDeleteKeyAction::FDeleteKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FDeleteKeyAction::FDeleteKeyAction(const FDeleteKeyAction& source)
	: FlowChartKeyAction(source) {

}

FDeleteKeyAction::~FDeleteKeyAction() {

}

FDeleteKeyAction& FDeleteKeyAction::operator=(const FDeleteKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FDeleteKeyAction::OnKeyDown() {
	Long it;
	NShape *shape;
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);

	Long count;
	Long(*indexes);
	canvas->flowChart->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberRemove(indexes, count);

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
}

//FEscapeKeyAction
FEscapeKeyAction::FEscapeKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FEscapeKeyAction::FEscapeKeyAction(const FEscapeKeyAction& source)
	: FlowChartKeyAction(source) {

}

FEscapeKeyAction::~FEscapeKeyAction() {

}

FEscapeKeyAction& FEscapeKeyAction::operator=(const FEscapeKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FEscapeKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);

	canvas->flowChart->GetSelecteds(&indexes, &count);
	Long i;
	for (i = 0; i < count; i++) {
		NShape *shape = canvas->flowChart->GetAt(indexes[i]);
		shape->Select(false);
	}

	FlowChartTemplate *flowChartTemplate = static_cast<FlowChartTemplate*>(this->editor->windows[1]);

	if (flowChartTemplate->mode == FlowChartTemplate::DRAWON && canvas->mode != DrawingPaper::DRAWING) {
		flowChartTemplate->mode = FlowChartTemplate::DRAWOFF;
		Long i = flowChartTemplate->flowChartTemplate->GetLength() - 1;
		while (i >= 7) { //numberBox만 없애기
			flowChartTemplate->flowChartTemplate->Detach(i);
			i--;
		}
		//editor->isUnModeMenuEnabled = FALSE;
	}

	if (canvas->mode == DrawingPaper::DRAWING) {
		canvas->templateSelected = NULL;
		flowChartTemplate->shapeSelected = NULL;
	}

	canvas->mode = DrawingPaper::IDLE;

	canvas->repaint();
	canvas->indexOfSelected = -1;

	if (indexes != 0) {
		delete[] indexes;
	}
}

//FLeftKeyAction
FLeftKeyAction::FLeftKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FLeftKeyAction::FLeftKeyAction(const FLeftKeyAction& source)
	: FlowChartKeyAction(source) {

}

FLeftKeyAction::~FLeftKeyAction() {

}

FLeftKeyAction& FLeftKeyAction::operator=(const FLeftKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FLeftKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);

	canvas->flowChart->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberOther(indexes, count);

	Long i;
	for (i = 0; i < count; i++) {
		NShape *shape = canvas->flowChart->GetAt(indexes[i]);
		Long x = shape->GetX();
		Long y = shape->GetY();

		shape->Move(x - MOVEDISTANCE, y);
	}
	canvas->repaint();

	if (indexes != 0) {
		delete[] indexes;
	}
}

//FRightKeyAction
FRightKeyAction::FRightKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FRightKeyAction::FRightKeyAction(const FRightKeyAction& source)
	: FlowChartKeyAction(source) {

}

FRightKeyAction::~FRightKeyAction() {

}

FRightKeyAction& FRightKeyAction::operator=(const FRightKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FRightKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);

	canvas->flowChart->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberOther(indexes, count);

	Long i;
	for (i = 0; i < count; i++) {
		NShape *shape = canvas->flowChart->GetAt(indexes[i]);
		Long x = shape->GetX();
		Long y = shape->GetY();

		shape->Move(x + MOVEDISTANCE, y);
	}
	canvas->repaint();
	if (indexes != 0) {
		delete[] indexes;
	}
}

//FUpKeyAction
FUpKeyAction::FUpKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FUpKeyAction::FUpKeyAction(const FUpKeyAction& source)
	: FlowChartKeyAction(source) {

}

FUpKeyAction::~FUpKeyAction() {

}

FUpKeyAction& FUpKeyAction::operator=(const FUpKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FUpKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);

	canvas->flowChart->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberOther(indexes, count);
	Long i;
	for (i = 0; i < count; i++) {
		NShape *shape = canvas->flowChart->GetAt(indexes[i]);
		Long x = shape->GetX();
		Long y = shape->GetY();

		shape->Move(x, y - MOVEDISTANCE);
	}
	canvas->repaint();
	if (indexes != 0) {
		delete[] indexes;
	}
}

//FDownKeyAction
FDownKeyAction::FDownKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FDownKeyAction::FDownKeyAction(const FDownKeyAction& source)
	: FlowChartKeyAction(source) {

}

FDownKeyAction::~FDownKeyAction() {

}

FDownKeyAction& FDownKeyAction::operator=(const FDownKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FDownKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);

	canvas->flowChart->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberOther(indexes, count);

	Long i;
	for (i = 0; i < count; i++) {
		NShape *shape = canvas->flowChart->GetAt(indexes[i]);

		Long x = shape->GetX();
		Long y = shape->GetY();

		shape->Move(x, y + MOVEDISTANCE);
	}

	canvas->repaint();
	if (indexes != 0) {
		delete[] indexes;
	}
}

//FCtrlDKeyAction
FCtrlDKeyAction::FCtrlDKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlDKeyAction::FCtrlDKeyAction(const FCtrlDKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlDKeyAction::~FCtrlDKeyAction() {

}

FCtrlDKeyAction& FCtrlDKeyAction::operator=(const FCtrlDKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlDKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWOFF) {
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode = FlowChartTemplate::DRAWON;

		NShape *one = new NumberBox(15, 85, 15, 15, QColor(230, 230, 230), Qt::SolidLine, QColor(0, 0, 0), String("1"));
		NShape *two = new NumberBox(15, 155, 15, 15, QColor(230, 230, 230), Qt::SolidLine, QColor(0, 0, 0), String("2"));
		NShape *three = new NumberBox(15, 225, 15, 15, QColor(230, 230, 230), Qt::SolidLine, QColor(0, 0, 0), String("3"));
		NShape *four = new NumberBox(15, 295, 15, 15, QColor(230, 230, 230), Qt::SolidLine, QColor(0, 0, 0), String("4"));
		NShape *five = new NumberBox(15, 365, 15, 15, QColor(230, 230, 230), Qt::SolidLine, QColor(0, 0, 0), String("5"));
		NShape *six = new NumberBox(15, 435, 15, 15, QColor(230, 230, 230), Qt::SolidLine, QColor(0, 0, 0), String("6"));
		NShape *seven = new NumberBox(15, 505, 15, 15, QColor(230, 230, 230), Qt::SolidLine, QColor(0, 0, 0), String("7"));
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(one);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(two);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(three);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(four);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(five);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(six);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(seven);

		//this->editor->isUnModeMenuEnabled = TRUE;
	}
}

//FOneKeyAction
FOneKeyAction::FOneKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FOneKeyAction::FOneKeyAction(const FOneKeyAction& source)
	: FlowChartKeyAction(source) {

}

FOneKeyAction::~FOneKeyAction() {

}

FOneKeyAction& FOneKeyAction::operator=(const FOneKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FOneKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(0);
	}
}

//FTwoKeyAction
FTwoKeyAction::FTwoKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FTwoKeyAction::FTwoKeyAction(const FTwoKeyAction& source)
	: FlowChartKeyAction(source) {

}

FTwoKeyAction::~FTwoKeyAction() {

}

FTwoKeyAction& FTwoKeyAction::operator=(const FTwoKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FTwoKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(1);
	}
}

//FThreeKeyAction
FThreeKeyAction::FThreeKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FThreeKeyAction::FThreeKeyAction(const FThreeKeyAction& source)
	: FlowChartKeyAction(source) {

}

FThreeKeyAction::~FThreeKeyAction() {

}

FThreeKeyAction& FThreeKeyAction::operator=(const FThreeKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FThreeKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(2);

	}
}

//FFourKeyAction
FFourKeyAction::FFourKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FFourKeyAction::FFourKeyAction(const FFourKeyAction& source)
	: FlowChartKeyAction(source) {

}

FFourKeyAction::~FFourKeyAction() {

}

FFourKeyAction& FFourKeyAction::operator=(const FFourKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FFourKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(3);

	}
}

//FFiveKeyAction
FFiveKeyAction::FFiveKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FFiveKeyAction::FFiveKeyAction(const FFiveKeyAction& source)
	: FlowChartKeyAction(source) {

}

FFiveKeyAction::~FFiveKeyAction() {

}

FFiveKeyAction& FFiveKeyAction::operator=(const FFiveKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FFiveKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(4);

	}
}

//FSixKeyAction
FSixKeyAction::FSixKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FSixKeyAction::FSixKeyAction(const FSixKeyAction& source)
	: FlowChartKeyAction(source) {

}

FSixKeyAction::~FSixKeyAction() {

}

FSixKeyAction& FSixKeyAction::operator=(const FSixKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FSixKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(5);

	}
}

//FSevenKeyAction
FSevenKeyAction::FSevenKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FSevenKeyAction::FSevenKeyAction(const FSevenKeyAction& source)
	: FlowChartKeyAction(source) {

}

FSevenKeyAction::~FSevenKeyAction() {

}

FSevenKeyAction& FSevenKeyAction::operator=(const FSevenKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FSevenKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(6);

	}
}

//FCtrlPlusKeyAction
FCtrlPlusKeyAction::FCtrlPlusKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlPlusKeyAction::FCtrlPlusKeyAction(const FCtrlPlusKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlPlusKeyAction::~FCtrlPlusKeyAction() {

}

FCtrlPlusKeyAction& FCtrlPlusKeyAction::operator=(const FCtrlPlusKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlPlusKeyAction::OnKeyDown() {
	Long oldRate = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->GetRate();
	Long rate;
	if (oldRate < 150) {
		rate = oldRate + 10;

		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->Set(rate);

		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->scrollController->Update();
		/*
		CString rateStatus;
		rateStatus.Format("%d", rate);
		rateStatus += "%";
		this->editor->statusBar->Modify(4, String((LPCTSTR)rateStatus));
		*/
	}
}

//FCtrlMinusKeyAction
FCtrlMinusKeyAction::FCtrlMinusKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlMinusKeyAction::FCtrlMinusKeyAction(const FCtrlMinusKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlMinusKeyAction::~FCtrlMinusKeyAction() {

}

FCtrlMinusKeyAction& FCtrlMinusKeyAction::operator=(const FCtrlMinusKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlMinusKeyAction::OnKeyDown() {
	Long oldRate = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->GetRate();
	Long rate;
	if (oldRate > 40) {
		rate = oldRate - 10;

		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->Set(rate);

		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->scrollController->Update();
		/*
		CString rateStatus;
		rateStatus.Format("%d", rate);
		rateStatus += "%";
		this->editor->statusBar->Modify(4, String((LPCTSTR)rateStatus));
		*/
	}
}

//FCtrlAKeyAction
FCtrlAKeyAction::FCtrlAKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlAKeyAction::FCtrlAKeyAction(const FCtrlAKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlAKeyAction::~FCtrlAKeyAction() {

}

FCtrlAKeyAction& FCtrlAKeyAction::operator=(const FCtrlAKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlAKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	NShape *flowChart = canvas->flowChart;
	flowChart->SelectAll();
	if (flowChart->GetLength() > 0) {
		canvas->mode = DrawingPaper::SELECT;
	}
}

//FCtrlCKeyAction
FCtrlCKeyAction::FCtrlCKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlCKeyAction::FCtrlCKeyAction(const FCtrlCKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlCKeyAction::~FCtrlCKeyAction() {

}

FCtrlCKeyAction& FCtrlCKeyAction::operator=(const FCtrlCKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlCKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	canvas->clipboard->Copy(canvas);
}

//FCtrlVKeyAction
FCtrlVKeyAction::FCtrlVKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlVKeyAction::FCtrlVKeyAction(const FCtrlVKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlVKeyAction::~FCtrlVKeyAction() {

}

FCtrlVKeyAction& FCtrlVKeyAction::operator=(const FCtrlVKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlVKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	canvas->clipboard->Paste(canvas);
}

//FCtrlXKeyAction
FCtrlXKeyAction::FCtrlXKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlXKeyAction::FCtrlXKeyAction(const FCtrlXKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlXKeyAction::~FCtrlXKeyAction() {

}

FCtrlXKeyAction& FCtrlXKeyAction::operator=(const FCtrlXKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlXKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	canvas->clipboard->Cut(canvas);
}

//FCtrlZKeyAction
FCtrlZKeyAction::FCtrlZKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlZKeyAction::FCtrlZKeyAction(const FCtrlZKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlZKeyAction::~FCtrlZKeyAction() {

}

FCtrlZKeyAction& FCtrlZKeyAction::operator=(const FCtrlZKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlZKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	if (canvas->memoryController->GetUndoMemory()->GetLength() > 0) {
		canvas->memoryController->RememberUndo();
		canvas->memoryController->Undo();
		canvas->flowChart->AscendingSort();
		canvas->memoryController->Quadrate();
	}
}

//FCtrlYKeyAction
FCtrlYKeyAction::FCtrlYKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlYKeyAction::FCtrlYKeyAction(const FCtrlYKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlYKeyAction::~FCtrlYKeyAction() {

}

FCtrlYKeyAction& FCtrlYKeyAction::operator=(const FCtrlYKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlYKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	if (canvas->memoryController->GetRedoMemory()->GetLength() > 0) {
		canvas->memoryController->RememberRedo();
		canvas->memoryController->Redo();
		canvas->flowChart->AscendingSort();
		canvas->memoryController->Quadrate();
	}
}