/******************************************************************
* 파일 이름 : FlowChart.h
* 기능 : 순서도 컨트롤 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#ifndef _FLOWCHART_H
#define _FLOWCHART_H

#include "Shape.h"
#include "Array.h"

typedef signed long int Long;

class DrawVisitor;

class FlowChart : public Shape {
public:
	FlowChart(Long capacity = 100);
	~FlowChart();

	FlowChart(const FlowChart& source);

	Long Attach(Shape *shape);

	Long Insert(Long index, Shape *shape);
	Long InsertRear(Long index, Shape *shape);

	Long Find(Shape *shape); // Make 함수에서 사용
	//Long Find(CDC *dc, CPoint point);
	//Long Find(CDC *dc, int x, int y);
	Long Find(Painter *painter, QPoint point);
	Long Find(Painter *painter, int x, int y);

	// 20160623 SequnceMake 만들때 너무 찾는게 많아서 만듬
	Long Find(Painter *painter, QRect& rect);
	Long Find(SHAPE identify);
	Long Find(Long fromIndex, SHAPE identify);
	void Find(Long styles, Long *(*indexes), Long *count);

	Long Erase(Long index);
	Long Erase(SHAPE identify);
	bool EraseSelectedAll();

	// 함수이름 Change 으로 바꿀 것!! 20160617
	void Swap(Long toIndex, Long fromIndex);
	void Swap(Long toIndex, Shape *shape);

	void Clear();

	FlowChart& operator =(const FlowChart& source);

	Shape& operator[](Long index);
	Shape* GetAt(Long index);
	Long GetCapacity() const;
	Long GetLength() const;
	Long GetCurrent() const;

	//virtual void DrawActiveShape(CDC *dc);
	virtual void DrawActiveShape(Painter *painter);
	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();

	///////////////////////////////////////////////////////////
	// 선택 관련
	void SelectAll();
	void UnSelectAll();
	void GetSelecteds(Long *(*indexes), Long *count);
	Long CountSelecteds();

	virtual void GetRegion(Painter *painter, QRegion *region) {};
	virtual void GetRegion(Painter *painter, Long thickness, QRegion *region) {};

	// 정렬 관련
	void AscendingSort();
	void DescendingSort();

	void GetRange(QRect *rect);
private:
	Array<Shape *> shapes;
	Long capacity;
	Long length;
	Long current;
};

Long CompareShapeAddress(void *one, void *other);
Long CompareCoordinateForFlowChart(void *one, void *other);

inline Long FlowChart::GetCapacity() const {
	return this->capacity;
}

inline Long FlowChart::GetLength() const {
	return this->length;
}

inline Long FlowChart::GetCurrent() const {
	return this->current;
}

#endif //_FLOWCHART_H
