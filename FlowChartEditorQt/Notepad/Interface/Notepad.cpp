#include "Notepad.h"
#include "GlyphFactory.h"
#include "Glyph.h"
#include "Note.h"
#include "Row.h"
#include "CaretController.h"
#include "CharacterMetrics.h"
#include "../GObject/Font.h"
#include "KeyActionFactory.h"
#include "KeyActions.h"
#include "Editor.h"
#include "Selector.h"
#include "Highlight.h"
#include "../GObject/GObject.h"
#include "../GObject/QtPainter.h"
#include "../GObject/QtGObjectFactory.h"
#include "Caret.h"
#include "../FlowChart/String.h"
#include "Scanner.h"

#include <qevent.h>
#include <qpainter.h>
#include <qstyle.h>

Notepad::Notepad(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);

	this->setFocusPolicy(Qt::WheelFocus);
	this->setAttribute(Qt::WA_InputMethodEnabled, true);

	this->caretController = new CaretController(this);
	this->isComposing = false;
	this->highlight = NULL;
	this->clipBoard = NULL;

	QRect rect = this->frameRect();
	this->painter = new QtPainter(rect.width(), rect.height());

	GlyphFactory glyphFactory;
	this->note = glyphFactory.Make("");
	this->current = glyphFactory.Make("\r\n");
	this->note->Add(this->current);

	this->characterMetrics = new CharacterMetrics(this);
	this->editor = new Editor(this);

	Long index = this->note->Move(0);
	this->current = this->note->GetAt(index);
	this->current->First();


	this->Notify();
}

Notepad::Notepad(String *text, QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);

	this->setFocusPolicy(Qt::WheelFocus);
	this->setAttribute(Qt::WA_InputMethodEnabled, true);

	this->caretController = new CaretController(this);
	this->isComposing = false;
	this->highlight = NULL;
	this->clipBoard = NULL;

	QRect rect = this->frameRect();
	this->painter = new QtPainter(rect.width(), rect.height());

	GlyphFactory glyphFactory;
	this->note = glyphFactory.Make("");
	Glyph *line = glyphFactory.Make("\r\n");
	Glyph *glyph;
	this->note->Add(line);

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

	this->characterMetrics = new CharacterMetrics(this);
	this->editor = new Editor(this);

	Long index = this->note->Move(0);
	this->current = this->note->GetAt(index);
	this->current->First();


	this->Notify();
}

Notepad::Notepad(char *text, QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);

	this->setFocusPolicy(Qt::WheelFocus);
	this->setAttribute(Qt::WA_InputMethodEnabled, true);

	this->caretController = new CaretController(this);
	this->isComposing = false;
	this->highlight = NULL;
	this->clipBoard = NULL;

	QRect rect = this->frameRect();
	this->painter = new QtPainter(rect.width(), rect.height());

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

	this->characterMetrics = new CharacterMetrics(this);
	this->editor = new Editor(this);

	Long index = this->note->Move(0);
	this->current = this->note->GetAt(index);
	this->current->First();


	this->Notify();
}

