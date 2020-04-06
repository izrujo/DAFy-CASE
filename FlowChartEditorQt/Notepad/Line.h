#ifndef _LINE_H
#define _LINE_H

#include "Composite.h"
#include <string>

typedef signed long int Long;
using namespace std;

class Glyph;
class Line : public Composite {
public:
	Line(Long capacity = 256);
	Line(const Line& source);
	virtual ~Line();

	virtual Glyph* Divide(Long index);
	virtual Glyph* Combine(Glyph *other);

	virtual Long MovePreviousWord();
	virtual Long MoveNextWord();

	Line& operator =(const Line& source);

	virtual string GetContent();
	virtual Glyph* Clone();
};

#endif //_LINE_H