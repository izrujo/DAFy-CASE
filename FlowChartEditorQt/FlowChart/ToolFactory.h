#ifndef _TOOLFACTORY_H
#define _TOOLFACTORY_H

#include "Tool.h"

class DrawingPaper;

class ToolFactory {
public:
	static Tool* Create(DrawingPaper *canvas, QPoint point);

protected:
	ToolFactory();
};

#endif