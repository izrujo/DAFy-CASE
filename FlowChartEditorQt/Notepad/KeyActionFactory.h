#ifndef KEYACTIONFACTORY_H
#define KEYACTIONFACTORY_H

#include <afxwin.h>

class KeyAction;
class NotepadForm;
class KeyActionFactory {
public:
	KeyActionFactory(NotepadForm *notepadForm = 0);
	~KeyActionFactory();
	KeyAction* Make(UINT nChar);
private:
	NotepadForm *notepadForm;
};

#endif // !KEYACTIONFACTORY_H
