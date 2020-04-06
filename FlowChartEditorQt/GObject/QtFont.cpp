#include "QtFont.h"
#include <qpainter.h>

QtFont::QtFont(const QString &family, int pointSize, int weight, bool italic)
	: Font(), QFont(family, pointSize, weight, italic) {

}

QtFont::QtFont(const QtFont& source)
	: Font(source), QFont(source) {

}

QtFont::~QtFont() {
	//QFont::~QFont();
}

QtFont& QtFont::operator=(const QtFont& source) {
	Font::operator=(source);
	QFont::operator=(source);

	return *this;
}

void QtFont::SetObject(QPainter *qPainter) {
	qPainter->setFont(static_cast<QFont&>(*this));
}

GObject* QtFont::Clone() {
	return new QtFont(*this);
}

QString& QtFont::GetFamily() {
	return this->family();
}

int QtFont::GetPointSize() {
	return this->pointSize();
}

int QtFont::GetWeight() {
	return this->weight();
}

bool QtFont::GetItalic() {
	return this->italic();
}