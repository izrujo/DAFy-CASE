#ifndef _FONTCOMMAND_H
#define _FONTCOMMAND_H

#include "Command.h"
class NotepadForm;

class FontCommand : public Command {
public:
	FontCommand(NotepadForm *notepadForm = 0);
	FontCommand(const FontCommand& source);
	~FontCommand();
	virtual void Execute();

	FontCommand& operator =(const FontCommand& source);
private:
	NotepadForm *notepadForm;
};

#endif //_FONTCOMMAND_H
