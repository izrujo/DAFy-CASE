#include "RuleKeeper.h"
#include "VariableList.h"

RuleKeeper::RuleKeeper() {

}

RuleKeeper::RuleKeeper(const RuleKeeper& source) {

}

RuleKeeper::~RuleKeeper() {

}

RuleKeeper& RuleKeeper::operator=(const RuleKeeper& source) {
	return *this;
}

VariableList* RuleKeeper::CheckVariableNamingRule(Array<String> variables) {
	bool isKept = true;
	String variable;
	char character;
	Long j;
	//1. 변수 목록을 만들다.
	VariableList *variableList = new VariableList(10);

	//2. 변수들 개수만큼 그리고 규칙을 지키는 동안 반복하다.
	Long i = 0;
	while (i < variables.GetLength() && isKept == true) {
		//2.1. 변수를 가져오다.
		variable = variables.GetAt(i);
		//2.2. 변수의 첫 번째 글자가 영문자가 아니면 규칙에 어긋난다.
		character = variable.GetAt(0);
		if ((character < 65 || character > 90) && (character < 97 || character > 122)) {
			isKept = false;
		}
		//2.3. 글자가 대문자인 동안 그리고 글자 개수만큼 반복한다.
		j = 1;
		while (j < variable.GetLength() && (character >= 65 && character <= 90)) {
			//2.3.1. 글자를 가져오다.
			character = variable.GetAt(++j);
		}
		//2.4. 첫 번째 글자가 대문자인데 대문자가 아닌 글자를 찾았으면 규칙에 어긋난다.
		if (j < variable.GetLength() && (variable.GetAt(0) >= 65 && variable.GetAt(0) <= 90)) {
			isKept = false;
		}
		//2.5. 변수 목록에 추가하다.
		variableList->Add(variable);
		i++;
	}
	//3. 변수 목록을 출력하다.
	if (isKept == false) {
		variableList->RemoveAll();
	}

	return variableList;
	//4. 끝내다.
}

bool RuleKeeper::CheckVariableUsingRule(Array<String> variables, VariableList *variableList) {
	bool isKept = true;
	String variable;
	Long index = -1;
	//1. 변수들 개수만큼 그리고 변수 목록에 현재 변수가 있는 동안 반복하다.
	Long i = 0;
	while (i < variables.GetLength() && (index != -1 || i == 0)) {
		//1.1. 변수를 가져오다.
		variable = variables.GetAt(i);
		//1.2. 변수 목록에서 찾는다.
		index = variableList->Find(variable);
		i++;
	}
	//2. 변수 목록에 입력받은 모든 변수들이 있는지 여부에 따라 규칙 준수 여부를 결정한다.
	if (index == -1) {
		isKept = false;
	}
	//3. 규칙 준수 여부를 출력하다.
	return isKept;
	//4. 끝내다.
}

bool RuleKeeper::CheckOperatorRule(Array<String> operators) {
	bool isKept = true;
	String oper;
	//1. 연산자들 개수만큼 반복하다.
	Long i = 0;
	while (i < operators.GetLength() && isKept == true) {
		//1.1. 연산자를 가져오다.
		oper = operators.GetAt(i);
		//1.2. 허용된 연산자가 아니면 규칙에 어긋난다.
		if (!(oper == "(" || oper == ")" || oper == "*" || oper == "+" || oper == "-" || oper == "/" ||
			oper == "<" || oper == "=" || oper == ">" || oper == "^" ||
			oper == "<>" || oper == "<=" || oper == ">=" || oper == "!=")) {
			isKept = false;
		}
		i++;
	}
	//2. 규칙 준수 여부를 출력하다.
	return isKept;
	//3. 끝내다.
}