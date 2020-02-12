#include "CaretController.h"
#include "Caret.h"
#include "CharacterMetrics.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Observer.h"

CaretController::CaretController(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->caret = 0;
	this->notepadForm->AttachObserver(this);
}

CaretController::CaretController(const CaretController& source) {
	this->notepadForm = source.notepadForm;
	this->caret = new Caret(*source.caret);
}

CaretController::~CaretController() {
	if (this->caret != 0) {
		delete this->caret;
	}
	this->notepadForm->DetachObserver(this);
}

void CaretController::Update() {
	if (this->caret == 0) {
		this->caret = new Caret(this->notepadForm);
	}
	Long height = this->notepadForm->characterMetrics->GetHeight();
	BOOL isComposing = this->notepadForm->GetIsComposing();
	Long x;
	if (isComposing == TRUE) {
		this->caret->Create(this->notepadForm->characterMetrics->GetDoubleByteWidth(), height);
		x = this->notepadForm->characterMetrics->GetX(this->notepadForm->current, this->notepadForm->current->GetCurrent() - 1);

	}
	else {
		this->caret->Create(2, height);
		x = this->notepadForm->characterMetrics->GetX(this->notepadForm->current, this->notepadForm->current->GetCurrent()); //??
	}

	Long index = this->notepadForm->note->GetCurrent();
	Long y = this->notepadForm->characterMetrics->GetY(index);
	this->caret->Move(x, y);
	this->caret->Show(true);
}

CaretController& CaretController::operator =(const CaretController& source) {
	this->notepadForm = source.notepadForm;
	this->caret = new Caret(*source.caret);

	return *this;
}