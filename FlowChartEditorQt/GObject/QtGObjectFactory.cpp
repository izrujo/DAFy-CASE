#include "QtGObjectFactory.h"
#include "QtPen.h"
#include "QtBrush.h"
#include "QtFont.h"

QtGObjectFactory::QtGObjectFactory()
	: GObjectFactory() {

}

QtGObjectFactory::~QtGObjectFactory() {

}

GObject* QtGObjectFactory::MakePen(const QBrush &brush, float width, Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join) {
	GObject *object = new QtPen(brush, width, style, cap, join);

	return object;
}

GObject* QtGObjectFactory::MakeBrush(const QColor &color, Qt::BrushStyle style) {
	GObject *object = new QtBrush(color, style);

	return object;
}

GObject* QtGObjectFactory::MakeFont(const QString &family, int pointSize, int weight, bool italic) {
	GObject *object = new QtFont(family, pointSize, weight, italic);

	return object;
}