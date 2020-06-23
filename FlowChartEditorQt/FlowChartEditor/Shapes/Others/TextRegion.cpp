#include "TextRegion.h"
#include "../../Paint/FlowChartVisitor.h"
#include "../../../Graphic Objects/Composite/Painter.h"
#include "../../../Graphic Objects/Factory/Qt/QtGObjectFactory.h"


TextRegion::TextRegion(float x, float y, float width, float height,
	QColor backGroundColor, Qt::PenStyle borderLine, QColor borderColor, String contents)
	: NShape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

TextRegion::~TextRegion() {

}

TextRegion::TextRegion(const TextRegion& source)
	:NShape(source) {

}

TextRegion& TextRegion::operator =(const TextRegion& source) {
	NShape::operator=(source);

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


NShape* TextRegion::Clone() {
	return new TextRegion(*this);
}

bool TextRegion::IsIncluded(QPointF point) {
	bool ret;

	QRectF rect(this->x, this->y, this->x + this->width, this->y + this->height);
	QRegion region(rect.toRect());

	ret = region.contains(point.toPoint());
	
	return ret;
}