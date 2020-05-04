#include "VariableList.h"

VariableList::VariableList(Long capacity)
	: variables(capacity) {
	this->capacity = capacity;
	this->length = 0;

	this->variables.Store(0, &String("AND"));
	this->variables.Store(1, &String("EOF"));
	this->variables.Store(2, &String("FALSE"));
	this->variables.Store(3, &String("NOT"));
	this->variables.Store(4, &String("OR"));
	this->variables.Store(5, &String("PRINT"));
	this->variables.Store(6, &String("READ"));
	this->variables.Store(7, &String("START"));
	this->variables.Store(8, &String("STOP"));
	this->variables.Store(9, &String("TRUE"));
	this->capacity += 10;
	this->length += 10;
}

VariableList::VariableList(const VariableList& source)
	: variables(source.variables) {
	Long i = 0;
	while (i < source.length) {
		this->variables.Modify(i, new String(*const_cast<VariableList&>(source).variables[i]));
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

VariableList::~VariableList() {
	Long i = 0;
	while (i < this->length) {
		if (this->variables[i] != 0) {
			delete this->variables[i];
		}
		i++;
	}
}

VariableList& VariableList::operator=(const VariableList& source) {
	String *string;

	Long i = 0;
	while (i < this->length) {
		string = this->variables.GetAt(i);
		if (string != 0) {
			delete string;
		}
		i++;
	}

	this->variables = source.variables;

	i = 0;
	while (i < source.GetLength()) {
		string = new String(*const_cast<VariableList&>(source).variables[i]);
		this->variables.Modify(i, string);
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long VariableList::Add(String *contents) {
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

Long VariableList::Find(String *contents) {
	//기능 : contents 가 num 이면 num 으로 시작하는 변수명이 있는지 확인한다.
	Long ret = -1;
	Long i = 0;
	//1. 변수목록의 개수만큼 그리고 contents로 시작하는 변수명이 없는 동안 반복한다.
	while (i < this->length && this->variables[i]->FindUntilLength(*contents) == -1) {
		//현재 변수명이 contents로 시작하는 변수명이 아니면 -1 출력
		i++;
	}
	if (i < this->length) {
		ret = i;
	}
	return ret;
}

String* VariableList::GetAt(Long index) {
	return this->variables.GetAt(index);
}