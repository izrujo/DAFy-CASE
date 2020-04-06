#include "QtPen.h"
#include <qpainter.h>

QtPen::QtPen(const QBrush &brush, float width,
	Qt::PenStyle style, Qt::PenCapStyle cap,
	Qt::PenJoinStyle join)
	: Pen(), QPen(brush, width, style, cap, join) {

}

QtPen::QtPen(const QtPen& source)
	: Pen(source), QPen(source) {

}

QtPen::~QtPen() {
	//QPen::~QPen();
}

QtPen& QtPen::operator=(const QtPen& source) {
	Pen::operator=(source);
	QPen::operator=(source);

	return *this;
}

void QtPen::SetObject(QPainter *qPainter) {
	qPainter->setPen(static_cast<QPen&>(*this));
}

GObject* QtPen::Clone() {
	return new QtPen(*this);
}

QBrush& QtPen::GetBrush() {
	return this->brush();
}

float QtPen::GetWidth() {
	return this->widthF();
}

int QtPen::GetPenStyle() {
	return this->style();
}

int QtPen::GetPenCapStyle() {
	return this->capStyle();
}

int QtPen::GetPenJoinStyle() {
	return this->joinStyle();
}