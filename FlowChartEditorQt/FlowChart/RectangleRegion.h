#ifndef _RECTANGLEREGION_H
#define _RECTANGLEREGION_H

#include "Shape.h"

class RectangleRegion : public Shape {
public:
	RectangleRegion(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
		PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""), Direction direction = DIRECTION);

	virtual ~RectangleRegion();

	RectangleRegion(const RectangleRegion& source);
	RectangleRegion& operator =(const RectangleRegion& source);

	void Draw(CDC *dc);
	void Draw(Painter *painter);

	virtual void Accept(FlowChartVisitor *draw) {};
	virtual Shape* Clone();

	virtual void GetRegion(CDC *dc, CRgn *region) {};  //마우스 드래그로 여러 도형 한번에 선택시 사용
	virtual void GetRegion(Painter *painter, CRgn *region) {};
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region) {};
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region) {};

	virtual BOOL IsIncluded(CDC *dc, POINT point);
};

#endif //_RECTANGLEREGION_H