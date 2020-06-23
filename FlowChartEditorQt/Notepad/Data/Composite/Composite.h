#ifndef _COMPOSITE_H
#define _COMPOSITE_H

#include "Glyph.h"
#include "../Utilities/Array.h"

class Composite : public Glyph {
public:
	Composite(Long capacity = 256);
	Composite(const Composite& source);
	virtual ~Composite() = 0; //abstract
	
	virtual Long Add(Glyph *glyph);
	virtual Long Add(Long index, Glyph *glyph);
	virtual Long Remove(Long index);
	virtual Glyph* GetAt(Long index);
	virtual Long First();
	virtual Long Last();
	virtual Long Previous();
	virtual Long Next();
	virtual Long Move(Long index);
	
	Composite& operator =(const Composite& source);
	Glyph* operator [](Long index);

	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long GetCurrent() const;
protected:
	Array<Glyph*> glyphs;
	Long capacity;
	Long length;
	Long current;
};

#endif //_COMPOSITE_H