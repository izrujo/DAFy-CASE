#include "TextRegion.h"
#include "../GObject/Painter.h"
#include "FlowChartVisitor.h"
#include "../GObject/QtGObjectFactory.h"

TextRegion::TextRegion(Long x, Long y, Long width, Long height,
	QColor backGroundColor, Qt::PenStyle borderLine, QColor borderColor, String contents)
	: Shape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

TextRegion::~TextRegion() {

}

TextRegion::TextRegion(const TextRegion& source)
	:Shape(source) {

}

TextRegion& TextRegion::operator =(const TextRegion& source) {
	Shape::operator=(source);

	return *this;
}

void TextRegion::Draw(GObject *painter) {
	QtGObjectFactory factory;
	GObject *current = painter->CurrentObject("Font");
	QString familyName = dynamic_cast<QFont*>(current)->family();
	GObject *font = factory.MakeFont(familyName, 50, 70, false);
	painter->SelectObject(*font);
	painter->Update();

	painter->DrawTextQ(this->x, this->y, QString::fromLocal8Bit(this->contents));

	painter->SelectObject(*current);
	painter->Update();
	if (font != NULL) {
		delete font;
	}
}


Shape* TextRegion::Clone() {
	return new TextRegion(*this);
}

bool TextRegion::IsIncluded(QPoint point) {
	bool ret;

	QRect rect(this->x, this->y, this->x + this->width, this->y + this->height);
	QRegion region(rect);

	ret = region.contains(point);
	
	return ret;
}