#include "FlowChartKeyActionFactory.h"
#include "FlowChartKeyActions.h"
#include "DrawingPaper.h"
#include "../FlowChartEditor.h"

#include <qevent.h>

FlowChartKeyActionFactory::FlowChartKeyActionFactory(FlowChartEditor *editor) {
	this->editor = editor;
}

FlowChartKeyActionFactory::FlowChartKeyActionFactory(const FlowChartKeyActionFactory& source) {
	this->editor = source.editor;
}

FlowChartKeyActionFactory::~FlowChartKeyActionFactory() {

}

FlowChartKeyActionFactory& FlowChartKeyActionFactory::operator=(const FlowChartKeyActionFactory& source) {
	this->editor = source.editor;

	return *this;
}

FlowChartKeyAction* FlowChartKeyActionFactory::Make(int modifiers, int key) {
	FlowChartKeyAction* keyAction = 0;

	bool isCtrl = false;
	if (modifiers == Qt::ControlModifier) {
		isCtrl = true;
	}

	if (isCtrl && key == Qt::Key_D) { //Ctrl + D
		keyAction = new CtrlDKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_Plus) {
		keyAction = new CtrlPlusKeyAction(this->editor);
	}
	else if (isCtrl&& key == Qt::Key_Minus) {
		keyAction = new CtrlMinusKeyAction(this->editor);
	}
	else if (key == Qt::Key_Delete) {
		keyAction = new DeleteKeyAction(this->editor);
		static_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::IDLE;
		static_cast<DrawingPaper*>(this->editor->windows[0])->indexOfSelected = -1;
	}
	else if (key == Qt::Key_Escape) {
		keyAction = new EscapeKeyAction(this->editor);
	}
	else if (key == Qt::Key_Left) {
		keyAction = new LeftKeyAction(this->editor);
	}
	else if (key == Qt::Key_Right) {
		keyAction = new RightKeyAction(this->editor);
	}
	else if (key == Qt::Key_Up) {
		keyAction = new UpKeyAction(this->editor);
	}
	else if (key == Qt::Key_Down) {
		keyAction = new DownKeyAction(this->editor);
	}
	else if (key == Qt::Key_1) { //1
		keyAction = new OneKeyAction(this->editor);
	}
	else if (key == Qt::Key_2) { //2
		keyAction = new TwoKeyAction(this->editor);
	}
	else if (key == Qt::Key_3) { //3
		keyAction = new ThreeKeyAction(this->editor);
	}
	else if (key == Qt::Key_4) { //4
		keyAction = new FourKeyAction(this->editor);
	}
	else if (key == Qt::Key_5) { //5
		keyAction = new FiveKeyAction(this->editor);
	}
	else if (key == Qt::Key_6) { //6
		keyAction = new SixKeyAction(this->editor);
	}
	else if (key == Qt::Key_7) { //7
		keyAction = new SevenKeyAction(this->editor);
	}

	return keyAction;
}