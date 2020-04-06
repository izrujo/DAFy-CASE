#ifndef KEYACTIONFACTORY_H
#define KEYACTIONFACTORY_H

class KeyAction;
class Notepad;
class QKeyEvent;

class KeyActionFactory {
public:
	KeyActionFactory(Notepad *notepad = 0);
	~KeyActionFactory();
	KeyAction* Make(int key);
private:
	Notepad *notepad;
};

#endif // !KEYACTIONFACTORY_H
