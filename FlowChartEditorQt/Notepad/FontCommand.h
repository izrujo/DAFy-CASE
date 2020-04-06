#ifndef _FONTCOMMAND_H
#define _FONTCOMMAND_H

#include "Command.h"
class Notepad;

class FontCommand : public Command {
public:
	FontCommand(Notepad *notepad = 0);
	FontCommand(const FontCommand& source);
	~FontCommand();
	virtual void Execute();

	FontCommand& operator =(const FontCommand& source);
private:
	Notepad *notepad;
};

#endif //_FONTCOMMAND_H
