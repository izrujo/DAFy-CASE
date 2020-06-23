#include "Composite.h"
#include "../Glyph.h"

Composite::Composite(Long capacity)
	: glyphs(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = 0;
}

Composite::Composite(const Composite& source)
	: glyphs(source.glyphs) {
	Long i = 0;
	while (i < source.length) {
		this->glyphs.Modify(i, (const_cast<Composite&>(source)).glyphs[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

Composite::~Composite() {
	Long i = 0;
	while (i < this->length) {
		if (this->glyphs[i] != 0) {
			delete this->glyphs[i];
		}
		i++;
	}
}

Long Composite::Add(Glyph *glyph) {
	Long index;
	if (this->length < this->capacity) {
		index = this->glyphs.Store(this->length, glyph);
	}
	else {
		index = this->glyphs.AppendFromRear(glyph);
		this->capacity++;
	}
	this->length++;
	this->current = index + 1;

	return index;
}

Long Composite::Add(Long index, Glyph *glyph) {
	index = this->glyphs.Insert(index, glyph);
	this->length++;
	this->capacity++;
	this->current = index + 1;

	return index;
}

Long Composite::Remove(Long index) {
	if (this->glyphs[index] != 0) {
		delete this->glyphs.GetAt(index);
	}
	this->current = index;
	index = this->glyphs.Delete(index);
	this->capacity--;
	this->length--;
	
	return index;
}

Glyph* Composite::GetAt(Long index) {
	return this->glyphs.GetAt(index);
}

Long Composite::First() {
	this->current = 0;

	return this->current;
}

Long Composite::Last() {
	this->current = this->length;

	return this->current;
}

Long Composite::Previous() {
	this->current--;
	if (this->current < 0) {
		this->current = 0;
	}

	return this->current;
}

Long Composite::Next() {
	this->current++;
	if (this->current > this->length) {
		this->current = this->length;
	}

	return this->current;
}

Long Composite::Move(Long index) {
	this->current = index;
	
	return this->current;
}

Composite& Composite::operator =(const Composite& source) {
	Long i = 0;
	while (i < this->length) {
		if (this->glyphs[i] != 0) {
			delete this->glyphs[i];
		}
		i++;
	}
	this->glyphs = source.glyphs;
	i = 0;
	while (i < source.length) {
		this->glyphs.Modify(i, (const_cast<Composite&>(source)).glyphs[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	return *this;
}

Glyph* Composite::operator [](Long index) {
	return this->glyphs[index];
}

Long Composite::GetCapacity() const {
	return this->capacity;
}
Long Composite::GetLength() const {
	return this->length;
}
Long Composite::GetCurrent() const {
	return this->current;
}