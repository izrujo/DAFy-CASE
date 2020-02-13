/******************************************************************
* 파일 이름 : Symbol.cpp
* 기능 : 기호의 추상화 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/

#include "Symbol.h"

Symbol::Symbol(Long x, Long y, Long width, Long height, QColor backGroundColor,
	QPen borderLine, QColor borderColor, String contents)
	:Shape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
}

Symbol::~Symbol() {
}

Symbol::Symbol(const Symbol& source)
	:Shape(source) {
}

Symbol& Symbol::operator =(const Symbol& source)
{
	Shape::operator=(source);
	return *this;
}