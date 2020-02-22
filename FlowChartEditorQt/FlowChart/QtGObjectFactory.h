#ifndef _QTGOBJECTFACTORY_H
#define _QTGOBJECTFACTORY_H

#include "GObjectFactory.h"

class QtGObjectFactory : public GObjectFactory {
public:
	QtGObjectFactory();
	virtual ~QtGObjectFactory();

	virtual GObject* MakePen(const QBrush &brush, float width, Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join);
	virtual GObject* MakeBrush(const QColor &color, Qt::BrushStyle style);
	virtual GObject* MakeFont(const QString &family, int pointSize, int weight, bool italic);
};

#endif //_QTGOBJECTFACTORY_H