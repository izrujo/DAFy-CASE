#include "Command.h"
#include "NotepadForm.h"

Command::Command(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

Command::Command(const Command& source) {
	this->notepadForm = source.notepadForm;
}

Command::~Command() {
}

Command& Command::operator =(const Command& source) {
	this->notepadForm = source.notepadForm;

	return *this;
}