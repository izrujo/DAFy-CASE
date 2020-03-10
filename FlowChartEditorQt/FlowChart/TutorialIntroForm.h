#ifndef _TUTORIALINTROFORM_H
#define _TUTORIALINTROFORM_H

#include <QtWidgets/QFrame>

class TextRegion;
class GObject;

class TutorialIntroForm : public QFrame
{
	Q_OBJECT

public:
	TutorialIntroForm(QWidget *parent = Q_NULLPTR);
protected:
	void closeEvent(QCloseEvent *event);
	void paintEvent(QPaintEvent *event);
	//BOOL OnEraseBkgnd(CDC *pDC);
	void mouseReleaseEvent(QMouseEvent *event);
	//void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	TextRegion *message;
	TextRegion *guide;
	GObject *painter;
};

#endif //_TUTORIALFORM_H
