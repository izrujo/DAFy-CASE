#include "KeyActions.h"
#include "KeyActionFactory.h"
#include "../Interface/Notepad.h"
#include "../Data/Glyph.h"
#include "../Data/Composite/Composite.h"
#include "../Data/Composite/Note.h"
#include "../Data/Composite/Row.h"
#include "../Data/Composite/Highlight.h"
#include "../Data/CharacterMetrics.h"
#include "../Data/Leaf/Character.h"
#include "../Edit/Editor.h"
#include "../Edit/Selector.h"
#include <string>

//KeyAction
KeyAction::KeyAction(Notepad *notepad) {
	this->notepad = notepad;
}

KeyAction::KeyAction(const KeyAction& source) {
	this->notepad = source.notepad;
}

KeyAction::~KeyAction() {
}

KeyAction& KeyAction::operator =(const KeyAction& source) {
	this->notepad = source.notepad;

	return *this;
}

//LeftKeyAction
LeftKeyAction::LeftKeyAction(Notepad *notepad)
	:KeyAction(notepad) {

}

LeftKeyAction::LeftKeyAction(const LeftKeyAction& source)
	: KeyAction(notepad) {

}

LeftKeyAction::~LeftKeyAction() {

}

void LeftKeyAction::OnKeyDown() {
	if (this->notepad->current->GetCurrent() > 0) {
		this->notepad->current->Previous();
	}
	else if (this->notepad->note->GetCurrent() > 0) {
		Long index = this->notepad->note->Previous();
		this->notepad->current = this->notepad->note->GetAt(index);
		this->notepad->current->Last();
	}

	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

LeftKeyAction& LeftKeyAction::operator = (const LeftKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//RightKeyAction
RightKeyAction::RightKeyAction(Notepad *notepad)
	:KeyAction(notepad) {
}

RightKeyAction::RightKeyAction(const RightKeyAction& source)
	: KeyAction(notepad) {
}

RightKeyAction::~RightKeyAction() {
}

void RightKeyAction::OnKeyDown() {
	if (this->notepad->current->GetCurrent() < this->notepad
		->current->GetLength()) {
		this->notepad->current->Next();
	}
	else if (this->notepad->note->GetCurrent() < this->notepad
		->note->GetLength() - 1) {
		Long index = this->notepad->note->Next();
		this->notepad->current = this->notepad->note->GetAt(index);
		this->notepad->current->First();
	}

	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

RightKeyAction& RightKeyAction::operator=(const RightKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//UpKeyAction
UpKeyAction::UpKeyAction(Notepad *notepad)
	:KeyAction(notepad) {

}

UpKeyAction::UpKeyAction(const UpKeyAction& source)
	: KeyAction(source) {

}

UpKeyAction::~UpKeyAction() {

}

void UpKeyAction::OnKeyDown() {
	if (this->notepad->note->GetCurrent() > 0) {
		Long x = this->notepad->characterMetrics->GetX(this->notepad->current);
		Long index = this->notepad->note->Previous();
		this->notepad->current = this->notepad->note->GetAt(index);
		Long column = this->notepad->characterMetrics->GetColumn(this->notepad->current, x);
		this->notepad->current->Move(column);
	}

	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

UpKeyAction& UpKeyAction::operator = (const UpKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//DownKeyAction
DownKeyAction::DownKeyAction(Notepad *notepad)
	:KeyAction(notepad) {

}

DownKeyAction::DownKeyAction(const DownKeyAction& source)
	: KeyAction(notepad) {

}

DownKeyAction::~DownKeyAction() {

}

void DownKeyAction::OnKeyDown() {
	if (this->notepad->note->GetCurrent() < this->notepad->note->GetLength() - 1) {
		Long x = this->notepad->characterMetrics->GetX(this->notepad->current);
		Long index = this->notepad->note->Next();
		this->notepad->current = this->notepad->note->GetAt(index);
		Long column = this->notepad->characterMetrics->GetColumn(this->notepad->current, x);
		this->notepad->current->Move(column);
	}

	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

DownKeyAction& DownKeyAction::operator=(const DownKeyAction& source) {
	KeyAction::operator=(source);
	return *this;

}

//HomeKeyAction
HomeKeyAction::HomeKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

HomeKeyAction::HomeKeyAction(const HomeKeyAction& source)
	: KeyAction(source) {
}

HomeKeyAction::~HomeKeyAction() {
}

void HomeKeyAction::OnKeyDown() {
	this->notepad->current->First();

	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

HomeKeyAction& HomeKeyAction::operator =(const HomeKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//EndKeyAction
EndKeyAction::EndKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

EndKeyAction::EndKeyAction(const EndKeyAction& source)
	: KeyAction(source) {
}

EndKeyAction::~EndKeyAction() {
}

void EndKeyAction::OnKeyDown() {
	this->notepad->current->Last();

	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

EndKeyAction& EndKeyAction::operator =(const EndKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlLeftKeyAction
CtrlLeftKeyAction::CtrlLeftKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

CtrlLeftKeyAction::CtrlLeftKeyAction(const CtrlLeftKeyAction& source)
	: KeyAction(source) {
}

CtrlLeftKeyAction::~CtrlLeftKeyAction() {
}

void CtrlLeftKeyAction::OnKeyDown() {
	Long index = this->notepad->note->MovePreviousWord();
	this->notepad->current = this->notepad->note->GetAt(index);

	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

CtrlLeftKeyAction& CtrlLeftKeyAction::operator =(const CtrlLeftKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlRightKeyAction
CtrlRightKeyAction::CtrlRightKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

CtrlRightKeyAction::CtrlRightKeyAction(const CtrlRightKeyAction& source)
	: KeyAction(source) {
}

CtrlRightKeyAction::~CtrlRightKeyAction() {
}

void CtrlRightKeyAction::OnKeyDown() {
	Long index = this->notepad->note->MoveNextWord();
	this->notepad->current = this->notepad->note->GetAt(index);

	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

CtrlRightKeyAction& CtrlRightKeyAction::operator =(const CtrlRightKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlHomeKeyAction
CtrlHomeKeyAction::CtrlHomeKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

CtrlHomeKeyAction::CtrlHomeKeyAction(const CtrlHomeKeyAction& source)
	: KeyAction(source) {
}

CtrlHomeKeyAction::~CtrlHomeKeyAction() {
}

void CtrlHomeKeyAction::OnKeyDown() {
	Long index = this->notepad->note->First();
	this->notepad->current = this->notepad->note->GetAt(index);
	this->notepad->current->First();

	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

CtrlHomeKeyAction& CtrlHomeKeyAction::operator =(const CtrlHomeKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlEndKeyAction
CtrlEndKeyAction::CtrlEndKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

CtrlEndKeyAction::CtrlEndKeyAction(const CtrlEndKeyAction& source)
	: KeyAction(source) {
}

CtrlEndKeyAction::~CtrlEndKeyAction() {
}

void CtrlEndKeyAction::OnKeyDown() {
	Long index = this->notepad->note->Last();
	this->notepad->current = this->notepad->note->GetAt(index);
	this->notepad->current->Last();

	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

CtrlEndKeyAction& CtrlEndKeyAction::operator =(const CtrlEndKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//DeleteKeyAction
DeleteKeyAction::DeleteKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

DeleteKeyAction::DeleteKeyAction(const DeleteKeyAction& source)
	: KeyAction(source) {
}

DeleteKeyAction::~DeleteKeyAction() {
}

void DeleteKeyAction::OnKeyDown() {
	if (this->notepad->highlight == NULL) {
		Long column = this->notepad->current->GetCurrent();
		Long lineLength = this->notepad->current->GetLength();
		if (column < lineLength) {
			this->notepad->current->Remove(column);
		}
		Long row = this->notepad->note->GetCurrent();
		Long noteLength = this->notepad->note->GetLength();
		if (column >= lineLength && row < noteLength - 1) {
			Glyph* other = this->notepad->note->GetAt(row + 1);
			this->notepad->current->Combine(other);
			this->notepad->note->Remove(row + 1);
		}
	}
	else {
		this->notepad->editor->Delete();
	}
}

DeleteKeyAction& DeleteKeyAction::operator =(const DeleteKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//BackSpaceKeyAction
BackSpaceKeyAction::BackSpaceKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

BackSpaceKeyAction::BackSpaceKeyAction(const BackSpaceKeyAction& source)
	: KeyAction(source) {
}

BackSpaceKeyAction::~BackSpaceKeyAction() {
}

void BackSpaceKeyAction::OnKeyDown() {
	if (this->notepad->highlight == NULL) {
		if (this->notepad->GetIsComposing() == false) {
			Long lineCurrent = this->notepad->current->GetCurrent();
			Long noteCurrent = this->notepad->note->GetCurrent();
			if (lineCurrent > 0) {
				this->notepad->current->Remove(lineCurrent - 1);
			}
			else if (lineCurrent <= 0 && noteCurrent > 0) {
				Glyph *previousLine = this->notepad->note->GetAt(noteCurrent - 1);
				Long index = previousLine->GetLength();
				this->notepad->current = previousLine->Combine(this->notepad->current);
				this->notepad->note->Remove(noteCurrent);
				this->notepad->current->Move(index);
			}
		}
	}
	else {
		this->notepad->editor->Delete();
	}
}

BackSpaceKeyAction& BackSpaceKeyAction::operator =(const BackSpaceKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftLeftKeyAction
ShiftLeftKeyAction::ShiftLeftKeyAction(Notepad *notepad)
	:KeyAction(notepad) {

}

ShiftLeftKeyAction::ShiftLeftKeyAction(const ShiftLeftKeyAction& source)
	: KeyAction(notepad) {

}

ShiftLeftKeyAction::~ShiftLeftKeyAction() {

}

void ShiftLeftKeyAction::OnKeyDown() {
	Long noteCurrent = this->notepad->note->GetCurrent();
	Long lineCurrent = this->notepad->current->GetCurrent();
	if (this->notepad->highlight == NULL) {
		this->notepad->highlight = new Highlight;
		this->notepad->editor->selector = new Selector(this->notepad, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}
	if (lineCurrent > 0) {
		Long endColumn = this->notepad->current->Previous();
		Long startColumn = lineCurrent;
		Long noteStartPosition = this->notepad->editor->selector->GetNoteStartPosition();
		Long noteEndPosition = this->notepad->editor->selector->GetNoteEndPosition();
		Long lineStartPosition = this->notepad->editor->selector->GetLineStartPosition();
		Long lineEndPosition = this->notepad->editor->selector->GetLineEndPosition();
		if (noteStartPosition < noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition < lineEndPosition)) {
			startColumn = endColumn;
		}
		this->notepad->editor->selector->Left(noteCurrent, startColumn, endColumn);
	}
	else if (noteCurrent > 0) {
		Long index = this->notepad->note->Previous();
		this->notepad->current = this->notepad->note->GetAt(index);
		Long endColumn = this->notepad->current->Last();
		this->notepad->editor->selector->Left(index, endColumn, endColumn);
	}
}

ShiftLeftKeyAction& ShiftLeftKeyAction::operator = (const ShiftLeftKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//ShiftRightKeyAction
ShiftRightKeyAction::ShiftRightKeyAction(Notepad *notepad)
	:KeyAction(notepad) {
}

ShiftRightKeyAction::ShiftRightKeyAction(const ShiftRightKeyAction& source)
	: KeyAction(notepad) {
}

ShiftRightKeyAction::~ShiftRightKeyAction() {
}

void ShiftRightKeyAction::OnKeyDown() {
	Long noteCurrent = this->notepad->note->GetCurrent();
	Long lineCurrent = this->notepad->current->GetCurrent();
	if (this->notepad->highlight == NULL) {
		this->notepad->highlight = new Highlight;
		this->notepad->editor->selector = new Selector(this->notepad, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	if (lineCurrent < this->notepad->current->GetLength()) {
		Long endColumn = this->notepad->current->Next();

		Long startColumn = lineCurrent;
		Long noteStartPosition = this->notepad->editor->selector->GetNoteStartPosition();
		Long noteEndPosition = this->notepad->editor->selector->GetNoteEndPosition();
		Long lineStartPosition = this->notepad->editor->selector->GetLineStartPosition();
		Long lineEndPosition = this->notepad->editor->selector->GetLineEndPosition();
		if (noteStartPosition > noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition > lineEndPosition)) {
			startColumn = endColumn;
		}
		this->notepad->editor->selector->Right(noteCurrent, startColumn, endColumn);
	}
	else if (noteCurrent < this->notepad->note->GetLength() - 1) {
		Long index = this->notepad->note->Next();
		this->notepad->current = this->notepad->note->GetAt(index);
		Long endColumn = this->notepad->current->First();

		this->notepad->editor->selector->Right(index, endColumn, endColumn);
	}
}

ShiftRightKeyAction& ShiftRightKeyAction::operator=(const ShiftRightKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//ShiftUpKeyAction
ShiftUpKeyAction::ShiftUpKeyAction(Notepad *notepad)
	:KeyAction(notepad) {

}

ShiftUpKeyAction::ShiftUpKeyAction(const ShiftUpKeyAction& source)
	: KeyAction(source) {

}

ShiftUpKeyAction::~ShiftUpKeyAction() {

}

void ShiftUpKeyAction::OnKeyDown() {
	Long noteCurrent = this->notepad->note->GetCurrent();
	Long lineCurrent = this->notepad->current->GetCurrent();
	if (noteCurrent > 0) {
		if (this->notepad->highlight == NULL) {
			this->notepad->highlight = new Highlight;
			this->notepad->editor->selector = new Selector(this->notepad, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
		}

		Long x = this->notepad->characterMetrics->GetX(this->notepad->current);
		Long index = this->notepad->note->Previous();
		this->notepad->current = this->notepad->note->GetAt(index);
		Long column = this->notepad->characterMetrics->GetColumn(this->notepad->current, x);
		this->notepad->current->Move(column);

		this->notepad->editor->UpSelect(noteCurrent, lineCurrent, index, column);
	}
}

ShiftUpKeyAction& ShiftUpKeyAction::operator = (const ShiftUpKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//ShiftDownKeyAction
ShiftDownKeyAction::ShiftDownKeyAction(Notepad *notepad)
	:KeyAction(notepad) {

}

ShiftDownKeyAction::ShiftDownKeyAction(const ShiftDownKeyAction& source)
	: KeyAction(notepad) {

}

ShiftDownKeyAction::~ShiftDownKeyAction() {

}

void ShiftDownKeyAction::OnKeyDown() {
	Long noteCurrent = this->notepad->note->GetCurrent();
	Long lineCurrent = this->notepad->current->GetCurrent();
	if (noteCurrent < this->notepad->note->GetLength() - 1) {
		if (this->notepad->highlight == NULL) {
			this->notepad->highlight = new Highlight;
			this->notepad->editor->selector = new Selector(this->notepad, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
		}

		Long x = this->notepad->characterMetrics->GetX(this->notepad->current);
		Long index = this->notepad->note->Next();
		this->notepad->current = this->notepad->note->GetAt(index);
		Long column = this->notepad->characterMetrics->GetColumn(this->notepad->current, x);
		this->notepad->current->Move(column);

		this->notepad->editor->DownSelect(noteCurrent, lineCurrent, index, column);
	}
}

ShiftDownKeyAction& ShiftDownKeyAction::operator=(const ShiftDownKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//ShiftHomeKeyAction
ShiftHomeKeyAction::ShiftHomeKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

ShiftHomeKeyAction::ShiftHomeKeyAction(const ShiftHomeKeyAction& source)
	: KeyAction(source) {
}

ShiftHomeKeyAction::~ShiftHomeKeyAction() {
}

void ShiftHomeKeyAction::OnKeyDown() {
	Long noteCurrent = this->notepad->note->GetCurrent();
	Long lineCurrent = this->notepad->current->GetCurrent();
	if (this->notepad->highlight == NULL) {
		this->notepad->highlight = new Highlight;
		this->notepad->editor->selector = new Selector(this->notepad, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long endColumn = this->notepad->current->First();

	Long noteStartPosition = this->notepad->editor->selector->GetNoteStartPosition();
	Long noteEndPosition = this->notepad->editor->selector->GetNoteEndPosition();
	Long lineStartPosition = this->notepad->editor->selector->GetLineStartPosition();
	Long lineEndPosition = this->notepad->editor->selector->GetLineEndPosition();
	Long startColumn = lineEndPosition;
	if (noteStartPosition == noteEndPosition && lineStartPosition < lineEndPosition) {
		startColumn = lineStartPosition;
	}
	else if (noteStartPosition < noteEndPosition) {
		startColumn = 0;
	}
	this->notepad->editor->selector->Left(noteCurrent, startColumn, endColumn);
}

ShiftHomeKeyAction& ShiftHomeKeyAction::operator =(const ShiftHomeKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftEndKeyAction
ShiftEndKeyAction::ShiftEndKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

ShiftEndKeyAction::ShiftEndKeyAction(const ShiftEndKeyAction& source)
	: KeyAction(source) {
}

ShiftEndKeyAction::~ShiftEndKeyAction() {
}

void ShiftEndKeyAction::OnKeyDown() {
	Long noteCurrent = this->notepad->note->GetCurrent();
	Long lineCurrent = this->notepad->current->GetCurrent();
	if (this->notepad->highlight == NULL) {
		this->notepad->highlight = new Highlight;
		this->notepad->editor->selector = new Selector(this->notepad, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long endColumn = this->notepad->current->Last();

	Long noteStartPosition = this->notepad->editor->selector->GetNoteStartPosition();
	Long noteEndPosition = this->notepad->editor->selector->GetNoteEndPosition();
	Long lineStartPosition = this->notepad->editor->selector->GetLineStartPosition();
	Long lineEndPosition = this->notepad->editor->selector->GetLineEndPosition();
	Long startColumn = lineEndPosition;
	if (noteStartPosition == noteEndPosition && lineStartPosition > lineEndPosition) {
		startColumn = lineStartPosition;
	}
	else if (noteStartPosition > noteEndPosition) {
		startColumn = this->notepad->current->GetLength();
	}
	this->notepad->editor->selector->Right(noteCurrent, startColumn, endColumn);
}

ShiftEndKeyAction& ShiftEndKeyAction::operator =(const ShiftEndKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftCtrlLeftKeyAction
ShiftCtrlLeftKeyAction::ShiftCtrlLeftKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

ShiftCtrlLeftKeyAction::ShiftCtrlLeftKeyAction(const ShiftCtrlLeftKeyAction& source)
	: KeyAction(source) {
}

ShiftCtrlLeftKeyAction::~ShiftCtrlLeftKeyAction() {
}

void ShiftCtrlLeftKeyAction::OnKeyDown() {
	Long noteCurrent = this->notepad->note->GetCurrent();
	Long lineCurrent = this->notepad->current->GetCurrent();
	if (this->notepad->highlight == NULL) {
		this->notepad->highlight = new Highlight;
		this->notepad->editor->selector = new Selector(this->notepad, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long index = this->notepad->note->MovePreviousWord();
	this->notepad->current = this->notepad->note->GetAt(index);

	Long endColumn = this->notepad->current->GetCurrent();
	Long startColumn = lineCurrent;
	Long noteStartPosition = this->notepad->editor->selector->GetNoteStartPosition();
	Long noteEndPosition = this->notepad->editor->selector->GetNoteEndPosition();
	Long lineStartPosition = this->notepad->editor->selector->GetLineStartPosition();
	Long lineEndPosition = this->notepad->editor->selector->GetLineEndPosition();
	if (noteCurrent > index || noteStartPosition < noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition < lineEndPosition)) {
		if (noteStartPosition == index && endColumn < lineStartPosition) {
			startColumn = lineStartPosition;
		}
		else {
			startColumn = endColumn;
		}
	}
	this->notepad->editor->selector->Left(index, startColumn, endColumn);
}

ShiftCtrlLeftKeyAction& ShiftCtrlLeftKeyAction::operator =(const ShiftCtrlLeftKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftCtrlRightKeyAction
ShiftCtrlRightKeyAction::ShiftCtrlRightKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

ShiftCtrlRightKeyAction::ShiftCtrlRightKeyAction(const ShiftCtrlRightKeyAction& source)
	: KeyAction(source) {
}

ShiftCtrlRightKeyAction::~ShiftCtrlRightKeyAction() {
}

void ShiftCtrlRightKeyAction::OnKeyDown() {
	Long noteCurrent = this->notepad->note->GetCurrent();
	Long lineCurrent = this->notepad->current->GetCurrent();
	if (this->notepad->highlight == NULL) {
		this->notepad->highlight = new Highlight;
		this->notepad->editor->selector = new Selector(this->notepad, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long index = this->notepad->note->MoveNextWord();
	this->notepad->current = this->notepad->note->GetAt(index);

	Long endColumn = this->notepad->current->GetCurrent();
	Long startColumn = lineCurrent;
	Long noteStartPosition = this->notepad->editor->selector->GetNoteStartPosition();
	Long noteEndPosition = this->notepad->editor->selector->GetNoteEndPosition();
	Long lineStartPosition = this->notepad->editor->selector->GetLineStartPosition();
	Long lineEndPosition = this->notepad->editor->selector->GetLineEndPosition();
	if (noteCurrent < index || noteStartPosition > noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition > lineEndPosition)) {
		if (noteStartPosition == index && endColumn > lineStartPosition) {
			startColumn = lineStartPosition;
		}
		else {
			startColumn = endColumn;
		}
	}
	this->notepad->editor->selector->Right(index, startColumn, endColumn);
}

ShiftCtrlRightKeyAction& ShiftCtrlRightKeyAction::operator =(const ShiftCtrlRightKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftCtrlHomeKeyAction
ShiftCtrlHomeKeyAction::ShiftCtrlHomeKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

ShiftCtrlHomeKeyAction::ShiftCtrlHomeKeyAction(const ShiftCtrlHomeKeyAction& source)
	: KeyAction(source) {
}

ShiftCtrlHomeKeyAction::~ShiftCtrlHomeKeyAction() {
}

void ShiftCtrlHomeKeyAction::OnKeyDown() {
	Long noteCurrent = this->notepad->note->GetCurrent();
	Long lineCurrent = this->notepad->current->GetCurrent();
	if (this->notepad->highlight == NULL) {
		this->notepad->highlight = new Highlight;
		this->notepad->editor->selector = new Selector(this->notepad, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long index = this->notepad->note->First();
	this->notepad->current = this->notepad->note->GetAt(index);
	Long column = this->notepad->current->First();

	this->notepad->editor->UpSelect(noteCurrent, lineCurrent, index, column);
}

ShiftCtrlHomeKeyAction& ShiftCtrlHomeKeyAction::operator =(const ShiftCtrlHomeKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftCtrlEndKeyAction
ShiftCtrlEndKeyAction::ShiftCtrlEndKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

ShiftCtrlEndKeyAction::ShiftCtrlEndKeyAction(const ShiftCtrlEndKeyAction& source)
	: KeyAction(source) {
}

ShiftCtrlEndKeyAction::~ShiftCtrlEndKeyAction() {
}

void ShiftCtrlEndKeyAction::OnKeyDown() {
	Long noteCurrent = this->notepad->note->GetCurrent();
	Long lineCurrent = this->notepad->current->GetCurrent();
	if (this->notepad->highlight == NULL) {
		this->notepad->highlight = new Highlight;
		this->notepad->editor->selector = new Selector(this->notepad, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long index = this->notepad->note->Last();
	this->notepad->current = this->notepad->note->GetAt(index);
	Long column = this->notepad->current->Last();

	this->notepad->editor->DownSelect(noteCurrent, lineCurrent, index, column);
}

ShiftCtrlEndKeyAction& ShiftCtrlEndKeyAction::operator =(const ShiftCtrlEndKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlAKeyAction
CtrlAKeyAction::CtrlAKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

CtrlAKeyAction::CtrlAKeyAction(const CtrlAKeyAction& source)
	: KeyAction(source) {
}

CtrlAKeyAction::~CtrlAKeyAction() {
}

void CtrlAKeyAction::OnKeyDown() {
	if (this->notepad->highlight == NULL) {
		this->notepad->highlight = new Highlight;
		this->notepad->editor->selector = new Selector(this->notepad);

		Long index = this->notepad->note->Last();
		this->notepad->current = this->notepad->note->GetAt(index);
		this->notepad->current->Last();

		Long i = 0;
		while (i <= index) {
			Glyph *line = this->notepad->note->GetAt(i);
			Long startColumn = 0;
			Long endColumn = line->GetLength();
			this->notepad->editor->selector->Right(i, startColumn, endColumn);
			i++;
		}
	}
}

CtrlAKeyAction& CtrlAKeyAction::operator =(const CtrlAKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlCKeyAction
CtrlCKeyAction::CtrlCKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

CtrlCKeyAction::CtrlCKeyAction(const CtrlCKeyAction& source)
	: KeyAction(source) {
}

CtrlCKeyAction::~CtrlCKeyAction() {
}

void CtrlCKeyAction::OnKeyDown() {
	this->notepad->editor->Copy();
}

CtrlCKeyAction& CtrlCKeyAction::operator =(const CtrlCKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlVKeyAction
CtrlVKeyAction::CtrlVKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

CtrlVKeyAction::CtrlVKeyAction(const CtrlVKeyAction& source)
	: KeyAction(source) {
}

CtrlVKeyAction::~CtrlVKeyAction() {
}

void CtrlVKeyAction::OnKeyDown() {
	this->notepad->editor->Paste();
	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

CtrlVKeyAction& CtrlVKeyAction::operator =(const CtrlVKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlXKeyAction
CtrlXKeyAction::CtrlXKeyAction(Notepad *notepad)
	: KeyAction(notepad) {
}

CtrlXKeyAction::CtrlXKeyAction(const CtrlXKeyAction& source)
	: KeyAction(source) {
}

CtrlXKeyAction::~CtrlXKeyAction() {
}

void CtrlXKeyAction::OnKeyDown() {
	this->notepad->editor->Copy();

	this->notepad->editor->Delete();
}

CtrlXKeyAction& CtrlXKeyAction::operator =(const CtrlXKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}