#ifndef _FLOWCHARTKEYACTIONS_H
#define _FLOWCHARTKEYACTIONS_H

#define MOVEDISTANCE 5
class FlowChartEditor;

class FlowChartKeyAction {
public:
	FlowChartKeyAction(FlowChartEditor *editor = 0);
	FlowChartKeyAction(const FlowChartKeyAction& source);
	virtual	~FlowChartKeyAction() = 0;
	FlowChartKeyAction& operator=(const FlowChartKeyAction& source);

	virtual void OnKeyDown() = 0;
protected:
	FlowChartEditor *editor;
};

//FDeleteKeyAction
class FDeleteKeyAction : public FlowChartKeyAction {
public:
	FDeleteKeyAction(FlowChartEditor *editor = 0);
	FDeleteKeyAction(const FDeleteKeyAction& source);
	virtual	~FDeleteKeyAction();
	FDeleteKeyAction& operator=(const FDeleteKeyAction& source);

	virtual void OnKeyDown();
};

//FEscapeKeyAction
class FEscapeKeyAction : public FlowChartKeyAction {
public:
	FEscapeKeyAction(FlowChartEditor *editor = 0);
	FEscapeKeyAction(const FEscapeKeyAction& source);
	virtual	~FEscapeKeyAction();
	FEscapeKeyAction& operator=(const FEscapeKeyAction& source);

	virtual void OnKeyDown();
};

//FLeftKeyAction
class FLeftKeyAction : public FlowChartKeyAction {
public:
	FLeftKeyAction(FlowChartEditor *editor = 0);
	FLeftKeyAction(const FLeftKeyAction& source);
	virtual	~FLeftKeyAction();
	FLeftKeyAction& operator=(const FLeftKeyAction& source);

	virtual void OnKeyDown();
};

//FRightKeyAction
class FRightKeyAction : public FlowChartKeyAction {
public:
	FRightKeyAction(FlowChartEditor *editor = 0);
	FRightKeyAction(const FRightKeyAction& source);
	virtual	~FRightKeyAction();
	FRightKeyAction& operator=(const FRightKeyAction& source);

	virtual void OnKeyDown();
};

//FUpKeyAction
class FUpKeyAction : public FlowChartKeyAction {
public:
	FUpKeyAction(FlowChartEditor *editor = 0);
	FUpKeyAction(const FUpKeyAction& source);
	virtual	~FUpKeyAction();
	FUpKeyAction& operator=(const FUpKeyAction& source);

	virtual void OnKeyDown();
};

//FDownKeyAction
class FDownKeyAction : public FlowChartKeyAction {
public:
	FDownKeyAction(FlowChartEditor *editor = 0);
	FDownKeyAction(const FDownKeyAction& source);
	virtual	~FDownKeyAction();
	FDownKeyAction& operator=(const FDownKeyAction& source);

	virtual void OnKeyDown();
};

//FCtrlDKeyAction
class FCtrlDKeyAction : public FlowChartKeyAction {
public:
	FCtrlDKeyAction(FlowChartEditor *editor = 0);
	FCtrlDKeyAction(const FCtrlDKeyAction& source);
	virtual	~FCtrlDKeyAction();
	FCtrlDKeyAction& operator=(const FCtrlDKeyAction& source);

	virtual void OnKeyDown();
};

//FOneKeyAction
class FOneKeyAction : public FlowChartKeyAction {
public:
	FOneKeyAction(FlowChartEditor *editor = 0);
	FOneKeyAction(const FOneKeyAction& source);
	virtual	~FOneKeyAction();
	FOneKeyAction& operator=(const FOneKeyAction& source);

	virtual void OnKeyDown();
};

//FTwoKeyAction
class FTwoKeyAction : public FlowChartKeyAction {
public:
	FTwoKeyAction(FlowChartEditor *editor = 0);
	FTwoKeyAction(const FTwoKeyAction& source);
	virtual	~FTwoKeyAction();
	FTwoKeyAction& operator=(const FTwoKeyAction& source);

	virtual void OnKeyDown();
};

//FThreeKeyAction
class FThreeKeyAction : public FlowChartKeyAction {
public:
	FThreeKeyAction(FlowChartEditor *editor = 0);
	FThreeKeyAction(const FThreeKeyAction& source);
	virtual	~FThreeKeyAction();
	FThreeKeyAction& operator=(const FThreeKeyAction& source);

	virtual void OnKeyDown();
};

//FFourKeyAction
class FFourKeyAction : public FlowChartKeyAction {
public:
	FFourKeyAction(FlowChartEditor *editor = 0);
	FFourKeyAction(const FFourKeyAction& source);
	virtual	~FFourKeyAction();
	FFourKeyAction& operator=(const FFourKeyAction& source);

