#ifndef _PREVIEWFORM_H
#define _PREVIEWFORM_H

#include <afxwin.h>
#include <afxext.h>
class FlowChartEditor;
class Shape;
class Painter;
class FlowChartFont;

class PreviewForm : public CFrameWnd {
public:
	PreviewForm(FlowChartEditor *editor=0, Shape *flowChart = 0);
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCommandRange(UINT uID);
	DECLARE_MESSAGE_MAP()
public:
	FlowChartEditor *editor;
	Shape *flowChart;
	Shape *a4Paper;
	Painter *painter;
	FlowChartFont *font;
	CToolBar toolBar;
};

#endif //_PREVIEWFORM_H