#include "ContentsAnalyzer.h"

ContentsAnalyzer::ContentsAnalyzer() {

}

ContentsAnalyzer::~ContentsAnalyzer() {

}

Array<String> ContentsAnalyzer::MakeOperators(String contents) {
	Array<String> operators;
	char character;
	//1. 내용의 처음부터 끝까지 반복하다.
	Long i = 0;
	while (i < contents.GetLength()) {
		String oper;
		//1.1. 글자를 가져오다.
		character = contents.GetAt(i);
		//1.2. _ , .를 제외한 특수기호이고 널 문자가 아닌 동안 반복하다.
		while ((character == 33 || character == 40 || character == 41 || character == 42 || character == 43 ||
			character == 45 || character == 47 || character == 60 || character == 61 || character == 62) &&
			character != '\0') {
			//1.2.2. 연산자를 만들다.
			oper += character;
			//1.2.1. 글자를 가져오다.
			character = contents.GetAt(++i);
		}
		//1.3. 연산자에 해당하는 특수기호이면 연산자를 연산자들에 추가하다.
		if (oper.GetLength() > 0) {
			operators.Store(operators.GetLength(), oper);
		}
		//1.4. _를 제외한 특수기호가 아닌 동안 반복하다.
		while ((!(character == 33 || character == 40 || character == 41 || character == 42 || character == 43 ||
			character == 45 || character == 47 || character == 60 || character == 61 || character == 62)) &&
			character != '\0') {
			character = contents.GetAt(++i);
		}
		if (character != '\0') { //특수기호를 찾았으면 특수기호부터 시작할 수 있도록 첨자를 줄여준다.
			i--;
		}
		i++;
	}
	//2. 연산자들을 출력하다.
	return operators;
	//3. 끝내다.
}

Array<String> ContentsAnalyzer::MakeVariables(String contents) {
	Array<String> variables;
	char character;
	bool isQuotes = false;
	//1. 내용의 처음부터 끝까지 반복하다.
	Long i = 0;
	while (i < contents.GetLength()) {
		String variable;
		//1.1. 글자를 가져오다.
		character = contents.GetAt(i);
		//1.2. 영문자이거나 숫자이거나 _이고 널 문자가 아닌 동안 반복하다.
		while (((character >= 48 && character <= 57) ||
			(character >= 65 && character <= 90) ||
			(character >= 97 && character <= 122) ||
			character == 95) &&
			character != '\0') {
			//1.2.2. 변수를 만들다.
			variable += character;
			//1.2.1. 글자를 가져오다.
			character = contents.GetAt(++i);
		}
		//1.3. 변수를 변수들에 추가하다.
		if (variable.GetLength() > 0) {
			variables.Store(variables.GetLength(), variable);
		}

		//1.4. 영문자가 아닌 동안 또는 따옴표 안인 동안 반복하다.
		// (따옴표 안이라면 영문자여도 반복한다.)
		while (((!((character >= 65 && character <= 90) ||
			(character >= 97 && character <= 122))) ||
			isQuotes == true) &&
			character != '\0') {
			if (isQuotes == false && (character == 34 || character == 39)) { //따옴표를 다시 만나면 지금부터 따옴표 밖임.
				isQuotes = true;
			}
			else if (isQuotes == true && (character == 34 || character == 39)) { //따옴표를 다시 만나면 지금부터 따옴표 밖임.
				isQuotes = false;
			}
			character = contents.GetAt(++i);
		}
		if (character != '\0') { //영문자를 찾았으면 영문자부터 시작할 수 있도록 첨자를 줄여준다.
			i--;
		}
		i++;
	}
	//2. 변수들을 출력하다.
	return variables;
	//3. 끝내다.
}

String ContentsAnalyzer::CorrectOperators(String contents) {
	//'≠' '≤' '≥'
	char character;
	//1. 내용의 처음부터 끝까지 반복하다.
	Long i = 0;
	while (i < contents.GetLength()) {
		//1.1. 글자를 가져오다.
		character = contents.GetAt(i);
		//1.2. 글자가 = 이고 첫 번째 글자가 아니면
		if (character == '=' && i > 0) {
			//1.2.1. 이전 글자를 가져오다.
			character = contents.GetAt(i - 1);
			switch (character) {
			case '!': //1.2.2. 이전 글자가 ! 이면 ≠로 고치다.
				contents.Delete(i - 1, 2);
				contents.Insert(i - 1, "≠");
				break;
			case '<': //1.2.3. 이전 글자가 < 이면 ≤로 고치다.
				contents.Delete(i - 1, 2);
				contents.Insert(i - 1, "≤");
				break;
			case '>': //1.2.4. 이전 글자가 > 이면 ≥로 고치다.
				contents.Delete(i - 1, 2);
				contents.Insert(i - 1, "≥");
				break;
			default:
				break;
			}
		}
		i++;
	}
	//2. 내용을 출력하다.
	return contents;
	//3. 끝내다.
}