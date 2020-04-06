#ifndef _TOOLTIP_H
#define _TOOLTIP_H

#include "../Notepad/NotepadForm.h"
#include <qcolor.h>
#include <QtWidgets/QFrame>

class SizeController;

class ToolTip : public NotepadForm {
public:
	static ToolTip* Instance();
	static ToolTip* Instance(char(*text), QColor color);
	static void Destroy();
	void Open(Long x, Long y, Long width, Long height);

	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;

protected:
	ToolTip();
	ToolTip(char(*text), QColor color);
	~ToolTip();

private:
	// 위치와 크기
	Long x;
	Long y;
	Long width;
	Long height;

	QColor color;
private:
	static ToolTip *instance;

protected:
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void paintEvent(QPaintEvent *event);
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

inline Long ToolTip::GetX() const {
	return this->x;
}
inline Long ToolTip::GetY() const {
	return this->y;
}
inline Long ToolTip::GetWidth() const {
	return this->width;
}
inline Long ToolTip::GetHeight() const {
	return this->height;
}

#endif //_TOOLTIP_H