	virtual void OnKeyDown();
};

//FFiveKeyAction
class FFiveKeyAction : public FlowChartKeyAction {
public:
	FFiveKeyAction(FlowChartEditor *editor = 0);
	FFiveKeyAction(const FFiveKeyAction& source);
	virtual	~FFiveKeyAction();
	FFiveKeyAction& operator=(const FFiveKeyAction& source);

	virtual void OnKeyDown();
};

//FSixKeyAction
class FSixKeyAction : public FlowChartKeyAction {
public:
	FSixKeyAction(FlowChartEditor *editor = 0);
	FSixKeyAction(const FSixKeyAction& source);
	virtual	~FSixKeyAction();
	FSixKeyAction& operator=(const FSixKeyAction& source);

	virtual void OnKeyDown();
};

//FSevenKeyAction
class FSevenKeyAction : public FlowChartKeyAction {
public:
	FSevenKeyAction(FlowChartEditor *editor = 0);
	FSevenKeyAction(const FSevenKeyAction& source);
	virtual	~FSevenKeyAction();
	FSevenKeyAction& operator=(const FSevenKeyAction& source);

	virtual void OnKeyDown();
};

//FCtrlPlusKeyAction
class FCtrlPlusKeyAction : public FlowChartKeyAction {
public:
	FCtrlPlusKeyAction(FlowChartEditor *editor = 0);
	FCtrlPlusKeyAction(const FCtrlPlusKeyAction& source);
	virtual	~FCtrlPlusKeyAction();
	FCtrlPlusKeyAction& operator=(const FCtrlPlusKeyAction& source);

	virtual void OnKeyDown();
};

//FCtrlMinusKeyAction
class FCtrlMinusKeyAction : public FlowChartKeyAction {
public:
	FCtrlMinusKeyAction(FlowChartEditor *editor = 0);
	FCtrlMinusKeyAction(const FCtrlMinusKeyAction& source);
	virtual	~FCtrlMinusKeyAction();
	FCtrlMinusKeyAction& operator=(const FCtrlMinusKeyAction& source);

	virtual void OnKeyDown();
};

//FCtrlAKeyAction
class FCtrlAKeyAction : public FlowChartKeyAction {
public:
	FCtrlAKeyAction(FlowChartEditor *editor = 0);
	FCtrlAKeyAction(const FCtrlAKeyAction& source);
	virtual	~FCtrlAKeyAction();
	FCtrlAKeyAction& operator=(const FCtrlAKeyAction& source);

	virtual void OnKeyDown();
};

//FCtrlCKeyAction
class FCtrlCKeyAction : public FlowChartKeyAction {
public:
	FCtrlCKeyAction(FlowChartEditor *editor = 0);
	FCtrlCKeyAction(const FCtrlCKeyAction& source);
	virtual	~FCtrlCKeyAction();
	FCtrlCKeyAction& operator=(const FCtrlCKeyAction& source);

	virtual void OnKeyDown();
};

//FCtrlVKeyAction
class FCtrlVKeyAction : public FlowChartKeyAction {
public:
	FCtrlVKeyAction(FlowChartEditor *editor = 0);
	FCtrlVKeyAction(const FCtrlVKeyAction& source);
	virtual	~FCtrlVKeyAction();
	FCtrlVKeyAction& operator=(const FCtrlVKeyAction& source);

	virtual void OnKeyDown();
};

//FCtrlXKeyAction
class FCtrlXKeyAction : public FlowChartKeyAction {
public:
	FCtrlXKeyAction(FlowChartEditor *editor = 0);
	FCtrlXKeyAction(const FCtrlXKeyAction& source);
	virtual	~FCtrlXKeyAction();
	FCtrlXKeyAction& operator=(const FCtrlXKeyAction& source);

	virtual void OnKeyDown();
};

//FCtrlZKeyAction
class FCtrlZKeyAction : public FlowChartKeyAction {
public:
	FCtrlZKeyAction(FlowChartEditor *editor = 0);
	FCtrlZKeyAction(const FCtrlZKeyAction& source);
	virtual	~FCtrlZKeyAction();
	FCtrlZKeyAction& operator=(const FCtrlZKeyAction& source);

	virtual void OnKeyDown();
};

//FCtrlYKeyAction
class FCtrlYKeyAction : public FlowChartKeyAction {
public:
	FCtrlYKeyAction(FlowChartEditor *editor = 0);
	FCtrlYKeyAction(const FCtrlYKeyAction& source);
	virtual	~FCtrlYKeyAction();
	FCtrlYKeyAction& operator=(const FCtrlYKeyAction& source);

	virtual void OnKeyDown();
};
#endif //_FLOWCHARTKEYACTIONS_H