#ifndef _HISTORYS_H
#define _HISTORYS_H

#include "Array.h"
#include "Shape.h"

class History {
public:
	History(Long capacity = 32);
	History(const History& source);
	virtual ~History() = 0;
	History& operator=(const History& source);

	Long Add(NShape *shape);
	Long Remove(Long index);
	Long Modify(Long index, NShape *shape);
	
	NShape* GetShape(Long index);

	virtual History* Clone() = 0;

	Long GetCapacity() const;
	Long GetLength() const;
protected:
	Array<NShape*> shapes;
	Long capacity;
	Long length;
};

inline Long History::GetCapacity() const {
	return this->capacity;
}
inline Long History::GetLength() const {
	return this->length;
}

//AddHistory
class AddHistory : public History {
public:
	AddHistory(Long capacity = 32);
	AddHistory(const AddHistory& source);
	virtual ~AddHistory();
	AddHistory& operator=(const AddHistory& source);

	virtual History* Clone();
};

//RemoveHistory
class RemoveHistory : public History {
public:
	RemoveHistory(Long capacity = 32);
	RemoveHistory(const RemoveHistory& source);
	virtual ~RemoveHistory();
	RemoveHistory& operator=(const RemoveHistory& source);

	virtual History* Clone();
};

//OtherHistory
class OtherHistory : public History {
public:
	OtherHistory(Long capacity = 32);
	OtherHistory(const OtherHistory& source);
	virtual ~OtherHistory();
	OtherHistory& operator=(const OtherHistory& source);

	virtual History* Clone();
};

#endif //_HISTORYS_H