/******************************************************************
* 파일 이름 : Template.h
* 기능 : 순서도 작성자 컨트롤 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 4월 13일 
*******************************************************************/

#ifndef _TEMPLATE_H
#define _TEMPLATE_H

#include "Block.h"

class Template : public Block {
public:
	Template(Long capacity = 30);
	Template(const Template& source);
	virtual ~Template();
	Template& operator =(const Template& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();		

	virtual void GetRegion(QRegion *region){};
	virtual void GetRegion(Long thickness, QRegion *region){};
};

//Long CompareCoordinateForTemplate(void *one, void *other); //이건 왜있는걸까?

#endif //_TEMPLATE_H
