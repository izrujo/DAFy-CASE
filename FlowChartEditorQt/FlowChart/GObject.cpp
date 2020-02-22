#include "GObject.h"

GObject::GObject() {

}

GObject::GObject(const GObject& source) {

}

GObject::~GObject() {

}

GObject& GObject::operator=(const GObject& source) {
	return *this;
}

void GObject::SetObject(QPainter *qPainter) {

}

string GObject::GetIdentify() {
	return "";
}