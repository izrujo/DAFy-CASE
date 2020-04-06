#ifndef _PAINTER_H
#define _PAINTER_H

#include "GObject.h"
#include "Array.h"

class Painter : public GObject {
public:
	Painter(Long capacity = 3);
	Painter(const Painter& source);
	virtual ~Painter() = 0;
	Painter& operator=(const Painter& source);

	virtual GObject* SelectObject(const GObject& object);
	virtual GObject* CurrentObject(string identify);
	virtual void Update();

	virtual GObject* GetAt(Long index);
	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
protected:
	Array<GObject*> objects;
	Long capacity;
	Long length;
};

inline Long Painter::GetCapacity() const {
	return this->capacity;
}

inline Long Painter::GetLength() const {
	return this->length;
}

#endif //_PAINTER_H