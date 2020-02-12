#include "Note.h"

Note::Note(Long capacity)
	: Composite(capacity) {
}

Note::Note(const Note& source)
	: Composite(source) {
}

Note::~Note() {
}

Long Note::Next() {
	this->current = Composite::Next();
	if (this->current >= this->length) {
		this->current = this->length - 1;
	}

	return this->current;
}

Long Note::Last() {
	this->current = this->length - 1;

	return this->current;
}

Long Note::MovePreviousWord() {
	Glyph *line;
	line = this->glyphs.GetAt(this->current);
	if (line->GetCurrent() >= 1) {
		line->MovePreviousWord();
	}
	else {
		if (this->current > 0) {
			this->current--;
			line = this->glyphs.GetAt(this->current);
			line->Last();
		}
	}

	return this->current;
}

Long Note::MoveNextWord() {
	Glyph *line;
	line = this->glyphs.GetAt(this->current);
	if (line->GetCurrent() < line->GetLength()) {
		line->MoveNextWord();
	}
	else {
		if (this->current < this->length - 1) {
			this->current++;
			line = this->glyphs.GetAt(this->current);
			line->First();
		}
	}

	return this->current;
}

Note& Note::operator =(const Note& source) {
	Composite::operator =(source);
	return *this;
}
string Note::GetContent() {
	string content = "";
	string characterString;
	Glyph *line;
	Glyph *character;
	Long j;
	Long i = 0;

	while (i < this->length) {
		line = this->glyphs.GetAt(i);
		j = 0;
		while (j < line->GetLength()) {
			character = line->GetAt(j);
			characterString = character->GetContent();
			if (characterString.length() == 8) {
				characterString = '\t';
			}
			content += characterString;
			j++;
		}
		if (i < this->length - 1) {
			content += "\n";
		}
		i++;
	}

	return content;
	/*
	string content = "";
	Long i = 0;
	while (i < this->length) {
		content += this->glyphs[i]->GetContent();
		i++;
	}
	return content;
	*/
}
Glyph* Note::Clone() {
	return new Note(*this);
}

Long Note::Add(Glyph *glyph) {
	Long index = Composite::Add(glyph);
	this->current = index;

	return index;
}

Long Note::Add(Long index, Glyph *glyph) {
	Composite::Add(index, glyph);
	this->current = index;

	return this->current;
}
Long Note::Remove(Long index) {
	Composite::Remove(index);
	this->current = index - 1;

	return -1;
}