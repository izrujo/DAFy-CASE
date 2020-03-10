#ifndef _FLOWCHARTKEYACTIONS_H
#define _FLOWCHARTKEYACTIONS_H

#define DISTANCE 5
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

//DeleteKeyAction
class DeleteKeyAction : public FlowChartKeyAction {
public:
	DeleteKeyAction(FlowChartEditor *editor = 0);
	DeleteKeyAction(const DeleteKeyAction& source);
	virtual	~DeleteKeyAction();
	DeleteKeyAction& operator=(const DeleteKeyAction& source);

	virtual void OnKeyDown();
};

//EscapeKeyAction
class EscapeKeyAction : public FlowChartKeyAction {
public:
	EscapeKeyAction(FlowChartEditor *editor = 0);
	EscapeKeyAction(const EscapeKeyAction& source);
	virtual	~EscapeKeyAction();
	EscapeKeyAction& operator=(const EscapeKeyAction& source);

	virtual void OnKeyDown();
};

//LeftKeyAction
class LeftKeyAction : public FlowChartKeyAction {
public:
	LeftKeyAction(FlowChartEditor *editor = 0);
	LeftKeyAction(const LeftKeyAction& source);
	virtual	~LeftKeyAction();
	LeftKeyAction& operator=(const LeftKeyAction& source);

	virtual void OnKeyDown();
};

//RightKeyAction
class RightKeyAction : public FlowChartKeyAction {
public:
	RightKeyAction(FlowChartEditor *editor = 0);
	RightKeyAction(const RightKeyAction& source);
	virtual	~RightKeyAction();
	RightKeyAction& operator=(const RightKeyAction& source);

	virtual void OnKeyDown();
};

//UpKeyAction
class UpKeyAction : public FlowChartKeyAction {
public:
	UpKeyAction(FlowChartEditor *editor = 0);
	UpKeyAction(const UpKeyAction& source);
	virtual	~UpKeyAction();
	UpKeyAction& operator=(const UpKeyAction& source);

	virtual void OnKeyDown();
};

//DownKeyAction
class DownKeyAction : public FlowChartKeyAction {
public:
	DownKeyAction(FlowChartEditor *editor = 0);
	DownKeyAction(const DownKeyAction& source);
	virtual	~DownKeyAction();
	DownKeyAction& operator=(const DownKeyAction& source);

	virtual void OnKeyDown();
};

//CtrlDKeyAction
class CtrlDKeyAction : public FlowChartKeyAction {
public:
	CtrlDKeyAction(FlowChartEditor *editor = 0);
	CtrlDKeyAction(const CtrlDKeyAction& source);
	virtual	~CtrlDKeyAction();
	CtrlDKeyAction& operator=(const CtrlDKeyAction& source);

	virtual void OnKeyDown();
};

//OneKeyAction
class OneKeyAction : public FlowChartKeyAction {
public:
	OneKeyAction(FlowChartEditor *editor = 0);
	OneKeyAction(const OneKeyAction& source);
	virtual	~OneKeyAction();
	OneKeyAction& operator=(const OneKeyAction& source);

	virtual void OnKeyDown();
};

//TwoKeyAction
class TwoKeyAction : public FlowChartKeyAction {
public:
	TwoKeyAction(FlowChartEditor *editor = 0);
	TwoKeyAction(const TwoKeyAction& source);
	virtual	~TwoKeyAction();
	TwoKeyAction& operator=(const TwoKeyAction& source);

	virtual void OnKeyDown();
};

//ThreeKeyAction
class ThreeKeyAction : public FlowChartKeyAction {
public:
	ThreeKeyAction(FlowChartEditor *editor = 0);
	ThreeKeyAction(const ThreeKeyAction& source);
	virtual	~ThreeKeyAction();
	ThreeKeyAction& operator=(const ThreeKeyAction& source);

	virtual void OnKeyDown();
};

//FourKeyAction
class FourKeyAction : public FlowChartKeyAction {
public:
	FourKeyAction(FlowChartEditor *editor = 0);
	FourKeyAction(const FourKeyAction& source);
	virtual	~FourKeyAction();
	FourKeyAction& operator=(const FourKeyAction& source);

	virtual void OnKeyDown();
};

