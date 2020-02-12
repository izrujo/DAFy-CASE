#ifndef _TOOLFACTORY_H
#define _TOOLFACTORY_H

#include <afxwin.h>

class Tool;
class DrawingPaper;

class ToolFactory {
public:
	static Tool* Create(DrawingPaper *canvas, CPoint point);

protected:
	ToolFactory();
};

#endif