#ifndef _GOBJECT_H
#define _GOBJECT_H

#include <string>

using namespace std;

class QPainter;

class GObject {
public:
	GObject();
	GObject(const GObject& source);
	virtual ~GObject() = 0;
	GObject& operator=(const GObject& source);

	virtual void SetObject(QPainter *qPainter);

	virtual GObject* Clone() = 0;
	virtual string GetIdentify();
};

#endif //_GOBJECT_H