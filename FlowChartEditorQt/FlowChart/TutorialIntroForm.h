#ifndef _TUTORIALINTROFORM_H
#define _TUTORIALINTROFORM_H

#include <afxwin.h>

class TextRegion;
class Painter;
class FlowChartFont;

class TutorialIntroForm : public CFrameWnd {
public:
	TutorialIntroForm();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
protected:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()
public:
	TextRegion *message;
	TextRegion *guide;
	Painter *painter;
	FlowChartFont *font;
};

#endif //_TUTORIALFORM_H
