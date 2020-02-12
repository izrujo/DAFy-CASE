
#ifndef _A4PAPER_H
#define _A4PAPER_H

#include "Shape.h"

class A4Paper : public Shape {
public:
	A4Paper(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
		PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""), Direction direction = DIRECTION);

	virtual ~A4Paper();

	A4Paper(const A4Paper& source);
	A4Paper& operator =(const A4Paper& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();
	/* 이거는 abstract 라 선언만 한듯
	virtual void GetRegion(CDC *dc, CRgn *region) {};  //마우스 드래그로 여러 도형 한번에 선택시 사용
	virtual void GetRegion(Painter *painter, CRgn *region) {};
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region) {};
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region) {};
	*/

	void SetIsMarking(bool isMarking);
	bool GetIsMarking() const;

	void ChangeMargin(Long leftmargin, Long topMargin, Long rightMargin, Long bottomMargin);
	Long GetLeftMargin() const;
	Long GetTopMargin() const;
	Long GetRightMargin() const;
	Long GetBottomMargin() const;
private:
	bool isMarking;
	Long leftMargin;
	Long topMargin;
	Long rightMargin;
	Long bottomMargin;
};

inline bool A4Paper::GetIsMarking() const {
	return this->isMarking;
}

inline Long A4Paper::GetLeftMargin() const {
	return this->leftMargin;
}

inline Long A4Paper::GetTopMargin() const {
	return this->topMargin;
}

inline Long A4Paper::GetRightMargin() const {
	return this->rightMargin;
}

inline Long A4Paper::GetBottomMargin() const {
	return this->bottomMargin;
}

#endif //_A4PAPER_H