#include "FlowChartFont.h"
#include "FlowChartEditor.h"

FlowChartFont::FlowChartFont(FlowChartEditor *editor) {
	this->editor = editor;
	CDC *dc = this->editor->GetDC();
	CFont *dcFont = dc->GetCurrentFont();
	dcFont->GetLogFont(&this->font);
	this->font.lfHeight = -18;
	this->font.lfWidth = 0;
	this->font.lfWeight = 700;
	strcpy(this->font.lfFaceName, _T("consolas"));
	this->color = 0x00000000;
}

FlowChartFont::FlowChartFont(FlowChartEditor *editor, LOGFONT font, COLORREF color) {
	this->editor = editor;
	this->font = font;
	this->color = color;
}

FlowChartFont::FlowChartFont(const FlowChartFont& source) {
	this->editor = source.editor;
	this->font = source.font;
	this->color = source.color;
}

FlowChartFont::~FlowChartFont() {

}

FlowChartFont& FlowChartFont::operator=(const FlowChartFont& source) {
	this->editor = source.editor;
	this->font = source.font;
	this->color = source.color;

	return *this;
}

HFONT FlowChartFont::Create() {
	return ::CreateFontIndirectA(&this->font);
}