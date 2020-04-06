#ifndef _CARETCONTROLLER_H
#define _CARETCONTROLLER_H

#include "Observer.h"

typedef signed long int Long;
class Notepad;
class Caret;

class CaretController : public Observer {
public:
	CaretController(Notepad *notepad = 0);
	CaretController(const CaretController& source);
	virtual ~CaretController();
	CaretController& operator =(const CaretController& source);
	
	virtual void Update();

	Caret* GetCaret() const;
private:
	Notepad *notepad;
	Caret *caret;
};

inline Caret* CaretController::GetCaret() const {
	return this->caret;
}

#endif //_CARETCONTROLLER_H