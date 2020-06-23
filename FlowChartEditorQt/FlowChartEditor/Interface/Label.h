/******************************************************************
* 파일 이름 :  Label.h
* 기     능 : Text Class boundary
* 작  성 자 : 송윤창
* 작성 일자 : 2015년 4월 20일 
*******************************************************************/
#ifndef _LABEL_H
#define _LABEL_H

#include "../../Notepad/Interface/Notepad.h"

#define ALLOWEDKEYCOUNT 79

typedef signed long int Long;
typedef unsigned long int ULong;

class Text;
class String;
class Caret;
class SizeController;

class Label : public Notepad {
public:
	static Label* Instance(QWidget *parent = Q_NULLPTR);
	static Label* Instance(String *text, QColor color = QColor(255, 255, 255), QWidget *parent = Q_NULLPTR);
	static void Destroy();
	void Open(float x, float y, float width, float height);

	bool IsAllowed(char key);

	float GetX() const;
	float GetY() const;
	float GetWidth() const;
	float GetHeight() const;

protected:
	Label(QWidget *parent = Q_NULLPTR);
	Label(String *text, QColor color, QWidget *parent = Q_NULLPTR);
	~Label();

public:
	SizeController *sizeController;
private:
	// 위치와 크기
	float x;
	float y;
	float width;
	float height;

	QColor color;

	char allowedKeys[ALLOWEDKEYCOUNT];
	bool isQuotes;
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

inline float Label::GetX() const {
	return this->x;
}
inline float Label::GetY() const {
	return this->y;
}
inline float Label::GetWidth() const {
	return this->width;
}
inline float Label::GetHeight() const {
	return this->height;
}

#endif //_LABEL_H