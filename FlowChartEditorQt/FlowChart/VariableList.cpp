#include "VariableList.h"

VariableList::VariableList(Long capacity)
	: variables(capacity) {
	this->variables.Store(0, String("AND"));
	this->variables.Store(1, String("EOF"));
	this->variables.Store(2, String("FALSE"));
	this->variables.Store(3, String("NOT"));
	this->variables.Store(4, String("OR"));
	this->variables.Store(5, String("PRINT"));
	this->variables.Store(6, String("READ"));
	this->variables.Store(7, String("START"));
	this->variables.Store(8, String("STOP"));
	this->variables.Store(9, String("TRUE"));
	this->length = 10;
	this->capacity = capacity;
}

VariableList::VariableList(const VariableList& source)
	: variables(source.variables) {
	this->capacity = source.capacity;
	this->length = source.length;
}

VariableList::~VariableList() {

}

VariableList& VariableList::operator=(const VariableList& source) {
	this->variables = source.variables;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long VariableList::Add(String contents) {
	Long index = -1;
	if (this->length < this->capacity) {
		index = this->variables.Store(this->length, contents);
	}
	else {
		index = this->variables.AppendFromRear(contents);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long VariableList::Find(String contents) {
	Long ret = -1;
	Long i = 0;
	while (i < this->length && this->variables[i] != contents) {
		i++;
	}
	if (i < this->length) {
		ret = i;
	}
	return ret;
}

Long VariableList::Remove(Long index) {
	if (index >= 0 && index < this->GetLength()) {
		index = this->variables.Delete(index);
		this->length--;
	}
	return index;
}

void VariableList::RemoveAll() {
	Long i = this->length - 1;
	while (i >= 0) {
		this->variables.Delete(i);
		i--;
	}
	this->length = 0;
}

String& VariableList::GetAt(Long index) {
	return this->variables.GetAt(index);
}