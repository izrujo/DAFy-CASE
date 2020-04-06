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

QColor& QtBrush::GetColor() {
	return const_cast<QColor&>(this->color()); //color() 함수가 const 형식 반환함.
}

int QtBrush::GetStyle() {
	return this->style();
}