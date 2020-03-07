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
#include "Painter.h"
#include "StatusBar.h"
#include "TutorialForm.h"
#include "Tutorials.h"
#include "ToolTip.h"
#include "TutorialController.h"

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

//DeleteKeyAction
DeleteKeyAction::DeleteKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

DeleteKeyAction::DeleteKeyAction(const DeleteKeyAction& source)
	: FlowChartKeyAction(source) {

}

DeleteKeyAction::~DeleteKeyAction() {

}

DeleteKeyAction& DeleteKeyAction::operator=(const DeleteKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void DeleteKeyAction::OnKeyDown() {
	Long it;
	Shape *shape;
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
EscapeKeyAction::EscapeKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

EscapeKeyAction::EscapeKeyAction(const EscapeKeyAction& source)
	: FlowChartKeyAction(source) {

}

EscapeKeyAction::~EscapeKeyAction() {

}

EscapeKeyAction& EscapeKeyAction::operator=(const EscapeKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void EscapeKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);

	canvas->flowChart->GetSelecteds(&indexes, &count);
	Long i;
	for (i = 0; i < count; i++) {
		Shape *shape = canvas->flowChart->GetAt(indexes[i]);
		shape->Select(false);
	}

	FlowChartTemplate *flowChartTemplate = static_cast<FlowChartTemplate*>(this->editor->windows[1]);

	if (flowChartTemplate->mode == FlowChartTemplate::DRAWON && canvas->mode != DrawingPaper::DRAWING) {
		flowChartTemplate->mode = FlowChartTemplate::DRAWOFF;
		Long i = dynamic_cast<Template*>(flowChartTemplate->flowChartTemplate)->GetLength() - 1;
		while (i >= 7) { //numberBox만 없애기
			dynamic_cast<Template*>(flowChartTemplate->flowChartTemplate)->Detach(i);
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
LeftKeyAction::LeftKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

LeftKeyAction::LeftKeyAction(const LeftKeyAction& source)
	: FlowChartKeyAction(source) {

}

LeftKeyAction::~LeftKeyAction() {

}

LeftKeyAction& LeftKeyAction::operator=(const LeftKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void LeftKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);

	canvas->flowChart->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberOther(indexes, count);

	Long i;
	for (i = 0; i < count; i++) {
		Shape *shape = canvas->flowChart->GetAt(indexes[i]);
		Long x = shape->GetX();
		Long y = shape->GetY();

		shape->Move(x - DISTANCE, y);
	}
	canvas->repaint();

	if (indexes != 0) {
		delete[] indexes;
	}
}

//RightKeyAction
RightKeyAction::RightKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

RightKeyAction::RightKeyAction(const RightKeyAction& source)
	: FlowChartKeyAction(source) {

}

RightKeyAction::~RightKeyAction() {

}

RightKeyAction& RightKeyAction::operator=(const RightKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void RightKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);

	canvas->flowChart->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberOther(indexes, count);

	Long i;
	for (i = 0; i < count; i++) {
		Shape *shape = canvas->flowChart->GetAt(indexes[i]);
		Long x = shape->GetX();
		Long y = shape->GetY();

		shape->Move(x + DISTANCE, y);
	}
	canvas->repaint();
	if (indexes != 0) {
		delete[] indexes;
	}
}

//UpKeyAction
UpKeyAction::UpKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

UpKeyAction::UpKeyAction(const UpKeyAction& source)
	: FlowChartKeyAction(source) {

}

UpKeyAction::~UpKeyAction() {

}

UpKeyAction& UpKeyAction::operator=(const UpKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void UpKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);

	canvas->flowChart->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberOther(indexes, count);
	Long i;
	for (i = 0; i < count; i++) {
		Shape *shape = canvas->flowChart->GetAt(indexes[i]);
		Long x = shape->GetX();
		Long y = shape->GetY();

		shape->Move(x, y - DISTANCE);
	}
	canvas->repaint();
	if (indexes != 0) {
		delete[] indexes;
	}
}

//DownKeyAction
DownKeyAction::DownKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

DownKeyAction::DownKeyAction(const DownKeyAction& source)
	: FlowChartKeyAction(source) {

}

DownKeyAction::~DownKeyAction() {

}

DownKeyAction& DownKeyAction::operator=(const DownKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void DownKeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);

	canvas->flowChart->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberOther(indexes, count);

	Long i;
	for (i = 0; i < count; i++) {
		Shape *shape = canvas->flowChart->GetAt(indexes[i]);

		Long x = shape->GetX();
		Long y = shape->GetY();

		shape->Move(x, y + DISTANCE);
	}

	canvas->repaint();
	if (indexes != 0) {
		delete[] indexes;
	}
}

//CtrlDKeyAction
CtrlDKeyAction::CtrlDKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

