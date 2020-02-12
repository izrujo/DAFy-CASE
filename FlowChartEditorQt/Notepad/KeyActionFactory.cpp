#include "KeyActionFactory.h"
#include "KeyActions.h"
#include <WinUser.h>
#include "NotepadForm.h"

KeyActionFactory::KeyActionFactory(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

KeyActionFactory::~KeyActionFactory() {

}

KeyAction* KeyActionFactory::Make(UINT nChar) {
	KeyAction* keyAction = 0;

	SHORT isCtrl = GetKeyState(VK_CONTROL) & 0X8000;
	SHORT isShift = GetKeyState(VK_SHIFT) & 0X8000;

	//Shift + Ctrl + KEY
	if (isShift && isCtrl && nChar == VK_LEFT) {
		keyAction = new ShiftCtrlLeftKeyAction(this->notepadForm);
	}
	else if (isShift && isCtrl && nChar == VK_RIGHT) {
		keyAction = new ShiftCtrlRightKeyAction(this->notepadForm);
	}
	else if (isShift && isCtrl && nChar == VK_HOME) {
		keyAction = new ShiftCtrlHomeKeyAction(this->notepadForm);
	}
	else if (isShift && isCtrl && nChar == VK_END) {
		keyAction = new ShiftCtrlEndKeyAction(this->notepadForm);
	}
	//Shift + KEY
	else if (isShift && nChar == VK_LEFT) {
		keyAction = new ShiftLeftKeyAction(this->notepadForm);
	}
	else if (isShift && nChar == VK_RIGHT) {
		keyAction = new ShiftRightKeyAction(this->notepadForm);
	}
	else if (isShift && nChar == VK_UP) {
		keyAction = new ShiftUpKeyAction(this->notepadForm);
	}
	else if (isShift && nChar == VK_DOWN) {
		keyAction = new ShiftDownKeyAction(this->notepadForm);
	}
	else if (isShift && nChar == VK_HOME) {
		keyAction = new ShiftHomeKeyAction(this->notepadForm);
	}
	else if (isShift && nChar == VK_END) {
		keyAction = new ShiftEndKeyAction(this->notepadForm);
	}
	//Ctrl + KEY
	else if (isCtrl && nChar == VK_LEFT) {
		keyAction = new CtrlLeftKeyAction(this->notepadForm);
	}
	else if (isCtrl && nChar == VK_RIGHT) {
		keyAction = new CtrlRightKeyAction(this->notepadForm);
	}
	else if (isCtrl && nChar == VK_HOME) {
		keyAction = new CtrlHomeKeyAction(this->notepadForm);
	}
	else if (isCtrl && nChar == VK_END) {
		keyAction = new CtrlEndKeyAction(this->notepadForm);
	}
	else if (isCtrl && nChar == 0x41) {
		keyAction = new CtrlAKeyAction(this->notepadForm);
	}
	else if (isCtrl && nChar == 0x43) {
		keyAction = new CtrlCKeyAction(this->notepadForm);
	}
	else if (isCtrl && nChar == 0x56) {
		keyAction = new CtrlVKeyAction(this->notepadForm);
	}
	else if (isCtrl && nChar == 0x58) {
		keyAction = new CtrlXKeyAction(this->notepadForm);
	}
	//KEY
	else if (nChar == VK_LEFT) {
		keyAction = new LeftKeyAction(this->notepadForm);
	}
	else if (nChar == VK_RIGHT) {
		keyAction = new RightKeyAction(this->notepadForm);
	}
	else if (nChar == VK_UP) {
		keyAction = new UpKeyAction(this->notepadForm);
	}
	else if (nChar == VK_DOWN) {
		keyAction = new DownKeyAction(this->notepadForm);
	}
	else if (nChar == VK_HOME) {
		keyAction = new HomeKeyAction(this->notepadForm);
	}
	else if (nChar == VK_END) {
		keyAction = new EndKeyAction(this->notepadForm);
	}
	else if (nChar == VK_DELETE) {
		keyAction = new DeleteKeyAction(this->notepadForm);
	}
	else if (nChar == VK_BACK) {
		keyAction = new BackSpaceKeyAction(this->notepadForm);
	}

	return keyAction;
}