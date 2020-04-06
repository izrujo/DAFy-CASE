#pragma once

#include <QtWidgets/QFrame>
#include "ui_Notepad.h"
#include "Subject.h"
#include <windows.h>

class CaretController;
class CharacterMetrics;
class Glyph;
class Editor;
class GObject;
class QMenuBar;
class QMenu;
class QAction;

class Notepad : public QFrame, public Subject
{
	Q_OBJECT

public:
	Notepad(QFrame *parent = Q_NULLPTR);

private:
	Ui::NotepadClass ui;

public:
	Glyph *note;
	Glyph *current; //Line
	CaretController *caretController;
	CharacterMetrics *characterMetrics;
	Glyph *highlight;
	Editor *editor;
	Glyph *clipBoard;
	GObject *painter;
	QMenuBar *menuBar;

protected:
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void inputMethodEvent(QInputMethodEvent *event);
	
	void paintEvent(QPaintEvent *event);
	void focusInEvent(QFocusEvent *event);
	void focusOutEvent(QFocusEvent *event);
	//void OnCommandRange(UINT uID);
	//void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

public:
	bool GetIsComposing() const;
private:
	bool isComposing;

	//¸Þ´º
private slots:
	void CommandRange(char *text);

private:
	void CreateActions();
	void CreateMenus();
	QMenu *formatMenu;
	QAction *fontSetAction;

};

inline bool Notepad::GetIsComposing() const {
	return this->isComposing;
}