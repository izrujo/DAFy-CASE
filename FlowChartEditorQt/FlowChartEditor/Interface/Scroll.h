#ifndef _SCROLL_H
#define _SCROLL_H

#include <qscrollbar.h>
typedef signed long int Long;

class Scroll : public QScrollBar
{
	Q_OBJECT

public:
	Scroll(Qt::Orientation orientation = Qt::Vertical, QWidget *parent = NULL);
	Scroll(const Scroll& source);
	~Scroll();

	bool SetFromConstructorFlag(bool flag);
private:
	bool isFromConstructor;
signals:
	void valueChanged(int value);
public slots:
	void Move(Long value);
};

#endif //_SCROLL_H