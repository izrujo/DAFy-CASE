/******************************************************************
* 파일 이름 : String.h
* 기능 : 문자열 라이브러리 파일
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 23일 
*******************************************************************/

#ifndef STRING_H
#define STRING_H

#include <string>
// #define MAX 65536
#define MAX 1000

using namespace std;

typedef signed long int Long;

class String{
	public:
		String();
		String(const String& source);
		String(char character, Long nRepeat = 1);         // 사용 : String('x',6); 결과 : "xxxxxx"		
		String(string characters);                        // 사용 : String(stirng("abc")); 결과 : "abc"		
		String(char (*chracters));                           // 사용 : String("abc"); 결과 : "abc"
		                                                  // 사용 : String(character); 결과 : "abc"
		String(char (*chracters),Long length);               // 사용 : String("abc", 4); 결과 : "abc"
		                                                  // 사용 : String(character,4); 결과 : "abc"
		~String();
		
		void Clear();                                     // 메모리 해제 개념
		void Empty();                                     // 0번째에 '\0' 삽입 개념    capacity 감소 비허용 length 감소 허용
		Long Delete(Long index, Long count);              // 메모리 이동 개념          Capacity 감소 비허용 length 감소 허용

		Long Insert(Long index, char character);          //capacity 증가 허용 length 증가 허용
		Long Insert(Long index, char (*characters));
		Long Insert(Long index, string characters);
		Long Insert(Long index, String *characters);
		
		Long Store(Long index, char character);           //capacity 증가 비허용 length 증가 허용
		Long Store(Long index, char (*characters));
		Long Store(Long index, string characters);
		Long Store(Long index, String *characters);
		
		Long SetAt(Long index, char character);           //Modify 개념 capacity 증가 비허용 length 증가 비허용 		
		
		Long Find(char character);                        //Searches this string for the first match of a substring.
		                                                  //The zero-based index of the first character; -1 if the substring or character is not found.
		Long Find(char (*characters));

		Long Find(char character, Long index);            //The index of the character in the string to begin the search with, or 0 to start from the beginning. 
		                                                  //The character at nStart is excluded from the search if nStart is not equal to 0.
		Long Find(char (*characters), Long index);

		Long ReversedFind(char character);                //Searches this CString object for the last match of a substring
		Long FindOneOf(char (*characters));               //Searches this string for the first character that matches any character contained

		Long Remove(char character);

		Long Replace(char oldCharacter, char newCharacter);
		Long Replace(char (*oldCharacter), char (*newCharacter));
		
		Long Compare(char (*characters));
		Long CompareNoCase(char (*characters));            //대소문자 상관없이 비교

		void TrimLeft();                                   // TrimLeft removes newline, space, and tab characters. 
		                                                   // remove a particular character from the beginning of a string.
		void TrimLeft(char character);
		void TrimLeft(char (*characters));
		void TrimRight();                                  // remove a particular character from the end of a string
		void TrimRight(char character);
		void TrimRight(char (*characters));

		void MakeUpper();
		void MakeLower();
		void MakeReverse();

		char GetAt(Long index);
		string GetDoubleByteAt(Long index);
		char* GetString();

		bool IsEmpty() const;
		bool IsHangle(Long index) const;

		String& operator=(const String& source);
		String& operator=(const char character);
		String& operator=(const char (*characters));
		String& operator=(const string characters);

		String& operator+(const String& characters);
		String& operator+(const char character);
		String& operator+(const char (*characters));
		String& operator+(const string characters);

		String& operator+=(const String& characters);
		String& operator+=(const char character);
		String& operator+=(const char (*characters));
		String& operator+=(const string characters);		

		// 첨자연산자 char 앞에 &를 사용해야 하지만 형변환 함수 오류가 너무 많아서 사용안함
		char operator[](Long index);
		
		operator char*();                                   //String을 char(*)로 형변환 함수
		// operator char*(void); 이렇게 하면 될 수도 있겠다는 생각이 들지만 test안해봄 20160622

		// String을 char(*)로 형변환 함수
		// operator char* (); // 20160505 형변환 연산자는 첨자연산자(operator[]) 와 함께 쓰이면 오류나기 때문에 c_str() 함수를 만듬
		// const char* c_str() const 그러나 오류 나는 곳이 많이서 원복
		// char* c_str() const;
		bool operator==(const char (*other));
		bool operator==(const string other);
		bool operator==(const String& other);

		bool operator!=(const char (*other));
		bool operator!=(const string other);
		bool operator!=(const String& other);

		bool operator<(const char (*other));
		bool operator<(const string other);
		bool operator<(const String& other);

		bool operator>(const char (*other));
		bool operator>(const string other);
		bool operator>(const String& other);

		bool operator<=(const char (*other));
		bool operator<=(const string other);
		bool operator<=(const String other);

		bool operator>=(const char (*other));
		bool operator>=(const string other);
		bool operator>=(const String other);

		Long GetCapacity() const;
		Long GetLength() const;
		Long GetCurrent() const; 

		// 2015-06-18
		Long First();
		Long Previous();
		Long Next();
		Long Last();

		// 2019-09-11 텍스트의 줄 개수 세는 연산
		Long CountLine();
		// 2019-11-28 여러 줄의 텍스트 중 가장 긴 줄의 텍스트 개수를 세는 연산
		Long CountLongestLine();
		// 2019-09-19 어떤 문자열의 개수 번째까지 동일한지 확인하는 연산
		Long FindUntilLength(char(*characters));
		// 2019-12-27 index부터 다지우기
		Long RemoveFrom(Long index);
	private:
		char (*front);
		Long capacity;
		Long length;
		Long current;		
};

inline Long String::GetCapacity() const{
	return this->capacity;
}

inline Long String::GetLength() const{
	return this->length;
}

inline Long String::GetCurrent() const{
	return this->current;
}

#endif STRING_H
