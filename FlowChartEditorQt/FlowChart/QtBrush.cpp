#include "QtBrush.h"
#include <qpainter.h>

QtBrush::QtBrush(const QColor &color, Qt::BrushStyle style)
	: Brush(), QBrush(color, style) {

}

QtBrush::QtBrush(const QtBrush& source)
	: Brush(source), QBrush(source) {

}

QtBrush::~QtBrush() {
	//QBrush::~QBrush();
}

QtBrush& QtBrush::operator=(const QtBrush& source) {
	Brush::operator=(source);
	QBrush::operator=(source);

	return *this;
}

void QtBrush::SetObject(QPainter *qPainter) {
	qPainter->setBrush(static_cast<QBrush&>(*this));
}

GObject* QtBrush::Clone() {
	return new QtBrush(*this);
}