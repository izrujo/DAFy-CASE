#include "VariableList.h"

VariableList::VariableList(Long capacity)
	: variables(capacity) {
	this->capacity = capacity;
	this->length = 0;
	
	//예약어 추가해두기
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
	this->length += 10;
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
	Long i = 0;
	//1. 내용 문자열의 길이만큼 반복한다.
	while (i < contents.GetLength()) {
		//1.1. 내용 문자열에서 문자를 가져온다.
		char character = contents.GetAt(i);
		//1.2. 영문자인 동안 또는 (변수 문자열의 길이가 1이상이고 숫자인 동안) 반복한다.
		String variable;
		while ((character >= 65 && character <= 90) || (character >= 97 && character <= 122) ||
			(variable.GetLength() > 0 && (character >= 48 && character <= 57))) {
			//1.2.1. 변수 문자열을 만들다.
			variable += character;
			//1.2.2. 내용 문자열에서 다음 문자를 가져온다.
			character = contents.GetAt(++i);
		}
		//1.3. 변수목록의 개수만큼 그리고, 변수문자열을 만들었고, 변수목록의 현재변수가 변수문자열과 같지 않은 동안 반복한다.
		Long j = 0;
		while (j < this->length && variable.GetLength() > 0 && this->variables[j] != variable) {
			//(1.3.1. 변수문자열과 같은 변수가 있는지 찾는다.)
			j++;
		}
		//1.4. 변수 문자열과 같은 변수를 못찾았고, 변수문자열을 만들었고, 예약어가 아니면 변수목록에 추가한다.
		if (j >= this->length && variable.GetLength() > 0 && (variable != "READ" && variable != "PRINT")) {
			if (this->length < this->capacity) {
				this->variables.Store(this->length, variable);
			}
			else {
				this->variables.AppendFromRear(variable);
				this->capacity++;
			}
			this->length++;
		}
		i++;
	}

	return this->length;
}

Long VariableList::Find(String contents) {
	//기능 : contents 가 num 이면 num 으로 시작하는 변수명이 있는지 확인한다.
	Long ret = -1;
	Long i = 0;
	//1. 변수목록의 개수만큼 그리고 contents로 시작하는 변수명이 없는 동안 반복한다.
	while (i < this->length && this->variables[i].FindUntilLength(contents) == -1) {
		//현재 변수명이 contents로 시작하는 변수명이 아니면 -1 출력
		i++;
	}
	if (i < this->length) {
		ret = i;
	}
	return ret;
}

String& VariableList::GetAt(Long index) {
	return this->variables.GetAt(index);
}