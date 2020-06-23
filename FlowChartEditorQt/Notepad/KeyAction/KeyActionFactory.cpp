#include "KeyActionFactory.h"
#include "KeyActions.h"
#include "../Interface/Notepad.h"
#include <windows.h>

#include <qevent.h>

KeyActionFactory::KeyActionFactory(Notepad *notepad) {
	this->notepad = notepad;
}

KeyActionFactory::~KeyActionFactory() {

}

KeyAction* KeyActionFactory::Make(int key) {
	KeyAction* keyAction = 0;
	
	SHORT isCtrl = GetKeyState(VK_CONTROL) & 0X8000;
	SHORT isShift = GetKeyState(VK_SHIFT) & 0X8000;

	//Shift + Ctrl + KEY
	if (isShift && isCtrl && key == Qt::Key_Left) {
		keyAction = new ShiftCtrlLeftKeyAction(this->notepad);
	}
	else if (isShift && isCtrl && key == Qt::Key_Right) {
		keyAction = new ShiftCtrlRightKeyAction(this->notepad);
	}
	else if (isShift && isCtrl && key == Qt::Key_Home) {
		keyAction = new ShiftCtrlHomeKeyAction(this->notepad);
	}
	else if (isShift && isCtrl && key == Qt::Key_End) {
		keyAction = new ShiftCtrlEndKeyAction(this->notepad);
	}
	//Shift + KEY
	else if (isShift && key == Qt::Key_Left) {
		keyAction = new ShiftLeftKeyAction(this->notepad);
	}
	else if (isShift && key == Qt::Key_Right) {
		keyAction = new ShiftRightKeyAction(this->notepad);
	}
	else if (isShift && key == Qt::Key_Up) {
		keyAction = new ShiftUpKeyAction(this->notepad);
	}
	else if (isShift && key == Qt::Key_Down) {
		keyAction = new ShiftDownKeyAction(this->notepad);
	}
	else if (isShift && key == Qt::Key_Home) {
		keyAction = new ShiftHomeKeyAction(this->notepad);
	}
	else if (isShift && key == Qt::Key_End) {
		keyAction = new ShiftEndKeyAction(this->notepad);
	}
	//Ctrl + KEY
	else if (isCtrl && key == Qt::Key_Left) {
		keyAction = new CtrlLeftKeyAction(this->notepad);
	}
	else if (isCtrl && key == Qt::Key_Right) {
		keyAction = new CtrlRightKeyAction(this->notepad);
	}
	else if (isCtrl && key == Qt::Key_Home) {
		keyAction = new CtrlHomeKeyAction(this->notepad);
	}
	else if (isCtrl && key == Qt::Key_End) {
		keyAction = new CtrlEndKeyAction(this->notepad);
	}
	else if (isCtrl && key == Qt::Key_A) {
		keyAction = new CtrlAKeyAction(this->notepad);
	}
	else if (isCtrl && key == Qt::Key_C) {
		keyAction = new CtrlCKeyAction(this->notepad);
	}
	else if (isCtrl && key == Qt::Key_V) {
		keyAction = new CtrlVKeyAction(this->notepad);
	}
	else if (isCtrl && key == Qt::Key_X) {
		keyAction = new CtrlXKeyAction(this->notepad);
	}
	//KEY
	else if (key == Qt::Key_Left) {
		keyAction = new LeftKeyAction(this->notepad);
	}
	else if (key == Qt::Key_Right) {
		keyAction = new RightKeyAction(this->notepad);
	}
	else if (key == Qt::Key_Up) {
		keyAction = new UpKeyAction(this->notepad);
	}
	else if (key == Qt::Key_Down) {
		keyAction = new DownKeyAction(this->notepad);
	}
	else if (key == Qt::Key_Home) {
		keyAction = new HomeKeyAction(this->notepad);
	}
	else if (key == Qt::Key_End) {
		keyAction = new EndKeyAction(this->notepad);
	}
	else if (key == Qt::Key_Delete) {
		keyAction = new DeleteKeyAction(this->notepad);
	}
	else if (key == Qt::Key_Backspace) {
		keyAction = new BackSpaceKeyAction(this->notepad);
	}

	return keyAction;
}
