#include "FlowChartKeyActions.h"
#include "../FlowChartEditor.h"
#include "FlowChartTemplate.h"
#include "DrawingPaper.h"
#include "Template.h"
#include "Shape.h"
#include "NumberBox.h"
#include "Zoom.h"
#include "ScrollController.h"
#include "FlowChart.h"
#include "../GObject/Painter.h"
#include "Clipboard.h"
#include "WindowTitle.h"
#include "../GObject/QtPainter.h"
#include "DrawVisitor.h"
#include "VariableList.h"
#include "Scroll.h"
#include "ZoomVisitor.h"
#include "Label.h"
#include "Line.h"
#include "PreviewForm.h"
#include "HistoryController.h"
#include "HistoryBook.h"
#include "Registrar.h"
#include "SheetManager.h"

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
#include <qpixmap.h>
#include <qaction.h>

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

	it = canvas->flowChart->GetLength() - 1;
	while (it >= 0) {
		shape = canvas->flowChart->GetAt(it);
		if (shape->IsSelected()) {
			canvas->flowChart->Detach(it);
		}
		it--;
	}
	canvas->mode = DrawingPaper::IDLE;
	canvas->indexOfSelected = -1;

	if (indexes != 0) {
		delete[] indexes;
	}

	canvas->Notify();
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

	Long i;
	for (i = 0; i < count; i++) {
		NShape *shape = canvas->flowChart->GetAt(indexes[i]);
		float x = shape->GetX();
		float y = shape->GetY();

		shape->Move(x - MOVEDISTANCE, y);
	}
	canvas->repaint();

	if (indexes != 0) {
		delete[] indexes;
	}

	canvas->Notify();
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

	Long i;
	for (i = 0; i < count; i++) {
		NShape *shape = canvas->flowChart->GetAt(indexes[i]);
		float x = shape->GetX();
		float y = shape->GetY();

		shape->Move(x + MOVEDISTANCE, y);
	}
	canvas->repaint();
	if (indexes != 0) {
		delete[] indexes;
	}

	canvas->Notify();
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
	Long i;
	for (i = 0; i < count; i++) {
		NShape *shape = canvas->flowChart->GetAt(indexes[i]);
		float x = shape->GetX();
		float y = shape->GetY();

		shape->Move(x, y - MOVEDISTANCE);
	}
	canvas->repaint();
	if (indexes != 0) {
		delete[] indexes;
	}

	canvas->Notify();
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

	Long i;
	for (i = 0; i < count; i++) {
		NShape *shape = canvas->flowChart->GetAt(indexes[i]);

		float x = shape->GetX();
		float y = shape->GetY();

		shape->Move(x, y + MOVEDISTANCE);
	}

	canvas->repaint();
	if (indexes != 0) {
		delete[] indexes;
	}

	canvas->Notify();
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

		NShape *terminal = dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(0);
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
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(one);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(two);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(three);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(four);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(five);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(six);
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Attach(seven);

		this->editor->drawingModeAction->setChecked(true);
	}
	else {
		dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->mode = FlowChartTemplate::DRAWOFF;
		Long i = dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetLength() - 1;
		while (i >= 7) { //numberBox만 없애기
			dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->Detach(i);
			i--;
		}

		this->editor->drawingModeAction->setChecked(false);
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

		editor->modeStatus->setText(QString::fromLocal8Bit("DRAWING"));
		QString style(QString::fromLocal8Bit("    단말 기호"));
		editor->messageStatus->setText(style);
		editor->statusBar->repaint();
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
		
		editor->modeStatus->setText(QString::fromLocal8Bit("DRAWING"));
		QString style(QString::fromLocal8Bit("    준비 기호"));
		editor->messageStatus->setText(style);
		editor->statusBar->repaint();
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

		editor->modeStatus->setText(QString::fromLocal8Bit("DRAWING"));
		QString style(QString::fromLocal8Bit("    입출력 기호"));
		editor->messageStatus->setText(style);
		editor->statusBar->repaint();
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

		editor->modeStatus->setText(QString::fromLocal8Bit("DRAWING"));
		QString style(QString::fromLocal8Bit("    처리 기호"));
		editor->messageStatus->setText(style);
		editor->statusBar->repaint();
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

		editor->modeStatus->setText(QString::fromLocal8Bit("DRAWING"));
		QString style(QString::fromLocal8Bit("    판단 기호"));
		editor->messageStatus->setText(style);
		editor->statusBar->repaint();
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

		editor->modeStatus->setText(QString::fromLocal8Bit("DRAWING"));
		QString style(QString::fromLocal8Bit("    입출력 기호"));
		editor->messageStatus->setText(style);
		editor->statusBar->repaint();
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

		editor->modeStatus->setText(QString::fromLocal8Bit("DRAWING"));
		QString style(QString::fromLocal8Bit("    단말 기호"));
		editor->messageStatus->setText(style);
		editor->statusBar->repaint();
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

		QString rateStatus;
		rateStatus = QString::number(rate);
		rateStatus += "%";
		dynamic_cast<FlowChartEditor*>(this->editor)->zoomStatus->setText(rateStatus);
		dynamic_cast<FlowChartEditor*>(this->editor)->statusBar->repaint();
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

		QString rateStatus;
		rateStatus = QString::number(rate);
		rateStatus += "%";
		dynamic_cast<FlowChartEditor*>(this->editor)->zoomStatus->setText(rateStatus);
		dynamic_cast<FlowChartEditor*>(this->editor)->statusBar->repaint();
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
	
	canvas->Notify();
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

	canvas->Notify();
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
	if (canvas->historyController->GetUndoHistoryBook()->GetLength() > 0) {
		canvas->historyController->Undo();
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
	if (canvas->historyController->GetRedoHistoryBook()->GetLength() > 0) {
		canvas->historyController->Redo();
	}
}

//FCtrlNKeyAction
FCtrlNKeyAction::FCtrlNKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlNKeyAction::FCtrlNKeyAction(const FCtrlNKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlNKeyAction::~FCtrlNKeyAction() {

}

FCtrlNKeyAction& FCtrlNKeyAction::operator=(const FCtrlNKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlNKeyAction::OnKeyDown() {
	(static_cast<DrawingPaper *>(this->editor->windows[0]))->New();
	(static_cast<DrawingPaper *>(this->editor->windows[0]))->setFocus();
	this->editor->repaint();
}

//FCtrlOKeyAction
FCtrlOKeyAction::FCtrlOKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlOKeyAction::FCtrlOKeyAction(const FCtrlOKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlOKeyAction::~FCtrlOKeyAction() {

}

FCtrlOKeyAction& FCtrlOKeyAction::operator=(const FCtrlOKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlOKeyAction::OnKeyDown() {
	QString fileName = QFileDialog::getOpenFileName((QWidget*)this->editor,
		QObject::tr("Load"), "",
		QObject::tr("(*.txt);;All Files (*)"));
	QFile file(fileName);
	bool isOpen = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (isOpen == true) {
		NShape *last = this->editor->sheetManager->GetTitle(this->editor->sheetManager->GetBinderLength() - 1);
		float lastRight = last->GetX() + last->GetWidth();

		DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
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

//FCtrlSKeyAction
FCtrlSKeyAction::FCtrlSKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlSKeyAction::FCtrlSKeyAction(const FCtrlSKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlSKeyAction::~FCtrlSKeyAction() {

}

FCtrlSKeyAction& FCtrlSKeyAction::operator=(const FCtrlSKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlSKeyAction::OnKeyDown() {
	Long current = this->editor->sheetManager->GetBinderCurrent();
	QString fileOpenPath = this->editor->sheetManager->GetFileOpenPath(current);
	if (fileOpenPath.isEmpty()) {
		NShape *canvasTitle = this->editor->sheetManager->GetTitle(current);
		QString fileName;
		QString fileName_(QString::fromLocal8Bit(canvasTitle->GetContents()));
		fileName_.remove(0, 1);

		fileName = QFileDialog::getSaveFileName((QWidget*)this->editor,
			QObject::tr("Save File"),
			fileName_,
			QObject::tr("Text files (*.txt)"));

		QFile file(fileName);
		bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);
		if (isOpen == true) {
			this->editor->sheetManager->ModifyFileOpenPath(fileName);
			(static_cast<DrawingPaper*>(this->editor->windows[0]))->Save(fileName);

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
				editor->windowClose->Move(windowCloseX, windowCloseY);
			}

			canvasTitle->Rewrite(fileName.toLocal8Bit().data());
		}
	}
	else {
		(static_cast<DrawingPaper*>(this->editor->windows[0]))->Save(fileOpenPath);

	}
	QString message = QString::fromLocal8Bit("    저장 성공");
	this->editor->messageStatus->setText(message);
	this->editor->statusBar->repaint();
}

//FCtrlAltSKeyAction
FCtrlAltSKeyAction::FCtrlAltSKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlAltSKeyAction::FCtrlAltSKeyAction(const FCtrlAltSKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlAltSKeyAction::~FCtrlAltSKeyAction() {

}

FCtrlAltSKeyAction& FCtrlAltSKeyAction::operator=(const FCtrlAltSKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlAltSKeyAction::OnKeyDown() {
	Long current = this->editor->sheetManager->GetBinderCurrent();
	NShape *canvasTitle = this->editor->sheetManager->GetTitle(current);
	QString fileName;
	QString fileName_(QString::fromLocal8Bit(canvasTitle->GetContents()));
	fileName_.remove(0, 1);

	fileName = QFileDialog::getSaveFileName((QWidget*)this->editor,
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
			editor->windowClose->Move(windowCloseX, windowCloseY);
		}

		canvasTitle->Rewrite(fileName.toLocal8Bit().data());

		QString message = QString::fromLocal8Bit("    저장 성공");
		this->editor->messageStatus->setText(message);
		this->editor->statusBar->repaint();
	}

}

//FCtrlAltIKeyAction
FCtrlAltIKeyAction::FCtrlAltIKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlAltIKeyAction::FCtrlAltIKeyAction(const FCtrlAltIKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlAltIKeyAction::~FCtrlAltIKeyAction() {

}

FCtrlAltIKeyAction& FCtrlAltIKeyAction::operator=(const FCtrlAltIKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlAltIKeyAction::OnKeyDown() {
	NShape *canvasTitle = this->editor->sheetManager->GetTitle(this->editor->sheetManager->GetBinderCurrent());
	QString fileName;
	QString fileName_(QString::fromLocal8Bit(canvasTitle->GetContents()));
	fileName_.remove(0, 1);

	fileName = QFileDialog::getSaveFileName((QWidget*)this->editor,
		QObject::tr("Save File"),
		fileName_,
		QObject::tr("Image files (*.jpg)"));

	QFile file(fileName);
	bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);
	if (isOpen == true && fileName.length() > 0) {
		NShape *flowChart = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->flowChart->Clone();
		NShape *paper = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->a4Paper->Clone();

		flowChart->UnSelectAll();

		GObject *painter = new QtPainter(paper->GetWidth(), paper->GetHeight());
		DrawVisitor drawVisitor(painter);

		GObject *font = dynamic_cast<DrawingPaper*>(this->editor->windows[0])->painter->CurrentObject("Font");
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

		dynamic_cast<QtPainter*>(painter)->qPixmap->save(fileName, "png");

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

//FCtrlPKeyAction
FCtrlPKeyAction::FCtrlPKeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FCtrlPKeyAction::FCtrlPKeyAction(const FCtrlPKeyAction& source)
	: FlowChartKeyAction(source) {

}

FCtrlPKeyAction::~FCtrlPKeyAction() {

}

FCtrlPKeyAction& FCtrlPKeyAction::operator=(const FCtrlPKeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FCtrlPKeyAction::OnKeyDown() {
	NShape *flowChart = dynamic_cast<DrawingPaper *>(this->editor->windows[0])->flowChart->Clone();
	PreviewForm *previewForm = new PreviewForm(this->editor, flowChart);
	previewForm->show();
}

//FAltF4KeyAction
FAltF4KeyAction::FAltF4KeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FAltF4KeyAction::FAltF4KeyAction(const FAltF4KeyAction& source)
	: FlowChartKeyAction(source) {

}

FAltF4KeyAction::~FAltF4KeyAction() {

}

FAltF4KeyAction& FAltF4KeyAction::operator=(const FAltF4KeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FAltF4KeyAction::OnKeyDown() {
	this->editor->close();
}

//FF2KeyAction
FF2KeyAction::FF2KeyAction(FlowChartEditor *editor)
	: FlowChartKeyAction(editor) {

}

FF2KeyAction::FF2KeyAction(const FF2KeyAction& source)
	: FlowChartKeyAction(source) {

}

FF2KeyAction::~FF2KeyAction() {

}

FF2KeyAction& FF2KeyAction::operator=(const FF2KeyAction& source) {
	FlowChartKeyAction::operator=(source);

	return *this;
}

void FF2KeyAction::OnKeyDown() {
	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	
	NShape *shape;
	float left, top, right, bottom, halfHeight;

	QRectF rect = canvas->frameRect();
	Long positionX = 0;
	Long positionY = 0;
	if (canvas->scrollController != NULL) {
		positionX = canvas->scrollController->GetScroll(1)->value();
		positionY = canvas->scrollController->GetScroll(0)->value();
	}
	NShape *holdA4Paper = canvas->a4Paper->Clone();
	NShape *holdFlowChart = canvas->flowChart->Clone();
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(canvas->zoom);
	holdA4Paper->Accept(zoomVisitor);
	holdFlowChart->Accept(zoomVisitor);

	shape = holdFlowChart->GetAt(canvas->indexOfSelected);

	if (canvas->indexOfSelected != -1 &&
		(shape->GetSymbolID() != ID_TERMINAL && !dynamic_cast<Line*>(shape))) {

		canvas->clearFocus();

		QColor color = shape->GetBackGroundColor();
		canvas->label = Label::Instance(&(shape->GetContents()), color, canvas);

		halfHeight = shape->GetHeight() / 2;
		left = shape->GetX() + halfHeight - positionX;
		top = shape->GetY() + 1 - positionY;
		right = shape->GetX() + shape->GetWidth() - halfHeight + 5 - positionX;
		bottom = shape->GetY() + shape->GetHeight() - 1 - positionY;

		canvas->label->Open(left, top, right - left, bottom - top);
		canvas->label->show();

		Long(*indexes) = new Long[canvas->flowChart->GetLength()];
		indexes[0] = canvas->indexOfSelected;

		canvas->Notify();
		
		shape = canvas->flowChart->GetAt(canvas->indexOfSelected);
		shape->Rewrite(String(""));
		canvas->label->setFocus();

		if (indexes != 0) {
			delete[] indexes;
		}

	}
}