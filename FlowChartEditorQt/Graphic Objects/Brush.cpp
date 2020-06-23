#include "Brush.h"

Brush::Brush()
	: GObject() {

}

Brush::Brush(const Brush& source)
	: GObject(source) {

}

Brush::~Brush() {

}

Brush& Brush::operator=(const Brush& source) {
	GObject::operator=(source);

	return *this;
}

void Brush::SetObject(QPainter *qPainter) {

}

string Brush::GetIdentify() {
	return "Brush";
}