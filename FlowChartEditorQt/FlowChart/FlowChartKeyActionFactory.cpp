#include "FlowChartKeyActionFactory.h"
#include "FlowChartKeyActions.h"
#include "DrawingPaper.h"
#include "../FlowChartEditor.h"

#include <qevent.h>

using namespace FlowChartEditorKey;

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

FlowChartEditorKey::KeyAction* FlowChartKeyActionFactory::Make(int modifiers, int key) {
	FlowChartEditorKey::KeyAction* keyAction = 0;

	bool isCtrl = false;
	if (modifiers == Qt::ControlModifier) {
		isCtrl = true;
	}

	if (isCtrl && key == Qt::Key_A) { //Ctrl + A
		keyAction = new FlowChartEditorKey::CtrlAKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_C) { //Ctrl + C
		keyAction = new FlowChartEditorKey::CtrlCKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_V) { //Ctrl + V
		keyAction = new FlowChartEditorKey::CtrlVKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_X) { //Ctrl + X
		keyAction = new FlowChartEditorKey::CtrlXKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_Z) { //Ctrl + Z
		keyAction = new FlowChartEditorKey::CtrlZKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_Y) { //Ctrl + Y
		keyAction = new FlowChartEditorKey::CtrlYKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_D) { //Ctrl + D
		keyAction = new FlowChartEditorKey::CtrlDKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_Plus) {
		keyAction = new FlowChartEditorKey::CtrlPlusKeyAction(this->editor);
	}
	else if (isCtrl&& key == Qt::Key_Minus) {
		keyAction = new FlowChartEditorKey::CtrlMinusKeyAction(this->editor);
	}
	else if (key == Qt::Key_Delete) {
		keyAction = new FlowChartEditorKey::DeleteKeyAction(this->editor);
		static_cast<DrawingPaper*>(this->editor->windows[0])->mode = DrawingPaper::IDLE;
		static_cast<DrawingPaper*>(this->editor->windows[0])->indexOfSelected = -1;
	}
	else if (key == Qt::Key_Escape) {
		keyAction = new FlowChartEditorKey::EscapeKeyAction(this->editor);
	}
	else if (key == Qt::Key_Left) {
		keyAction = new FlowChartEditorKey::LeftKeyAction(this->editor);
	}
	else if (key == Qt::Key_Right) {
		keyAction = new FlowChartEditorKey::RightKeyAction(this->editor);
	}
	else if (key == Qt::Key_Up) {
		keyAction = new FlowChartEditorKey::UpKeyAction(this->editor);
	}
	else if (key == Qt::Key_Down) {
		keyAction = new FlowChartEditorKey::DownKeyAction(this->editor);
	}
	else if (key == Qt::Key_1) { //1
		keyAction = new FlowChartEditorKey::OneKeyAction(this->editor);
	}
	else if (key == Qt::Key_2) { //2
		keyAction = new FlowChartEditorKey::TwoKeyAction(this->editor);
	}
	else if (key == Qt::Key_3) { //3
		keyAction = new FlowChartEditorKey::ThreeKeyAction(this->editor);
	}
	else if (key == Qt::Key_4) { //4
		keyAction = new FlowChartEditorKey::FourKeyAction(this->editor);
	}
	else if (key == Qt::Key_5) { //5
		keyAction = new FlowChartEditorKey::FiveKeyAction(this->editor);
	}
	else if (key == Qt::Key_6) { //6
		keyAction = new FlowChartEditorKey::SixKeyAction(this->editor);
	}
	else if (key == Qt::Key_7) { //7
		keyAction = new FlowChartEditorKey::SevenKeyAction(this->editor);
	}

	return keyAction;
}