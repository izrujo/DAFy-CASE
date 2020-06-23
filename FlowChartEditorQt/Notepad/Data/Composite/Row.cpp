#include "Row.h"
#include "../Glyph.h"
#include "../Leaf/Character.h"

Row::Row(Long capacity)
	: Composite(capacity) {
}

Row::Row(const Row& source)
	: Composite(source){
}

Row::~Row() {
}

Long Row::MovePreviousWord() {
	while (this->current > 0 && (this->glyphs[this->current - 1]->GetContent())[0] == ' ') {
		this->current--;
	}
	while (this->current > 0 && (this->glyphs[this->current - 1]->GetContent())[0] != ' ') {
		this->current--;
	}

	return this->current;
}

Long Row::MoveNextWord() {
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

Row& Row::operator =(const Row& source) {
	Composite::operator =(source);

	return *this;
}

string Row::GetContent() {
	string content = "";
	Long i = 0;
	while (i < this->length) {
		content += this->glyphs[i]->GetContent();
		i++;
	}
	return content;
}

Glyph* Row::Clone() {
	return new Row(*this);
}

Glyph* Row::Divide(Long index) {
	Glyph *line = new Row;
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
Glyph* Row::Combine(Glyph *other) {
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