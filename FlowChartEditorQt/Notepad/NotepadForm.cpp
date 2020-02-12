#include "NotepadForm.h"
#include "GlyphFactory.h"
#include "Glyph.h"
#include "Note.h"
#include "Row.h"
#include "CaretController.h"
#include "CharacterMetrics.h"
#include "Font.h"
#include "KeyActionFactory.h"
#include "KeyActions.h"
#include "CommandFactory.h"
#include "Command.h"
#include <WinUser.h>
#include <imm.h>
#include <afxdlgs.h>
#include "resource.h"
#include "Editor.h"
#include "Selector.h"
#include "Highlight.h"
#include "../FlowChart/String.h"
#include "Scanner.h"

BEGIN_MESSAGE_MAP(NotepadForm, CWnd)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_COMPOSITION, OnImeComposition)
	ON_MESSAGE(WM_IME_CHAR, OnImeChar)
	ON_MESSAGE(WM_IME_STARTCOMPOSITION, OnImeStartComposition)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_COMMAND_RANGE(IDM_FORMAT_FONT, IDM_FORMAT_FONT, OnCommandRange)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MENUSELECT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

NotepadForm::NotepadForm() {
	this->note = NULL;
	this->current = NULL;
	this->caretController = NULL;
	this->font = NULL;
	this->characterMetrics = NULL;
	this->isComposing = FALSE;
	this->highlight = NULL;
	this->editor = NULL;
	this->clipBoard = NULL;
}

NotepadForm::NotepadForm(String *text) {
	GlyphFactory glyphFactory;
	this->note = glyphFactory.Make("");
	Glyph *line = glyphFactory.Make("\r\n");
	Glyph *glyph;
	this->note->Add(line);
#if 0
	this->current = line;
	Scanner scanner(text->GetString());
	while (scanner.IsEnd() == FALSE) {
		string token = scanner.GetToken();
		Glyph *glyph = glyphFactory.Make(token.c_str());
		if (token != "\r\n") {
			this->current->Add(glyph);
		}
		else {
			Long index = this->note->Add(glyph);
			this->current = this->note->GetAt(index);
		}
		scanner.Next();
	}
#endif
	Long i = 0;
	while (i < text->GetLength()) {
		char character = text->GetAt(i);
		if (character == '\n') {
			glyph = glyphFactory.Make("\r\n");
			this->note->Add(glyph);
		}
		else {
			glyph = glyphFactory.Make(&character);
			this->note->GetAt(this->note->GetLength() - 1)->Add(glyph);
		}
		i++;
	}
	this->current = this->note->GetAt(this->note->GetLength() - 1);
	this->caretController = NULL;
	this->font = NULL;
	this->characterMetrics = NULL;
	this->isComposing = FALSE;
	this->highlight = NULL;
	this->editor = NULL;
	this->clipBoard = NULL;
}

NotepadForm::NotepadForm(char *text) {
	GlyphFactory glyphFactory;
	this->note = glyphFactory.Make("");
	Glyph *line = glyphFactory.Make("\r\n");
	this->note->Add(line);
	this->current = line;
	Scanner scanner(text);
	while (scanner.IsEnd() == FALSE) {
		string token = scanner.GetToken();
		Glyph *glyph = glyphFactory.Make(token.c_str());
		if (token != "\r\n") {
			this->current->Add(glyph);
		}
		else {
			Long index = this->note->Add(glyph);
			this->current = this->note->GetAt(index);
		}
		scanner.Next();
	}

	this->current = this->note->GetAt(this->note->GetLength() - 1);
	this->caretController = NULL;
	this->font = NULL;
	this->characterMetrics = NULL;
	this->isComposing = FALSE;
	this->highlight = NULL;
	this->editor = NULL;
	this->clipBoard = NULL;
}

int NotepadForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);
	if (this->note == NULL) {
		GlyphFactory glyphFactory;
		this->note = glyphFactory.Make("");
		this->current = glyphFactory.Make("\r\n");
		this->note->Add(this->current);
	}
	//this->font = new Font(this);
	this->characterMetrics = new CharacterMetrics(this);
	//this->menu.LoadMenuA(IDR_MENU1);
	//this->SetMenu(&menu);
	this->editor = new Editor(this);

	Long index = this->note->Move(0);
	this->current = this->note->GetAt(index);
	this->current->First();

	this->Notify();

	return 0;
}


void NotepadForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	GlyphFactory glyphFactory;
	TCHAR content[2];
	Long index;

	if (this->highlight != NULL) {
		this->editor->Delete();
	}

	if (nChar >= 32 || nChar == VK_TAB) {
		content[0] = nChar;
		Glyph *character = glyphFactory.Make(content);

		index = this->current->GetCurrent();

		if (index >= this->current->GetLength()) {
			this->current->Add(character);
		}
		else {
			this->current->Add(index, character);
		}
	}
	else if (nChar == VK_RETURN) {
		index = this->current->GetCurrent();

		if (index < this->current->GetLength()) {
			this->current = this->current->Divide(index);
			index = this->note->GetCurrent();
			this->note->Add(index + 1, this->current);
			this->current->First();
		}
		else {
			this->current = glyphFactory.Make("\r\n");
			index = this->note->GetCurrent();
			this->note->Add(index + 1, this->current);
		}
	}
	this->Notify();
	this->Invalidate();
}

LRESULT NotepadForm::OnImeComposition(WPARAM wParam, LPARAM lParam) {
	TCHAR buffer[2];
	Long index;

	if (this->highlight != NULL) {
		this->editor->Delete();
	}

	if (lParam & GCS_COMPSTR) {
		buffer[0] = (TCHAR)HIBYTE(LOWORD(wParam));
		buffer[1] = (TCHAR)LOBYTE(LOWORD(wParam));

		if (this->isComposing == TRUE) {
			index = this->current->GetCurrent();
			this->current->Remove(index - 1);
		}

		if (buffer[0] != '\0') {
			this->isComposing = TRUE;
			GlyphFactory glyphFactory;
			Glyph *doubleByteCharacter = glyphFactory.Make(buffer);
			index = this->current->GetCurrent();

			if (index >= this->current->GetLength()) {
				this->current->Add(doubleByteCharacter);
			}
			else {
				this->current->Add(index, doubleByteCharacter);
			}
		}
		else {
			this->isComposing = FALSE;
		}
		this->Notify();
		this->Invalidate();
	}

	return ::DefWindowProc(this->m_hWnd, WM_IME_COMPOSITION, wParam, lParam);
}

LRESULT NotepadForm::OnImeChar(WPARAM wParam, LPARAM lParam) {
	TCHAR buffer[2];
	Long index = this->current->GetCurrent();
	this->current->Remove(index - 1);

	if (this->highlight != NULL) {
		this->editor->Delete();
	}

	if (IsDBCSLeadByte((BYTE)(wParam >> 8)) == TRUE) {
		buffer[0] = (TCHAR)HIBYTE(LOWORD(wParam));
		buffer[1] = (TCHAR)LOBYTE(LOWORD(wParam));
	}
	else {
		buffer[0] = (TCHAR)wParam;
	}

	GlyphFactory glyphFactory;
	Glyph *glyph = glyphFactory.Make(buffer);

	if (this->current->GetCurrent() >= this->current->GetLength()) {
		this->current->Add(glyph);
	}
	else {
		this->current->Add(this->current->GetCurrent(), glyph);
	}

	this->isComposing = FALSE;
	this->Notify();
	this->Invalidate();


	return 0;
}

LRESULT NotepadForm::OnImeStartComposition(WPARAM wParam, LPARAM lParam) {
	return 0;
}

