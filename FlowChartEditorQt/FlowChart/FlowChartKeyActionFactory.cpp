#include "FlowChartKeyActionFactory.h"
#include "FlowChartKeyActions.h"
#include "DrawingPaper.h"
#include "../FlowChartEditor.h"

#include <windows.h>

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

	SHORT isCtrl = GetKeyState(VK_CONTROL) & 0X8000;

	bool isAlt = false;
	if (modifiers == Qt::AltModifier) {
		isAlt = true;
	}

	if (isCtrl && isAlt && key == Qt::Key_S) { //Ctrl + Alt + S
		keyAction = new FCtrlAltSKeyAction(this->editor);
	}
	else if (isCtrl && isAlt && key == Qt::Key_I) { //Ctrl + Alt + I
		keyAction = new FCtrlAltIKeyAction(this->editor);
	}
	else if (isAlt && key == Qt::Key_F4) { //Alt + F4
		keyAction = new FAltF4KeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_A) { //Ctrl + A
		keyAction = new FCtrlAKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_C) { //Ctrl + C
		keyAction = new FCtrlCKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_V) { //Ctrl + V
		keyAction = new FCtrlVKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_X) { //Ctrl + X
		keyAction = new FCtrlXKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_Z) { //Ctrl + Z
		keyAction = new FCtrlZKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_Y) { //Ctrl + Y
		keyAction = new FCtrlYKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_D) { //Ctrl + D
		keyAction = new FCtrlDKeyAction(this->editor);
	}
	else if (isCtrl && (key == Qt::Key_Plus || key == Qt::Key_Equal)) {
		keyAction = new FCtrlPlusKeyAction(this->editor);
	}
	else if (isCtrl&& key == Qt::Key_Minus) {
		keyAction = new FCtrlMinusKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_N) { //Ctrl + N
		keyAction = new FCtrlNKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_O) { //Ctrl + O
		keyAction = new FCtrlOKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_S) { //Ctrl + S
		keyAction = new FCtrlSKeyAction(this->editor);
	}
	else if (isCtrl && key == Qt::Key_P) {
		keyAction = new FCtrlPKeyAction(this->editor);
	}
	else if (key == Qt::Key_Delete) {
		keyAction = new FDeleteKeyAction(this->editor);
	}
	else if (key == Qt::Key_Escape) {
		keyAction = new FEscapeKeyAction(this->editor);
	}
	else if (key == Qt::Key_Left) {
		keyAction = new FLeftKeyAction(this->editor);
	}
	else if (key == Qt::Key_Right) {
		keyAction = new FRightKeyAction(this->editor);
	}
	else if (key == Qt::Key_Up) {
		keyAction = new FUpKeyAction(this->editor);
	}
	else if (key == Qt::Key_Down) {
		keyAction = new FDownKeyAction(this->editor);
	}
	else if (key == Qt::Key_1) { //1
		keyAction = new FOneKeyAction(this->editor);
	}
	else if (key == Qt::Key_2) { //2
		keyAction = new FTwoKeyAction(this->editor);
	}
	else if (key == Qt::Key_3) { //3
		keyAction = new FThreeKeyAction(this->editor);
	}
	else if (key == Qt::Key_4) { //4
		keyAction = new FFourKeyAction(this->editor);
	}
	else if (key == Qt::Key_5) { //5
		keyAction = new FFiveKeyAction(this->editor);
	}
	else if (key == Qt::Key_6) { //6
		keyAction = new FSixKeyAction(this->editor);
	}
	else if (key == Qt::Key_7) { //7
		keyAction = new FSevenKeyAction(this->editor);
	}

	return keyAction;
}