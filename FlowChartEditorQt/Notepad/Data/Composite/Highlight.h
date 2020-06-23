#ifndef _HIGHLIGHT_H
#define _HIGHLIGHT_H

#include "Composite.h"

class Highlight : public Composite {
public:
	Highlight(Long capacity = 256);
	Highlight(const Highlight& source);
	virtual ~Highlight();

	virtual string GetContent();
	virtual Glyph* Clone();

	Highlight& operator =(const Highlight& source);
};

#endif //_HIGHLIGHT_H