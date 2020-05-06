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
#include "SketchBook.h"
#include "WindowTitle.h"
#include "../GObject/QtPainter.h"
#include "DrawVisitor.h"
#include "VariableList.h"

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
	canvas->mode = DrawingPaper::IDLE;
	canvas->indexOfSelected = -1;

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
		float x = shape->GetX();
		float y = shape->GetY();

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
		float x = shape->GetX();
		float y = shape->GetY();

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
		float x = shape->GetX();
		float y = shape->GetY();

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

		float x = shape->GetX();
		float y = shape->GetY();

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

		NShape *terminal = dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->flowChartTemplate->GetAt(0);
		float x = terminal->GetX() - 5;
		float y = terminal->GetY() - 5;
		float size = 20.0F;
		QColor backgroundColor(235, 235, 235);
		QColor borderColor(0, 0, 0);

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
		NShape *last = this->editor->sketchBook->GetCanvas(this->editor->sketchBook->GetLength() - 1);
		float lastRight = last->GetX() + last->GetWidth();

		DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
		//마지막 캔버스 타이틀의 오른쪽이 윈도우의 오른쪽보다 작을 때만 추가로 열 수 있다.
		if (lastRight + 186 < canvas->x() + canvas->width()) { //186은 캔버스 타이틀의 최소 너비
			//스케치북을 접는다 : 원래 펼쳐져 있던 캔버스의 순서도를 저장한다.
			this->editor->sketchBook->Unfold(canvas->flowChart->Clone(),
				new Memory(*canvas->memoryController->GetUndoMemory()),
				new Memory(*canvas->memoryController->GetRedoMemory()),
				new VariableList(*canvas->variableList));
			//제일 끝에 있는 캔버스 타이틀 뒤에 새로운 캔버스 타이틀 붙이기
			//열기
			(static_cast<DrawingPaper *>(this->editor->windows[0]))->Load(fileName);
			//경로를 포함한 파일이름을 수정해서 딱 파일이름만 남도록 처리
			Long length = fileName.length();
			Long i = length - 1;
			while (i >= 0 && fileName[i] != '/') {
				length--;
				i--;
			}
			QString fileName_ = fileName;
			fileName_.remove(0, length);
			fileName_.remove(fileName_.length() - 4, 4);
			fileName_.insert(0, ' ');
			//파일이름이 10자가 넘으면 한 글자당 width 10씩 늘림
			float width = 186.0F;
			if (fileName_.length() > 10) {
				width = width + (fileName_.length() - 10) * 10;
			}
			//새로운 캔버스 타이틀 만들기
			NShape *canvasTitle = new WindowTitle(last->GetX() + last->GetWidth(), last->GetY(),
				width, last->GetHeight(),
				QColor(235, 235, 235), Qt::SolidLine, QColor(235, 235, 235), fileName_.toLocal8Bit().data());
			NShape *flowChart = canvas->flowChart->Clone();
			//새로운 캔버스 타이틀 맨 뒤에 추가하기
			Long current = this->editor->sketchBook->Add(canvasTitle, flowChart, fileName);

			//스케치북을 펼친다 : 현재 캔버스의 쪽과 캔버스 타이틀 색깔 바꾸기
			this->editor->sketchBook->Fold(QPoint(canvasTitle->GetX(), canvasTitle->GetY()));
			this->editor->sketchBook->Update();
			//캔버스 닫는거 옮기기
			float windowCloseX = canvasTitle->GetX() + canvasTitle->GetWidth() - 26 - 3; //24=사각형길이,3=여유공간
			float windowCloseY = canvasTitle->GetY() + 4;
			editor->windowClose->Move(windowCloseX, windowCloseY);

			//순서도는 Load()에 의해 이미 바뀌어 있음.
			//메모리는 Add에 의해서 비어있는 메모리가 생성되는데 바로 그걸 가져와서 바꿔치기
			Memory *undoMemory = new Memory(*this->editor->sketchBook->GetUndoMemory(current));
			Memory *redoMemory = new Memory(*this->editor->sketchBook->GetRedoMemory(current));
			canvas->memoryController->ChangeMemory(undoMemory, redoMemory);
			//변수 목록은 Load()에 의해 이미 바뀌어 있음.

			canvas->setFocus(); //focus message 찾아서
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
	QString fileOpenPath = this->editor->sketchBook->GetFileOpenPath(this->editor->sketchBook->GetCurrent());
	if (fileOpenPath.isEmpty()) {
		NShape *canvasTitle = this->editor->sketchBook->GetCanvas(this->editor->sketchBook->GetCurrent());
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
			this->editor->sketchBook->ModifyFileOpenPath(fileName);
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
				editor->sketchBook->Arrange((static_cast<DrawingPaper *>(this->editor->windows[0]))->x());
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
	NShape *canvasTitle = this->editor->sketchBook->GetCanvas(this->editor->sketchBook->GetCurrent());
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
		this->editor->sketchBook->ModifyFileOpenPath(fileName);
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
			editor->sketchBook->Arrange((static_cast<DrawingPaper *>(this->editor->windows[0]))->x());
			//캔버스 닫는거 옮기기
			float windowCloseX = canvasTitle->GetX() + canvasTitle->GetWidth() - 26 - 3; //24=사각형길이,3=여유공간
			float windowCloseY = canvasTitle->GetY() + 4;
			editor->windowClose->Move(windowCloseX, windowCloseY);
		}

		canvasTitle->Rewrite(fileName.toLocal8Bit().data());
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
	NShape *canvasTitle = this->editor->sketchBook->GetCanvas(this->editor->sketchBook->GetCurrent());
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
	//아직
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