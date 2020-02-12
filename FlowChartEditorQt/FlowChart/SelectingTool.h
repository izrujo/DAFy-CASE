#ifndef _SELECTINGTOOL_H
#define _SELECTINGTOOL_H

#include "Tool.h"

typedef signed long int Long;
class SelectingTool : public Tool {

public:
	static SelectingTool* Instance();

	static void Destroy();

	virtual void OnLButtonDown( DrawingPaper *canvas, UINT nFlags, CPoint point );
	virtual void OnMouseMove( DrawingPaper *canvas, UINT nFlags, CPoint point );
	virtual void OnLButtonUp( DrawingPaper *canvas, UINT nFlags, CPoint point );

protected:
	SelectingTool();

private:
	static SelectingTool *instance;	
};

#endif //_SELECTINGTOOL_H