#include "String.h"
#include <cstring>
#include <string>
#include <memory.h>
#include <iostream>
#include <cassert>
#pragma warning (disable : 4996)
#if 0
using namespace std;
int main(int argc, char* argv[])
{

	String generalConstructor;
	cout << "1. 생성자 테스트" << endl;
	cout << "1.1 생성자  생성시 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 65536개의 문자 배열을 생성한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << generalConstructor.GetCapacity() << endl;
	cout << "    Length      : " << generalConstructor.GetLength() << endl;
	cout << "    Current     : " << generalConstructor.GetCurrent() << endl;
	cout << "    GetString() : " << generalConstructor.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	generalConstructor.Empty();
	cout << "1.2 생성자  Empty() 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 65536개의 문자 배열을 삭제한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << generalConstructor.GetCapacity() << endl;
	cout << "    Length      : " << generalConstructor.GetLength() << endl;
	cout << "    Current     : " << generalConstructor.GetCurrent() << endl;
	cout << "    GetString() : " << generalConstructor.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	generalConstructor.Clear();
	String repeatConstructor('x', 3);
	cout << "1.3 반복 생성자  생성시 테스트" << endl;
	cout << "    입력 : character:'x',nRepeat:3 " << endl;
	cout << "    기능 : character를 nRepeat만큼 반복하여 생성한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << repeatConstructor.GetCapacity() << endl;
	cout << "    Length      : " << repeatConstructor.GetLength() << endl;
	cout << "    Current     : " << repeatConstructor.GetCurrent() << endl;
	cout << "    GetString() : " << repeatConstructor.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	repeatConstructor.Empty();
	cout << "1.4 반복 생성자  Empty() 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자 배열을 삭제한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << repeatConstructor.GetCapacity() << endl;
	cout << "    Length      : " << repeatConstructor.GetLength() << endl;
	cout << "    Current     : " << repeatConstructor.GetCurrent() << endl;
	cout << "    GetString() : " << repeatConstructor.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	repeatConstructor = "ABCDEF";
	String copyConstructor(repeatConstructor);

	cout << "1.5 복사 생성자  생성시 테스트" << endl;
	cout << "    입력 : repeatConstructor " << endl;
	cout << "    기능 : repeatConstructor 객체를 복사한다." << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    복사할 repeatConstructor 객체 정보 " << endl;
	cout << "    Capacity    : " << repeatConstructor.GetCapacity() << endl;
	cout << "    Length      : " << repeatConstructor.GetLength() << endl;
	cout << "    Current     : " << repeatConstructor.GetCurrent() << endl;
	cout << "    GetString() : " << repeatConstructor.GetString() << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    복사된 copyConstructor 객체 정보 " << endl;
	cout << "    Capacity    : " << copyConstructor.GetCapacity() << endl;
	cout << "    Length      : " << copyConstructor.GetLength() << endl;
	cout << "    Current     : " << copyConstructor.GetCurrent() << endl;
	cout << "    GetString() : " << copyConstructor.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	copyConstructor.Empty();
	cout << "1.6 복사 생성자  Empty() 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자 배열을 삭제한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << copyConstructor.GetCapacity() << endl;
	cout << "    Length      : " << copyConstructor.GetLength() << endl;
	cout << "    Current     : " << copyConstructor.GetCurrent() << endl;
	cout << "    GetString() : " << copyConstructor.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	string pattern = "AAAAAAAAAAAAAAB";
	String stringConstructor(pattern);
	cout << "1.7 string자료형을 파라미터로 입력받는 생성자 생성시 테스트" << endl;
	cout << "    입력 : pattern " << endl;
	cout << "    기능 : string 자료형인 pattern을 파라미터로 입력받아 생성함" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << stringConstructor.GetCapacity() << endl;
	cout << "    Length      : " << stringConstructor.GetLength() << endl;
	cout << "    Current     : " << stringConstructor.GetCurrent() << endl;
	cout << "    GetString() : " << stringConstructor.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	stringConstructor.Empty();
	cout << "1.8 string자료형을 파라미터로 입력받는 생성자 Empty() 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자 배열을 삭제한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << stringConstructor.GetCapacity() << endl;
	cout << "    Length      : " << stringConstructor.GetLength() << endl;
	cout << "    Current     : " << stringConstructor.GetCurrent() << endl;
	cout << "    GetString() : " << stringConstructor.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String bufferTest("aaaaaaaaaaaaaab");
	cout << "1.9 문자열을 파라미터로 받는 생성자 생성시 테스트" << endl;
	cout << "    입력 : 'aaaaaaaaaaaaaab' " << endl;
	cout << "    기능 : 문자열을 파라미터로 입력받아 생성함" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << bufferTest.GetCapacity() << endl;
	cout << "    Length      : " << bufferTest.GetLength() << endl;
	cout << "    Current     : " << bufferTest.GetCurrent() << endl;
	cout << "    GetString() : " << bufferTest.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	bufferTest.Empty();
	cout << "1.10 문자열을 파라미터로 받는 생성자  Empty() 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자 배열을 삭제한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << bufferTest.GetCapacity() << endl;
	cout << "    Length      : " << bufferTest.GetLength() << endl;
	cout << "    Current     : " << bufferTest.GetCurrent() << endl;
	cout << "    GetString() : " << bufferTest.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	char character[30] = "aaaaaaaaaaaaabc";
	// 공백 짜름
	String bufferTest2(character);

	cout << "1.11 문자열을 파라미터로 받는 생성자 생성시 테스트" << endl;
	cout << "    입력 : character " << endl;
	cout << "    기능 : 문자열을 파라미터로 입력받아 생성함" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << bufferTest2.GetCapacity() << endl;
	cout << "    Length      : " << bufferTest2.GetLength() << endl;
	cout << "    Current     : " << bufferTest2.GetCurrent() << endl;
	cout << "    GetString() : " << bufferTest2.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	bufferTest2.Empty();
	cout << "1.12 문자열을 파라미터로 받는 생성자  Empty() 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자 배열을 삭제한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << bufferTest2.GetCapacity() << endl;
	cout << "    Length      : " << bufferTest2.GetLength() << endl;
	cout << "    Current     : " << bufferTest2.GetCurrent() << endl;
	cout << "    GetString() : " << bufferTest2.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String bufferTest3("aaaaaaaaaaaaaab", 15);
	cout << "1.13 문자열과, 문자열길이를 파라미터로 받는 생성자 생성시 테스트" << endl;
	cout << "    입력 : buffer : 'aaaaaaaaaaaaaab', length : 15 " << endl;
	cout << "    기능 : 문자열과 문자열길이를 파라미터로 입력받아 문자열 길이만큼 생성함" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << bufferTest3.GetCapacity() << endl;
	cout << "    Length      : " << bufferTest3.GetLength() << endl;
	cout << "    Current     : " << bufferTest3.GetCurrent() << endl;
	cout << "    GetString() : " << bufferTest3.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	bufferTest3.Empty();
	cout << "1.14 문자열과, 문자열길이를 파라미터로 받는 생성자 Empty() 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자 배열을 삭제한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << bufferTest3.GetCapacity() << endl;
	cout << "    Length      : " << bufferTest3.GetLength() << endl;
	cout << "    Current     : " << bufferTest3.GetCurrent() << endl;
	cout << "    GetString() : " << bufferTest3.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	char character2[30] = "aaaaaaaaaaaaabc";
	// 공백 짜름
	String bufferTest4(character2, 14);

	cout << "1.15 문자열과, 문자열길이를 파라미터로 받는 생성자 생성시 테스트" << endl;
	cout << "    입력 : character " << endl;
	cout << "    기능 : 문자열을 파라미터로 입력받아 생성함" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << bufferTest4.GetCapacity() << endl;
	cout << "    Length      : " << bufferTest4.GetLength() << endl;
	cout << "    Current     : " << bufferTest4.GetCurrent() << endl;
	cout << "    GetString() : " << bufferTest4.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	bufferTest4.Empty();
	cout << "1.16 문자열과, 문자열길이를 파라미터로 받는 생성자 Empty() 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자 배열을 삭제한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << bufferTest4.GetCapacity() << endl;
	cout << "    Length      : " << bufferTest4.GetLength() << endl;
	cout << "    Current     : " << bufferTest4.GetCurrent() << endl;
	cout << "    GetString() : " << bufferTest4.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String bufferTest5('a', 15);
	String replacementConstructor = bufferTest5;

	cout << "1.17 치환생성자" << endl;
	cout << "    입력 : bufferTest5 " << endl;
	cout << "    기능 : 치환된 객체를 입력받아 생성함" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << replacementConstructor.GetCapacity() << endl;
	cout << "    Length      : " << replacementConstructor.GetLength() << endl;
	cout << "    Current     : " << replacementConstructor.GetCurrent() << endl;
	cout << "    GetString() : " << replacementConstructor.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	replacementConstructor.Empty();
	cout << "1.18 치환생성자 Empty() 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자 배열을 삭제한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << replacementConstructor.GetCapacity() << endl;
	cout << "    Length      : " << replacementConstructor.GetLength() << endl;
	cout << "    Current     : " << replacementConstructor.GetCurrent() << endl;
	cout << "    GetString() : " << replacementConstructor.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String replacementConstructor2 = "AAAAAAAAAAAAAAB";
	cout << "1.19 치환생성자" << endl;
	cout << "    입력 : 'AAAAAAAAAAAAAAB' " << endl;
	cout << "    기능 : 치환된 문자열를 입력받아 생성함" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << replacementConstructor2.GetCapacity() << endl;
	cout << "    Length      : " << replacementConstructor2.GetLength() << endl;
	cout << "    Current     : " << replacementConstructor2.GetCurrent() << endl;
	cout << "    GetString() : " << replacementConstructor2.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	replacementConstructor2.Empty();
	cout << "1.20 치환생성자 Empty() 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자 배열을 삭제한다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << replacementConstructor2.GetCapacity() << endl;
	cout << "    Length      : " << replacementConstructor2.GetLength() << endl;
	cout << "    Current     : " << replacementConstructor2.GetCurrent() << endl;
	cout << "    GetString() : " << replacementConstructor2.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String isEmpty = "AAAAAAAAAAAAAAB";
	bool retVo = isEmpty.IsEmpty();
	cout << "2. 기본함수 테스트 " << endl;
	cout << "2.1 IsEmpty 함수 테스트" << endl;
	cout << "    입력 : 없음 " << endl;
	cout << "    기능 : 문자의 존재 유무를 판단함" << endl;
	cout << "    출력 : 문자의 존재 0 빈문자 1" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    Capacity    : " << isEmpty.GetCapacity() << endl;
	cout << "    Length      : " << isEmpty.GetLength() << endl;
	cout << "    Current     : " << isEmpty.GetCurrent() << endl;
	cout << "    GetString() : " << isEmpty.GetString() << endl;
	cout << "    ReturnValue : " << retVo << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;	


	String modifyString("abcdef");
	int retVo2;
	cout << "3 연산함수 테스트" << endl;
	cout << "3.1 SetAt() 함수 테스트" << endl;
	cout << "    입력 : index:2, character:'C' " << endl;
	cout << "    기능 : index 위치에 character로 modify 기능 함" << endl;
	cout << "    출력 : 수정된 위치, 수정이 없을시 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << modifyString.GetString() << endl;
	retVo2 = modifyString.SetAt(2, 'C');
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << modifyString.GetString() << endl;
	cout << "    ReturnValue : " << retVo2 << endl;
	cout << "    Capacity    : " << modifyString.GetCapacity() << endl;
	cout << "    Length      : " << modifyString.GetLength() << endl;
	cout << "    Current     : " << modifyString.GetCurrent() << endl;

	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String insertString;
	insertString = "aaaaaaaaaaaaaab";
	int retVo3;
	cout << "3.2 Insert() 함수 테스트" << endl;
	cout << "    입력 : index:14, character:'C' " << endl;
	cout << "    기능 : index 위치에 배열을 1개 늘리고 character 하나를 삽입 함" << endl;
	cout << "    출력 : 수정된 위치, 수정이 없을시 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << insertString.GetString() << endl;
	cout << "    Capacity    : " << insertString.GetCapacity() << endl;
	cout << "    Length      : " << insertString.GetLength() << endl;
	cout << "    Current     : " << insertString.GetCurrent() << endl;

	retVo3 = insertString.Insert(14, 'C');
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << insertString.GetString() << endl;
	cout << "    Capacity    : " << insertString.GetCapacity() << endl;
	cout << "    Length      : " << insertString.GetLength() << endl;
	cout << "    Current     : " << insertString.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String insertString2("aaaaaaaaaaaaaab");
	int retVo4;
	cout << "3.3 Insert() 함수 테스트" << endl;
	cout << "    입력 : index:14, character:'CCC' " << endl;
	cout << "    기능 : index 위치에 배열을 3개 늘리고 character 세개를 삽입 함" << endl;
	cout << "    출력 : 수정된 위치, 수정이 없을시 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << insertString2.GetString() << endl;
	cout << "    Capacity    : " << insertString2.GetCapacity() << endl;
	cout << "    Length      : " << insertString2.GetLength() << endl;
	cout << "    Current     : " << insertString2.GetCurrent() << endl;
	retVo4 = insertString2.Insert(14, "CCC");
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << insertString2.GetString() << endl;
	cout << "    Capacity    : " << insertString2.GetCapacity() << endl;
	cout << "    Length      : " << insertString2.GetLength() << endl;
	cout << "    Current     : " << insertString2.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	//String insertString2("aaaaaaaaaaaaaab",15);
	String insertString3 = "aaaaaaaaaaaaaab";
	string pattern2 = "CCC";
	int retVo5;
	cout << "3.4 Insert() 함수 테스트" << endl;
	cout << "    입력 : index:14, characters: string " << endl;
	cout << "    기능 : index 위치에 배열을 string.length()개 늘리고 string 문자들을 삽입 함" << endl;
	cout << "    출력 : 수정된 위치, 수정이 없을시 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << insertString3.GetString() << endl;
	cout << "    Capacity    : " << insertString3.GetCapacity() << endl;
	cout << "    Length      : " << insertString3.GetLength() << endl;
	cout << "    Current     : " << insertString3.GetCurrent() << endl;
	retVo5 = insertString3.Insert(14, pattern2);
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << insertString3.GetString() << endl;
	cout << "    Capacity    : " << insertString3.GetCapacity() << endl;
	cout << "    Length      : " << insertString3.GetLength() << endl;
	cout << "    Current     : " << insertString3.GetCurrent() << endl;
	cout << "    ReturnValue : " << retVo5 << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String storeString;
	int retVo6;
	cout << "3.5 Store() 함수 테스트" << endl;
	cout << "    입력 : Index 0번부터 10번까지 ABCDEFGHIJ 입력 " << endl;
	cout << "    기능 : Index 위치에 한 글자씩 입력 Store함" << endl;
	cout << "    출력 : 수정된 위치, 수정이 없을시 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << storeString.GetString() << endl;
	cout << "    Capacity    : " << storeString.GetCapacity() << endl;
	cout << "    Length      : " << storeString.GetLength() << endl;
	cout << "    Current     : " << storeString.GetCurrent() << endl;

	for (int i = 0; i < 10; i++)
		retVo6 = storeString.Store(i, 'A' + i);
	//retVo6 = storeString.Store(2,'A');	
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << storeString.GetString() << endl;
	cout << "    Capacity    : " << storeString.GetCapacity() << endl;
	cout << "    Length      : " << storeString.GetLength() << endl;
	cout << "    Current     : " << storeString.GetCurrent() << endl;
	cout << "    ReturnValue : " << retVo6 << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String storeString2;
	int retVo7;
	int retVo8;
	int retVo9;
	cout << "3.6 Store() 함수 테스트" << endl;
	cout << "    입력 : Index 0번부터 'ABCDEFGHIJ' 입력 " << endl;
	cout << "    기능 : Index 위치에 문자열을 Store함" << endl;
	cout << "    출력 : 수정된 위치, 수정이 없을시 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << storeString2.GetString() << endl;
	cout << "    Capacity    : " << storeString2.GetCapacity() << endl;
	cout << "    Length      : " << storeString2.GetLength() << endl;
	cout << "    Current     : " << storeString2.GetCurrent() << endl;

	retVo7 = storeString2.Store(0, "ABCDEFGHIJ");
	retVo8 = storeString2.GetLength();
	retVo9 = storeString2.Store(retVo8, "abcdefghij");

	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << storeString2.GetString() << endl;
	cout << "    Capacity    : " << storeString2.GetCapacity() << endl;
	cout << "    Length      : " << storeString2.GetLength() << endl;
	cout << "    Current     : " << storeString2.GetCurrent() << endl;
	cout << "    ReturnValue : " << retVo7 << endl;
	cout << "    ReturnValue : " << retVo9 << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String storeString3;
	int retVo10;
	int retVo11;
	cout << "3.7 Store() 함수 테스트" << endl;
	cout << "    입력 : Index:0 string:'ABCDEFGHIJ'" << endl;
	cout << "    기능 : Index 위치에 string 문자열을 Store함" << endl;
	cout << "    출력 : 수정된 위치, 수정이 없을시 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << storeString3.GetString() << endl;
	cout << "    Capacity    : " << storeString3.GetCapacity() << endl;
	cout << "    Length      : " << storeString3.GetLength() << endl;
	cout << "    Current     : " << storeString3.GetCurrent() << endl;

	string string2 = "ABCDEFG";
	storeString3.Store(0, "AAAAB");
	retVo10 = storeString3.GetLength();
	retVo11 = storeString3.Store(retVo10, string2);

	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << storeString3.GetString() << endl;
	cout << "    Capacity    : " << storeString3.GetCapacity() << endl;
	cout << "    Length      : " << storeString3.GetLength() << endl;
	cout << "    Current     : " << storeString3.GetCurrent() << endl;
	cout << "    ReturnValue : " << retVo11 << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String deleteString = "ABCDEFGHIJKLMNO";
	int retVo13;
	cout << "3.8 Delete() 함수 테스트" << endl;
	cout << "    입력 : Index:2 count 5" << endl;
	cout << "    기능 : Index 위치에서 count만큼 Delete 함" << endl;
	cout << "    출력 : 삭제된 위치, 삭제 없을시 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << deleteString.GetString() << endl;
	cout << "    Capacity    : " << deleteString.GetCapacity() << endl;
	cout << "    Length      : " << deleteString.GetLength() << endl;
	cout << "    Current     : " << deleteString.GetCurrent() << endl;

	retVo13 = deleteString.Delete(2, 5);

	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << deleteString.GetString() << endl;
	cout << "    Capacity    : " << deleteString.GetCapacity() << endl;
	cout << "    Length      : " << deleteString.GetLength() << endl;
	cout << "    Current     : " << deleteString.GetCurrent() << endl;
	cout << "    ReturnValue : " << retVo13 << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;
	deleteString.Clear();

	String makeUpperString = "abcdefghij";
	cout << "3.9 MakeUpper() 함수 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 소문자를 대문자로 변환함" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << makeUpperString.GetString() << endl;
	makeUpperString.MakeUpper();
	cout << "    함수실행 후   " << endl;
	cout << makeUpperString.GetString() << endl;

	cout << "3.10 MakeLower() 함수 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 대문자를 소문자로 변환함" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << makeUpperString.GetString() << endl;
	makeUpperString.MakeLower();
	cout << "    함수실행 후   " << endl;
	cout << makeUpperString.GetString() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	makeUpperString.Clear();

	String compareString = "bbb";
	int retVo16;
	cout << "3.11 Compare() 함수 테스트" << endl;
	cout << "    입력 : characters" << endl;
	cout << "    기능 : 문자의 크기 비교" << endl;
	cout << "    출력 : 같으면 0, this가 크면 1 this가 작으면 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;
	retVo16 = compareString.Compare("bb");
	cout << "    함수실행 후   " << endl;
	cout << "    결과값      : " << retVo16 << endl;
	cout << "    GetString() : " << compareString.GetString() << endl;
	cout << "    Capacity    : " << compareString.GetCapacity() << endl;
	cout << "    Length      : " << compareString.GetLength() << endl;
	cout << "    Current     : " << compareString.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String compareNoCaseString = "bbb";
	int retVo17;
	cout << "3.12 Compare() 함수 테스트" << endl;
	cout << "    입력 : characters" << endl;
	cout << "    기능 : 문자의 크기 비교" << endl;
	cout << "    출력 : 같으면 0, this가 크면 1 this가 작으면 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;
	retVo17 = compareNoCaseString.CompareNoCase("BBB");
	cout << "    함수실행 후   " << endl;
	cout << "    결과값      : " << retVo17 << endl;
	cout << "    GetString() : " << compareNoCaseString.GetString() << endl;
	cout << "    Capacity    : " << compareNoCaseString.GetCapacity() << endl;
	cout << "    Length      : " << compareNoCaseString.GetLength() << endl;
	cout << "    Current     : " << compareNoCaseString.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;
	compareString.Clear();
	compareNoCaseString.Clear();

	//                  0123456789012345678901234567890123456
	String findString = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac";
	int retVo18;
	cout << "3.12 Find() 함수 테스트" << endl;
	cout << "    입력 : character: 'b'" << endl;
	cout << "    기능 : 문자위치 찾기" << endl;
	cout << "    출력 : 찾으면 위치값, 못찾으면 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;

	retVo18 = findString.Find('b');
	cout << "    함수실행 후   " << endl;
	cout << "    결과값      : " << retVo18 << endl;
	cout << "    GetString() : " << findString.GetString() << endl;
	cout << "    Capacity    : " << findString.GetCapacity() << endl;
	cout << "    Length      : " << findString.GetLength() << endl;
	cout << "    Current     : " << findString.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String findString2 = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac";
	int retVo19;
	cout << "3.13 Find() 함수 테스트" << endl;
	cout << "    입력 : character: 'bb'" << endl;
	cout << "    기능 : 문자위치 찾기" << endl;
	cout << "    출력 : 찾으면 위치값, 못찾으면 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;

	retVo19 = findString.Find("bb");
	cout << "    함수실행 후   " << endl;
	cout << "    결과값      : " << retVo19 << endl;
	cout << "    GetString() : " << findString2.GetString() << endl;
	cout << "    Capacity    : " << findString2.GetCapacity() << endl;
	cout << "    Length      : " << findString2.GetLength() << endl;
	cout << "    Current     : " << findString2.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String findString3 = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac";
	int retVo20;
	cout << "3.14 Find() 함수 테스트" << endl;
	cout << "    입력 : character: 'b', index: 11" << endl;
	cout << "    기능 : index 위치부터 문자위치 찾기" << endl;
	cout << "    출력 : 찾으면 위치값, 못찾으면 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;

	retVo20 = findString3.Find('b', 11);
	cout << "    함수실행 후   " << endl;
	cout << "    결과값      : " << retVo20 << endl;
	cout << "    GetString() : " << findString3.GetString() << endl;
	cout << "    Capacity    : " << findString3.GetCapacity() << endl;
	cout << "    Length      : " << findString3.GetLength() << endl;
	cout << "    Current     : " << findString3.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String findString4 = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac";
	int retVo21;
	cout << "3.15 Find() 함수 테스트" << endl;
	cout << "    입력 : character: 'bb', index: 14" << endl;
	cout << "    기능 : index 위치부터 문자열 위치 찾기" << endl;
	cout << "    출력 : 찾으면 위치값, 못찾으면 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;

	retVo21 = findString4.Find("bb", 20);
	cout << "    함수실행 후   " << endl;
	cout << "    결과값      : " << retVo21 << endl;
	cout << "    GetString() : " << findString4.GetString() << endl;
	cout << "    Capacity    : " << findString4.GetCapacity() << endl;
	cout << "    Length      : " << findString4.GetLength() << endl;
	cout << "    Current     : " << findString4.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String findString5 = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac";
	int retVo22;
	cout << "3.16 RevercedFind() 함수 테스트" << endl;
	cout << "    입력 : character: 'b'" << endl;
	cout << "    기능 : 뒤부터 같은 문자 위치 찾기" << endl;
	cout << "    출력 : 찾으면 위치값, 못찾으면 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;

	retVo22 = findString5.ReversedFind('b');
	cout << "    함수실행 후   " << endl;
	cout << "    결과값      : " << retVo22 << endl;
	cout << "    GetString() : " << findString5.GetString() << endl;
	cout << "    Capacity    : " << findString5.GetCapacity() << endl;
	cout << "    Length      : " << findString5.GetLength() << endl;
	cout << "    Current     : " << findString5.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String findString6 = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac";
	int retVo23;
	cout << "3.17 FindOneOfFind() 함수 테스트" << endl;
	cout << "    입력 : character: 'cdef'" << endl;
	cout << "    기능 : 하나라도 같은 문자 위치 찾기" << endl;
	cout << "    출력 : 찾으면 위치값, 못찾으면 -1" << endl;
	cout << "    ---------------------------------------------------" << endl;

	retVo23 = findString6.FindOneOf("cdef");
	cout << "    함수실행 후   " << endl;
	cout << "    결과값      : " << retVo23 << endl;
	cout << "    GetString() : " << findString6.GetString() << endl;
	cout << "    Capacity    : " << findString6.GetCapacity() << endl;
	cout << "    Length      : " << findString6.GetLength() << endl;
	cout << "    Current     : " << findString6.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	findString.Clear();
	findString2.Clear();
	findString3.Clear();
	findString4.Clear();
	//findString5.Clear();
	findString6.Clear();

	String removeString = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac";
	int retVo24;
	cout << "3.17 ReMove() 함수 테스트" << endl;
	cout << "    입력 : character: 'a'" << endl;
	cout << "    기능 : 입력문자 삭제함" << endl;
	cout << "    출력 : 삭제한 카운트, 변화없을시 0" << endl;
	cout << "    ---------------------------------------------------" << endl;

	retVo24 = removeString.Remove('a');
	cout << "    함수실행 후   " << endl;
	cout << "    결과값      : " << retVo24 << endl;
	cout << "    GetString() : " << removeString.GetString() << endl;
	cout << "    Capacity    : " << removeString.GetCapacity() << endl;
	cout << "    Length      : " << removeString.GetLength() << endl;
	cout << "    Current     : " << removeString.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String replaceString = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac";
	int retVo25;
	cout << "3.18 RePlace() 함수 테스트" << endl;
	cout << "    입력 : oldCharacter: 'a',newCharacter: 'f'" << endl;
	cout << "    기능 : oldCharacter 문자를 newCharacter문자로 바꾸는 기능" << endl;
	cout << "    출력 : 변경 카운트, 변화없을시 0" << endl;
	cout << "    ---------------------------------------------------" << endl;

	retVo25 = replaceString.Replace('a', 'f');
	cout << "    함수실행 후   " << endl;
	cout << "    결과값      : " << retVo25 << endl;
	cout << "    GetString() : " << replaceString.GetString() << endl;
	cout << "    Capacity    : " << replaceString.GetCapacity() << endl;
	cout << "    Length      : " << replaceString.GetLength() << endl;
	cout << "    Current     : " << replaceString.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	//String replaceString ="aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac";
	//int retVo26;
	//cout << "3.18 RePlace() 함수 테스트" << endl;
	//cout << "    입력 : oldCharacter: 'a',newCharacter: 'f'"<< endl;
	//cout << "    기능 : oldCharacter 문자를 newCharacter문자로 바꾸는 기능" << endl;
	//cout << "    출력 : 변경 카운트, 변화없을시 0" << endl;
	//cout << "    ---------------------------------------------------"<< endl;
	//retVo26 = replaceString.Replace('a','f');
	//cout << "    함수실행 후   " << endl;
	//cout << "    결과값      : " << retVo25   << endl;
	//cout << "    GetString() : " << replaceString.GetString()   << endl;
	//cout << "    Capacity    : " << replaceString.GetCapacity() << endl;
	//cout << "    Length      : " << replaceString.GetLength()   << endl;
	//cout << "    Current     : " << replaceString.GetCurrent()  << endl;	
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;


	String makeReverseString = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac";
	cout << "3.20 MakeReverse() 함수 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자를 뒤집는다" << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	makeReverseString.MakeReverse();
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << makeReverseString.GetString() << endl;
	cout << "    Capacity    : " << makeReverseString.GetCapacity() << endl;
	cout << "    Length      : " << makeReverseString.GetLength() << endl;
	cout << "    Current     : " << makeReverseString.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;


	String trimeString = " \n  \n\t\t\t\t\t \n \n\n\t\t\taaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac";
	cout << "3.21 TrimLeft() 함수 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자열의 시작부분에 공백, 탭, 줄바꿈을 잘라낸다." << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << trimeString.GetString() << endl;
	cout << "    Capacity    : " << trimeString.GetCapacity() << endl;
	cout << "    Length      : " << trimeString.GetLength() << endl;
	cout << "    Current     : " << trimeString.GetCurrent() << endl;
	trimeString.TrimLeft();
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << trimeString.GetString() << endl;
	cout << "    Capacity    : " << trimeString.GetCapacity() << endl;
	cout << "    Length      : " << trimeString.GetLength() << endl;
	cout << "    Current     : " << trimeString.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String trimeString2 = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaac \n  \n\t\t\t\t\t \n \n\n\t\t\t";
	cout << "3.22 TrimRight() 함수 테스트" << endl;
	cout << "    입력 : 없음" << endl;
	cout << "    기능 : 문자열의 끝부분에 공백, 탭, 줄바꿈을 잘라낸다." << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << trimeString2.GetString() << endl;
	cout << "    Capacity    : " << trimeString2.GetCapacity() << endl;
	cout << "    Length      : " << trimeString2.GetLength() << endl;
	cout << "    Current     : " << trimeString2.GetCurrent() << endl;
	trimeString2.TrimRight();
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << trimeString2.GetString() << endl;
	cout << "    Capacity    : " << trimeString2.GetCapacity() << endl;
	cout << "    Length      : " << trimeString2.GetLength() << endl;
	cout << "    Current     : " << trimeString2.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String trimeString3 = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaaccc";
	cout << "3.23 TrimLeft() 함수 테스트" << endl;
	cout << "    입력 : character:a" << endl;
	cout << "    기능 : 문자열의 앞부분부터 입력받은 문자가 존재하면 잘라낸다." << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << trimeString3.GetString() << endl;
	cout << "    Capacity    : " << trimeString3.GetCapacity() << endl;
	cout << "    Length      : " << trimeString3.GetLength() << endl;
	cout << "    Current     : " << trimeString3.GetCurrent() << endl;
	trimeString3.TrimLeft('a');
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << trimeString3.GetString() << endl;
	cout << "    Capacity    : " << trimeString3.GetCapacity() << endl;
	cout << "    Length      : " << trimeString3.GetLength() << endl;
	cout << "    Current     : " << trimeString3.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String trimeString4 = "aaaaaaaaabaaaaaaaaabbaaaaaaaabbbaaaaaaaccc";
	cout << "3.24 TrimRight() 함수 테스트" << endl;
	cout << "    입력 : character:c" << endl;
	cout << "    기능 : 문자열의 뒷부분부터 입력받은 문자가 존재하면 잘라낸다." << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << trimeString4.GetString() << endl;
	cout << "    Capacity    : " << trimeString4.GetCapacity() << endl;
	cout << "    Length      : " << trimeString4.GetLength() << endl;
	cout << "    Current     : " << trimeString4.GetCurrent() << endl;
	trimeString4.TrimRight('c');
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << trimeString4.GetString() << endl;
	cout << "    Capacity    : " << trimeString4.GetCapacity() << endl;
	cout << "    Length      : " << trimeString4.GetLength() << endl;
	cout << "    Current     : " << trimeString4.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	String trimeString5 = "ccccc";
	cout << "3.25 TrimRight() 함수 테스트" << endl;
	cout << "    입력 : character:c" << endl;
	cout << "    기능 : 문자열의 뒷부분부터 입력받은 문자가 존재하면 잘라낸다." << endl;
	cout << "    출력 : 없음" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << trimeString5.GetString() << endl;
	cout << "    Capacity    : " << trimeString5.GetCapacity() << endl;
	cout << "    Length      : " << trimeString5.GetLength() << endl;
	cout << "    Current     : " << trimeString5.GetCurrent() << endl;
	trimeString5.TrimRight('c');
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << trimeString5.GetString() << endl;
	cout << "    Capacity    : " << trimeString5.GetCapacity() << endl;
	cout << "    Length      : " << trimeString5.GetLength() << endl;
	cout << "    Current     : " << trimeString5.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	cout << "3.26 형변환 함수 테스트" << endl;
	cout << "    GetString() : " << static_cast <char*> (findString5) << endl;

	String operaterString;

	cout << "3.27 operater=() 함수 테스트" << endl;
	cout << "    입력 : character:b" << endl;
	cout << "    기능 : 문자열의 뒷 부분에 입력받은 character를 붙여넣다." << endl;
	cout << "    출력 : String값" << endl;
	cout << "    ---------------------------------------------------" << endl;
	cout << "    함수실행 전   " << endl;
	cout << "    GetString() : " << operaterString.GetString() << endl;
	cout << "    Capacity    : " << operaterString.GetCapacity() << endl;
	cout << "    Length      : " << operaterString.GetLength() << endl;
	cout << "    Current     : " << operaterString.GetCurrent() << endl;
	operaterString = 'b';
	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << operaterString.GetString() << endl;
	cout << "    Capacity    : " << operaterString.GetCapacity() << endl;
	cout << "    Length      : " << operaterString.GetLength() << endl;
	cout << "    Current     : " << operaterString.GetCurrent() << endl;
	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	cout << "3.28 operater+() 함수 테스트" << endl;
	cout << "    ---------------------------------------------------" << endl;

	String operatorString2 = "abc";
	String operatorString3 = "def";

	string operatorString6 = "zzz";
	cout << "    " << operatorString2 + operatorString3 << endl;
	cout << "    " << operatorString2 + 'a' << endl;
	cout << "    " << operatorString2 + "ddd" << endl;
	cout << "    " << operatorString2 + operatorString6 << endl;

	cout << "    " << static_cast<char*>(operatorString2 + operatorString3) << endl;
	cout << "    " << static_cast<char*>(operatorString2 + 'a') << endl;
	cout << "    " << static_cast<char*>(operatorString2 + "ddd") << endl;
	cout << "    " << static_cast<char*>(operatorString2 + operatorString6) << endl;


	cout << "3.29 operater+=() 함수 테스트" << endl;
	cout << "    ---------------------------------------------------" << endl;

	String operatorString4 = "abc";
	String operatorString5 = "def";

	string operatorString7 = "zzz";

	operatorString4 += operatorString5;
	cout << "    " << static_cast<char*>(operatorString4) << endl;

	operatorString4 += 'a';
	cout << "    " << static_cast<char*>(operatorString4) << endl;

	operatorString4 += "ddd";
	cout << "    " << static_cast<char*>(operatorString4) << endl;

	operatorString4 += operatorString7;
	cout << "    " << static_cast<char*>(operatorString4) << endl;


	cout << "3.30 IsHangle() 함수 테스트" << endl;
	cout << "    ---------------------------------------------------" << endl;

	String operatorString8 = "a한";

	cout << "    GetString() : " << operatorString8.GetString() << endl;

	cout << "    " << operatorString8.IsHangle(0) << endl;
	cout << "    " << operatorString8.IsHangle(1) << endl;

	cout << "3.31 TrimLeft() 함수 테스트" << endl;
	cout << "    ---------------------------------------------------" << endl;

	String operatorString9 = "ababababbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";

	cout << "    GetString() : " << operatorString9.GetString() << endl;
	cout << "    Capacity    : " << operatorString9.GetCapacity() << endl;
	cout << "    Length      : " << operatorString9.GetLength() << endl;
	cout << "    Current     : " << operatorString9.GetCurrent() << endl;

	operatorString9.TrimLeft("ab");

	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << operatorString9.GetString() << endl;
	cout << "    Capacity    : " << operatorString9.GetCapacity() << endl;
	cout << "    Length      : " << operatorString9.GetLength() << endl;
	cout << "    Current     : " << operatorString9.GetCurrent() << endl;

	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	cout << "3.32 TrimRight() 함수 테스트" << endl;
	cout << "    ---------------------------------------------------" << endl;

	String operatorString10 = "ababababbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbabababab";

	cout << "    GetString() : " << operatorString10.GetString() << endl;
	cout << "    Capacity    : " << operatorString10.GetCapacity() << endl;
	cout << "    Length      : " << operatorString10.GetLength() << endl;
	cout << "    Current     : " << operatorString10.GetCurrent() << endl;

	operatorString10.TrimRight("ab");

	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << operatorString10.GetString() << endl;
	cout << "    Capacity    : " << operatorString10.GetCapacity() << endl;
	cout << "    Length      : " << operatorString10.GetLength() << endl;
	cout << "    Current     : " << operatorString10.GetCurrent() << endl;

	//cout << "\n\n    getchar() 입력 : 의미 없음"<< getchar() << "\n\n" << endl;

	cout << "3.33 replace() 함수 테스트" << endl;
	cout << "    ---------------------------------------------------" << endl;

	String operatorString11 = "ababababbbbbbbbbbbbbbbabababbbbbbbbbbbbbbbbbbbbabababab";

	cout << "    GetString() : " << operatorString11.GetString() << endl;
	cout << "    Capacity    : " << operatorString11.GetCapacity() << endl;
	cout << "    Length      : " << operatorString11.GetLength() << endl;
	cout << "    Current     : " << operatorString11.GetCurrent() << endl;

	operatorString11.Replace("ab", "ccc");

	cout << "    함수실행 후   " << endl;
	cout << "    GetString() : " << operatorString11.GetString() << endl;
	cout << "    Capacity    : " << operatorString11.GetCapacity() << endl;
	cout << "    Length      : " << operatorString11.GetLength() << endl;
	cout << "    Current     : " << operatorString11.GetCurrent() << endl;

	cout << "\n\n    getchar() 입력 : 의미 없음" << getchar() << "\n\n" << endl;
	return 0;
}

