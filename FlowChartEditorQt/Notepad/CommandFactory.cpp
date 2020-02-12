#include "CommandFactory.h"
#include "Command.h"
#include "FontCommand.h"
#include "NotepadForm.h"
#include "resource.h"

CommandFactory::CommandFactory(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CommandFactory::CommandFactory(const CommandFactory& source) {
	this->notepadForm = source.notepadForm;
}

CommandFactory::~CommandFactory() {
}

Command* CommandFactory::Make(int uID) {
	Command *command = 0;
	if (uID == IDM_FORMAT_FONT) {
		command = new FontCommand(this->notepadForm);
	}

	return command;
}

CommandFactory& CommandFactory::operator =(const CommandFactory& source) {
	this->notepadForm = source.notepadForm;

	return *this;
}