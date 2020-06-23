#include "HistoryBook.h"
#include "Historys.h"

HistoryBook::HistoryBook(Long capacity)
	: historys(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

HistoryBook::HistoryBook(const HistoryBook& source)
	: historys(source.historys) {
	Long i = 0;
	while (i < source.length) {
		this->historys.Modify(i, (const_cast<HistoryBook&>(source)).historys[i]->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
}

HistoryBook::~HistoryBook() {
	Long i = 0;
	while (i < this->length) {
		if (this->historys[i] != 0) {
			delete this->historys[i];
		}
		i++;
	}
}

HistoryBook& HistoryBook::operator=(const HistoryBook& source) {
	Long i = 0;
	while (i < this->length) {
		if (this->historys[i] != 0) {
			delete this->historys[i];
		}
		i++;
	}
	this->historys = source.historys;
	i = 0;
	while (i < source.length) {
		this->historys.Modify(i, (const_cast<HistoryBook&>(source)).historys[i]->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long HistoryBook::Add(History *history) {
	
	//50개로 제한
	if (this->length >= 50) {
		if (this->historys[0] != 0) {
			delete this->historys[0];
		}
		this->historys.Delete(0);
		this->capacity--;
		this->length--;
	}
	
	Long index;
	if (this->length < this->capacity) {
		index = this->historys.Store(this->length, history);
	}
	else {
		index = this->historys.AppendFromRear(history);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long HistoryBook::Remove(Long index) {
	if (this->historys[index] != 0) {
		delete this->historys[index];
	}
	this->historys.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}

void HistoryBook::RemoveAll() {
	Long i = 0;
	while (i < this->length) {
		if (this->historys[0] != 0) {
			delete this->historys[0];
		}
		this->historys.Delete(0);
		this->capacity--;
		i++;
	}
	this->length = 0;
}

History* HistoryBook::GetAt(Long index) {
	return this->historys.GetAt(index);
}

HistoryBook* HistoryBook::Clone() {
	return new HistoryBook(*this);
}