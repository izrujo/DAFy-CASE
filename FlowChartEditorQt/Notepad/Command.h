#ifndef _COMMAND_H
#define _COMMAND_H

typedef signed long int Long;
class Notepad;
class Command {
public:
	Command(Notepad *notepad = 0);
	Command(const Command& source);
	virtual ~Command() = 0;
	virtual void Execute() = 0;
	Command& operator =(const Command& source);
protected:
	Notepad *notepad;
};

#endif //_COMMAND_H