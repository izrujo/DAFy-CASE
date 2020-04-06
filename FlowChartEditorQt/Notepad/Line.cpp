#include "Line.h"
#include "Glyph.h"
#include "Character.h"

Line::Line(Long capacity)
	: Composite(capacity) {
}

Line::Line(const Line& source)
	: Composite(source){
}

Line::~Line() {
}

Long Line::MovePreviousWord() {
	while (this->current > 0 && (this->glyphs[this->current - 1]->GetContent())[0] == ' ') {
		this->current--;
	}
	while (this->current > 0 && (this->glyphs[this->current - 1]->GetContent())[0] != ' ') {
		this->current--;
	}

	return this->current;
}

Long Line::MoveNextWord() {
	while (this->current < this->length && (this->glyphs[this->current]->GetContent())[0] == ' ') {
		this->current++;
	}
	while (this->current < this->length && (this->glyphs[this->current]->GetContent())[0] != ' ') {
		this->current++;
	}
	while (this->current < this->length && (this->glyphs[this->current]->GetContent())[0] == ' ') {
		this->current++;
	}

	return this->current;
}

Line& Line::operator =(const Line& source) {
	Composite::operator =(source);

	return *this;
}

string Line::GetContent() {
	string content = "";
	Long i = 0;
	while (i < this->length) {
		content += this->glyphs[i]->GetContent();
		i++;
	}
	return content;
}

Glyph* Line::Clone() {
	return new Line(*this);
}

Glyph* Line::Divide(Long index) {
	Glyph *line = new Line;
	Glyph *character;
	Long i = index;
	Long length = this->length;
	while (i < length) {
		character = this->glyphs.GetAt(index);
		line->Add(character);
		this->glyphs.Delete(index);
		this->capacity--;
		this->length--;
		i++;
	}

	return line;
}
Glyph* Line::Combine(Glyph *other) {
	Long i = 0;
	while (i < other->GetLength()) {
		Glyph *character = other->GetAt(i);
		Glyph *characterOther = character->Clone();
		if (this->length < this->capacity) {
			this->glyphs.Store(this->length, characterOther);
		}
		else {
			this->glyphs.AppendFromRear(characterOther);
			this->capacity++;
		}
		this->length++;
		i++;
	}
	return this;
}