#endif

String::String() {
	this->front = new char[MAX];
	this->front[0] = '\0';
	this->capacity = MAX;
	this->length = 0;
	this->current = -1;
}

String::String(const String& source) {
	this->front = new char[source.capacity];

	if (source.length > 0) {
		memcpy(this->front, source.front, source.length);
	}
	this->front[source.length] = '\0';
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

String::String(char character, Long nRepeat) {
	Long capacity = MAX;

	while (capacity - 1 < nRepeat) {
		capacity += MAX;
	}

	this->front = new char[capacity];
	memset(this->front, character, nRepeat);
	this->front[nRepeat] = '\0';
	this->capacity = capacity;
	this->length = nRepeat;
	this->current = this->length - 1;
}

String::String(string characters) {
	Long capacity = MAX;
	Long length;

	length = characters.size();

	while (capacity - 1 < length)
		capacity += MAX;

	this->front = new char[capacity];

	memcpy(this->front, characters.c_str(), length);
	this->front[length] = '\0';
	this->capacity = capacity;
	this->length = length;
	this->current = this->length - 1;
}

String::String(char(*chracters)) {
	Long capacity = MAX;
	Long length;

	length = strlen(chracters);

	while (capacity - 1 < length)
		capacity += MAX;

	this->front = new char[capacity];

	memcpy(this->front, chracters, length);
	this->front[length] = '\0';
	this->capacity = capacity;
	this->length = length;
	this->current = length - 1;
}

String::String(char(*chracters), Long length) {
	Long capacity = MAX;

	while (capacity - 1 < length)
		capacity += MAX;

	this->front = new char[capacity];
	memcpy(this->front, chracters, length);
	this->front[length] = '\0';
	this->capacity = capacity;
	this->length = length;
	this->current = this->length - 1;
}

String::~String() {
	if (this->front != 0) {
		delete[] this->front;
	}
}

void String::Clear() {
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = 0;
	this->capacity = 0;
	this->length = 0;
	this->current = -1;
}

void String::Empty() {
	this->front[0] = '\0';
	this->length = 0;
	this->current = -1;
}

Long String::Delete(Long index, Long count) {
	this->current = index;

	assert(count > 0 && this->length - (this->current + count) >= 0);

	memmove(this->front + this->current, this->front + this->current + count, length - count);
	this->length -= count;
	this->front[this->length] = '\0';

	return -1;
}

Long String::Insert(Long index, char character) {
	assert(index >= 0 && index < this->length);

	char(*temp);
	this->current = index;

	if (this->length + 1 >= this->capacity - 1) {
		temp = new char[this->capacity + 1];

		memcpy(temp, this->front, this->length);

		if (this->front != 0) {
			delete[] this->front;
			this->front = 0;
		}
		this->front = temp;
		(this->capacity)++;
	}

	memmove(this->front + this->current + 1, this->front + this->current, this->length - this->current);
	this->front[this->current] = character;
	(this->length)++;
	this->front[this->length] = '\0';

	return this->current;
}

Long String::Insert(Long index, char(*characters)) {
	assert(index >= 0 && index < this->length);

	Long length;
	char(*temp);

	length = strlen(characters);

	if (this->length + length > this->capacity - 1) {
		temp = new char[this->length + length + 1];
		memcpy(temp, this->front, this->length);

		if (this->front != 0)
			delete[] this->front;

		this->front = temp;
		this->capacity = this->length + length + 1;
	}

	this->current = index;

	memmove(this->front + this->current + length, this->front + this->current, this->length - this->current);
	memcpy(this->front + this->current, characters, length);
	this->length += length;
	this->front[this->length] = '\0';

	return this->current;
}

Long String::Insert(Long index, string characters) {
	assert(index >= 0 && index < this->length);

	Long length;
	char *temp;

	this->current = index;
	length = characters.size(); // string.size() same as string.length();

	if (this->length + length > this->capacity - 1) {
		temp = new char[this->capacity + length];
		memcpy(temp, this->front, this->length);

		if (this->front != 0) {
			delete[] this->front;
			this->front = 0;
		}
		this->front = temp;
		this->capacity += length;
	}

	memmove(this->front + this->current + length, this->front + this->current, this->length - this->current);
	memcpy(this->front + this->current, characters.c_str(), length);
	this->length += length;
	this->front[this->length] = '\0';

	return this->current;
}

Long String::Store(Long index, char character) {
	assert(index >= this->length && index < this->capacity);

	this->current = index;
	this->front[this->current] = character;
	(this->length)++;
	this->front[this->length] = '\0';

	return this->current;
}

Long String::Store(Long index, char(*characters)) {
	assert(index >= this->length && index + this->length < this->capacity);

	Long length;

	this->current = index;
	length = strlen(characters);
	memcpy(this->front + this->current, characters, length);
	this->length = this->length + length;
	this->front[this->length] = '\0';

	return this->current;
}

Long String::Store(Long index, string characters) {
	assert(index >= this->length && this->current + length < this->capacity);

	Long length;

	this->current = index;
	length = characters.size();

	memcpy(this->front + this->current, characters.c_str(), length);
	this->length += length;
	this->front[this->length] = '\0';

	return this->current;
}

Long String::SetAt(Long index, char character) {
	assert(index >= 0 && index < this->length);

	this->current = index;
	this->front[this->current] = character;
	return this->current;
}

Long String::Find(char character) {
#if 0
	Long i = 0;
	this->current = -1;

	while (i < this->length && this->current == -1) {
		if (this->front[i] == character) {
			this->current = i;
		}
		i++;
	}
	return this->current;
#endif
	Long i = 0;
	Long index = -1;

	while (i < this->length && this->front[i] != character) {
		i++;
	}

	if (i < this->length) {
		index = i;
	}

	return index;
}

Long String::Find(char(*characters)) {
#if 0
	Long length;
	Long count;
	Long i = 0;
	Long j;

	this->current = -1;
	length = strlen(characters);

	while (i < this->length && this->current == -1) {

		j = 0;
		count = 0;
		while (j < length && j == count) {
			if (this->front[i + j] == characters[j]) {
				count++;
			}
			j++;
		}

		if (length == count) {
			this->current = i;
		}
		i++;
	}

	return this->current;
#endif
	Long length;
	Long count;
	Long i = 0;

	Long index = -1;
	length = strlen(characters); //문자열의 길이
	//count = this->length - ( i + 1 );
	count = this->length - i;

	while (i < this->length && count >= length && strncmp(this->front + i, characters, length) != 0) {
		i++;
		//count = this->length - ( i + 1 );
		count = this->length - i;

	}
	if (i < this->length && count >= length) {
		index = i;
	}

	return index;
}

Long String::Find(char character, Long index) {
#if 0
	Long i = index;
	this->current = -1;

	while (i < this->length && this->current == -1) {
		if (this->front[i] == character) {
			this->current = i;
		}
		i++;
	}
	return this->current;
#endif
	Long i = index;
	index = -1;

	while (i < this->length && this->front[i] != character) {
		i++;
	}

	if (i < this->length) {
		index = i;
	}

	return index;
}

Long String::Find(char(*characters), Long index) {
#if 0
	Long length;
	Long count;
	Long i = index;
	Long j;

	this->current = -1;
	length = strlen(characters);

	while (i < this->length && this->current == -1) {

		j = 0;
		count = 0;
		while (j < length && j == count) {
			if (this->front[i + j] == characters[j]) {
				count++;
			}
			j++;
		}

		if (length == count) {
			this->current = i;
		}
		i++;
	}

	return this->current;
#endif
	Long length;
	Long count;
	Long i = index;

	index = -1;
	length = strlen(characters);
	//count = this->length - (i + 1);
	count = this->length - i;

	while (i < this->length && count >= length && strncmp(this->front + i, characters, length) != 0) {
		i++;
		//count = this->length - ( i + 1);
		count = this->length - i;
	}
	if (i < this->length && count >= length) {
		index = i;
	}

	return index;
}

Long String::ReversedFind(char character) {
#if 0
	Long i = this->length - 1;
	this->current = -1;

	while (i >= 0 && this->current == -1) {
		if (this->front[i] == character) {
			this->current = i;
		}
		i--;
	}
	return this->current;
#endif
	Long i = this->length - 1;
	Long index = -1;

	while (i >= 0 && this->front[i] != character) {

		i--;
	}
	if (i >= 0) {
		index = i;
	}

	return index;
}

Long String::FindOneOf(char(*characters)) {
	Long length;
	Long i;
	Long j;
	Long index = -1;

	// this->current = -1;
	length = strlen(characters);

	i = 0;
	while (i < this->length && this->current == -1) {
		j = 0;
		while (j < length) {
			if (this->front[i] == characters[j]) {
				index = i;
			}
			j++;
		}
		i++;
	}

	return index;
}

Long String::Remove(char character) {
	Long count = 0;
	for (int i = 0; i < this->length; i++) {
		if (this->front[i] == character) {
			memmove(this->front + i, this->front + i + 1, this->length - i - 1);
			this->front[this->length - 1] = '\0';
			(this->length)--;
			count++;
			i--;
		}
	}
	// this->current = -1;
	return count;
}

Long String::Replace(char oldCharacter, char newCharacter) {
	Long count = 0;
	for (int i = 0; i < this->length; i++) {
		if (this->front[i] == oldCharacter) {
			memset(this->front + i, newCharacter, sizeof(char));
			count++;
		}
	}
	// this->current = -1;
	return count;
}

Long String::Replace(char(*oldCharacter), char(*newCharacter)) {

	Long(*indexes);
	char(*temp);

	Long length;
	Long count;

	Long capacity;
	Long fixLength;
	Long copySize = 0;
	Long indexToWrite = 0;
	Long indexToRead = 0;
	Long oldCharacterLength = strlen(oldCharacter);
	Long newCharacterLength = strlen(newCharacter);

	Long it = 0;
	Long i = 0;
	Long j = 0;
	Long k = 0;

	indexes = new Long[this->length];

	length = strlen(oldCharacter);
	//count = this->length - ( i + 1 );
	count = this->length - i;

	while (i < this->length && count >= length) {
		if (strncmp(this->front + i, oldCharacter, length) == 0) {
			indexes[j] = i;
			it++;
			j++;
		}
		i++;
		count = this->length - i;
	}

	fixLength = this->length - (strlen(oldCharacter) * it) + (strlen(newCharacter) * it);

	capacity = this->capacity;
	while (this->capacity - 1 <= fixLength)
		capacity += MAX;

	temp = new char[capacity];

	while (k < it) {
		copySize = indexes[k] - indexToRead;
		memcpy(temp + indexToWrite, this->front + indexToRead, copySize);
		indexToWrite += copySize;
		indexToRead += (copySize + oldCharacterLength);

		memcpy(temp + indexToWrite, newCharacter, newCharacterLength);
		indexToWrite += newCharacterLength;

		k++;
	}

	temp[fixLength] = '\0';

	delete[] this->front;
	this->front = temp;
	this->capacity = capacity;
	this->length = fixLength;

	return it;
}

Long String::Compare(char(*characters)) {
#if 0	
	Long retVo;
	Long length;
	Long it;
	Long i = 0;

	length = strlen(characters);

	if (this->length <= length)
		it = this->length;
	else
		it = length;

	if (this->front[i] > characters[i])
		retVo = 1;
	if (this->front[i] < characters[i])
		retVo = -1;
	if (this->front[i] == characters[i])
		retVo = 0;

	i++;
	while (i < it && retVo == 0) {

		if (this->front[i] > characters[i])
			retVo = 1;
		if (this->front[i] < characters[i])
			retVo = -1;
		if (this->front[i] == characters[i])
			retVo = 0;
		i++;
	}

	if (retVo == 0 && this->length > length)
		retVo = 1;
	if (retVo == 0 && this->length < length)
		retVo = -1;

	return retVo;
#endif
	return strcmp(this->front, characters);

}

Long String::CompareNoCase(char(*characters)) {
#if 0
	Long retVo;
	char(*one);
	char(*other);
	Long length;
	Long it;
	Long i = 0;

	one = new char[this->length + 1];
	memcpy(one, this->front, this->length);
	one[this->length] = '\0';

	for (int i = 0; i < this->length; i++) {
		if (one[i] >= 'a' && one[i] <= 'z')
			one[i] = one[i] - 32;
	}

	length = strlen(characters);
	other = new char[length + 1];
	memcpy(other, characters, length);
	other[this->length] = '\0';

	for (int j = 0; j < this->length; j++) {
		if (other[j] >= 'a' && other[j] <= 'z')
			other[j] = other[j] - 32;
	}

	if (this->length <= length)
		it = this->length;
	else
		it = length;

	if (one[i] > other[i])
		retVo = 1;
	if (one[i] < other[i])
		retVo = -1;
	if (one[i] == other[i])
		retVo = 0;

	i++;
	while (i < it && retVo == 0) {

		if (one[i] > other[i])
			retVo = 1;
		if (one[i] < other[i])
			retVo = -1;
		if (one[i] == other[i])
			retVo = 0;
		i++;
	}

	if (retVo == 0 && this->length > length)
		retVo = 1;
	if (retVo == 0 && this->length < length)
		retVo = -1;

	return retVo;
#endif
	return _strnicmp(this->front, characters, strlen(characters));

}

void String::TrimLeft() {
	assert(this->length > 0);

	this->current = 0;

	while (this->front[this->current] != '\0' && (this->front[this->current] == ' ' ||
		this->front[this->current] == '\n' || this->front[this->current] == '\t')) {
		(this->current)++;
	}

	memmove(this->front, this->front + this->current, this->length - this->current);
	this->length = this->length - this->current;
	this->front[this->length] = '\0';
	this->current = -1;
}

void String::TrimLeft(char character) {
	assert(this->length > 0);
	this->current = 0;

	while (this->front[this->current] == character && this->front[this->current] != '\0') {
		(this->current)++;
	}

	memmove(this->front, this->front + this->current, this->length - this->current);
	this->length = this->length - this->current;
	this->front[this->length] = '\0';
	this->current = -1;
}

void String::TrimLeft(char(*characters)) {
	assert(this->length > 0);

	Long length;
	Long identical;
	Long count = 0;
	Long i;
	Long j;

	length = strlen(characters);

	i = 0;
	while (i < this->length && i / length == count) {
		j = 0;
		identical = 0;

		while (j < length && j == identical) {
			if (this->front[i + j] == characters[j]) {
				identical++;
			}
			j++;
		}

		if (identical == length)
			count++;
		this->current = i;
		i += length;
	}

	memmove(this->front, this->front + this->current, this->length - this->current);
	this->length = this->length - this->current;
	this->front[this->length] = '\0';
	this->current = -1;
}

void String::TrimRight() {
	assert(this->length > 0);

	this->current = this->length - 1;

	while (this->current >= 0 && (this->front[this->current] == ' ' ||
		this->front[this->current] == '\n' || this->front[this->current] == '\t')) {
		(this->current)--;
	}

	this->length = this->current + 1;
	this->front[this->length] = '\0';
	this->current = -1;

}

void String::TrimRight(char character) {
	assert(this->length > 0);

	this->current = this->length - 1;

	while (this->front[this->current] == character && this->current >= 0) {
		(this->current)--;
	}

	this->length = this->current + 1;
	this->front[this->length] = '\0';
	this->current = -1;
}

void String::TrimRight(char(*characters)) {
	assert(this->length > 0);

	Long i;
	Long j;
	Long k;
	Long identical;
	Long length;
	Long count = 0;

	length = strlen(characters);

	i = 0;
	j = this->length;
	while (i <= this->length / length && count == i) {
		this->current = j;
		j -= length;
		k = 0;
		identical = 0;

		while (k < length && k == identical) {
			if (this->front[j + k] == characters[k]) {
				identical++;
			}
			k++;
		}

		if (identical == length) {
			count++;
		}
		i++;
	}

	this->length = this->current;
	this->front[this->length] = '\0';
	this->current = -1;
}

void String::MakeUpper() {
#if 0
	for (int i = 0; i < this->length; i++) {
		if (this->front[i] >= 'a' && this->front[i] <= 'z')
			this->front[i] = this->front[i] - 32;
	}
#endif
	_strupr(this->front);
}

void String::MakeLower() {
#if 0
	for (int i = 0; i < this->length; i++) {
		if (this->front[i] >= 'A' && this->front[i] <= 'Z')
			this->front[i] = this->front[i] + 32;
	}
#endif
	_strlwr(this->front);
}

void String::MakeReverse() {
#if 0	
	assert(this->length > 0);

	char(*temp);
	temp = new char[this->capacity];
	for (int i = 0; i < this->length; i++) {
		memcpy(temp + i, this->front + this->length - 1 - i, 1);
	}
	temp[length] = '\0';

	delete[] this->front;
	this->front = temp;
	this->current = -1;
#endif
	_strrev(this->front);
}

char String::GetAt(Long index) {
	return this->front[index];
}

string String::GetDoubleByteAt(Long index) {
	char doubleByteCharacter[3];
	doubleByteCharacter[0] = this->front[index];
	doubleByteCharacter[1] = this->front[index + 1];
	doubleByteCharacter[2] = '\0';
	return string(doubleByteCharacter);
}

char* String::GetString() {
	return (this->front);
}

bool String::IsEmpty() const {
	bool retVo = false;

	if (this->length < 1) {
		retVo = true;
	}
	return retVo;
}

bool String::IsHangle(Long index) const {
	bool retVo = false;

	if ((this->front[index] & 0x80) == 0x80)
		retVo = true;

	return retVo;
}

String& String::operator=(const String& source) {

	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = new char[source.capacity];

	if (source.length > 0) {
		memcpy(this->front, source.front, source.length);
	}

	this->front[source.length] = '\0';
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
	return *this;
}

String& String::operator=(const char character) {
	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = new char[MAX];

	this->front[0] = character;

	this->front[1] = '\0';
	this->capacity = MAX;
	this->length = 1;
	this->current = 0;

	return *this;
}

String& String::operator=(const char(*characters)) {
	Long length;
	Long capacity = MAX;

	if (this->front != 0) {
		delete[] this->front;
	}

	length = strlen(characters);

	while (capacity - 1 < length) {
		capacity += MAX;
	}

	this->front = new char[capacity];

	if (length > 0) {
		memcpy(this->front, characters, length);
	}

	this->capacity = capacity;
	this->front[length] = '\0';
	this->length = length;
	this->current = 0;

	return *this;
}

String& String::operator=(const string characters) {
	Long length;
	Long capacity = MAX;

	if (this->front != 0) {
		delete[] this->front;
	}

	length = characters.size();

	while (capacity - 1 < length) {
		capacity += MAX;
	}

	this->front = new char[capacity];

	if (length > 0) {
		memcpy(this->front, characters.c_str(), length);
	}

	this->capacity = capacity;
	this->front[length] = '\0';
	this->length = length;
	this->current = 0;
	return *this;

}

String& String::operator+(const String& characters) {
	Long capacity = MAX;
	char(*temp);

	while (capacity - 1 < this->length + characters.length) {
		capacity += MAX;
	}

	temp = new char[capacity];

	if (this->length > 0) {
		memcpy(temp, this->front, this->length);
	}
	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = temp;
	this->capacity = capacity;

	if (characters.length > 0) {
		memcpy(this->front + this->length, characters.front, characters.length);
	}

	this->length = this->length + characters.length;
	this->front[this->length] = '\0';
	this->current = 0;

	return *this;
}

String& String::operator+(const char character) {
	Long capacity = MAX;
	char(*temp);

	while (capacity - 1 < this->length + 1) {
		capacity += MAX;
	}

	temp = new char[capacity];

	if (this->length > 0) {
		memcpy(temp, this->front, this->length);
	}

	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temp;
	this->capacity = capacity;

	this->front[this->length] = character;
	(this->length)++;
	this->front[this->length] = '\0';
	this->current = 0;

	return *this;
}

String& String::operator+(const char(*characters)) {
	Long capacity = MAX;
	Long length;
	char(*temp);

	length = strlen(characters);

	while (capacity - 1 < this->length + length) {
		capacity += MAX;
	}

	temp = new char[capacity];

	if (this->length > 0) {
		memcpy(temp, this->front, this->length);
	}

	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temp;
	this->capacity = capacity;

	if (length > 0) {
		memcpy(this->front + this->length, characters, length);
	}

	this->length = this->length + length;
	this->front[this->length] = '\0';
	this->current = 0;

	return *this;
}

String& String::operator+(const string characters) {
	Long capacity = MAX;
	Long length;
	char(*temp);

	length = characters.size();

	while (capacity - 1 < this->length + length) {
		capacity += MAX;
	}

	temp = new char[capacity];
	if (this->length > 0) {
		memcpy(temp, this->front, this->length);
	}

	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temp;
	this->capacity = capacity;

	if (length > 0) {
		memcpy(this->front + this->length, characters.c_str(), length);
	}

	this->length = this->length + length;
	this->front[this->length] = '\0';
	this->current = 0;

	return *this;
}

String& String::operator+=(const String& characters) {
	Long capacity = MAX;
	char(*temp);

	while (capacity - 1 < this->length + characters.length) {
		capacity += MAX;
	}

	temp = new char[capacity];

	if (this->length > 0) {
		memcpy(temp, this->front, this->length);
	}

	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temp;
	this->capacity = capacity;

	if (characters.length > 0) {
		memcpy(this->front + this->length, characters.front, characters.length);
	}
	this->length = this->length + characters.length;
	this->front[this->length] = '\0';
	this->current = 0;

	return *this;
}

String& String::operator+=(const char character) {
	Long capacity = MAX;
	char(*temp);

	while (capacity - 1 < this->length + 1) {
		capacity += MAX;
	}

	temp = new char[capacity];
	if (this->length > 0) {
		memcpy(temp, this->front, this->length);
	}

	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temp;

	this->capacity = capacity;

	this->front[this->length] = character;
	(this->length)++;
	this->front[this->length] = '\0';
	this->current = 0;

	return *this;
}

String& String::operator+=(const char(*characters)) {
	Long capacity = MAX;
	Long length;
	char(*temp);

	length = strlen(characters);

	while (capacity - 1 < this->length + length) {
		capacity += MAX;
	}

	temp = new char[capacity];

	if (this->length > 0) {
		memcpy(temp, this->front, this->length);
	}

	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = temp;
	this->capacity = capacity;

	if (length > 0) {
		memcpy(this->front + this->length, characters, length);
	}
	this->length = this->length + length;
	this->front[this->length] = '\0';
	this->current = 0;

	return *this;
}

String& String::operator+=(const string characters) {
	Long capacity = MAX;
	Long length;
	char(*temp);

	length = characters.size();

	while (capacity - 1 < this->length + length) {
		capacity += MAX;
	}

	temp = new char[capacity];

	if (this->length > 0) {
		memcpy(temp, this->front, this->length);
	}

	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = temp;

	this->capacity = capacity;
	if (length > 0) {
		memcpy(temp + this->length, characters.c_str(), length);
	}
	this->length = this->length + length;
	this->front[this->length] = '\0';
	this->current = 0;

	return *this;
}

char String::operator[](Long index) {
	return this->front[index];
}

String::operator char*() {
	return this->front;
}

#if 0
char* String::c_str() const {
	return this->front;
}
#endif

bool String::operator==(const char(*other)) {
	bool retVo = false;

	if (strcmp(this->front, other) == 0)
		retVo = true;

	return retVo;
}

bool String::operator==(const string other) {
	bool retVo = false;

	if (strcmp(this->front, other.c_str()) == 0)
		retVo = true;

	return retVo;
}

bool String::operator==(const String& other) {

	bool retVo = false;

	if (strcmp(this->front, other.front) == 0)
		retVo = true;

	return retVo;

}

bool String::operator!=(const char(*other)) {
	bool retVo = false;

	if (strcmp(this->front, other) != 0)
		retVo = true;

	return retVo;
}

bool String::operator!=(const string other) {
	bool retVo = false;

	if (strcmp(this->front, other.c_str()) != 0)
		retVo = true;

	return retVo;
}

bool String::operator!=(const String& other) {

	bool retVo = false;

	if (strcmp(this->front, other.front) != 0)
		retVo = true;

	return retVo;

}

bool String::operator<(const char(*other)) {
	bool retVo = false;

	if (strcmp(this->front, other) < 0)
		retVo = true;

	return retVo;
}

bool String::operator<(const string other) {
	bool retVo = false;

	if (strcmp(this->front, other.c_str()) < 0)
		retVo = true;
	return retVo;
}

bool String::operator<(const String& other) {
	bool retVo = false;

	if (strcmp(this->front, other.front) < 0)
		retVo = true;

	return retVo;
}

bool String::operator>(const char(*other)) {
	bool retVo = false;

	if (strcmp(this->front, other) > 0)
		retVo = true;

	return retVo;
}

bool String::operator>(const string other) {
	bool retVo = false;

	if (strcmp(this->front, other.c_str()) > 0)
		retVo = true;

	return retVo;
}

bool String::operator>(const String& other) {
	bool retVo = false;

	if (strcmp(this->front, other.front) > 0)
		retVo = true;

	return retVo;
}

bool String::operator<=(const char(*other)) {
	bool retVo = false;

	if (strcmp(this->front, other) <= 0)
		retVo = true;

	return retVo;
}

bool String::operator<=(const string other) {
	bool retVo = false;

	if (strcmp(this->front, other.c_str()) <= 0)
		retVo = true;

	return retVo;
}

bool String::operator<=(const String other) {
	bool retVo = false;

	if (strcmp(this->front, other.front) <= 0)
		retVo = true;

	return retVo;
}

bool String::operator>=(const char(*other)) {
	bool retVo = false;

	if (strcmp(this->front, other) >= 0)
		retVo = true;

	return retVo;
}

bool String::operator>=(const string other) {
	bool retVo = false;

	if (strcmp(this->front, other.c_str()) >= 0)
		retVo = true;

	return retVo;
}

bool String::operator>=(const String other) {
	bool retVo = false;

	if (strcmp(this->front, other.front) >= 0)
		retVo = true;

	return retVo;
}

//////////////////////////////////////////////////////////////////
// 2015-06-18
Long String::First() {
	this->current = 0;

	return this->current;
}

Long String::Previous() {
	this->current--;
	if (this->current < 0) {
		this->current = 0;
	}
	return this->current;
}

Long String::Next() {
	this->current++;
	if (this->current >= this->length) {
		this->current = this->length - 1;
	}

	return this->current;
}

Long String::Last() {
	this->current = this->length - 1;

	return this->current;
}

Long String::CountLine() {
	Long count = 1;
	Long i = 0;
	while (i < this->length) {
		String character = this->front[i];
		if (character == '\n') {
			count++;
		}
		i++;
	}

	return count;
}

Long String::FindUntilLength(char(*characters)) {
	Long length = strlen(characters);

	Long index = -1;
	Long i = 0;
	while (i < length && i < this->length && this->front[i] == characters[i]) {
		i++;
	}
	if (i == length) {
		index = i;
	}
	return index;
}

Long String::CountLongestLine() {
	Long characterCount = 0;
	Long longestCharacterCount = 0;
	Long enterCount = 0;

	//1. 개수만큼 반복하다.
	Long i = 0;
	while (i < this->length) {
		String character = this->front[i];
		//1.1. 개행 문자가 아니면 문자개수를 세다.
		//1.2. 개행 문자이면 개행 문자 개수를 세다.
		(character != '\n') ? (characterCount++) : (enterCount++);
		//1.3. 줄이 바꼈고 문자 개수가 최대문자개수보다 크면 최대문자개수를 구하다.
		if (character == '\n' && characterCount > longestCharacterCount) { 
			longestCharacterCount = characterCount;
			characterCount = 0;
		}
		i++;
	}
	
	if (enterCount < 1) {
		longestCharacterCount = characterCount;
	}

	return longestCharacterCount;
}

Long String::RemoveFrom(Long index) {
	Long count = 0;
	for (int i = index; i < this->length; i++) {
		memmove(this->front + i, this->front + i + 1, this->length - i - 1);
		this->front[this->length - 1] = '\0';
		(this->length)--;
		count++;
		i--;
	}
	return count;
}