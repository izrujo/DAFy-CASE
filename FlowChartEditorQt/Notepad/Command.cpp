#include "Command.h"
#include "Notepad.h"

Command::Command(Notepad *notepad) {
	this->notepad = notepad;
}

Command::Command(const Command& source) {
	this->notepad = source.notepad;
}

Command::~Command() {
}

Command& Command::operator =(const Command& source) {
	this->notepad = source.notepad;

	return *this;
}