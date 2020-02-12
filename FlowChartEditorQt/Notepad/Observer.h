#ifndef _OBSERVER_H
#define _OBSERVER_H

class Subject;

class Observer {
public:
	Observer();
	Observer(const Observer& source);
	virtual ~Observer() = 0;
	virtual void Update() = 0;
};

#endif //_OBSERVER_H