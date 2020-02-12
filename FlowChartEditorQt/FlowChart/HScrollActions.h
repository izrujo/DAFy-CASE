#ifndef _HSCROLLACTIONS_H
#define _HSCROLLACTIONS_H

#include <afxwin.h>

class DrawingPaper;
class HScrollAction {
public:
	HScrollAction(DrawingPaper *drawingPaper = 0);
	HScrollAction(const HScrollAction& source);
	virtual ~HScrollAction() = 0;
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) = 0;
	HScrollAction& operator=(const HScrollAction& source);
protected:
	DrawingPaper *drawingPaper;
};

class LineLeftAction : public HScrollAction {
public:
	LineLeftAction(DrawingPaper *drawingPaper = 0);
	LineLeftAction(const LineLeftAction& source);
	virtual ~LineLeftAction();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	LineLeftAction& operator=(const LineLeftAction& source);
};

class LineRightAction : public HScrollAction {
public:
	LineRightAction(DrawingPaper *drawingPaper = 0);
	LineRightAction(const LineRightAction& source);
	virtual ~LineRightAction();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	LineRightAction& operator=(const LineRightAction& source);
};

class PageLeftAction : public HScrollAction {
public:
	PageLeftAction(DrawingPaper *drawingPaper = 0);
	PageLeftAction(const PageLeftAction& source);
	virtual ~PageLeftAction();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	PageLeftAction& operator=(const PageLeftAction& source);
};

class PageRightAction : public HScrollAction {
public:
	PageRightAction(DrawingPaper *drawingPaper = 0);
	PageRightAction(const PageRightAction& source);
	virtual ~PageRightAction();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	PageRightAction& operator=(const PageRightAction& source);
};

class ThumbTrackHScrollAction : public HScrollAction {
public:
	ThumbTrackHScrollAction(DrawingPaper *drawingPaper = 0);
	ThumbTrackHScrollAction(const ThumbTrackHScrollAction& source);
	virtual ~ThumbTrackHScrollAction();
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	ThumbTrackHScrollAction& operator=(const ThumbTrackHScrollAction& source);
};

#endif // !_HSCROLLACTIONS_H
