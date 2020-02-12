#include "FlowChartKeyActionFactory.h"
#include "FlowChartKeyActions.h"
#include <WinUser.h>

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

FlowChartKeyAction* FlowChartKeyActionFactory::Make(UINT nChar) {
	FlowChartKeyAction* keyAction = 0;

	SHORT isCtrl = GetKeyState(VK_CONTROL) & 0X8000;

	if (isCtrl && nChar == 0x44) { //Ctrl + D
		keyAction = new CtrlDKeyAction(this->editor);
	}
	else if (isCtrl && nChar == VK_OEM_PLUS) {
		keyAction = new CtrlPlusKeyAction(this->editor);
	}
	else if (isCtrl&& nChar == VK_OEM_MINUS) {
		keyAction = new CtrlMinusKeyAction(this->editor);
	}
	else if (nChar == 0x31) { //1
		keyAction = new OneKeyAction(this->editor);
	}
	else if (nChar == 0x32) { //2
		keyAction = new TwoKeyAction(this->editor);
	}
	else if (nChar == 0x33) { //3
		keyAction = new ThreeKeyAction(this->editor);
	}
	else if (nChar == 0x34) { //4
		keyAction = new FourKeyAction(this->editor);
	}
	else if (nChar == 0x35) { //5
		keyAction = new FiveKeyAction(this->editor);
	}
	else if (nChar == 0x36) { //6
		keyAction = new SixKeyAction(this->editor);
	}
	else if (nChar == 0x37) { //7
		keyAction = new SevenKeyAction(this->editor);
	}

	return keyAction;
}