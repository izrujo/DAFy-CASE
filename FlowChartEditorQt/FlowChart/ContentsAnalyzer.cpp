#include "ContentsAnalyzer.h"

ContentsAnalyzer::ContentsAnalyzer(String contents)
	: contents(contents) {

}

ContentsAnalyzer::~ContentsAnalyzer() {

}

Array<String*> ContentsAnalyzer::MakeOperators() {
	String contents = this->contents; //복사
	//1. 내용에서 공백을 지우다.
	contents.Remove(' ');
	//2. 내용에서 개행문자를 지우다.
	contents.Remove('\n');

	Array<String*> operators;
	char character;
	//3. 내용의 처음부터 끝까지 반복하다.
	Long i = 0;
	while (i < contents.GetLength()) {
		String *oper = new String;
		//3.1. 글자를 가져오다.
		character = contents.GetAt(i);
		//3.2. _를 제외한 특수기호이고 널 문자가 아닌 동안 반복하다.
		while ((character == 33 || character == 40 || character == 41 || character == 42 || character == 42 ||
			character == 45 || character == 47 || character == 60 || character == 61 || character == 62) &&
			character != '\0') {
			//3.2.2. 연산자를 만들다.
			oper += character;
			//3.2.1. 글자를 가져오다.
			character = contents.GetAt(++i);
		}
		//3.3. 연산자를 연산자들에 추가하다.
		operators.Store(operators.GetLength(), oper);
		//3.4. _를 제외한 특수기호가 아닌 동안 반복하다.
		while (!(character == 33 || character == 40 || character == 41 || character == 42 || character == 42 ||
			character == 45 || character == 47 || character == 60 || character == 61 || character == 62)) {
			character = contents.GetAt(++i);
		}
		i++;
	}
	//4. 연산자들을 출력하다.
	return operators;
	//5. 끝내다.
}

Array<String*> ContentsAnalyzer::MakeVariables() {
	String contents = this->contents; //복사
	//1. 내용에서 공백을 지우다.
	contents.Remove(' ');
	//2. 내용에서 개행문자를 지우다.
	contents.Remove('\n');

	Array<String*> variables;
	char character;
	//3. 내용의 처음부터 끝까지 반복하다.
	Long i = 0;
	while (i < contents.GetLength()) {
		String *variable = new String;
		//3.1. 글자를 가져오다.
		character = contents.GetAt(i);
		//3.2. 영문자이거나 숫자이거나 _이고 널 문자가 아닌 동안 반복하다.
		while (((character >= 48 && character <= 57) ||
			(character >= 65 && character <= 90) ||
			(character >= 97 && character <= 122) ||
			character == 95) &&
			character != '\0') {
			//3.2.2. 연산자를 만들다.
			variable += character;
			//3.2.1. 글자를 가져오다.
			character = contents.GetAt(++i);
		}
		//3.3. 연산자를 연산자들에 추가하다.
		variables.Store(variables.GetLength(), variable);
		//3.4. 영문자이거나 숫자이거나 _가 아닌 동안 반복하다.
		while (!((character >= 48 && character <= 57) ||
			(character >= 65 && character <= 90) ||
			(character >= 97 && character <= 122) ||
			character == 95)) {
			character = contents.GetAt(++i);
		}
		i++;
	}
	//4. 연산자들을 출력하다.
	return variables;
	//5. 끝내다.
}

String ContentsAnalyzer::CorrectOperators() {
	//'≠' '≤' '≥'
	char character;
	//1. 내용의 처음부터 끝까지 반복하다.
	Long i = 0;
	while (i < this->contents.GetLength()) {
		//1.1. 글자를 가져오다.
		character = this->contents.GetAt(i);
		//1.2. 글자가 = 이고 첫 번째 글자가 아니면
		if (character == '=' && i > 0) {
			//1.2.1. 이전 글자를 가져오다.
			character = this->contents.GetAt(i - 1);
			switch (character) {
			//1.2.2. 이전 글자가 ! 이면 ≠로 고치다.
			case '!':
				this->contents.Delete(i - 1, 2);
				this->contents.Insert(i - 1, '≠');
			//1.2.3. 이전 글자가 < 이면 ≤로 고치다.
			case '<':
				this->contents.Delete(i - 1, 2);
				this->contents.Insert(i - 1, '≤');
			//1.2.4. 이전 글자가 > 이면 ≥로 고치다.
			case '>':
				this->contents.Delete(i - 1, 2);
				this->contents.Insert(i - 1, '≥');
			}
		}
		i++;
	}
	//2. 내용을 출력하다.
	return this->contents;
	//3. 끝내다.
}