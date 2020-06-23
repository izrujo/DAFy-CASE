#include "Editor.h"
#include "Selector.h"
#include "Scanner.h"
#include "../Interface/Notepad.h"
#include "../Data/Glyph.h"
#include "../Data/GlyphFactory.h"
#include "../Data/Composite/Highlight.h"

#include <qclipboard.h>
#include <qmimedata.h>

Editor::Editor(Notepad *notepad) {
	this->notepad = notepad;
	this->selector = 0;
}

Editor::Editor(const Editor& source) {
	this->notepad = source.notepad;
	this->selector = source.selector;
}

Editor::~Editor() {
	if (this->selector != NULL) {
		delete this->selector;
	}
}

void Editor::UpSelect(Long noteCurrent, Long lineCurrent, Long row, Long column) {
	Long i = noteCurrent;
	while (i >= row) {
		Glyph *line = this->notepad->note->GetAt(i);
		Long startColumn;
		Long noteStartPosition = this->notepad->editor->selector->GetNoteStartPosition();
		Long noteEndPosition = this->notepad->editor->selector->GetNoteEndPosition();
		Long lineStartPosition = this->notepad->editor->selector->GetLineStartPosition();
		Long lineEndPosition = this->notepad->editor->selector->GetLineEndPosition();
		if (noteStartPosition >= noteEndPosition &&
			(noteStartPosition != noteEndPosition || lineStartPosition >= lineEndPosition)) {
			if (i == noteCurrent) {
				startColumn = lineCurrent;
			}
			else {
				startColumn = line->GetLength();
			}
		}
		else {
			if (i == noteCurrent) {
				if (noteStartPosition == noteEndPosition) {
					startColumn = lineStartPosition;
				}
				else {
					startColumn = 0;
				}
			}
			else {
				if (i == noteStartPosition) {
					if (column > lineStartPosition) {
						startColumn = column;
					}
					else {
						startColumn = lineStartPosition;
					}
				}
				else if (i == row) {
					startColumn = column;
				}
				else {
					startColumn = 0;
				}
			}
		}
		Long endColumn = 0;
		if (i == row) {
			endColumn = column;
		}
		this->selector->Left(i, startColumn, endColumn);
		i--;
	}
}

void Editor::DownSelect(Long noteCurrent, Long lineCurrent, Long row, Long column) {
	Long i = noteCurrent;
	while (i <= row) {
		Glyph *line = this->notepad->note->GetAt(i);
		Long startColumn;
		Long noteStartPosition = this->notepad->editor->selector->GetNoteStartPosition();
		Long noteEndPosition = this->notepad->editor->selector->GetNoteEndPosition();
		Long lineStartPosition = this->notepad->editor->selector->GetLineStartPosition();
		Long lineEndPosition = this->notepad->editor->selector->GetLineEndPosition();
		if (noteStartPosition <= noteEndPosition &&
			(noteStartPosition != noteEndPosition || lineStartPosition <= lineEndPosition)) {
			if (i == noteCurrent) {
				startColumn = lineCurrent;
			}
			else {
				startColumn = 0;
			}
		}
		else {
			if (i == noteCurrent) {
				if (noteStartPosition == noteEndPosition) {
					startColumn = lineStartPosition;
				}
				else {
					startColumn = line->GetLength();
				}
			}
			else {
				if (i == noteStartPosition) {
					if (column < lineStartPosition) {
						startColumn = column;
					}
					else {
						startColumn = lineStartPosition;
					}
				}
				else if (i == row) {
					startColumn = column;
				}
				else {
					startColumn = 0;
				}
			}
		}
		Long endColumn = line->GetLength();
		if (i == row) {
			endColumn = column;
		}
		this->selector->Right(i, startColumn, endColumn);
		i++;
	}
}

void Editor::Copy() {
	QClipboard *clipboard = QApplication::clipboard();

	QString newText;
	Long i = 0;
	while (i < this->notepad->highlight->GetLength()) {
		Glyph *line = this->notepad->highlight->GetAt(i);
		string content = line->GetContent();
		content.append("\r\n"); //std
		newText.append(QString::fromLocal8Bit(content.c_str())); //QString
		i++;
	}
	newText.remove(newText.length() - 2, 2);
	clipboard->setText(newText);
}

