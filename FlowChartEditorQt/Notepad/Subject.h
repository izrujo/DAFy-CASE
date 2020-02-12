#ifndef _SUBJECT_H
#define _SUBJECT_H

#include "Array.h"

typedef signed long int Long;
class Observer;
class Subject {
public:
	Subject(Long capacity = 256);
	Subject(const Subject& source);
	virtual ~Subject();
	virtual Long AttachObserver(Observer *observer);
	virtual Long DetachObserver(Observer *observer);
	virtual void Notify();
	Observer* GetAt(Long index);
	Subject& operator =(const Subject& source);

	Long GetCapacity() const;
	Long GetLength() const;
private:
	Array<Observer*> observers;
	Long capacity;
	Long length;
};
inline Long Subject::GetCapacity() const {
	return this->capacity;
}
inline Long Subject::GetLength() const {
	return this->length;
}
int CompareObserverLinks(void *one, void *other);

#endif //_SUBJECT_H