void NotepadForm::OnPaint() {
	Glyph *line;
	string content;
	CPaintDC dc(this);
	CFont *oldFont;
	COLORREF oldColor;
	CFont font;
	this->font->Create(font);
	oldFont = dc.SelectObject(&font);
	oldColor = dc.SetTextColor(this->font->GetColor());

	Long i = 0;
	while (i < this->note->GetLength()) {
		line = this->note->GetAt(i);
		content = line->GetContent();
		dc.TextOutA(0, i * (this->characterMetrics->GetHeight()), content.c_str());
		i++;
	}

	if (this->highlight != NULL) {
		COLORREF oldBkColor = dc.SetBkColor(RGB(0, 0, 235));
		oldColor = dc.SetTextColor(RGB(255, 255, 255));

		Long noteStartPosition = this->editor->selector->GetNoteStartPosition();
		Long noteEndPosition = this->editor->selector->GetNoteEndPosition();
		Long height = this->characterMetrics->GetHeight();

		Long lineStartPosition = this->editor->selector->GetLineStartPosition();
		Glyph *startLine = this->note->GetAt(noteStartPosition);
		Long startLineX = this->characterMetrics->GetX(startLine, lineStartPosition);

		Long lineEndPosition = this->editor->selector->GetLineEndPosition();
		Glyph *endLine = this->note->GetAt(noteEndPosition);
		Long endX = this->characterMetrics->GetX(endLine, lineEndPosition);

		Long x;
		Long y = noteStartPosition * height;
		if (noteStartPosition < noteEndPosition) {
			x = startLineX;
		}
		else if (noteStartPosition > noteEndPosition) {
			y = noteEndPosition * height;
			x = endX;
		}
		else {
			if (lineStartPosition <= lineEndPosition) {
				x = startLineX;
			}
			else {
				x = endX;
			}
		}

		i = 0;
		while (i < this->highlight->GetLength()) {
			Glyph *highlight = this->highlight->GetAt(i);
			string content = highlight->GetContent();
			dc.TextOutA(x, y, content.c_str());
			y += height;
			x = 0;
			i++;
		}

		dc.SetBkColor(oldBkColor);
	}
	dc.SelectObject(oldFont);
	dc.SetTextColor(oldColor);
}

void NotepadForm::OnSetFocus(CWnd *pNewWnd) {
	if (this->caretController == NULL) {
		this->caretController = new CaretController(this);
	}
	this->Notify();
}

void NotepadForm::OnKillFocus(CWnd *pNewWnd) {
	if (this->caretController != NULL) {
		delete this->caretController;
		this->caretController = NULL;
	}
}

void NotepadForm::OnCommandRange(UINT uID) {
	CommandFactory commandFactory(this);
	Command *command = commandFactory.Make(uID);
	if (command != NULL) {
		command->Execute();
		delete command;
	}

	this->Invalidate();
}

void NotepadForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	KeyActionFactory keyActionFactory(this);
	KeyAction *keyAction = keyActionFactory.Make(nChar);

	if (keyAction != 0) {
		keyAction->OnKeyDown(nChar, nRepCnt, nFlags);
		delete keyAction;
	}

	this->Notify();
	this->Invalidate();
}

void NotepadForm::OnLButtonDown(UINT nFlags, CPoint point) {
	Long noteCurrent = this->note->GetCurrent();
	Long lineCurrent = this->current->GetCurrent();

	Long row = this->characterMetrics->GetRow(point.y);

	if (row >= this->note->GetLength()) {
		row = this->note->GetLength() - 1;
	}

	Long index = this->note->Move(row);
	this->current = this->note->GetAt(index);
	Long column = this->characterMetrics->GetColumn(this->current, point.x);
	Long lineIndex = this->current->Move(column);

	//선택하다 추가
	if (nFlags != 5) {
		if (this->highlight != NULL) {
			delete this->highlight;
			this->highlight = NULL;
		}
	}

	if (nFlags == 5) {
		if (this->highlight == NULL) {
			this->highlight = new Highlight;
			this->editor->selector = new Selector(this, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
		}
		if (noteCurrent == index && lineCurrent > lineIndex) {
			Long endColumn = column;
			Long startColumn = lineCurrent;
			Long noteStartPosition = this->editor->selector->GetNoteStartPosition();
			Long noteEndPosition = this->editor->selector->GetNoteEndPosition();
			Long lineStartPosition = this->editor->selector->GetLineStartPosition();
			Long lineEndPosition = this->editor->selector->GetLineEndPosition();
			if (noteStartPosition < noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition < lineEndPosition)) {
				startColumn = endColumn;
			}
			this->editor->selector->Left(noteCurrent, startColumn, endColumn);
		}
		else if (noteCurrent == index && lineCurrent < lineIndex) {
			Long endColumn = column;
			Long startColumn = lineCurrent;
			Long noteStartPosition = this->editor->selector->GetNoteStartPosition();
			Long noteEndPosition = this->editor->selector->GetNoteEndPosition();
			Long lineStartPosition = this->editor->selector->GetLineStartPosition();
			Long lineEndPosition = this->editor->selector->GetLineEndPosition();
			if (noteStartPosition > noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition > lineEndPosition)) {
				startColumn = endColumn;
			}
			this->editor->selector->Right(noteCurrent, startColumn, endColumn);
		}

		if (index < noteCurrent) {
			this->editor->UpSelect(noteCurrent, lineCurrent, index, lineIndex);
		}
		else if (index > noteCurrent) {
			this->editor->DownSelect(noteCurrent, lineCurrent, index, lineIndex);
		}
	}

	this->Notify();
	this->Invalidate(); //선택하다 추가
}

