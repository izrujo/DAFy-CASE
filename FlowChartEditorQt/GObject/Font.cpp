#include "Font.h"

Font::Font()
	: GObject() {

}

Font::Font(const Font& source)
	: GObject(source) {

}

Font::~Font() {

}

Font& Font::operator=(const Font& source) {
	GObject::operator=(source);

	return *this;
}

void Font::SetObject(QPainter *qPainter) {

}

string Font::GetIdentify() {
	return "Font";
}