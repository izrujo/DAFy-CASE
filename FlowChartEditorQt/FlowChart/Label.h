/******************************************************************
* 파일 이름 :  Label.h
* 기     능 : Text Class boundary
* 작  성 자 : 송윤창
* 작성 일자 : 2015년 4월 20일 
*******************************************************************/
#ifndef _LABEL_H
#define _LABEL_H

#include "../Notepad/Notepad.h"

typedef signed long int Long;
typedef unsigned long int ULong;

class Text;
class String;
class Caret;
class SizeController;

class Label : public Notepad {
public:
	static Label* Instance(QWidget *parent = Q_NULLPTR);
	static Label* Instance(String *text, QWidget *parent = Q_NULLPTR);
	static void Destroy();
	void Open(Long x, Long y, Long width, Long height);

	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;

protected:
	Label(QWidget *parent = Q_NULLPTR);
	Label(String *text, QWidget *parent = Q_NULLPTR);
	~Label();

public:
	SizeController *sizeController;
private:
	// 위치와 크기
	Long x;
	Long y;
	Long width;
	Long height;

	//QColor color; Notepad StyleSheet 기능 이용
private:
	static Label *instance;
protected:
	void resizeEvent(QResizeEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void inputMethodEvent(QInputMethodEvent *event);
	void paintEvent(QPaintEvent *event);
	void focusInEvent(QFocusEvent *event);
	void focusOutEvent(QFocusEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
};

inline Long Label::GetX() const {
	return this->x;
}
inline Long Label::GetY() const {
	return this->y;
}
inline Long Label::GetWidth() const {
	return this->width;
}
inline Long Label::GetHeight() const {
	return this->height;
}

#endif //_LABEL_H