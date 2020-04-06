//Caret.h

#ifndef _CARET_H
#define _CARET_H

#include <qobject.h>
#include <qtimer.h>
#include <qrect.h>
#include <qpainter.h>

typedef signed long int Long;

class QWidget;

class Caret : public QObject
{
	Q_OBJECT

public:
	Caret(QWidget *parent = Q_NULLPTR);
	Caret(const Caret& source);
	~Caret();
	Caret& operator=(const Caret& source);

	void Show();
	void Hide();
	void Set(QRect rect);
	void Paint(QPainter& painter);

public slots:
	void onTimer();

private:
	QWidget *parent;
	bool isVisible;
	bool isBlink;
	QRect rect;
	QTimer timer;
};

#endif // !_CARET_H
