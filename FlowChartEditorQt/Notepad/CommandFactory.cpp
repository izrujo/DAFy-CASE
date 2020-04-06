#include "CommandFactory.h"
#include "Command.h"
#include "FontCommand.h"
#include "Notepad.h"

CommandFactory::CommandFactory(Notepad *notepad) {
	this->notepad = notepad;
}

CommandFactory::CommandFactory(const CommandFactory& source) {
	this->notepad = source.notepad;
}

CommandFactory::~CommandFactory() {
}

Command* CommandFactory::Make(QString text) {
	Command *command = 0;
	if (text == "FontSet") {
		command = new FontCommand(this->notepad);
	}

	return command;
}

CommandFactory& CommandFactory::operator =(const CommandFactory& source) {
	this->notepad = source.notepad;

	return *this;
}