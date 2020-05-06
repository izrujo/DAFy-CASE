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
#include "Preparation.h"
#include "../Notepad/GlyphFactory.h"
#include "../GObject/Font.h"
#include "RuleKeeper.h"
#include "ContentsAnalyzer.h"
#include "VariableList.h"
#include "../Notepad/Highlight.h"
#include "../Notepad/Editor.h"
#include "../Notepad/Selector.h"
#include "../Notepad/KeyActionFactory.h"
#include "../Notepad/KeyActions.h"
#include "InputOutput.h"

#include <qevent.h>
#include <windows.h>
#include <qlabel.h>
#include <qstatusbar.h>

Label *Label::instance = 0;

Label *Label::Instance(String *text, QColor color, QWidget *parent)
{
	if (instance == 0)
	{
		instance = new Label(text, color, parent);
	}
	return instance;
}

Label *Label::Instance(QWidget *parent)
{
	if (instance == 0)
	{
		instance = new Label(parent);
	}
	return instance;
}


Label::Label(QWidget *parent)
	: Notepad(parent) {
	this->x = 0.0F;
	this->y = 0.0F;
	this->width = 0.0F;
	this->height = 0.0F;
	this->sizeController = NULL;
	this->color = QColor(255, 255, 255);

	this->sizeController = new SizeController(this);

	//공백 ! " ' ( ) * + , - . / 0~9 < = > A~Z ^ _ a~z
	char buffer;
	Long number = 32;
	Long i = 0;
	while (number <= 122) {
		if ((number >= 32 && number <= 34) || (number >= 39 && number <= 57) || // 공백문자 ~ " OR ' ~ 9 OR
			(number >= 60 && number <= 62) || (number >= 65 && number <= 90) || // < ~ > OR A ~ Z OR
			(number >= 94 && number <= 95) || (number >= 97 && number <= 122)) { // ^ ~ _ OR a ~ z
			buffer = number;
			this->allowedKeys[i++] = buffer;
		}
		number++;
	}

	this->isQuotes = false;
}

Label::Label(String *text, QColor color, QWidget *parent)
	: Notepad(text, parent) {
	this->x = 0.0F;
	this->y = 0.0F;
	this->width = 0.0F;
	this->height = 0.0F;
	this->sizeController = NULL;
	this->color = color;

	this->sizeController = new SizeController(this);

	//공백 ! " ' ( ) * + , - . / 0~9 < = > A~Z ^ _ a~z
	char buffer;
	Long number = 32;
	Long i = 0;
	while (number <= 122) {
		if ((number >= 32 && number <= 34) || (number >= 39 && number <= 57) || // 공백문자 ~ " OR ' ~ 9 OR
			(number >= 60 && number <= 62) || (number >= 65 && number <= 90) || // < ~ > OR A ~ Z OR
			(number >= 94 && number <= 95) || (number >= 97 && number <= 122)) { // ^ ~ _ OR a ~ z
			buffer = number;
			this->allowedKeys[i++] = buffer;
		}
		number++;
	}

	this->isQuotes = false;
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

void Label::Open(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Label::resizeEvent(QResizeEvent *event) {
	Notepad::resizeEvent(event);
}

void Label::keyPressEvent(QKeyEvent *event) {
	DrawingPaper *drawingPaper = (DrawingPaper *)this->parentWidget();
	if (drawingPaper->variableList == NULL) {
		Notepad::keyPressEvent(event);
	}
	else {
		int key = event->key();

		KeyActionFactory keyActionFactory(this);
		KeyAction *keyAction = keyActionFactory.Make(key);

		FlowChartEditor *editor = (FlowChartEditor*)drawingPaper->parentWidget();
		String text = event->text().toStdString();
		char *character = text;
		if (this->IsAllowed(*character) == true || keyAction != 0 || key == Qt::Key_Return) {
			Notepad::keyPressEvent(event);
			if (keyAction != 0) {
				delete keyAction;
			}
		}
		else {
			QString message = QString::fromLocal8Bit("    입력할 수 없는 문자입니다.");
			editor->messageStatus->setText(message);
			editor->statusBar->repaint();
		}
	}
}

void Label::inputMethodEvent(QInputMethodEvent *event) {
	DrawingPaper *drawingPaper = (DrawingPaper*)this->parentWidget();
	if (drawingPaper->variableList == NULL) {
		Notepad::inputMethodEvent(event);
	}
	else {
		if (this->isQuotes == true) {
			Notepad::inputMethodEvent(event);
		}
	}
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
	DrawingPaper *canvas = (DrawingPaper *)this->parentWidget();

	string content = this->note->GetContent();
	String contents(content);

	NShape *shape = canvas->flowChart->GetAt(canvas->indexOfSelected);

	//=====================intellisense========================
	if (canvas->variableList == NULL) {
		shape->Rewrite(contents);
		this->Destroy();
		canvas->label = NULL;
	}
	else {
		FlowChartEditor *editor = (FlowChartEditor*)canvas->parentWidget();
		QString message;

		bool isKeptVariableRule = true;
		bool isKeptOperatorRule = true;

		ContentsAnalyzer analyzer;
		RuleKeeper ruleKeeper;
		Array<String> variables = analyzer.MakeVariables(contents);
		Array<String> operators = analyzer.MakeOperators(contents);

		if (dynamic_cast<Preparation *>(shape)) {
			if (canvas->variableList != NULL) {
				delete canvas->variableList;
				canvas->variableList = NULL;
			}
			canvas->variableList = ruleKeeper.CheckVariableNamingRule(variables);
			isKeptVariableRule = (canvas->variableList->GetLength() > 0);
		}
		else {
			isKeptVariableRule = ruleKeeper.CheckVariableUsingRule(variables, canvas->variableList);
			if (dynamic_cast<InputOutput*>(shape)) {
				isKeptOperatorRule = (operators.GetLength() < 1);
			}
			else {
				isKeptOperatorRule = ruleKeeper.CheckOperatorRule(operators);
				contents = analyzer.CorrectOperators(contents);
			}
		}

		if (isKeptVariableRule == true && isKeptOperatorRule == true) {
			shape->Rewrite(contents);
			this->Destroy();
			canvas->label = NULL;
			message = QString::fromLocal8Bit("");
		}
		else {
			if (dynamic_cast<Preparation *>(shape)) {
				message = QString::fromLocal8Bit("    변수 선언이 잘못됐습니다.");
			}
			else {
				message = QString::fromLocal8Bit("    잘못된 변수 또는 연산자입니다.");
			}

			if (this->highlight == NULL) {
				this->highlight = new Highlight;
				this->editor->selector = new Selector(this);

				Long index = this->note->Last();
				this->current = this->note->GetAt(index);
				this->current->Last();

				Long i = 0;
				while (i <= index) {
					Glyph *line = this->note->GetAt(i);
					Long startColumn = 0;
					Long endColumn = line->GetLength();
					this->editor->selector->Right(i, startColumn, endColumn);
					i++;
				}
			}
			this->setFocus();
		}
		editor->messageStatus->setText(message);
		editor->statusBar->repaint();
	}
	//=========================================================
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

bool Label::IsAllowed(char key) {
	bool isAllowed = true;
	if (this->isQuotes == false) {
		Long i = 0;
		while (i < ALLOWEDKEYCOUNT && key != this->allowedKeys[i]) {
			i++;
		}
		if (key == 34 || key == 39) {
			this->isQuotes = true;
		}
		else if (i >= ALLOWEDKEYCOUNT) {
			isAllowed = false;
		}

	}

	return isAllowed;
}