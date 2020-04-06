#include "GObjectFactory.h"

GObjectFactory::GObjectFactory() {

}

GObjectFactory::~GObjectFactory() {

}

GObject* GObjectFactory::MakePen(const QBrush &brush, float width, Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join) {
	return 0;
}

GObject* GObjectFactory::MakeBrush(const QColor &color, Qt::BrushStyle style) {
	return 0;
}

GObject* GObjectFactory::MakeFont(const QString &family, int pointSize, int weight, bool italic) {
	return 0;
}