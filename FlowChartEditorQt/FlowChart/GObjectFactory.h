#ifndef _GOBJECTFACTORY_H
#define _GOBJECTFACTORY_H

#include <qpen.h>
#include <qbrush.h>
#include <qfont.h>

class GObject;

class GObjectFactory {
public:
	GObjectFactory();
	virtual ~GObjectFactory() = 0;

	virtual GObject* MakePen() = 0;
	virtual GObject* MakeBrush() = 0;
	virtual GObject* MakeFont() = 0;
};

#endif //_GOBJECTFACTORY_H