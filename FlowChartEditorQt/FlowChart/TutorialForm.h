#ifndef _TUTORIALFORM_H
#define _TUTORIALFORM_H

#include <afxwin.h>
#include "Array.h"

class Template;
class Painter;
class FlowChart;
class FlowChartFont;
class TextRegion;
class Tutorial;
class TutorialMark;
class TutorialController;

class TutorialForm : public CFrameWnd {
public:
	TutorialForm();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	DECLARE_MESSAGE_MAP()
public:
	Template *lists;
	Painter *painter;
	FlowChart *sample;
	FlowChartFont *font;
	Tutorial *main;
	TutorialMark *current;
	Tutorial *lastConcrete;
	TutorialController *tutorialController;
};

#endif //_TUTORIALFORM_H