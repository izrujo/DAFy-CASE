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

FlowChartEditorKey::KeyAction::KeyAction(FlowChartEditor *editor) {
	this->editor = editor;
}

FlowChartEditorKey::KeyAction::KeyAction(const FlowChartEditorKey::KeyAction& source) {
	this->editor = source.editor;
}

FlowChartEditorKey::KeyAction::~KeyAction() {

}

FlowChartEditorKey::KeyAction& FlowChartEditorKey::KeyAction::operator=(const FlowChartEditorKey::KeyAction& source) {
	this->editor = source.editor;

	return *this;
}

//FlowChartEditorKey::DeleteKeyAction
FlowChartEditorKey::DeleteKeyAction::DeleteKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::DeleteKeyAction::DeleteKeyAction(const FlowChartEditorKey::DeleteKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::DeleteKeyAction::~DeleteKeyAction() {

}

FlowChartEditorKey::DeleteKeyAction& FlowChartEditorKey::DeleteKeyAction::operator=(const FlowChartEditorKey::DeleteKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::DeleteKeyAction::OnKeyDown() {
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

//EscapeKeyAction
FlowChartEditorKey::EscapeKeyAction::EscapeKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::EscapeKeyAction::EscapeKeyAction(const FlowChartEditorKey::EscapeKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::EscapeKeyAction::~EscapeKeyAction() {

}

FlowChartEditorKey::EscapeKeyAction& FlowChartEditorKey::EscapeKeyAction::operator=(const FlowChartEditorKey::EscapeKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::EscapeKeyAction::OnKeyDown() {
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

//LeftKeyAction
FlowChartEditorKey::LeftKeyAction::LeftKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::LeftKeyAction::LeftKeyAction(const FlowChartEditorKey::LeftKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::LeftKeyAction::~LeftKeyAction() {

}

FlowChartEditorKey::LeftKeyAction& FlowChartEditorKey::LeftKeyAction::operator=(const FlowChartEditorKey::LeftKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::LeftKeyAction::OnKeyDown() {
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

//RightKeyAction
FlowChartEditorKey::RightKeyAction::RightKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::RightKeyAction::RightKeyAction(const FlowChartEditorKey::RightKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::RightKeyAction::~RightKeyAction() {

}

FlowChartEditorKey::RightKeyAction& FlowChartEditorKey::RightKeyAction::operator=(const FlowChartEditorKey::RightKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::RightKeyAction::OnKeyDown() {
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

//UpKeyAction
FlowChartEditorKey::UpKeyAction::UpKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::UpKeyAction::UpKeyAction(const FlowChartEditorKey::UpKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::UpKeyAction::~UpKeyAction() {

}

FlowChartEditorKey::UpKeyAction& FlowChartEditorKey::UpKeyAction::operator=(const FlowChartEditorKey::UpKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::UpKeyAction::OnKeyDown() {
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

//DownKeyAction
FlowChartEditorKey::DownKeyAction::DownKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::DownKeyAction::DownKeyAction(const FlowChartEditorKey::DownKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::DownKeyAction::~DownKeyAction() {

}

FlowChartEditorKey::DownKeyAction& FlowChartEditorKey::DownKeyAction::operator=(const FlowChartEditorKey::DownKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::DownKeyAction::OnKeyDown() {
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

//CtrlDKeyAction
FlowChartEditorKey::CtrlDKeyAction::CtrlDKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::CtrlDKeyAction::CtrlDKeyAction(const FlowChartEditorKey::CtrlDKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::CtrlDKeyAction::~CtrlDKeyAction() {

}

FlowChartEditorKey::CtrlDKeyAction& FlowChartEditorKey::CtrlDKeyAction::operator=(const FlowChartEditorKey::CtrlDKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::CtrlDKeyAction::OnKeyDown() {
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

//OneKeyAction
FlowChartEditorKey::OneKeyAction::OneKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::OneKeyAction::OneKeyAction(const FlowChartEditorKey::OneKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::OneKeyAction::~OneKeyAction() {

}

FlowChartEditorKey::OneKeyAction& FlowChartEditorKey::OneKeyAction::operator=(const FlowChartEditorKey::OneKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::OneKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(0);
	}
}

//TwoKeyAction
FlowChartEditorKey::TwoKeyAction::TwoKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::TwoKeyAction::TwoKeyAction(const FlowChartEditorKey::TwoKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::TwoKeyAction::~TwoKeyAction() {

}

FlowChartEditorKey::TwoKeyAction& FlowChartEditorKey::TwoKeyAction::operator=(const FlowChartEditorKey::TwoKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::TwoKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(1);
	}
}

//ThreeKeyAction
FlowChartEditorKey::ThreeKeyAction::ThreeKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::ThreeKeyAction::ThreeKeyAction(const FlowChartEditorKey::ThreeKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::ThreeKeyAction::~ThreeKeyAction() {

}

FlowChartEditorKey::ThreeKeyAction& FlowChartEditorKey::ThreeKeyAction::operator=(const FlowChartEditorKey::ThreeKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::ThreeKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(2);

	}
}

//FourKeyAction
FlowChartEditorKey::FourKeyAction::FourKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::FourKeyAction::FourKeyAction(const FlowChartEditorKey::FourKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::FourKeyAction::~FourKeyAction() {

}

FlowChartEditorKey::FourKeyAction& FlowChartEditorKey::FourKeyAction::operator=(const FlowChartEditorKey::FourKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::FourKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(3);

	}
}

//FiveKeyAction
FlowChartEditorKey::FiveKeyAction::FiveKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::FiveKeyAction::FiveKeyAction(const FlowChartEditorKey::FiveKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::FiveKeyAction::~FiveKeyAction() {

}

FlowChartEditorKey::FiveKeyAction& FlowChartEditorKey::FiveKeyAction::operator=(const FlowChartEditorKey::FiveKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::FiveKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(4);

	}
}

//SixKeyAction
FlowChartEditorKey::SixKeyAction::SixKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::SixKeyAction::SixKeyAction(const FlowChartEditorKey::SixKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::SixKeyAction::~SixKeyAction() {

}

FlowChartEditorKey::SixKeyAction& FlowChartEditorKey::SixKeyAction::operator=(const FlowChartEditorKey::SixKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::SixKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(5);

	}
}

//SevenKeyAction
FlowChartEditorKey::SevenKeyAction::SevenKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::SevenKeyAction::SevenKeyAction(const FlowChartEditorKey::SevenKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::SevenKeyAction::~SevenKeyAction() {

}

FlowChartEditorKey::SevenKeyAction& FlowChartEditorKey::SevenKeyAction::operator=(const FlowChartEditorKey::SevenKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::SevenKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(6);

	}
}

//CtrlPlusKeyAction
FlowChartEditorKey::CtrlPlusKeyAction::CtrlPlusKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::CtrlPlusKeyAction::CtrlPlusKeyAction(const FlowChartEditorKey::CtrlPlusKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::CtrlPlusKeyAction::~CtrlPlusKeyAction() {

}

FlowChartEditorKey::CtrlPlusKeyAction& FlowChartEditorKey::CtrlPlusKeyAction::operator=(const FlowChartEditorKey::CtrlPlusKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::CtrlPlusKeyAction::OnKeyDown() {
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

//CtrlMinusKeyAction
FlowChartEditorKey::CtrlMinusKeyAction::CtrlMinusKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::CtrlMinusKeyAction::CtrlMinusKeyAction(const FlowChartEditorKey::CtrlMinusKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::CtrlMinusKeyAction::~CtrlMinusKeyAction() {

}

FlowChartEditorKey::CtrlMinusKeyAction& FlowChartEditorKey::CtrlMinusKeyAction::operator=(const FlowChartEditorKey::CtrlMinusKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::CtrlMinusKeyAction::OnKeyDown() {
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

//CtrlAKeyAction
FlowChartEditorKey::CtrlAKeyAction::CtrlAKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::CtrlAKeyAction::CtrlAKeyAction(const FlowChartEditorKey::CtrlAKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::CtrlAKeyAction::~CtrlAKeyAction() {

}

FlowChartEditorKey::CtrlAKeyAction& FlowChartEditorKey::CtrlAKeyAction::operator=(const FlowChartEditorKey::CtrlAKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::CtrlAKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	NShape *flowChart = canvas->flowChart;
	flowChart->SelectAll();
	if (flowChart->GetLength() > 0) {
		canvas->mode = DrawingPaper::SELECT;
	}
}

//CtrlCKeyAction
FlowChartEditorKey::CtrlCKeyAction::CtrlCKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::CtrlCKeyAction::CtrlCKeyAction(const FlowChartEditorKey::CtrlCKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::CtrlCKeyAction::~CtrlCKeyAction() {

}

FlowChartEditorKey::CtrlCKeyAction& FlowChartEditorKey::CtrlCKeyAction::operator=(const FlowChartEditorKey::CtrlCKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::CtrlCKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	canvas->clipboard->Copy(canvas);
}

//CtrlVKeyAction
FlowChartEditorKey::CtrlVKeyAction::CtrlVKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::CtrlVKeyAction::CtrlVKeyAction(const FlowChartEditorKey::CtrlVKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::CtrlVKeyAction::~CtrlVKeyAction() {

}

FlowChartEditorKey::CtrlVKeyAction& FlowChartEditorKey::CtrlVKeyAction::operator=(const FlowChartEditorKey::CtrlVKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::CtrlVKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	canvas->clipboard->Paste(canvas);
}

//CtrlXKeyAction
FlowChartEditorKey::CtrlXKeyAction::CtrlXKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::CtrlXKeyAction::CtrlXKeyAction(const FlowChartEditorKey::CtrlXKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::CtrlXKeyAction::~CtrlXKeyAction() {

}

FlowChartEditorKey::CtrlXKeyAction& FlowChartEditorKey::CtrlXKeyAction::operator=(const FlowChartEditorKey::CtrlXKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::CtrlXKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	canvas->clipboard->Cut(canvas);
}

//CtrlZKeyAction
FlowChartEditorKey::CtrlZKeyAction::CtrlZKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::CtrlZKeyAction::CtrlZKeyAction(const FlowChartEditorKey::CtrlZKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::CtrlZKeyAction::~CtrlZKeyAction() {

}

FlowChartEditorKey::CtrlZKeyAction& FlowChartEditorKey::CtrlZKeyAction::operator=(const FlowChartEditorKey::CtrlZKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::CtrlZKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	if (canvas->memoryController->GetUndoMemory()->GetLength() > 0) {
		canvas->memoryController->RememberUndo();
		canvas->memoryController->Undo();
		canvas->flowChart->AscendingSort();
		canvas->memoryController->Quadrate();
	}
}

//CtrlYKeyAction
FlowChartEditorKey::CtrlYKeyAction::CtrlYKeyAction(FlowChartEditor *editor)
	: KeyAction(editor) {

}

FlowChartEditorKey::CtrlYKeyAction::CtrlYKeyAction(const FlowChartEditorKey::CtrlYKeyAction& source)
	: KeyAction(source) {

}

FlowChartEditorKey::CtrlYKeyAction::~CtrlYKeyAction() {

}

FlowChartEditorKey::CtrlYKeyAction& FlowChartEditorKey::CtrlYKeyAction::operator=(const FlowChartEditorKey::CtrlYKeyAction& source) {
	KeyAction::operator=(source);

	return *this;
}

void FlowChartEditorKey::CtrlYKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	if (canvas->memoryController->GetRedoMemory()->GetLength() > 0) {
		canvas->memoryController->RememberRedo();
		canvas->memoryController->Redo();
		canvas->flowChart->AscendingSort();
		canvas->memoryController->Quadrate();
	}
}