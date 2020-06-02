#include "SheetBinder.h"
#include "Sheet.h"

SheetBinder::SheetBinder(Long capacity) 
	: sheets(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
}

SheetBinder::SheetBinder(const SheetBinder& source) 
	: sheets(source.sheets) {

	Long i = 0;
	while (i < source.length) {
		this->sheets.Modify(i, const_cast<SheetBinder&>(source).sheets[i]->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

SheetBinder::~SheetBinder() {
	Long i = 0;
	while (i < this->length) {
		if (this->sheets[i] != 0) {
			delete this->sheets[i];
		}
		i++;
	}
}

SheetBinder& SheetBinder::operator=(const SheetBinder& source) {
	Long i = 0;
	while (i < this->length) {
		if (this->sheets[i] != 0) {
			delete this->sheets[i];
		}
		i++;
	}

	this->sheets = source.sheets;

	i = 0;
	while (i < source.length) {
		this->sheets.Modify(i, const_cast<SheetBinder&>(source).sheets[i]->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
	
	return *this;
}

Long SheetBinder::Add(Sheet *sheet) {
	if (this->length < this->capacity) {
		this->current = this->sheets.Store(this->length, sheet);
	}
	else {
		this->current = this->sheets.AppendFromRear(sheet);
		this->capacity++;
	}
	this->length++;

	return this->current;
}

Long SheetBinder::Insert(Long index, Sheet *sheet) {
	this->current = this->sheets.Insert(index, sheet);
	if (this->length >= this->capacity) {
		this->capacity++;
	}
	this->length++;

	return this->current;
}

Long SheetBinder::Remove(Long index) {
	if (this->sheets[index] != 0) {
		delete this->sheets[index];
		this->sheets.Delete(index);
		this->capacity--;
		this->length--;
		this->current = 0; //Sheet를 닫으면 맨 앞의 시트를 연다.
	}

	return -1;
}

Sheet* SheetBinder::GetAt(Long index) {
	return this->sheets.GetAt(index);
}

Long SheetBinder::Move(Long current) {
	this->current = current;

	return this->current;
}