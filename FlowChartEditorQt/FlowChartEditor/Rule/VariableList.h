#ifndef _VARIABLELIST_H
#define _VARIABLELIST_H

#include "../../Utilities/Array.h"
#include "../../Utilities/String.h"

class VariableList {
public:
	VariableList(Long capacity = 10);
	VariableList(const VariableList& source);
	~VariableList();
	VariableList& operator=(const VariableList& source);

	Long Add(String contents);
	Long Find(String contents);
	Long Remove(Long index);
	void RemoveAll();

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