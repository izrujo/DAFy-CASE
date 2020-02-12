/* **********************************************************************
 그리기, 이동하기, 크기조정하기같은 기능을 수행하는 도구
 State Pattern
 Singleton Pattern
 *************************************************************************/
#ifndef _TOOL_H
#define _TOOL_H

#include <afxwin.h>

class DrawingPaper;

typedef signed long int Long;

class Tool {
public:
	static Tool* Instance();

	void IterationMake(DrawingPaper *canvas);
	void SelectionMake(DrawingPaper *canvas);
	void SequenceMake(DrawingPaper *canvas);

	void MoveMake(DrawingPaper *canvas);
	void SizeMake(DrawingPaper *canvas);
	void IntervalMake(DrawingPaper *canvas);	

	virtual void OnLButtonDown( DrawingPaper *canvas, UINT nFlags, CPoint point ) = 0;
	virtual void OnMouseMove( DrawingPaper *canvas, UINT nFlags, CPoint point ) = 0;
	virtual void OnLButtonUp( DrawingPaper *canvas, UINT nFlags, CPoint point ) = 0;

protected:
	Tool();
};

#endif // _TOOL_H