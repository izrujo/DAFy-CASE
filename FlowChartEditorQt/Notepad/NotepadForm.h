#ifndef _NOTEPADFORM_H
#define _NOTEPADFORM_H

#include <afxwin.h>
#include "Subject.h"

class Font;
class CaretController;
class CharacterMetrics;
class Glyph;
class Editor;
class String;
class NotepadForm : public CWnd, public Subject {
public:
	NotepadForm();
	NotepadForm(String *text);
	NotepadForm(char *text);
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	Glyph *note;
	Glyph *current; //Line
	CaretController *caretController;
	Font *font;
	CharacterMetrics *characterMetrics;
	Glyph *highlight;
	Editor *editor;
	Glyph *clipBoard;
protected:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeChar(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd *pNewWnd);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
	afx_msg void OnCommandRange(UINT uID);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	BOOL GetIsComposing() const;
private:
	BOOL isComposing;
	CMenu menu;
};
inline BOOL NotepadForm::GetIsComposing() const {
	return this->isComposing;
}

#endif //_NOTEPADFORM_H