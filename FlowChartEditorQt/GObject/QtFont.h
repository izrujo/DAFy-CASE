#ifndef _QTFONT_H
#define _QTFONT_H

#include "Font.h"
#include <qfont.h>

class QtFont : public Font, public QFont {
public:
	QtFont(const QString &family = "Malgun Gothic", int pointSize = 10, int weight = 50, bool italic = false);
	QtFont(const QtFont& source);
	virtual ~QtFont();
	QtFont& operator=(const QtFont& source);

	virtual void SetObject(QPainter *qPainter);

	virtual GObject* Clone();

	virtual QString& GetFamily();
	virtual int GetPointSize();
	virtual int GetWeight();
	virtual bool GetItalic();
};

#endif //_QTFONT_H