//FiveKeyAction
class FiveKeyAction : public FlowChartKeyAction {
public:
	FiveKeyAction(FlowChartEditor *editor = 0);
	FiveKeyAction(const FiveKeyAction& source);
	virtual	~FiveKeyAction();
	FiveKeyAction& operator=(const FiveKeyAction& source);

	virtual void OnKeyDown();
};

//SixKeyAction
class SixKeyAction : public FlowChartKeyAction {
public:
	SixKeyAction(FlowChartEditor *editor = 0);
	SixKeyAction(const SixKeyAction& source);
	virtual	~SixKeyAction();
	SixKeyAction& operator=(const SixKeyAction& source);

	virtual void OnKeyDown();
};

//SevenKeyAction
class SevenKeyAction : public FlowChartKeyAction {
public:
	SevenKeyAction(FlowChartEditor *editor = 0);
	SevenKeyAction(const SevenKeyAction& source);
	virtual	~SevenKeyAction();
	SevenKeyAction& operator=(const SevenKeyAction& source);

	virtual void OnKeyDown();
};

//CtrlPlusKeyAction
class CtrlPlusKeyAction : public FlowChartKeyAction {
public:
	CtrlPlusKeyAction(FlowChartEditor *editor = 0);
	CtrlPlusKeyAction(const CtrlPlusKeyAction& source);
	virtual	~CtrlPlusKeyAction();
	CtrlPlusKeyAction& operator=(const CtrlPlusKeyAction& source);

	virtual void OnKeyDown();
};

//CtrlMinusKeyAction
class CtrlMinusKeyAction : public FlowChartKeyAction {
public:
	CtrlMinusKeyAction(FlowChartEditor *editor = 0);
	CtrlMinusKeyAction(const CtrlMinusKeyAction& source);
	virtual	~CtrlMinusKeyAction();
	CtrlMinusKeyAction& operator=(const CtrlMinusKeyAction& source);

	virtual void OnKeyDown();
};

//CtrlAKeyAction
class CtrlAKeyAction : public FlowChartKeyAction {
public:
	CtrlAKeyAction(FlowChartEditor *editor = 0);
	CtrlAKeyAction(const CtrlAKeyAction& source);
	virtual	~CtrlAKeyAction();
	CtrlAKeyAction& operator=(const CtrlAKeyAction& source);

	virtual void OnKeyDown();
};

//CtrlCKeyAction
class CtrlCKeyAction : public FlowChartKeyAction {
public:
	CtrlCKeyAction(FlowChartEditor *editor = 0);
	CtrlCKeyAction(const CtrlCKeyAction& source);
	virtual	~CtrlCKeyAction();
	CtrlCKeyAction& operator=(const CtrlCKeyAction& source);

	virtual void OnKeyDown();
};

//CtrlVKeyAction
class CtrlVKeyAction : public FlowChartKeyAction {
public:
	CtrlVKeyAction(FlowChartEditor *editor = 0);
	CtrlVKeyAction(const CtrlVKeyAction& source);
	virtual	~CtrlVKeyAction();
	CtrlVKeyAction& operator=(const CtrlVKeyAction& source);

	virtual void OnKeyDown();
};

//CtrlXKeyAction
class CtrlXKeyAction : public FlowChartKeyAction {
public:
	CtrlXKeyAction(FlowChartEditor *editor = 0);
	CtrlXKeyAction(const CtrlXKeyAction& source);
	virtual	~CtrlXKeyAction();
	CtrlXKeyAction& operator=(const CtrlXKeyAction& source);

	virtual void OnKeyDown();
};

//CtrlZKeyAction
class CtrlZKeyAction : public FlowChartKeyAction {
public:
	CtrlZKeyAction(FlowChartEditor *editor = 0);
	CtrlZKeyAction(const CtrlZKeyAction& source);
	virtual	~CtrlZKeyAction();
	CtrlZKeyAction& operator=(const CtrlZKeyAction& source);

	virtual void OnKeyDown();
};

//CtrlYKeyAction
class CtrlYKeyAction : public FlowChartKeyAction {
public:
	CtrlYKeyAction(FlowChartEditor *editor = 0);
	CtrlYKeyAction(const CtrlYKeyAction& source);
	virtual	~CtrlYKeyAction();
	CtrlYKeyAction& operator=(const CtrlYKeyAction& source);

	virtual void OnKeyDown();
};

#endif //_FLOWCHARTKEYACTIONS_H