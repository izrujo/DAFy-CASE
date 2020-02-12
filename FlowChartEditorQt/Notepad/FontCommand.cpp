#include "FontCommand.h"
#include "NotepadForm.h"
#include "Font.h"
#include "CharacterMetrics.h"
#include <afxdlgs.h>

FontCommand::FontCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}
FontCommand::FontCommand(const FontCommand& source) {
	this->notepadForm = source.notepadForm;
}
FontCommand::~FontCommand() {
}
void FontCommand::Execute() {
	LOGFONT logFont = this->notepadForm->font->GetFont();
	COLORREF color;
	CFontDialog fontDialog(&logFont);
	int ret = fontDialog.DoModal();
	if (ret == IDOK) {
		//폰트 대화 상자에서 폰트 정보를 가져온다.
		fontDialog.GetCurrentFont(&logFont);
		color = fontDialog.GetColor();
		if (this->notepadForm->font != NULL) {
			delete this->notepadForm->font;
		}
		this->notepadForm->font = new Font(logFont, color, this->notepadForm);
		if (this->notepadForm->characterMetrics != NULL) {
			delete this->notepadForm->characterMetrics;
		}
		this->notepadForm->characterMetrics = new CharacterMetrics(this->notepadForm);
		this->notepadForm->Notify();
		this->notepadForm->Invalidate();
	}
}

FontCommand& FontCommand::operator =(const FontCommand& source) {
	this->notepadForm = source.notepadForm;

	return *this;
}