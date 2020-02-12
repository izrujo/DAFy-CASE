#include "TextRegion.h"
#include "Painter.h"
#include "FlowChartVisitor.h"

TextRegion::TextRegion(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents, Direction direction)
	:Shape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

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

void TextRegion::Draw(CDC *dc) {
	CFont font;
	font.CreateFontA(-100, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "±¼¸²");
	CFont *oldFont = dc->SelectObject(&font);
	COLORREF oldColor = dc->SetTextColor(this->backGroundColor);

	BOOL ret = dc->TextOut(this->x, this->y, CString(this->contents));

	dc->SetTextColor(oldColor);
	dc->SelectObject(oldFont);
}

void TextRegion::Draw(Painter *painter) {
	RECT rect = { this->x, this->y, this->x + this->width, this->y + this->height };
	painter->DrawText(50, this->contents, this->contents.GetLength(), &rect, NULL);
}

Shape* TextRegion::Clone() {
	return new TextRegion(*this);
}

BOOL TextRegion::IsIncluded(CDC *dc, POINT point) {
	CRgn region;
	BOOL ret;
	region.CreateRectRgn(x, y, x + width, y + height);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}