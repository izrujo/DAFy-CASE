#include "QtPainter.h"

#include <qpainter.h>
#include <qpixmap.h>

QtPainter::QtPainter(Long width, Long height, Long capacity)
	: Painter(capacity) {
	this->qPixmap = new QPixmap(width, height);
	this->qPainter = new QPainter(this->qPixmap);
}

QtPainter::QtPainter(const QtPainter& source)
	: Painter(source) {
	this->qPixmap = source.qPixmap;
	this->qPainter = source.qPainter;
}

QtPainter::~QtPainter() {
	if (this->qPixmap != NULL) {
		delete this->qPixmap;
	}
	if (this->qPainter != NULL) {
		delete this->qPainter;
	}
}

QtPainter& QtPainter::operator=(const QtPainter& source) {
	Painter::operator=(source);

	return *this;
}

void QtPainter::Update(Long index) {
	GObject *object = this->objects.GetAt(index);
	object->SetObject(this->qPainter);
}

GObject* QtPainter::Clone() {
	return new QtPainter(*this);
}