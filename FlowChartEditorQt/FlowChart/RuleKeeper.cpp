#include "RuleKeeper.h"
#include "VariableList.h"

#include <qchar.h>

RuleKeeper::RuleKeeper()
	: variableList() {
	// ! " ' ( ) * + , - . / 0~9 < = > A~Z ^ _ a~z
	char buffer;
	Long number = 33;
	Long i = 0;
	while (number <= 122) {
		if ((number >= 33 && number <= 34) || (number >= 39 && number <= 57) || // ! ~ " OR ' ~ 9 OR
			(number >= 60 && number <= 62) || (number >= 65 && number <= 90) || // < ~ > OR A ~ Z OR
			(number >= 94 && number <= 95) || (number >= 97 && number <= 122)) { // ^ ~ _ OR a ~ z
			buffer = number;
			this->allowedKeys[i++] = buffer;
		}
		number++;
	}

	this->isQuotes = false;
}

RuleKeeper::RuleKeeper(const RuleKeeper& source)
	: variableList(source.variableList) {
	Long i = 0;
	while (i < 78) {
		this->allowedKeys[i] = source.allowedKeys[i];
		i++;
	}

	this->isQuotes = source.isQuotes;
}

RuleKeeper::~RuleKeeper() {
	if (this->variableList != 0) {
		delete this->variableList;
	}
}

RuleKeeper& RuleKeeper::operator=(const RuleKeeper& source) {
	this->variableList = source.variableList;

	Long i = 0;
	while (i < 78) {
		this->allowedKeys[i] = source.allowedKeys[i];
		i++;
	}

	this->isQuotes = source.isQuotes;

	return *this;
}

bool RuleKeeper::IsAllowed(char key) {
	bool isAllowed = true;
	if (this->isQuotes == false) {
		Long i = 0;
		while (i < 77 && key != this->allowedKeys[i]) {
			i++;
		}
		if (i >= 77) {
			isAllowed = false;
		}
	}

	return isAllowed;
}

bool RuleKeeper::IsKeptVariableRule(String allContents) {
	//공백 문자와 개행 문자를 제거한다.
	allContents.Remove(' ');
	allContents.Remove('\n');

	bool isKept = true;

	VariableList tempList;
	char character;
	Long contentsLength = allContents.GetLength();
	String variable;

	//임시 변수 목록을 만든다.
	Long i = 0;
	while (i < contentsLength) {
		character = allContents.GetAt(i);
		while (character != ',' && character != '=' && i < contentsLength) {
			variable.Store(variable.GetLength(), character);
			character = allContents.GetAt(++i);
		}
		tempList.Add(variable);
		if (character == '=') {
			while (character != ',' && i < contentsLength) {
				character = allContents.GetAt(++i);
			}
		}
		i++;
	}
	//임시 변수 목록이 규칙에 알맞은 변수만을 가지고 있는지 확인한다.
	//규칙에 어긋난 변수가 하나라도 있으면 통과하지 못할 것이다.
	Long j = 0;
	while (j < tempList.GetLength()) {
		variable = tempList.GetAt(j);
		character = variable.GetAt(0);
		//현재 변수의 첫 번째 글자가 영문자가 아니면 규칙에 어긋난다.
		if (!((character >= 65 && character <= 90) || (character >= 97 && character <= 122))) {
			isKept = false;
		}
		//현재 변수의 첫 번째 글자가 영문 대문자이면 모두 대문자가 아니면 규칙에 어긋난다.(기호상수)
		Long k = 1;
		while (k < variable.GetLength() && (character >= 97 && character <= 122)) {
			character = variable.GetAt(k);
			k++;
		}
		if (k < variable.GetLength()) { //대문자가 아닌 글자를 찾았으면
			isKept = false;
		}
		//현재 변수에 _를 제외한 특수문자가 있으면(영문자이거나 숫자이거나 _이면 참) 규칙에 어긋난다.
		k = 1;
		while (k < variable.GetLength() &&
			((character >= 65 && character <= 90) || (character >= 97 && character <= 122) ||
			(character >= 48 && character <= 57) ||
				(character == 95))) {
			character = variable.GetAt(k);
			k++;
		}
		if (k < variable.GetLength()) { //_를 제외한 특수문자를 찾았으면
			isKept = false;
		}

		j++;
	}

	//규칙에 맞게 변수를 선언했으면 변수 목록을 기억한다.
	if (isKept == true) {
		this->variableList = &tempList;
		this->variableList->SetKeywords();
	}

	return isKept;
}

Long RuleKeeper::FindVariable(String allContents) {
	allContents.Remove(' ');
	allContents.Remove('\n');

	Long index = 0;

	VariableList tempList;
	char character;
	Long contentsLength = allContents.GetLength();
	String variable;

	//임시 변수 목록을 만든다.
	Long i = 0;
	while (i < contentsLength) {
		character = allContents.GetAt(i);
		//영문자, 숫자, _ 인 동안 반복한다.
		while (i < contentsLength &&
			((character >= 65 && character <= 90) || (character >= 97 && character <= 122) ||
			(character >= 48 && character <= 57) ||
				(character == 95))) {
			variable.Store(variable.GetLength(), character);
			character = allContents.GetAt(i++);
		}
		//!!!예약어를 넣지 않도록 해야 한다!!!
		tempList.Add(variable); 
		//변수 목록을 다 만든 게 아니면 영문 소문자를 찾는다.
		while (i < contentsLength &&
			(character < 97 || character > 122)) {
			character = allContents.GetAt(i++);
		}

		i++;
	}

	//하나라도 없는게 있으면 안됨.
	Long j = 0;
	while (j < tempList.GetLength() && index != -1) {
		variable = tempList.GetAt(j);
		index = this->variableList->Find(variable);

		j++;
	}

	return index;
}

bool RuleKeeper::CorrectOperator(String allContents) {
	//'≠' '≤' '≥'
	allContents.Remove(' ');
	allContents.Remove('\n');

	bool isCorrect = true;

	char character;
	Long contentsLength = allContents.GetLength();
	String writtenOperator;

	Long i = 0;
	while (i < contentsLength) {
		character = allContents.GetAt(i);
		// ! * - + = < > / ^ 이 기호들인 경우에만 연산자를 만든다.
		if (character == '!' || character == '*' || character == '-' || character == '+' ||
			character == '=' || character == '<' || character == '>' || character == '/' ||
			character == '^') {
			writtenOperator.Store(writtenOperator.GetLength(), character);
		}
		else{
			writtenOperator.Clear();
		}

		if (writtenOperator.GetLength() > 1) {
			if (writtenOperator == "<=") {
				allContents.Delete(i - 1, 2);
				allContents.Store(i - 1, '≤');
				isCorrect = true;
			}
			else if (writtenOperator == ">=") {
				allContents.Delete(i - 1, 2);
				allContents.Store(i - 1, '≥');
				isCorrect = true;
			}
			else if (writtenOperator == "!=") {
				allContents.Delete(i - 1, 2);
				allContents.Store(i - 1, '≠');
				isCorrect = true;
			}
			else if (writtenOperator == "<>") {
				isCorrect = true;
			}
			else {
				isCorrect = false;
			}
		}

		i++;
	}


	return isCorrect;
}