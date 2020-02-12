#ifndef _NUMBERBOX_H
#define _NUMBERBOX_H

#include "Shape.h"

class NumberBox : public Shape {
public:
	NumberBox(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
		PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""), Direction direction = DIRECTION);

	virtual ~NumberBox();

	NumberBox(const NumberBox& source);
	NumberBox& operator =(const NumberBox& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();

	virtual void GetRegion(CDC *dc, CRgn *region) {};  //마우스 드래그로 여러 도형 한번에 선택시 사용
	virtual void GetRegion(Painter *painter, CRgn *region) {};
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region) {};
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region) {};
};

#endif //_NUMBERBOX_H