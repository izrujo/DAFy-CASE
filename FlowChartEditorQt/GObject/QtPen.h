#ifndef _QTPEN_H
#define _QTPEN_H

#include "Pen.h"
#include <qpen.h>
#include <qbrush.h>

class QtPen : public Pen, public QPen {
public:
	QtPen(const QBrush &brush = QBrush(QColor(0, 0, 0), Qt::SolidPattern), float width = 1,
		Qt::PenStyle style = Qt::SolidLine, Qt::PenCapStyle cap = Qt::SquareCap,
		Qt::PenJoinStyle join = Qt::BevelJoin);
	QtPen(const QtPen& source);
	virtual ~QtPen();
	QtPen& operator=(const QtPen& source);

	virtual void SetObject(QPainter *qPainter);

	virtual GObject* Clone();

	virtual QBrush& GetBrush();
	virtual float GetWidth();
	virtual int GetPenStyle();
	virtual int GetPenCapStyle();
	virtual int GetPenJoinStyle();
};

#endif //_QTPEN_H