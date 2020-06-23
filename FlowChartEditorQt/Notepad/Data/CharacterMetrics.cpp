#include "CharacterMetrics.h"
#include "Glyph.h"
#include "Leaf/Character.h"
#include "../Interface/Notepad.h"

#include "../../Graphic Objects/GObject.h"

#include <qfont.h>

CharacterMetrics::CharacterMetrics(Notepad *notepad) {
	this->notepad = notepad;

	GObject *font = this->notepad->painter->CurrentObject("Font");
	//QFontMetrics metrics(QFont(font->GetFamily(), font->GetPointSize(), font->GetWeight(), font->GetItalic())); //=>Qt 5.14.2 에서 안되는 코드 ???
	QString family = font->GetFamily();
	Long pointSize = font->GetPointSize();
	Long weight = font->GetWeight();
	bool italic = font->GetItalic();
	QFont metricsFont(family, pointSize, weight, italic); 
	QFontMetrics metrics(metricsFont);
	QChar buffer;

	Long i = 1;
	while (i < 128) {
		buffer = i;
		this->widths[i] = metrics.horizontalAdvance(buffer);
		i++;
	}
	this->widths[9] = this->widths[32] * 8; //Tab 처리
	this->widths[0] = this->widths[32];
	this->widths[i] = metrics.horizontalAdvance('가'); //한글
	this->height = metrics.height(); //28
	this->descent= metrics.descent(); //5 : 
}

CharacterMetrics::CharacterMetrics(const CharacterMetrics& source) {
	this->notepad = source.notepad;

	Long i = 0;
	while (i < 129) {
		this->widths[i] = source.widths[i];
		i++;
	}

	this->height = source.height;
	this->descent = source.descent;
}

CharacterMetrics::~CharacterMetrics() {

}

CharacterMetrics& CharacterMetrics::operator =(const CharacterMetrics& source) {
	this->notepad = source.notepad;

	Long i = 0;
	while (i < 129) {
		this->widths[i] = source.widths[i];
		i++;
	}

	this->height = source.height;
	this->descent = source.descent;

	return *this;
}

Long CharacterMetrics::GetX(Glyph *line) {
	Long x = 0;

	Long i = 0;
	while (i < line->GetCurrent()) {
		Glyph *character = line->GetAt(i);

		if (dynamic_cast<SingleByteCharacter*>(character)) {
			string content = character->GetContent();
			if (content.length() == 1) {
				x += this->widths[content[0]];
			}
			else {
				x += this->widths[9]; //Tab
			}
		}
		else if (dynamic_cast<DoubleByteCharacter*>(character)) {
			x += this->widths[128];
		}

		i++;
	}

	return x;
}

Long CharacterMetrics::GetX(Glyph *line, Long index) {
	Long x = 0;

	Long i = 0;
	while (i < index) {
		Glyph *character = line->GetAt(i);

		if (dynamic_cast<SingleByteCharacter*>(character)) {
			string content = character->GetContent();
			if (content.length() == 1) {
				x += this->widths[content[0]];
			}
			else {
				x += this->widths[9]; //Tab
			}
		}
		else if (dynamic_cast<DoubleByteCharacter*>(character)) {
			x += this->widths[128];
		}

		i++;
	}

	return x;
}

Long CharacterMetrics::GetX(const string& buffer) {
	Long x = 0;

	Long i = 0;
	while (i < buffer.length()) {
		if (!(buffer[i] & 0x80)) {
			x += this->widths[buffer[0]];
			/*
			if (buffer.length() == 1) {
				x += this->widths[buffer[0]];
			}
			else {
				x += this->widths[9]; //Tab
			}*/
			i++;
		}
		else if (buffer[i] & 0x80) {
			x += this->widths[128];
			i += 2;
		}
	}

	return x;
}

Long CharacterMetrics::GetY(Long index) {
	return this->height * (index);
}

Long CharacterMetrics::GetColumn(Glyph *line, Long x) {
	Long index = 0;
	Long currentX = 0;
	Long previousX = -1;
	Glyph *character;
	string content;
	Long asciiIndex;
	Long width;

	while (index < line->GetLength() && currentX < x) {
		character = line->GetAt(index);
		content = character->GetContent();

		if (dynamic_cast<SingleByteCharacter*>(character)) {
			if (content[1] == '\0') { // 탭이 아닐 때
				asciiIndex = content[0];
			}
			else {
				asciiIndex = 9;
			}
			width = this->widths[asciiIndex];
		}
		else if (dynamic_cast<DoubleByteCharacter*>(character)) {
			width = this->widths[128];
		}
		previousX = currentX;
		currentX += width;
		index++;
	}

	if ((x - previousX) < (currentX - x)) {
		index--;
	}

	return index;
}

Long CharacterMetrics::GetRow(Long y) {
	return y / this->height;
}