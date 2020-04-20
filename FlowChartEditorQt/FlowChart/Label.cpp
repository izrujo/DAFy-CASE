/******************************************************************
 * 파일 이름 :  Label.cpp
 * 기     능 : Text Class boundary
 * 작  성 자 : 송윤창
 * 작성 일자 : 2015년 4월 20일
*******************************************************************/
#include "Label.h"
#include "String.h"
#include "Shape.h"

#include "FlowChart.h"
#include "../FlowChartEditor.h"
#include "DrawingPaper.h"

#include "../Notepad/GlyphFactory.h"
#include "../Notepad/Glyph.h"
#include "../Notepad/Row.h"
#include "../Notepad/CharacterMetrics.h"
#include "Process.h"
#include "Creator.h"
#include "SizeController.h"
#include "VariableList.h"
#include "Preparation.h"
#include "../Notepad/GlyphFactory.h"
#include "../GObject/Font.h"

#include <qevent.h>
#include <windows.h>

Label* Label::instance = 0;

Label* Label::Instance(String *text, QColor color, QWidget *parent)
{
	if (instance == 0)
	{
		instance = new Label(text, color, parent);
	}
	return instance;
}

Label* Label::Instance(QWidget *parent)
{
	if (instance == 0)
	{
		instance = new Label(parent);
	}
	return instance;
}


Label::Label(QWidget *parent)
	: Notepad(parent) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->sizeController = NULL;
	this->color = QColor(255, 255, 255);

	this->sizeController = new SizeController(this);
}

Label::Label(String *text, QColor color, QWidget *parent)
	: Notepad(text, parent) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->sizeController = NULL;
	this->color = color;

	this->sizeController = new SizeController(this);
}

Label::~Label() {
	if (this->sizeController != NULL) {
		delete this->sizeController;
	}
}

void Label::Destroy() {
	if (instance != 0)
	{
		delete instance;
	}
	instance = 0;
}

void Label::Open(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Label::resizeEvent(QResizeEvent *event) {
	Notepad::resizeEvent(event);
}

void Label::keyPressEvent(QKeyEvent *event) {
	Notepad::keyPressEvent(event);
	int nChar = event->key();
	/* 한 칸 띄우기 없음
	//특수문자면 한칸 띄우는데 예외들 : ' " > <  . !
	if (((nChar >= 33 && nChar <= 47) || (nChar >= 58 && nChar <= 64)
		|| (nChar >= 91 && nChar <= 96) || (nChar >= 123 && nChar <= 126))
		&& (nChar != 34 && nChar != 39 && nChar != 60 && nChar != 62 && nChar != 33 /*&& nChar != 46)) { //여기가 예외인 특수기호들
		GlyphFactory glyphFactory;
		Glyph *glyph = glyphFactory.Make(" ");
		Long index = this->current->GetCurrent();

		if (index >= this->current->GetLength()) {
			this->current->Add(glyph);
		}
		else {
			this->current->Add(index, glyph);
		}
	}
	*/
	bool isControlPressed = ((::GetKeyState(VK_CONTROL) & 0x8000) != 0);
	DrawingPaper *drawingPaper = (DrawingPaper*)this->parentWidget();
	NShape *shape = drawingPaper->flowChart->GetAt(drawingPaper->indexOfSelected);
	//준비기호가 아닐 때 처리한다.
	if (!(dynamic_cast<Preparation*>(shape)) && !isControlPressed) {
		bool isMustCheck = false;
		//영문이 입력되면 무조건 처리한다.
		if ((nChar >= Qt::Key_A && nChar <= Qt::Key_Z) /*|| (nChar >= 97 && nChar <= 122)*/) {
			isMustCheck = true;
		}
		//숫자가 입력되면 원래 한 글자 이상이 입력되어 있었어야 하고 그 원래 글자가 영문이면 처리한다.
		else if ((nChar >= Qt::Key_0 && nChar <= Qt::Key_9) && this->current->GetCurrent() > 1) {
			char previous = *(this->current->GetAt(this->current->GetCurrent() - 2)->GetContent().c_str());
			if ((previous >= Qt::Key_A && previous <= Qt::Key_Z) /*|| (previous >= 97 && previous <= 122)*/) {
				isMustCheck = true;
			}
		}
		if (isMustCheck == true) {
			//현재 위치에 해당하는 단어만 추출하기
			String variable;

			Glyph *line = this->current->Clone();
			Long startIndex = line->MovePreviousWord();
			Long endIndex = line->MoveNextWord();
			Long i = startIndex;
			char character = *(line->GetAt(i++)->GetContent().c_str());
			variable += character;
			while (i < endIndex && ((character >= Qt::Key_A && character <= Qt::Key_Z) /*|| (character >= 97 && character <= 122)*/ ||
				(variable.GetLength() > 0 && (character >= Qt::Key_0 && character <= Qt::Key_9)))) {
				character = *(line->GetAt(i)->GetContent().c_str());
				variable += character;
				i++;
			}
			Long ret = drawingPaper->variableList->Find(variable);
			character = *(line->GetAt(startIndex)->GetContent().c_str());
			if (ret == -1 && (character != Qt::Key_Apostrophe && character != Qt::Key_QuoteDbl)) { //따옴표 뒤에 쓴 글자면 안함
				this->current->Remove(this->current->GetCurrent() - 1);
				BOOL result = PlaySound((LPCWSTR)"sound_button_wrong0.2.wav", NULL, SND_FILENAME);
			}
		}
	}
}

void Label::inputMethodEvent(QInputMethodEvent *event) {
	Notepad::inputMethodEvent(event);
}

void Label::paintEvent(QPaintEvent *event) {
	QRect frameRect = this->frameRect();
	this->painter->Resize(frameRect.width(), frameRect.height(), this->color);
	Notepad::paintEvent(event);
}

void Label::focusInEvent(QFocusEvent *event) {
	Notepad::focusInEvent(event);
}

void Label::focusOutEvent(QFocusEvent *event) {
	Notepad::focusOutEvent(event);

	//19.09.03 Label의 (편집된)내용을 기호 안의 실제 데이터로 넣는 처리==================
	DrawingPaper *canvas = (DrawingPaper*)this->parentWidget();

	string content = this->note->GetContent();
	String contents(content);

	NShape *shape = canvas->flowChart->GetAt(canvas->indexOfSelected);

	shape->Rewrite(contents);
	//=====================intellisense========================
	if (dynamic_cast<Preparation*>(shape)) {
		if (canvas->variableList != NULL) {
			delete canvas->variableList;
		}
		canvas->variableList = new VariableList;
		canvas->variableList->Add(shape->GetContents());
	}
	//=========================================================

	this->Destroy();
}

void Label::mousePressEvent(QMouseEvent *event) {
	if (this->sizeController != NULL) {
		delete this->sizeController;
		this->sizeController = NULL;
	}

	Notepad::mousePressEvent(event);

	if (this->sizeController == NULL) {
		this->sizeController = new SizeController(this);
	}
}

void Label::mouseMoveEvent(QMouseEvent *event) {
	Notepad::mouseMoveEvent(event);
}