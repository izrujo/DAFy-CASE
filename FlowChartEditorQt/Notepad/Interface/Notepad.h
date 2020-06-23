#pragma once

#include <QtWidgets/QFrame>
#include "ui_Notepad.h"
#include "../Observer/Subject.h"
#include <windows.h>

class CaretController;
class CharacterMetrics;
class Glyph;
class Editor;
class GObject;
class String;

class Notepad : public QFrame, public Subject
{
	Q_OBJECT

public:
	Notepad(QWidget *parent = Q_NULLPTR);
	Notepad(String *text, QWidget *parent = Q_NULLPTR);
	Notepad(char *text, QWidget *parent = Q_NULLPTR);

private:
	NotepadUi::Ui::NotepadClass ui;

public:
	Glyph *note;
	Glyph *current; //Line
	CaretController *caretController;
	CharacterMetrics *characterMetrics;
	Glyph *highlight;
	Editor *editor;
	Glyph *clipBoard;
	GObject *painter;

protected:
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void inputMethodEvent(QInputMethodEvent *event);
	void paintEvent(QPaintEvent *event);
	void focusInEvent(QFocusEvent *event);
	void focusOutEvent(QFocusEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

public:
	bool GetIsComposing() const;

private:
	bool isComposing;
};

inline bool Notepad::GetIsComposing() const {
	return this->isComposing;
}