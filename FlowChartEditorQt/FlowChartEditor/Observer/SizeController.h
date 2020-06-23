#ifndef _SIZECONTROLLER_H
#define _SIZECONTROLLER_H

#include "../../Notepad/Observer/Observer.h"

typedef signed long int Long;
class Label;

class SizeController : public Observer {
public:
	SizeController(Label *label = 0);
	SizeController(const SizeController& source);
	virtual ~SizeController();
	virtual void Update();
	SizeController& operator =(const SizeController& source);
private:
	Label *label;
};

#endif //_SIZECONTROLLER_H