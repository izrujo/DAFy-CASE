#include "KeyActions.h"
#include "KeyActionFactory.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Composite.h"
#include "CharacterMetrics.h"
#include "Character.h"
#include "Note.h"
#include "Row.h"
#include "Editor.h"
#include "Selector.h"
#include "Highlight.h"
#include <string>

//KeyAction
KeyAction::KeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

KeyAction::KeyAction(const KeyAction& source) {
	this->notepadForm = source.notepadForm;
}

KeyAction::~KeyAction() {
}

KeyAction& KeyAction::operator =(const KeyAction& source) {
	this->notepadForm = source.notepadForm;

	return *this;
}

//LeftKeyAction
LeftKeyAction::LeftKeyAction(NotepadForm *notepadForm)
	:KeyAction(notepadForm) {

}

LeftKeyAction::LeftKeyAction(const LeftKeyAction& source)
	: KeyAction(notepadForm) {

}

LeftKeyAction::~LeftKeyAction() {

}

void LeftKeyAction::OnKeyDown(UINT nChar, UINT nRepeatCnt, UINT nFlags) {
	if (this->notepadForm->current->GetCurrent() > 0) {
		this->notepadForm->current->Previous();
	}
	else if (this->notepadForm->note->GetCurrent() > 0) {
		Long index = this->notepadForm->note->Previous();
		this->notepadForm->current = this->notepadForm->note->GetAt(index);
		this->notepadForm->current->Last();
	}

	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

LeftKeyAction& LeftKeyAction::operator = (const LeftKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//RightKeyAction
RightKeyAction::RightKeyAction(NotepadForm *notepadForm)
	:KeyAction(notepadForm) {
}

RightKeyAction::RightKeyAction(const RightKeyAction& source)
	: KeyAction(notepadForm) {
}

RightKeyAction::~RightKeyAction() {
}

void RightKeyAction::OnKeyDown(UINT nChar, UINT nRepeatCnt, UINT nFlags) {
	if (this->notepadForm->current->GetCurrent() < this->notepadForm
		->current->GetLength()) {
		this->notepadForm->current->Next();
	}
	else if (this->notepadForm->note->GetCurrent() < this->notepadForm
		->note->GetLength() - 1) {
		Long index = this->notepadForm->note->Next();
		this->notepadForm->current = this->notepadForm->note->GetAt(index);
		this->notepadForm->current->First();
	}

	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

RightKeyAction& RightKeyAction::operator=(const RightKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//UpKeyAction
UpKeyAction::UpKeyAction(NotepadForm *notepadForm)
	:KeyAction(notepadForm) {

}

UpKeyAction::UpKeyAction(const UpKeyAction& source)
	: KeyAction(source) {

}

UpKeyAction::~UpKeyAction() {

}

void UpKeyAction::OnKeyDown(UINT nChar, UINT nRepeatCnt, UINT nFlags) {
	if (this->notepadForm->note->GetCurrent() > 0) {
		Long x = this->notepadForm->characterMetrics->GetX(this->notepadForm->current);
		Long index = this->notepadForm->note->Previous();
		this->notepadForm->current = this->notepadForm->note->GetAt(index);
		Long column = this->notepadForm->characterMetrics->GetColumn(this->notepadForm->current, x);
		this->notepadForm->current->Move(column);
	}

	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

UpKeyAction& UpKeyAction::operator = (const UpKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//DownKeyAction
DownKeyAction::DownKeyAction(NotepadForm *notepadForm)
	:KeyAction(notepadForm) {

}

DownKeyAction::DownKeyAction(const DownKeyAction& source)
	: KeyAction(notepadForm) {

}

DownKeyAction::~DownKeyAction() {

}

void DownKeyAction::OnKeyDown(UINT nChar, UINT nRepeatCnt, UINT nFlags) {
	if (this->notepadForm->note->GetCurrent() < this->notepadForm->note->GetLength() - 1) {
		Long x = this->notepadForm->characterMetrics->GetX(this->notepadForm->current);
		Long index = this->notepadForm->note->Next();
		this->notepadForm->current = this->notepadForm->note->GetAt(index);
		Long column = this->notepadForm->characterMetrics->GetColumn(this->notepadForm->current, x);
		this->notepadForm->current->Move(column);
	}

	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

DownKeyAction& DownKeyAction::operator=(const DownKeyAction& source) {
	KeyAction::operator=(source);
	return *this;

}

//HomeKeyAction
HomeKeyAction::HomeKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

HomeKeyAction::HomeKeyAction(const HomeKeyAction& source)
	: KeyAction(source) {
}

HomeKeyAction::~HomeKeyAction() {
}

void HomeKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->notepadForm->current->First();

	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

HomeKeyAction& HomeKeyAction::operator =(const HomeKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//EndKeyAction
EndKeyAction::EndKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

EndKeyAction::EndKeyAction(const EndKeyAction& source)
	: KeyAction(source) {
}

EndKeyAction::~EndKeyAction() {
}

void EndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->notepadForm->current->Last();

	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

EndKeyAction& EndKeyAction::operator =(const EndKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlLeftKeyAction
CtrlLeftKeyAction::CtrlLeftKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

CtrlLeftKeyAction::CtrlLeftKeyAction(const CtrlLeftKeyAction& source)
	: KeyAction(source) {
}

CtrlLeftKeyAction::~CtrlLeftKeyAction() {
}

void CtrlLeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long index = this->notepadForm->note->MovePreviousWord();
	this->notepadForm->current = this->notepadForm->note->GetAt(index);

	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

CtrlLeftKeyAction& CtrlLeftKeyAction::operator =(const CtrlLeftKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlRightKeyAction
CtrlRightKeyAction::CtrlRightKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

CtrlRightKeyAction::CtrlRightKeyAction(const CtrlRightKeyAction& source)
	: KeyAction(source) {
}

CtrlRightKeyAction::~CtrlRightKeyAction() {
}

void CtrlRightKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long index = this->notepadForm->note->MoveNextWord();
	this->notepadForm->current = this->notepadForm->note->GetAt(index);

	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

CtrlRightKeyAction& CtrlRightKeyAction::operator =(const CtrlRightKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlHomeKeyAction
CtrlHomeKeyAction::CtrlHomeKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

CtrlHomeKeyAction::CtrlHomeKeyAction(const CtrlHomeKeyAction& source)
	: KeyAction(source) {
}

CtrlHomeKeyAction::~CtrlHomeKeyAction() {
}

void CtrlHomeKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long index = this->notepadForm->note->First();
	this->notepadForm->current = this->notepadForm->note->GetAt(index);
	this->notepadForm->current->First();

	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

CtrlHomeKeyAction& CtrlHomeKeyAction::operator =(const CtrlHomeKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlEndKeyAction
CtrlEndKeyAction::CtrlEndKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

CtrlEndKeyAction::CtrlEndKeyAction(const CtrlEndKeyAction& source)
	: KeyAction(source) {
}

CtrlEndKeyAction::~CtrlEndKeyAction() {
}

void CtrlEndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long index = this->notepadForm->note->Last();
	this->notepadForm->current = this->notepadForm->note->GetAt(index);
	this->notepadForm->current->Last();

	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

CtrlEndKeyAction& CtrlEndKeyAction::operator =(const CtrlEndKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//DeleteKeyAction
DeleteKeyAction::DeleteKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

DeleteKeyAction::DeleteKeyAction(const DeleteKeyAction& source)
	: KeyAction(source) {
}

DeleteKeyAction::~DeleteKeyAction() {
}

void DeleteKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->notepadForm->highlight == NULL) {
		Long column = this->notepadForm->current->GetCurrent();
		Long lineLength = this->notepadForm->current->GetLength();
		if (column < lineLength) {
			this->notepadForm->current->Remove(column);
		}
		Long row = this->notepadForm->note->GetCurrent();
		Long noteLength = this->notepadForm->note->GetLength();
		if (column >= lineLength && row < noteLength - 1) {
			Glyph* other = this->notepadForm->note->GetAt(row + 1);
			this->notepadForm->current->Combine(other);
			this->notepadForm->note->Remove(row + 1);
		}
	}
	else {
		this->notepadForm->editor->Delete();
	}
}

DeleteKeyAction& DeleteKeyAction::operator =(const DeleteKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//BackSpaceKeyAction
BackSpaceKeyAction::BackSpaceKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

BackSpaceKeyAction::BackSpaceKeyAction(const BackSpaceKeyAction& source)
	: KeyAction(source) {
}

BackSpaceKeyAction::~BackSpaceKeyAction() {
}

void BackSpaceKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->notepadForm->highlight == NULL) {
		if (this->notepadForm->GetIsComposing() == FALSE) {
			Long lineCurrent = this->notepadForm->current->GetCurrent();
			Long noteCurrent = this->notepadForm->note->GetCurrent();
			if (lineCurrent > 0) {
				this->notepadForm->current->Remove(lineCurrent - 1);
			}
			else if (lineCurrent <= 0 && noteCurrent > 0) {
				Glyph *previousLine = this->notepadForm->note->GetAt(noteCurrent - 1);
				Long index = previousLine->GetLength();
				this->notepadForm->current = previousLine->Combine(this->notepadForm->current);
				this->notepadForm->note->Remove(noteCurrent);
				this->notepadForm->current->Move(index);
			}
		}
	}
	else {
		this->notepadForm->editor->Delete();
	}
}

BackSpaceKeyAction& BackSpaceKeyAction::operator =(const BackSpaceKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftLeftKeyAction
ShiftLeftKeyAction::ShiftLeftKeyAction(NotepadForm *notepadForm)
	:KeyAction(notepadForm) {

}

ShiftLeftKeyAction::ShiftLeftKeyAction(const ShiftLeftKeyAction& source)
	: KeyAction(notepadForm) {

}

ShiftLeftKeyAction::~ShiftLeftKeyAction() {

}

void ShiftLeftKeyAction::OnKeyDown(UINT nChar, UINT nRepeatCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	if (this->notepadForm->highlight == NULL) {
		this->notepadForm->highlight = new Highlight;
		this->notepadForm->editor->selector = new Selector(this->notepadForm, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}
	if (lineCurrent > 0) {
		Long endColumn = this->notepadForm->current->Previous();
		Long startColumn = lineCurrent;
		Long noteStartPosition = this->notepadForm->editor->selector->GetNoteStartPosition();
		Long noteEndPosition = this->notepadForm->editor->selector->GetNoteEndPosition();
		Long lineStartPosition = this->notepadForm->editor->selector->GetLineStartPosition();
		Long lineEndPosition = this->notepadForm->editor->selector->GetLineEndPosition();
		if (noteStartPosition < noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition < lineEndPosition)) {
			startColumn = endColumn;
		}
		this->notepadForm->editor->selector->Left(noteCurrent, startColumn, endColumn);
	}
	else if (noteCurrent > 0) {
		Long index = this->notepadForm->note->Previous();
		this->notepadForm->current = this->notepadForm->note->GetAt(index);
		Long endColumn = this->notepadForm->current->Last();
		this->notepadForm->editor->selector->Left(index, endColumn, endColumn);
	}
}

ShiftLeftKeyAction& ShiftLeftKeyAction::operator = (const ShiftLeftKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//ShiftRightKeyAction
ShiftRightKeyAction::ShiftRightKeyAction(NotepadForm *notepadForm)
	:KeyAction(notepadForm) {
}

ShiftRightKeyAction::ShiftRightKeyAction(const ShiftRightKeyAction& source)
	: KeyAction(notepadForm) {
}

ShiftRightKeyAction::~ShiftRightKeyAction() {
}

void ShiftRightKeyAction::OnKeyDown(UINT nChar, UINT nRepeatCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	if (this->notepadForm->highlight == NULL) {
		this->notepadForm->highlight = new Highlight;
		this->notepadForm->editor->selector = new Selector(this->notepadForm, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	if (lineCurrent < this->notepadForm->current->GetLength()) {
		Long endColumn = this->notepadForm->current->Next();

		Long startColumn = lineCurrent;
		Long noteStartPosition = this->notepadForm->editor->selector->GetNoteStartPosition();
		Long noteEndPosition = this->notepadForm->editor->selector->GetNoteEndPosition();
		Long lineStartPosition = this->notepadForm->editor->selector->GetLineStartPosition();
		Long lineEndPosition = this->notepadForm->editor->selector->GetLineEndPosition();
		if (noteStartPosition > noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition > lineEndPosition)) {
			startColumn = endColumn;
		}
		this->notepadForm->editor->selector->Right(noteCurrent, startColumn, endColumn);
	}
	else if (noteCurrent < this->notepadForm->note->GetLength() - 1) {
		Long index = this->notepadForm->note->Next();
		this->notepadForm->current = this->notepadForm->note->GetAt(index);
		Long endColumn = this->notepadForm->current->First();

		this->notepadForm->editor->selector->Right(index, endColumn, endColumn);
	}
}

ShiftRightKeyAction& ShiftRightKeyAction::operator=(const ShiftRightKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//ShiftUpKeyAction
ShiftUpKeyAction::ShiftUpKeyAction(NotepadForm *notepadForm)
	:KeyAction(notepadForm) {

}

ShiftUpKeyAction::ShiftUpKeyAction(const ShiftUpKeyAction& source)
	: KeyAction(source) {

}

ShiftUpKeyAction::~ShiftUpKeyAction() {

}

void ShiftUpKeyAction::OnKeyDown(UINT nChar, UINT nRepeatCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	if (noteCurrent > 0) {
		if (this->notepadForm->highlight == NULL) {
			this->notepadForm->highlight = new Highlight;
			this->notepadForm->editor->selector = new Selector(this->notepadForm, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
		}

		Long x = this->notepadForm->characterMetrics->GetX(this->notepadForm->current);
		Long index = this->notepadForm->note->Previous();
		this->notepadForm->current = this->notepadForm->note->GetAt(index);
		Long column = this->notepadForm->characterMetrics->GetColumn(this->notepadForm->current, x);
		this->notepadForm->current->Move(column);

		this->notepadForm->editor->UpSelect(noteCurrent, lineCurrent, index, column);
	}
}

ShiftUpKeyAction& ShiftUpKeyAction::operator = (const ShiftUpKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//ShiftDownKeyAction
ShiftDownKeyAction::ShiftDownKeyAction(NotepadForm *notepadForm)
	:KeyAction(notepadForm) {

}

ShiftDownKeyAction::ShiftDownKeyAction(const ShiftDownKeyAction& source)
	: KeyAction(notepadForm) {

}

ShiftDownKeyAction::~ShiftDownKeyAction() {

}

void ShiftDownKeyAction::OnKeyDown(UINT nChar, UINT nRepeatCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	if (noteCurrent < this->notepadForm->note->GetLength() - 1) {
		if (this->notepadForm->highlight == NULL) {
			this->notepadForm->highlight = new Highlight;
			this->notepadForm->editor->selector = new Selector(this->notepadForm, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
		}

		Long x = this->notepadForm->characterMetrics->GetX(this->notepadForm->current);
		Long index = this->notepadForm->note->Next();
		this->notepadForm->current = this->notepadForm->note->GetAt(index);
		Long column = this->notepadForm->characterMetrics->GetColumn(this->notepadForm->current, x);
		this->notepadForm->current->Move(column);

		this->notepadForm->editor->DownSelect(noteCurrent, lineCurrent, index, column);
	}
}

ShiftDownKeyAction& ShiftDownKeyAction::operator=(const ShiftDownKeyAction& source) {
	KeyAction::operator=(source);
	return *this;
}

//ShiftHomeKeyAction
ShiftHomeKeyAction::ShiftHomeKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

ShiftHomeKeyAction::ShiftHomeKeyAction(const ShiftHomeKeyAction& source)
	: KeyAction(source) {
}

ShiftHomeKeyAction::~ShiftHomeKeyAction() {
}

void ShiftHomeKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	if (this->notepadForm->highlight == NULL) {
		this->notepadForm->highlight = new Highlight;
		this->notepadForm->editor->selector = new Selector(this->notepadForm, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long endColumn = this->notepadForm->current->First();

	Long noteStartPosition = this->notepadForm->editor->selector->GetNoteStartPosition();
	Long noteEndPosition = this->notepadForm->editor->selector->GetNoteEndPosition();
	Long lineStartPosition = this->notepadForm->editor->selector->GetLineStartPosition();
	Long lineEndPosition = this->notepadForm->editor->selector->GetLineEndPosition();
	Long startColumn = lineEndPosition;
	if (noteStartPosition == noteEndPosition && lineStartPosition < lineEndPosition) {
		startColumn = lineStartPosition;
	}
	else if (noteStartPosition < noteEndPosition) {
		startColumn = 0;
	}
	this->notepadForm->editor->selector->Left(noteCurrent, startColumn, endColumn);
}

ShiftHomeKeyAction& ShiftHomeKeyAction::operator =(const ShiftHomeKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftEndKeyAction
ShiftEndKeyAction::ShiftEndKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

ShiftEndKeyAction::ShiftEndKeyAction(const ShiftEndKeyAction& source)
	: KeyAction(source) {
}

ShiftEndKeyAction::~ShiftEndKeyAction() {
}

void ShiftEndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	if (this->notepadForm->highlight == NULL) {
		this->notepadForm->highlight = new Highlight;
		this->notepadForm->editor->selector = new Selector(this->notepadForm, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long endColumn = this->notepadForm->current->Last();

	Long noteStartPosition = this->notepadForm->editor->selector->GetNoteStartPosition();
	Long noteEndPosition = this->notepadForm->editor->selector->GetNoteEndPosition();
	Long lineStartPosition = this->notepadForm->editor->selector->GetLineStartPosition();
	Long lineEndPosition = this->notepadForm->editor->selector->GetLineEndPosition();
	Long startColumn = lineEndPosition;
	if (noteStartPosition == noteEndPosition && lineStartPosition > lineEndPosition) {
		startColumn = lineStartPosition;
	}
	else if (noteStartPosition > noteEndPosition) {
		startColumn = this->notepadForm->current->GetLength();
	}
	this->notepadForm->editor->selector->Right(noteCurrent, startColumn, endColumn);
}

ShiftEndKeyAction& ShiftEndKeyAction::operator =(const ShiftEndKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftCtrlLeftKeyAction
ShiftCtrlLeftKeyAction::ShiftCtrlLeftKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

ShiftCtrlLeftKeyAction::ShiftCtrlLeftKeyAction(const ShiftCtrlLeftKeyAction& source)
	: KeyAction(source) {
}

ShiftCtrlLeftKeyAction::~ShiftCtrlLeftKeyAction() {
}

void ShiftCtrlLeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	if (this->notepadForm->highlight == NULL) {
		this->notepadForm->highlight = new Highlight;
		this->notepadForm->editor->selector = new Selector(this->notepadForm, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long index = this->notepadForm->note->MovePreviousWord();
	this->notepadForm->current = this->notepadForm->note->GetAt(index);

	Long endColumn = this->notepadForm->current->GetCurrent();
	Long startColumn = lineCurrent;
	Long noteStartPosition = this->notepadForm->editor->selector->GetNoteStartPosition();
	Long noteEndPosition = this->notepadForm->editor->selector->GetNoteEndPosition();
	Long lineStartPosition = this->notepadForm->editor->selector->GetLineStartPosition();
	Long lineEndPosition = this->notepadForm->editor->selector->GetLineEndPosition();
	if (noteCurrent > index || noteStartPosition < noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition < lineEndPosition)) {
		if (noteStartPosition == index && endColumn < lineStartPosition) {
			startColumn = lineStartPosition;
		}
		else {
			startColumn = endColumn;
		}
	}
	this->notepadForm->editor->selector->Left(index, startColumn, endColumn);
}

ShiftCtrlLeftKeyAction& ShiftCtrlLeftKeyAction::operator =(const ShiftCtrlLeftKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftCtrlRightKeyAction
ShiftCtrlRightKeyAction::ShiftCtrlRightKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

ShiftCtrlRightKeyAction::ShiftCtrlRightKeyAction(const ShiftCtrlRightKeyAction& source)
	: KeyAction(source) {
}

ShiftCtrlRightKeyAction::~ShiftCtrlRightKeyAction() {
}

void ShiftCtrlRightKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	if (this->notepadForm->highlight == NULL) {
		this->notepadForm->highlight = new Highlight;
		this->notepadForm->editor->selector = new Selector(this->notepadForm, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long index = this->notepadForm->note->MoveNextWord();
	this->notepadForm->current = this->notepadForm->note->GetAt(index);

	Long endColumn = this->notepadForm->current->GetCurrent();
	Long startColumn = lineCurrent;
	Long noteStartPosition = this->notepadForm->editor->selector->GetNoteStartPosition();
	Long noteEndPosition = this->notepadForm->editor->selector->GetNoteEndPosition();
	Long lineStartPosition = this->notepadForm->editor->selector->GetLineStartPosition();
	Long lineEndPosition = this->notepadForm->editor->selector->GetLineEndPosition();
	if (noteCurrent < index || noteStartPosition > noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition > lineEndPosition)) {
		if (noteStartPosition == index && endColumn > lineStartPosition) {
			startColumn = lineStartPosition;
		}
		else {
			startColumn = endColumn;
		}
	}
	this->notepadForm->editor->selector->Right(index, startColumn, endColumn);
}

ShiftCtrlRightKeyAction& ShiftCtrlRightKeyAction::operator =(const ShiftCtrlRightKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftCtrlHomeKeyAction
ShiftCtrlHomeKeyAction::ShiftCtrlHomeKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

ShiftCtrlHomeKeyAction::ShiftCtrlHomeKeyAction(const ShiftCtrlHomeKeyAction& source)
	: KeyAction(source) {
}

ShiftCtrlHomeKeyAction::~ShiftCtrlHomeKeyAction() {
}

void ShiftCtrlHomeKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	if (this->notepadForm->highlight == NULL) {
		this->notepadForm->highlight = new Highlight;
		this->notepadForm->editor->selector = new Selector(this->notepadForm, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long index = this->notepadForm->note->First();
	this->notepadForm->current = this->notepadForm->note->GetAt(index);
	Long column = this->notepadForm->current->First();

	this->notepadForm->editor->UpSelect(noteCurrent, lineCurrent, index, column);
}

ShiftCtrlHomeKeyAction& ShiftCtrlHomeKeyAction::operator =(const ShiftCtrlHomeKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//ShiftCtrlEndKeyAction
ShiftCtrlEndKeyAction::ShiftCtrlEndKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

ShiftCtrlEndKeyAction::ShiftCtrlEndKeyAction(const ShiftCtrlEndKeyAction& source)
	: KeyAction(source) {
}

ShiftCtrlEndKeyAction::~ShiftCtrlEndKeyAction() {
}

void ShiftCtrlEndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	if (this->notepadForm->highlight == NULL) {
		this->notepadForm->highlight = new Highlight;
		this->notepadForm->editor->selector = new Selector(this->notepadForm, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	Long index = this->notepadForm->note->Last();
	this->notepadForm->current = this->notepadForm->note->GetAt(index);
	Long column = this->notepadForm->current->Last();

	this->notepadForm->editor->DownSelect(noteCurrent, lineCurrent, index, column);
}

ShiftCtrlEndKeyAction& ShiftCtrlEndKeyAction::operator =(const ShiftCtrlEndKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlAKeyAction
CtrlAKeyAction::CtrlAKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

CtrlAKeyAction::CtrlAKeyAction(const CtrlAKeyAction& source)
	: KeyAction(source) {
}

CtrlAKeyAction::~CtrlAKeyAction() {
}

void CtrlAKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->notepadForm->highlight == NULL) {
		this->notepadForm->highlight = new Highlight;
		this->notepadForm->editor->selector = new Selector(this->notepadForm);

		Long index = this->notepadForm->note->Last();
		this->notepadForm->current = this->notepadForm->note->GetAt(index);
		this->notepadForm->current->Last();

		Long i = 0;
		while (i <= index) {
			Glyph *line = this->notepadForm->note->GetAt(i);
			Long startColumn = 0;
			Long endColumn = line->GetLength();
			this->notepadForm->editor->selector->Right(i, startColumn, endColumn);
			i++;
		}
	}
}

CtrlAKeyAction& CtrlAKeyAction::operator =(const CtrlAKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlCKeyAction
CtrlCKeyAction::CtrlCKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

CtrlCKeyAction::CtrlCKeyAction(const CtrlCKeyAction& source)
	: KeyAction(source) {
}

CtrlCKeyAction::~CtrlCKeyAction() {
}

void CtrlCKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->notepadForm->editor->Copy();
}

CtrlCKeyAction& CtrlCKeyAction::operator =(const CtrlCKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlVKeyAction
CtrlVKeyAction::CtrlVKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

CtrlVKeyAction::CtrlVKeyAction(const CtrlVKeyAction& source)
	: KeyAction(source) {
}

CtrlVKeyAction::~CtrlVKeyAction() {
}

void CtrlVKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->notepadForm->editor->Paste();
	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

CtrlVKeyAction& CtrlVKeyAction::operator =(const CtrlVKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}

//CtrlXKeyAction
CtrlXKeyAction::CtrlXKeyAction(NotepadForm *notepadForm)
	: KeyAction(notepadForm) {
}

CtrlXKeyAction::CtrlXKeyAction(const CtrlXKeyAction& source)
	: KeyAction(source) {
}

CtrlXKeyAction::~CtrlXKeyAction() {
}

void CtrlXKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->notepadForm->editor->Copy();

	this->notepadForm->editor->Delete();
}

CtrlXKeyAction& CtrlXKeyAction::operator =(const CtrlXKeyAction& source) {
	KeyAction::operator =(source);

	return *this;
}