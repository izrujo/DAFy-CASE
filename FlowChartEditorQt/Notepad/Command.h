#ifndef _COMMAND_H
#define _COMMAND_H

typedef signed long int Long;
class NotepadForm;
class Command {
public:
	Command(NotepadForm *notepadForm = 0);
	Command(const Command& source);
	virtual ~Command() = 0;
	virtual void Execute() = 0;
	Command& operator =(const Command& source);
protected:
	NotepadForm *notepadForm;
};

#endif //_COMMAND_H