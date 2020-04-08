#ifndef _EXECUTIONS_H
#define _EXECUTIONS_H

#include "Array.h"
#include "Shape.h"

class Execution {
public:
	Execution(Long capacity = 32);
	Execution(const Execution& source);
	virtual ~Execution() = 0;
	Execution& operator=(const Execution& source);

	Long Add(NShape *shape, Long position);
	Long Remove(Long index);

	Long Modify(Long index, Long position);
	
	NShape* GetShape(Long index);
	Long GetPosition(Long index);

	virtual Execution* Clone() = 0;

	Long GetCapacity() const;
	Long GetLength() const;
protected:
	Array<NShape*> shapes;
	Array<Long> positions;
	Long capacity;
	Long length;
};

inline Long Execution::GetCapacity() const {
	return this->capacity;
}
inline Long Execution::GetLength() const {
	return this->length;
}

//AddExecution
class AddExecution : public Execution {
public:
	AddExecution(Long capacity = 32);
	AddExecution(const AddExecution& source);
	virtual ~AddExecution();
	AddExecution& operator=(const AddExecution& source);

	virtual Execution* Clone();
};

//RemoveExecution
class RemoveExecution : public Execution {
public:
	RemoveExecution(Long capacity = 32);
	RemoveExecution(const RemoveExecution& source);
	virtual ~RemoveExecution();
	RemoveExecution& operator=(const RemoveExecution& source);

	virtual Execution* Clone();
};

//OtherExecution
class OtherExecution : public Execution {
public:
	OtherExecution(Long capacity = 32);
	OtherExecution(const OtherExecution& source);
	virtual ~OtherExecution();
	OtherExecution& operator=(const OtherExecution& source);

	virtual Execution* Clone();
};

#endif //_EXECUTIONS_H