//Caret.cpp
#include "Caret.h"
#include "NotePadForm.h"

Caret::Caret(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->x = 0;
	this->y = 0;
}

Caret::Caret(const Caret& source) {
	this->notepadForm = source.notepadForm;
	this->x = source.x;
	this->y = source.y;
}

Caret::~Caret() {
	::DestroyCaret();
}

void Caret::Create(Long width, Long height) {
	this->notepadForm->CreateSolidCaret(width, height);
}

void Caret::Move(Long x, Long y) {
	this->x = x;
	this->y = y;
	CPoint point(x, y);
	this->notepadForm->SetCaretPos(point);
}

void Caret::Show(bool isShow) {
	if (isShow == TRUE) {
		this->notepadForm->ShowCaret();
	}
	else {
		this->notepadForm->HideCaret();
	}
}

Caret& Caret::operator=(const Caret& source) {
	this->notepadForm = source.notepadForm;
	this->x = source.x;
	this->y = source.y;

	return *this;
}