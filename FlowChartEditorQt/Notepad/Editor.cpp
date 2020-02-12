#include "Editor.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "GlyphFactory.h"
#include "Highlight.h"
#include "Selector.h"
#include "Scanner.h"

Editor::Editor(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->selector = 0;
}

Editor::Editor(const Editor& source) {
	this->notepadForm = source.notepadForm;
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
		Glyph *line = this->notepadForm->note->GetAt(i);
		Long startColumn;
		Long noteStartPosition = this->notepadForm->editor->selector->GetNoteStartPosition();
		Long noteEndPosition = this->notepadForm->editor->selector->GetNoteEndPosition();
		Long lineStartPosition = this->notepadForm->editor->selector->GetLineStartPosition();
		Long lineEndPosition = this->notepadForm->editor->selector->GetLineEndPosition();
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
		Glyph *line = this->notepadForm->note->GetAt(i);
		Long startColumn;
		Long noteStartPosition = this->notepadForm->editor->selector->GetNoteStartPosition();
		Long noteEndPosition = this->notepadForm->editor->selector->GetNoteEndPosition();
		Long lineStartPosition = this->notepadForm->editor->selector->GetLineStartPosition();
		Long lineEndPosition = this->notepadForm->editor->selector->GetLineEndPosition();
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
	CString clipBoard;
	Long i = 0;
	while (i < this->notepadForm->highlight->GetLength()) {
		Glyph *line = this->notepadForm->highlight->GetAt(i);
		string content = line->GetContent();
		content.append("\r\n");
		clipBoard.Append(content.c_str());
		i++;
	}

	HANDLE handle;
	char *address = NULL;
	handle = ::GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, clipBoard.GetLength() - 1);
	address = (char*)::GlobalLock(handle);
	if (address == NULL) {
		::GlobalFree(handle);
	}
	strcpy(address, clipBoard);
	if (::OpenClipboard(this->notepadForm->m_hWnd)) {
		::EmptyClipboard();
		::SetClipboardData(CF_TEXT, handle);
		::CloseClipboard();
	}
	::GlobalUnlock(handle);
}

void Editor::Paste() {
	string clipBoard;
	HANDLE handle;
	LPSTR address = NULL;
	if (::IsClipboardFormatAvailable(CF_TEXT) != FALSE) {
		if (::OpenClipboard(this->notepadForm->m_hWnd)) {
			handle = GetClipboardData(CF_TEXT);
			if (handle != NULL) {
				address = (LPSTR)::GlobalLock(handle);
				clipBoard = address;
				::GlobalUnlock(handle);
			}
			CloseClipboard();
		}
	}
	Scanner scanner(clipBoard);
	GlyphFactory glyphFactory;
	Glyph *glyphClipBoard = glyphFactory.Make("");
	Glyph *clipBoardLine = glyphFactory.Make("\r\n");
	glyphClipBoard->Add(clipBoardLine);
	while (scanner.IsEnd() == FALSE) {
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
	Long current = this->notepadForm->current->GetCurrent();
	Glyph *line = this->notepadForm->current->Divide(current);
	Glyph *copiedLine = glyphClipBoard->GetAt(i++);
	this->notepadForm->current->Combine(copiedLine);

	while (i < glyphClipBoard->GetLength()) {
		copiedLine = glyphClipBoard->GetAt(i);
		Long noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->note->Add(noteCurrent + 1, copiedLine);
		i++;
	}
	this->notepadForm->current = this->notepadForm->note->GetAt(this->notepadForm->note->GetCurrent());
	this->notepadForm->current->Combine(line);
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
	Glyph *line = this->notepadForm->note->GetAt(noteStart);
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
			Glyph *nextLine = this->notepadForm->note->GetAt(noteStart + 1);
			line->Combine(nextLine);
			this->notepadForm->note->Remove(noteStart + 1);
		}
		i++;
	}
	this->notepadForm->current = this->notepadForm->note->GetAt(noteStart);
	if (this->notepadForm->highlight != NULL) {
		delete this->notepadForm->highlight;
		this->notepadForm->highlight = NULL;
	}
}

Editor& Editor::operator=(const Editor& source) {
	this->notepadForm = source.notepadForm;
	this->selector = source.selector;

	return *this;
}