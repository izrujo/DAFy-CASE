#include "QtGObjectFactory.h"
#include "../../Leaf/Qt/QtPen.h"
#include "../../Leaf/Qt/QtBrush.h"
#include "../../Leaf/Qt/QtFont.h"

QtGObjectFactory::QtGObjectFactory()
	: GObjectFactory() {

}

QtGObjectFactory::~QtGObjectFactory() {

}

GObject* QtGObjectFactory::MakePen(const QBrush &brush, float width, Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join) {
	return new QtPen(brush, width, style, cap, join);
}

GObject* QtGObjectFactory::MakeBrush(const QColor &color, Qt::BrushStyle style) {
	return new QtBrush(color, style);
}

GObject* QtGObjectFactory::MakeFont(const QString &family, int pointSize, int weight, bool italic) {
	return new QtFont(family, pointSize, weight, italic);
}