CtrlDKeyAction::CtrlDKeyAction(const CtrlDKeyAction& source)
	: FlowChartKeyAction(source) {

}

CtrlDKeyAction::~CtrlDKeyAction() {

}

CtrlDKeyAction& CtrlDKeyAction::operator=(const CtrlDKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void CtrlDKeyAction::OnKeyDown() {
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

		this->editor->isUnModeMenuEnabled = TRUE;
	}
}

//OneKeyAction
OneKeyAction::OneKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

OneKeyAction::OneKeyAction(const OneKeyAction& source)
	: FlowChartKeyAction(source) {

}

OneKeyAction::~OneKeyAction() {

}

OneKeyAction& OneKeyAction::operator=(const OneKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void OneKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(0);
	}
}

//TwoKeyAction
TwoKeyAction::TwoKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

TwoKeyAction::TwoKeyAction(const TwoKeyAction& source)
	: FlowChartKeyAction(source) {

}

TwoKeyAction::~TwoKeyAction() {

}

TwoKeyAction& TwoKeyAction::operator=(const TwoKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void TwoKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(1);
	}
}

//ThreeKeyAction
ThreeKeyAction::ThreeKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

ThreeKeyAction::ThreeKeyAction(const ThreeKeyAction& source)
	: FlowChartKeyAction(source) {

}

ThreeKeyAction::~ThreeKeyAction() {

}

ThreeKeyAction& ThreeKeyAction::operator=(const ThreeKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void ThreeKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(2);

	}
}

//FourKeyAction
FourKeyAction::FourKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FourKeyAction::FourKeyAction(const FourKeyAction& source)
	: FlowChartKeyAction(source) {

}

FourKeyAction::~FourKeyAction() {

}

FourKeyAction& FourKeyAction::operator=(const FourKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FourKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(3);

	}
}

//FiveKeyAction
FiveKeyAction::FiveKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FiveKeyAction::FiveKeyAction(const FiveKeyAction& source)
	: FlowChartKeyAction(source) {

}

FiveKeyAction::~FiveKeyAction() {

}

FiveKeyAction& FiveKeyAction::operator=(const FiveKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FiveKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(4);

	}
}

//SixKeyAction
SixKeyAction::SixKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

SixKeyAction::SixKeyAction(const SixKeyAction& source)
	: FlowChartKeyAction(source) {

}

SixKeyAction::~SixKeyAction() {

}

SixKeyAction& SixKeyAction::operator=(const SixKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void SixKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(5);

	}
}

//SevenKeyAction
SevenKeyAction::SevenKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

SevenKeyAction::SevenKeyAction(const SevenKeyAction& source)
	: FlowChartKeyAction(source) {

}

SevenKeyAction::~SevenKeyAction() {

}

SevenKeyAction& SevenKeyAction::operator=(const SevenKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void SevenKeyAction::OnKeyDown() {
	if (dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode == FlowChartTemplate::DRAWON) {
		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected =
			static_cast<Template*>(dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate)->GetAt(6);

	}
}

//CtrlPlusKeyAction
CtrlPlusKeyAction::CtrlPlusKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

CtrlPlusKeyAction::CtrlPlusKeyAction(const CtrlPlusKeyAction& source)
	: FlowChartKeyAction(source) {

}

CtrlPlusKeyAction::~CtrlPlusKeyAction() {

}

CtrlPlusKeyAction& CtrlPlusKeyAction::operator=(const CtrlPlusKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void CtrlPlusKeyAction::OnKeyDown() {
	Long oldRate = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->GetRate();
	Long rate;
	if (oldRate < 150) {
		rate = oldRate + 10;

		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->Set(rate);

		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->scrollController->Update();

		CString rateStatus;
		rateStatus.Format("%d", rate);
		rateStatus += "%";
		this->editor->statusBar->Modify(4, String((LPCTSTR)rateStatus));
	}
}

//CtrlMinusKeyAction
CtrlMinusKeyAction::CtrlMinusKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

CtrlMinusKeyAction::CtrlMinusKeyAction(const CtrlMinusKeyAction& source)
	: FlowChartKeyAction(source) {

}

CtrlMinusKeyAction::~CtrlMinusKeyAction() {

}

CtrlMinusKeyAction& CtrlMinusKeyAction::operator=(const CtrlMinusKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void CtrlMinusKeyAction::OnKeyDown() {
	Long oldRate = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->GetRate();
	Long rate;
	if (oldRate > 40) {
		rate = oldRate - 10;

		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->zoom->Set(rate);

		dynamic_cast<DrawingPaper*>(this->editor->windows[0])->scrollController->Update();

		CString rateStatus;
		rateStatus.Format("%d", rate);
		rateStatus += "%";
		this->editor->statusBar->Modify(4, String((LPCTSTR)rateStatus));
	}
}