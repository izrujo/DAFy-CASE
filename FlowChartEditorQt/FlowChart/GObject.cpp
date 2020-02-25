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

//Painter 가상 함수 정의
GObject* GObject::SelectObject(const GObject& object) {
	return 0;
}

GObject* GObject::CurrentObject(string identify) {
	return 0;
}

void GObject::Update() {

}

GObject* GObject::GetAt(Long index) {
	return 0;
}

Long GObject::GetCapacity() const {
	return 0;
}

Long GObject::GetLength() const {
	return -1;
}