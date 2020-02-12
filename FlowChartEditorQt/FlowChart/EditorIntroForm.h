#ifndef _EDITORINTROFORM_H
#define _EDITORINTROFORM_H

#include <afxwin.h>

class EditorIntroForm : public CFrameWnd {
public:
	EditorIntroForm();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	afx_msg void OnClose();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

#endif //_EDITORINTROFORM_H