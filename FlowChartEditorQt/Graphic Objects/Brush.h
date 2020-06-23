#ifndef _BRUSH_H
#define _BRUSH_H

#include "GObject.h"

class Brush : public GObject {
public:
	Brush();
	Brush(const Brush& source);
	virtual ~Brush() = 0;
	Brush& operator=(const Brush& source);

	virtual void SetObject(QPainter *qPainter);
	
	virtual string GetIdentify();
};

#endif //_BRUSH_H