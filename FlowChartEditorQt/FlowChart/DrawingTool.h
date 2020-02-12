#ifndef _DRAWINGTOOL_H
#define _DRAWINGTOOL_H

#include "Tool.h"

class DrawingTool : public Tool {
public:
	static DrawingTool* Instance();

	static void Destroy();

	virtual void OnLButtonDown( DrawingPaper *canvas, UINT nFlags, CPoint point );
	virtual void OnMouseMove( DrawingPaper *canvas, UINT nFlags, CPoint point );
	virtual void OnLButtonUp( DrawingPaper *canvas, UINT nFlags, CPoint point );

protected:
	DrawingTool();

private:
	static DrawingTool *instance;
};

#endif // _DRAWINGTOOL_H