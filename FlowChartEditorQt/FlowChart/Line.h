/******************************************************************
* 파일 이름 : Line.h
* 기능 : 선의 추상화 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/

#ifndef _LINE_H
#define _LINE_H

#include "Shape.h"

class Line : public NShape {
public:
	Line(float x, float y, float width, float height,
		QColor backGroundColor = QColor(255, 255, 255), Qt::PenStyle borderLine = Qt::SolidLine,
		QColor borderColor = QColor(0, 0, 0), String contents = static_cast<String>(""));

	virtual ~Line() = 0;

	Line(const Line& source);
	Line& operator =(const Line& source);

	void ChangeArrowSize(float arrowSize);

	virtual bool IsStyle(Long style);
	float GetArrowSize() const;
protected:
	float arrowSize;
};

inline bool Line::IsStyle(Long style) {
	return ((style >> 1) % 2) ? (true) : (false);
}
inline float Line::GetArrowSize() const {
	return this->arrowSize;
}
#endif// _LINE_H