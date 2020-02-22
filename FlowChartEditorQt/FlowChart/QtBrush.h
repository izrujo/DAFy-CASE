#ifndef _QTBRUSH_H
#define _QTBRUSH_H

#include "Brush.h"
#include <qbrush.h>

class QtBrush : public Brush, public QBrush {
public:
	QtBrush(const QColor &color = QColor(255, 255, 255), Qt::BrushStyle style = Qt::SolidPattern);
	QtBrush(const QtBrush& source);
	virtual ~QtBrush();
	QtBrush& operator=(const QtBrush& source);

	virtual void SetObject(QPainter *qPainter);

	virtual GObject* Clone();
};

#endif //_QTBRUSH_H