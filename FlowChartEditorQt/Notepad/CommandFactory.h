#ifndef _COMMANDFACTORY_H
#define _COMMANDFACTORY_H

class Notepad;
class Command;
#include <qstring.h>

class CommandFactory {
public:
	CommandFactory(Notepad *notepad = 0);
	CommandFactory(const CommandFactory& source);
	~CommandFactory();
	Command* Make(QString text);
	CommandFactory& operator =(const CommandFactory& source);
private:
	Notepad *notepad;
};

#endif //_COMMANDFACTORY_H