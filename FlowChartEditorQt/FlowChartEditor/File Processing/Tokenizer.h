// Tokenizer.h

#ifndef _TOKENIZER_H
#define _TOKENIZER_H

#include "../../Utilities/Array.h"
#include "../../Utilities/String.h"

typedef signed long int Long;

class Tokenizer{
public:
	Tokenizer();
	~Tokenizer();
	void Scan(char (*line), char delimiter);
	String& GetAt(Long index);
	Long GetCapacity() const;
	Long GetLength() const;
private:
	Array<String> tokens;
	Long capacity;
	Long length;
};

inline Long Tokenizer::GetCapacity() const{
	return this->capacity;
}

inline Long Tokenizer::GetLength() const{
	return this->length;
}

#endif //_TOKENIZER_H