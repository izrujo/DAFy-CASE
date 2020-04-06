#ifndef _QTGOBJECTFACTORY_H
#define _QTGOBJECTFACTORY_H

#include "GObjectFactory.h"

class QtGObjectFactory : public GObjectFactory {
public:
	QtGObjectFactory();
	virtual ~QtGObjectFactory();

	virtual GObject* MakePen(const QBrush &brush, float width, Qt::PenStyle style = Qt::SolidLine, 
		Qt::PenCapStyle cap = Qt::SquareCap, Qt::PenJoinStyle join = Qt::BevelJoin);
	virtual GObject* MakeBrush(const QColor &color, Qt::BrushStyle style = Qt::SolidPattern);
	virtual GObject* MakeFont(const QString &family, int pointSize, int weight, bool italic);
};

#endif //_QTGOBJECTFACTORY_H