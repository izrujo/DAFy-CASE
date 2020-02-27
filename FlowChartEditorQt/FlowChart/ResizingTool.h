#ifndef _RESIZINGTOOL_H
#define _RESIZINGTOOL_H

#include "Tool.h"

class ResizingTool : public Tool {
public:
	static ResizingTool* Instance();
	static void Destroy();

	virtual void OnLButtonDown( DrawingPaper *canvas, QPoint point );
	virtual void OnMouseMove( DrawingPaper *canvas, QPoint point );
	virtual void OnLButtonUp( DrawingPaper *canvas, QPoint point );

protected:
	ResizingTool();

private:
	static ResizingTool *instance;
};

#endif // _RESIZINGTOOL_H