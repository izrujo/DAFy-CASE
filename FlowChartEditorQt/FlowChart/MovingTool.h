#ifndef _MOVINGTOOL_H
#define _MOVINGTOOL_H

#include "Tool.h"
class FlowChart;

class MovingTool : public Tool {
public:
	static MovingTool* Instance();
	static void Destroy();

	virtual void OnLButtonDown( DrawingPaper *canvas, QPoint point );
	virtual void OnMouseMove( DrawingPaper *canvas, QPoint point );
	virtual void OnLButtonUp( DrawingPaper *canvas, QPoint point );

protected:
	MovingTool();
	~MovingTool();

private:
	static MovingTool *instance;
};

#endif // _MOVINGTOOL_H