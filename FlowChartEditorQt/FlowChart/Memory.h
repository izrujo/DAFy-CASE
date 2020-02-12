#ifndef _MEMORY_H
#define _MEMORY_H

#include "Array.h"
class Execution;
class Shape;

class Memory {
public:
	Memory(Long capacity = 20);
	Memory(const Memory& source);
	~Memory();
	Memory& operator=(const Memory& source);

	Long Add(Execution *execution);
	Long Remove(Long index);
	void RemoveAll();

	Execution* GetAt(Long index);

	void Quadrate(Shape *flowChart);

	Long GetCapacity() const;
	Long GetLength() const;
private:
	Array<Execution*> executions;
	Long capacity;
	Long length;
};

inline Long Memory::GetCapacity() const {
	return this->capacity;
}
inline Long Memory::GetLength() const {
	return this->length;
}

#endif //_MEMORY_H