void Notepad::closeEvent(QCloseEvent *event) {
	if (this->characterMetrics != NULL) {
		delete this->characterMetrics;
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
	if (this->painter != NULL) {
		delete this->painter;
	}
}

void Notepad::resizeEvent(QResizeEvent *event) {
	if (this->painter != NULL) {
		QRect rect = this->frameRect();
		this->painter->Resize(rect.width(), rect.height());
	}
	if (this->note != NULL) {
		this->Notify();
	}
}

void Notepad::keyPressEvent(QKeyEvent *event) {
	int key = event->key();
	//==========OnKeyDown==========
	KeyActionFactory keyActionFactory(this);
	KeyAction *keyAction = keyActionFactory.Make(key);

	if (keyAction != 0) {
		keyAction->OnKeyDown();
		delete keyAction;
	}
	//==========OnKeyDown==========

	//==========OnChar==========
	GlyphFactory glyphFactory;
	char content[2];
	Long index;
	bool isShiftOrNo =
		(event->modifiers() == Qt::ShiftModifier) || (event->modifiers() == Qt::NoModifier);

	if (isShiftOrNo && key >= Qt::Key_Space && key <= Qt::Key_AsciiTilde || key == Qt::Key_Tab) {
		if (this->highlight != NULL) {
			this->editor->Delete();
		}
		content[0] = *event->text().toLocal8Bit().data();
		Glyph *character = glyphFactory.Make(content);

		index = this->current->GetCurrent();

		if (index >= this->current->GetLength()) {
			this->current->Add(character);
		}
		else {
			this->current->Add(index, character);
		}
	}
	else if (isShiftOrNo && key == Qt::Key_Return) {
		if (this->highlight != NULL) {
			this->editor->Delete();
		}
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

	//==========OnChar==========


	this->Notify();
	this->repaint();
}

void Notepad::inputMethodEvent(QInputMethodEvent *event) {
	QString preeditString = event->preeditString();
	QString commitString = event->commitString();
	Long replacementLength = event->replacementLength();
	Long replacementStart = event->replacementStart();

	//qDebug() << "preedit : " << preeditString;
	//qDebug() << "commit : " << commitString;
	//qDebug() << "length : " << replacementLength;
	//qDebug() << "start : " << replacementStart;
	//qDebug() << "=======";

	if (commitString == "" && preeditString == "") {
		this->isComposing = false;
	}

	if (this->isComposing == true) {
		this->current->Remove(this->current->GetCurrent() - 1);
	}

	GlyphFactory glyphFactory;
	Glyph *doubleByteCharacter;
	if (preeditString != "") {
		this->isComposing = true;
		doubleByteCharacter = glyphFactory.Make(preeditString.toLocal8Bit().data());
		if (this->current->GetCurrent() >= this->current->GetLength()) {
			this->current->Add(doubleByteCharacter);
		}
		else {
			this->current->Add(this->current->GetCurrent(), doubleByteCharacter);
		}
	}
	else if (commitString != "") {
		this->isComposing = false;
		doubleByteCharacter = glyphFactory.Make(commitString.toLocal8Bit().data());
		if (this->current->GetCurrent() >= this->current->GetLength()) {
			this->current->Add(doubleByteCharacter);
		}
		else {
			this->current->Add(this->current->GetCurrent(), doubleByteCharacter);
		}
	}

	this->Notify();
	this->repaint();
}

void Notepad::paintEvent(QPaintEvent *event) {
	QPainter dc(this);

	//QRect frameRect = this->frameRect();
	//this->painter->Resize(frameRect.width(), frameRect.height());

	Glyph *line;
	string content;

	Long firstY = 0;
	Long i = 0;
	while (i < this->note->GetLength()) {
		line = this->note->GetAt(i);
		content = line->GetContent();
		this->painter->DrawTextQ(0, firstY + (i + 1) * (this->characterMetrics->GetHeight()) - (this->characterMetrics->GetDescent()),
			QString::fromLocal8Bit(content.c_str()));
		i++;
	}

	if (this->highlight != NULL) {
		GObject *oldPen = this->painter->CurrentObject("Pen");
		QtGObjectFactory factory;
		GObject *pen = factory.MakePen(QBrush(QColor(255, 255, 255)), oldPen->GetWidth()); // Qt는 폰트 색깔이 Pen 색깔
		this->painter->SelectObject(*pen);
		this->painter->Update();
		GObject *brush = factory.MakeBrush(QColor(0, 0, 235));

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
		Long y = (noteStartPosition + 1) * height;
		if (noteStartPosition < noteEndPosition) {
			x = startLineX;
		}
		else if (noteStartPosition > noteEndPosition) {
			y = (noteEndPosition + 1) * height;
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
		y += firstY;
		i = 0;
		while (i < this->highlight->GetLength()) {
			Glyph *highlight = this->highlight->GetAt(i);
			string content = highlight->GetContent();
			QRect boundingRect = this->painter->BoundingRect(QRect(x, y - height, 0, 0), Qt::AlignLeft | Qt::AlignTop,
				QString::fromLocal8Bit(content.c_str())); //매개변수 rect의 0, 0은 무시됨.
			boundingRect.setHeight(height);
			this->painter->FillRect(boundingRect, *brush);
			this->painter->DrawTextQ(x, y - this->characterMetrics->GetDescent(), QString::fromLocal8Bit(content.c_str()));
			y += height;
			x = 0;
			i++;
		}

		this->painter->SelectObject(*oldPen);
		if (brush != NULL) {
			delete brush;
		}
		if (pen != NULL) {
			delete pen;
		}
	}
	this->painter->Render(&dc, 0, 0);

	if (this->caretController != NULL) {
		this->caretController->GetCaret()->Paint(dc);
	}
}

void Notepad::focusInEvent(QFocusEvent *event) {
	if (this->caretController == NULL) {
		this->caretController = new CaretController(this);
	}
	this->Notify();
}

void Notepad::focusOutEvent(QFocusEvent *event) {
	if (this->caretController != NULL) {
		delete this->caretController;
		this->caretController = NULL;
	}
}

void Notepad::mousePressEvent(QMouseEvent *event) {
	Long noteCurrent = this->note->GetCurrent();
	Long lineCurrent = this->current->GetCurrent();

	Long row = this->characterMetrics->GetRow(event->pos().y());

	if (row >= this->note->GetLength()) {
		row = this->note->GetLength() - 1;
	}

	Long index = this->note->Move(row);
	this->current = this->note->GetAt(index);
	Long column = this->characterMetrics->GetColumn(this->current, event->pos().x());
	Long lineIndex = this->current->Move(column);

	//선택하다 추가
	if (event->modifiers() != Qt::ShiftModifier) {
		if (this->highlight != NULL) {
			delete this->highlight;
			this->highlight = NULL;
		}
	}

	if (event->modifiers() == Qt::ShiftModifier) {
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
	this->repaint(); //선택하다 추가
}

void Notepad::mouseMoveEvent(QMouseEvent *event) {
	//if (nFlags == MK_LBUTTON) { //mouseTracking 디폴트(off)면 마우스가 눌러진 상태에서 움직이면 이 함수가 불러짐
	Long noteCurrent = this->note->GetCurrent();
	Long lineCurrent = this->current->GetCurrent();
	if (this->highlight == NULL) {
		this->highlight = new Highlight;
		this->editor->selector = new Selector(this, noteCurrent, lineCurrent, noteCurrent, lineCurrent);
	}

	//언더플로, 오버플로 설정. 좌표 범위가 윈도우 범위 넘어가면 생기는 오류 방지.
	Long y = event->pos().y();
	if (y < 0) {
		y = 0;
	}
	else if (y > this->frameRect().bottom()) {
		y = this->frameRect().bottom();
	}
	Long x = event->pos().x();
	if (x < 0) {
		x = 0;
	}
	else if (x > this->frameRect().right()) {
		x = this->frameRect().right();
	}
	//=========================

	Long row = this->characterMetrics->GetRow(y);
	if (row >= this->note->GetLength()) {
		row = this->note->GetLength() - 1;
	}
	Long index = this->note->Move(row);
	this->current = this->note->GetAt(index);
	Long column = this->characterMetrics->GetColumn(this->current, x);
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
	this->repaint();
}