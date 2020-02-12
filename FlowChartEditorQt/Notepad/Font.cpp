#include "Font.h"
#include "NotepadForm.h"


Font::Font(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	CDC *dc = this->notepadForm->GetDC();
	CFont *dcFont = dc->GetCurrentFont();
	dcFont->GetLogFont(&this->font);
	this->color = 0x00000000;
}

Font::Font(LOGFONT Font, COLORREF color, NotepadForm *notepadForm) {
	this->font = Font;
	this->color = color;
	this->notepadForm = notepadForm;
}

Font::Font(const Font& source) {
	this->font = source.font;
	this->color = source.color;
	this->notepadForm = source.notepadForm;
}

Font::~Font() {
}

void Font::Create(CFont& font) {
	font.CreateFontIndirectA(&this->font);
}

Font& Font::operator = (const Font& source) {
	this->font = source.font;
	this->color = source.color;
	this->notepadForm = source.notepadForm;

	return *this;
}