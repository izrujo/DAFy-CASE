#ifndef _VARIABLELIST_H
#define _VARIABLELIST_H

#include "Array.h"
#include "String.h"

class VariableList {
public:
	VariableList(Long capacity = 10);
	VariableList(const VariableList& source);
	~VariableList();
	VariableList& operator=(const VariableList& source);

	Long Add(String contents); //기호의 내용을 입력받아 해당 기호의 변수 목록을 만드는 연산
	Long Find(String contents);
	void SetKeywords();

	String& GetAt(Long index);
	Long GetCapacity() const;
	Long GetLength() const;
private:
	Array<String> variables;
	Long capacity;
	Long length;
};

inline Long VariableList::GetCapacity() const {
	return this->capacity;
}
inline Long VariableList::GetLength() const {
	return this->length;
}

#endif //_VARIABLELIST_H