#ifndef _MOVINGTOOL_H
#define _MOVINGTOOL_H

#include "Tool.h"

class MovingTool : public Tool {
public:
	static MovingTool* Instance();
	static void Destroy();

	virtual void OnLButtonDown( DrawingPaper *canvas, QPointF point );
	virtual void OnMouseMove( DrawingPaper *canvas, QPointF point );
	virtual void OnLButtonUp( DrawingPaper *canvas, QPointF point );

protected:
	MovingTool();
	~MovingTool();

private:
	static MovingTool *instance;
};

#endif // _MOVINGTOOL_H