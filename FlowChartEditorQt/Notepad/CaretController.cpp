#include "CaretController.h"
#include "Caret.h"
#include "CharacterMetrics.h"
#include "Notepad.h"
#include "Glyph.h"
#include "Observer.h"
#include "GObject.h"
#include "QtPainter.h"

#include <qpainter.h>
#include <qmenubar.h>

CaretController::CaretController(Notepad *notepad) {
	this->notepad = notepad;
	this->caret = 0;
	this->notepad->AttachObserver(this);
}

CaretController::CaretController(const CaretController& source) {
	this->notepad = source.notepad;
	this->caret = new Caret(*source.caret);
}

CaretController::~CaretController() {
	if (this->caret != 0) {
		delete this->caret;
	}
	this->notepad->DetachObserver(this);
}

CaretController& CaretController::operator =(const CaretController& source) {
	this->notepad = source.notepad;
	this->caret = new Caret(*source.caret);

	return *this;
}

void CaretController::Update() {
	if (this->caret == 0) {
		this->caret = new Caret(this->notepad);
	}
	Long x;
	Long y;
	Long width;
	Long height = this->notepad->characterMetrics->GetHeight();
	bool isComposing = this->notepad->GetIsComposing();
	if (isComposing == true) {
		width = this->notepad->characterMetrics->GetDoubleByteWidth();
		x = this->notepad->characterMetrics->GetX(this->notepad->current, this->notepad->current->GetCurrent() - 1);

	}
	else {
		width = 2;
		x = this->notepad->characterMetrics->GetX(this->notepad->current, this->notepad->current->GetCurrent()); //??
	}
	Long index = this->notepad->note->GetCurrent();
	y = this->notepad->menuBar->y() + this->notepad->menuBar->height() + this->notepad->characterMetrics->GetY(index);

	QRect rect(x, y, width, height);
	this->caret->Hide();
	this->caret->Set(rect);
	this->caret->Show();
}