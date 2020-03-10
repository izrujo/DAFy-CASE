#ifndef _EDITORINTROFORM_H
#define _EDITORINTROFORM_H

#include <QtWidgets/QFrame>

class EditorIntroForm : public QFrame {
public:
	EditorIntroForm(QWidget *parent = Q_NULLPTR);
	~EditorIntroForm();
protected:
	void paintEvent(QPaintEvent *event);
};

#endif //_EDITORINTROFORM_H