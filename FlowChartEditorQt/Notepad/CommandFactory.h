#ifndef _COMMANDFACTORY_H
#define _COMMANDFACTORY_H

class NotepadForm;
class Command;

class CommandFactory {
public:
	CommandFactory(NotepadForm *notepadForm = 0);
	CommandFactory(const CommandFactory& source);
	~CommandFactory();
	Command* Make(int uID);
	CommandFactory& operator =(const CommandFactory& source);
private:
	NotepadForm *notepadForm;
};

#endif //_COMMANDFACTORY_H