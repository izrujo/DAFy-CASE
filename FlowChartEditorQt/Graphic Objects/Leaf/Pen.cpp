#include "Pen.h"

Pen::Pen()
	: GObject() {

}

Pen::Pen(const Pen& source)
	: GObject(source) {

}

Pen::~Pen() {

}

Pen& Pen::operator=(const Pen& source) {
	GObject::operator=(source);

	return *this;
}

void Pen::SetObject(QPainter *qPainter) {

}

string Pen::GetIdentify() {
	return "Pen";
}