void NotepadForm::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags == MK_LBUTTON) {
		Long noteCurrent = this->note->GetCurrent();
		Long lineCurrent = this->current->GetCurrent();
		if (this->highlight == NULL) {
			this->highlight = new Highlight;
			this->editor->selector = new Selector(this, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
		}

		Long row = this->characterMetrics->GetRow(point.y);
		if (row >= this->note->GetLength()) {
			row = this->note->GetLength() - 1;
		}
		Long index = this->note->Move(row);
		this->current = this->note->GetAt(index);
		Long column = this->characterMetrics->GetColumn(this->current, point.x);
		Long lineIndex = this->current->Move(column);

		if (noteCurrent == index && lineCurrent > lineIndex) {
			Long endColumn = column;
			Long startColumn = lineCurrent;
			Long noteStartPosition = this->editor->selector->GetNoteStartPosition();
			Long noteEndPosition = this->editor->selector->GetNoteEndPosition();
			Long lineStartPosition = this->editor->selector->GetLineStartPosition();
			Long lineEndPosition = this->editor->selector->GetLineEndPosition();
			if (noteStartPosition < noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition < lineEndPosition)) {
				startColumn = endColumn;
			}
			this->editor->selector->Left(noteCurrent, startColumn, endColumn);
		}
		else if (noteCurrent == index && lineCurrent < lineIndex) {
			Long endColumn = column;
			Long startColumn = lineCurrent;
			Long noteStartPosition = this->editor->selector->GetNoteStartPosition();
			Long noteEndPosition = this->editor->selector->GetNoteEndPosition();
			Long lineStartPosition = this->editor->selector->GetLineStartPosition();
			Long lineEndPosition = this->editor->selector->GetLineEndPosition();
			if (noteStartPosition > noteEndPosition || (noteStartPosition == noteEndPosition && lineStartPosition > lineEndPosition)) {
				startColumn = endColumn;
			}
			this->editor->selector->Right(noteCurrent, startColumn, endColumn);
		}

		if (index < noteCurrent) {
			this->editor->UpSelect(noteCurrent, lineCurrent, index, lineIndex);
		}
		else if (index > noteCurrent) {
			this->editor->DownSelect(noteCurrent, lineCurrent, index, lineIndex);
		}

		this->Notify();
		this->Invalidate();
	}
}

void NotepadForm::OnClose() {
	if (this->characterMetrics != NULL) {
		delete this->characterMetrics;
	}
	if (this->font != NULL) {
		delete this->font;
	}
	if (this->note != NULL) {
		delete this->note;
	}
	if (this->highlight != NULL) {
		delete this->highlight;
	}
	if (this->editor != NULL) {
		delete this->editor;
	}
	if (this->clipBoard != NULL) {
		delete this->clipBoard;
	}

	CWnd::OnClose();
}