#ifndef _EDITORINTROFORM_H
#define _EDITORINTROFORM_H

#include <QtWidgets/QFrame>
#include "ui_EditorIntroForm.h"

class EditorIntroForm : public QFrame 
{
	Q_OBJECT

private:
	EditorIntroFormUi::Ui::EditorIntroFormClass ui;
public:
	EditorIntroForm(QWidget *parent = Q_NULLPTR);
protected:
	void paintEvent(QPaintEvent *event);
	void closeEvent(QCloseEvent* event);
};

#endif //_EDITORINTROFORM_H