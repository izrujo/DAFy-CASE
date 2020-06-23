#ifndef _PEN_H
#define _PEN_H

#include "GObject.h"

class Pen : public GObject {
public:
	Pen();
	Pen(const Pen& source);
	virtual ~Pen() = 0;
	Pen& operator=(const Pen& source);

	virtual void SetObject(QPainter *qPainter);

	virtual string GetIdentify();
};

#endif //_PEN_H