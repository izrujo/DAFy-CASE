#ifndef _DRAWINGTOOL_H
#define _DRAWINGTOOL_H

#include "Tool.h"

class DrawingTool : public Tool {
public:
	static DrawingTool* Instance();

	static void Destroy();

	virtual void OnLButtonDown(DrawingPaper *canvas, QPoint point);
	virtual void OnMouseMove(DrawingPaper *canvas, QPoint point);
	virtual void OnLButtonUp(DrawingPaper *canvas, QPoint point);

protected:
	DrawingTool();

private:
	static DrawingTool *instance;
};

#endif // _DRAWINGTOOL_H