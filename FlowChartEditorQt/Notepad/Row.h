#ifndef _ROW_H
#define _ROW_H

#include "Composite.h"
#include <string>

typedef signed long int Long;
using namespace std;

class Glyph;
class Row : public Composite {
public:
	Row(Long capacity = 256);
	Row(const Row& source);
	virtual ~Row();

	virtual Glyph* Divide(Long index);
	virtual Glyph* Combine(Glyph *other);

	virtual Long MovePreviousWord();
	virtual Long MoveNextWord();

	Row& operator =(const Row& source);

	virtual string GetContent();
	virtual Glyph* Clone();
};

#endif //_ROW_H