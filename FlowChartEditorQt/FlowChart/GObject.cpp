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

//Qt Concrete GObject virtual declarations
//QtPen
QBrush& GObject::GetBrush() {
	return QBrush(); //return empty QString instance
}

float GObject::GetWidth() {
	return -1;
}

int GObject::GetPenStyle() {
	return -1;
}

int GObject::GetPenCapStyle() {
	return -1;
}

int GObject::GetPenJoinStyle() {
	return -1;
}

//QtBrush
QColor& GObject::GetColor() {
	return QColor(); //return empty QString instance
}

int GObject::GetStyle() {
	return -1;
}

//QtFont
QString& GObject::GetFamily() {
	return QString();  //return empty QString instance
}

int GObject::GetPointSize() {
	return -1;
}

int GObject::GetWeight() {
	return -1;
}

bool GObject::GetItalic() {
	return false;
}