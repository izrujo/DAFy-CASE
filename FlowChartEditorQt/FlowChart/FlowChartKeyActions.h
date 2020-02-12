#ifndef _FLOWCHARTKEYACTIONS_H
#define _FLOWCHARTKEYACTIONS_H

#include <afxwin.h>
class FlowChartEditor;

class FlowChartKeyAction {
public:
	FlowChartKeyAction(FlowChartEditor *editor = 0);
	FlowChartKeyAction(const FlowChartKeyAction& source);
	virtual	~FlowChartKeyAction() = 0;
	FlowChartKeyAction& operator=(const FlowChartKeyAction& source);

	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
protected:
	FlowChartEditor *editor;
};

//CtrlDKeyAction
class CtrlDKeyAction : public FlowChartKeyAction {
public:
	CtrlDKeyAction(FlowChartEditor *editor = 0);
	CtrlDKeyAction(const CtrlDKeyAction& source);
	virtual	~CtrlDKeyAction();
	CtrlDKeyAction& operator=(const CtrlDKeyAction& source);

	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

//OneKeyAction
class OneKeyAction : public FlowChartKeyAction {
public:
	OneKeyAction(FlowChartEditor *editor = 0);
	OneKeyAction(const OneKeyAction& source);
	virtual	~OneKeyAction();
	OneKeyAction& operator=(const OneKeyAction& source);

	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

//TwoKeyAction
class TwoKeyAction : public FlowChartKeyAction {
public:
	TwoKeyAction(FlowChartEditor *editor = 0);
	TwoKeyAction(const TwoKeyAction& source);
	virtual	~TwoKeyAction();
	TwoKeyAction& operator=(const TwoKeyAction& source);

	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

//ThreeKeyAction
class ThreeKeyAction : public FlowChartKeyAction {
public:
	ThreeKeyAction(FlowChartEditor *editor = 0);
	ThreeKeyAction(const ThreeKeyAction& source);
	virtual	~ThreeKeyAction();
	ThreeKeyAction& operator=(const ThreeKeyAction& source);

	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

//FourKeyAction
class FourKeyAction : public FlowChartKeyAction {
public:
	FourKeyAction(FlowChartEditor *editor = 0);
	FourKeyAction(const FourKeyAction& source);
	virtual	~FourKeyAction();
	FourKeyAction& operator=(const FourKeyAction& source);

	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

//FiveKeyAction
class FiveKeyAction : public FlowChartKeyAction {
public:
	FiveKeyAction(FlowChartEditor *editor = 0);
	FiveKeyAction(const FiveKeyAction& source);
	virtual	~FiveKeyAction();
	FiveKeyAction& operator=(const FiveKeyAction& source);

	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

//SixKeyAction
class SixKeyAction : public FlowChartKeyAction {
public:
	SixKeyAction(FlowChartEditor *editor = 0);
	SixKeyAction(const SixKeyAction& source);
	virtual	~SixKeyAction();
	SixKeyAction& operator=(const SixKeyAction& source);

	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

//SevenKeyAction
class SevenKeyAction : public FlowChartKeyAction {
public:
	SevenKeyAction(FlowChartEditor *editor = 0);
	SevenKeyAction(const SevenKeyAction& source);
	virtual	~SevenKeyAction();
	SevenKeyAction& operator=(const SevenKeyAction& source);

	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

//CtrlPlusKeyAction
class CtrlPlusKeyAction : public FlowChartKeyAction {
public:
	CtrlPlusKeyAction(FlowChartEditor *editor = 0);
	CtrlPlusKeyAction(const CtrlPlusKeyAction& source);
	virtual	~CtrlPlusKeyAction();
	CtrlPlusKeyAction& operator=(const CtrlPlusKeyAction& source);

	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

//CtrlMinusKeyAction
class CtrlMinusKeyAction : public FlowChartKeyAction {
public:
	CtrlMinusKeyAction(FlowChartEditor *editor = 0);
	CtrlMinusKeyAction(const CtrlMinusKeyAction& source);
	virtual	~CtrlMinusKeyAction();
	CtrlMinusKeyAction& operator=(const CtrlMinusKeyAction& source);

	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif //_FLOWCHARTKEYACTIONS_H