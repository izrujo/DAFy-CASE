#include "FontCommand.h"
#include "Notepad.h"
#include "CharacterMetrics.h"
#include "GObject.h"
#include "QtGObjectFactory.h"

#include <qfont.h>
#include <qfontdialog.h>

FontCommand::FontCommand(Notepad *notepad) {
	this->notepad = notepad;
}
FontCommand::FontCommand(const FontCommand& source) {
	this->notepad = source.notepad;
}
FontCommand::~FontCommand() {
}
void FontCommand::Execute() {
	//취소 눌렀을 때 설정할 원래 폰트
	GObject *oldFont = this->notepad->painter->CurrentObject("Font");
	QFont initial(oldFont->GetFamily(), oldFont->GetPointSize(), oldFont->GetWeight(), oldFont->GetItalic());

	bool ok;
	QFont userfont = QFontDialog::getFont(&ok, initial, this->notepad);

	if (ok == true) {
		QtGObjectFactory factory;
		GObject *font = factory.MakeFont(userfont.family(), userfont.pointSize(), userfont.weight(), userfont.italic());
		this->notepad->painter->SelectObject(*font);
		//색깔 설정 필요함.Pen => dialog에 색깔 설정이 없음.
		this->notepad->painter->Update();
		if (this->notepad->characterMetrics != NULL) {
			delete this->notepad->characterMetrics;
		}
		this->notepad->characterMetrics = new CharacterMetrics(this->notepad);
		this->notepad->Notify();
		this->notepad->repaint();
	}
}

FontCommand& FontCommand::operator =(const FontCommand& source) {
	this->notepad = source.notepad;

	return *this;
}