void Editor::Paste() {
	QString oldText;

	const QClipboard *clipboard = QApplication::clipboard();
	const QMimeData *mimeData = clipboard->mimeData();
	if(mimeData->hasText()) {
		oldText = mimeData->text();
	}

	Scanner scanner(oldText.toLocal8Bit().data());
	GlyphFactory glyphFactory;
	Glyph *glyphClipBoard = glyphFactory.Make("");
	Glyph *clipBoardLine = glyphFactory.Make("\r\n");
	glyphClipBoard->Add(clipBoardLine);
	while (scanner.IsEnd() == false) {
		string token = scanner.GetToken();
		if (token != "\r\n") {
			Glyph *glyph = glyphFactory.Make(token.c_str());
			clipBoardLine->Add(glyph);
		}
		else {
			clipBoardLine= glyphFactory.Make(token.c_str());
			glyphClipBoard->Add(clipBoardLine);
		}
		scanner.Next();
	}

	Long i = 0;
	Long current = this->notepad->current->GetCurrent();
	Glyph *line = this->notepad->current->Divide(current);
	Glyph *copiedLine = glyphClipBoard->GetAt(i++);
	Long j = 0;
	while (j < copiedLine->GetLength()) {
		this->notepad->current->Add(copiedLine->GetAt(j));
		j++;
	}

	while (i < glyphClipBoard->GetLength()) {
		copiedLine = glyphClipBoard->GetAt(i);
		Long noteCurrent = this->notepad->note->GetCurrent();
		this->notepad->note->Add(noteCurrent + 1, copiedLine);
		i++;
	}
	this->notepad->current = this->notepad->note->GetAt(this->notepad->note->GetCurrent());
	this->notepad->current->Combine(line);	
}

void Editor::Delete() {
	Long start;
	Long end;
	Long noteStart = this->selector->GetNoteStartPosition();
	Long noteEnd = this->selector->GetNoteEndPosition();
	if (noteStart < noteEnd) {
		start = this->selector->GetLineStartPosition();
		end = this->selector->GetLineEndPosition();
	}
	else if (noteStart > noteEnd) {
		noteStart = this->selector->GetNoteEndPosition();
		noteEnd = this->selector->GetNoteStartPosition();
		start = this->selector->GetLineEndPosition();
		end = this->selector->GetLineStartPosition();
	}
	else {
		if (this->selector->GetLineStartPosition() < this->selector->GetLineEndPosition()) {
			start = this->selector->GetLineStartPosition();
			end = this->selector->GetLineEndPosition();
		}
		else {
			start = this->selector->GetLineEndPosition();
			end = this->selector->GetLineStartPosition();
		}
	}
	Glyph *line = this->notepad->note->GetAt(noteStart);
	Long noteRepeatCount = noteEnd - noteStart + 1;
	Long i = 0;
	while (i < noteRepeatCount) {
		Long lineEnd = end;
		if (noteRepeatCount > 1) {
			if (i == noteRepeatCount - 1) {
				lineEnd = end + start;
			}
			else {
				lineEnd = line->GetLength();
			}
		}
		Long repeatCount = lineEnd - start;
		Long j = 0;
		while (j < repeatCount) {
			line->Remove(start);
			j++;
		}
		if (i < noteRepeatCount - 1) {
			Glyph *nextLine = this->notepad->note->GetAt(noteStart + 1);
			line->Combine(nextLine);
			this->notepad->note->Remove(noteStart + 1);
		}
		i++;
	}
	this->notepad->current = this->notepad->note->GetAt(noteStart);
	if (this->notepad->highlight != NULL) {
		delete this->notepad->highlight;
		this->notepad->highlight = NULL;
	}
}

Editor& Editor::operator=(const Editor& source) {
	this->notepad = source.notepad;
	this->selector = source.selector;

	return *this;
}