/*
파일명 : Block.h
기능 : Shape의 Composite 클래스
작성자 : 김찬형
작성일 : 20.02.18
*/


#ifndef _BLOCK_H
#define _BLOCK_H

#include "Shape.h"
#include "Array.h"

using FlowChartShape::Shape;

class Block : public Shape {
public:
	Block(Long capacity = 30);
	Block(const Block& source);
	virtual ~Block() = 0;
	Block& operator=(const Block& source);
	Shape* operator[](Long index);

	virtual Long Attach(Shape *shape);
	virtual Long Insert(Long index, Shape *shape);
	virtual Long Detach(Long index);
	virtual Long Detach(SHAPE identify);
	virtual bool DetachSelectedAll();
	virtual Shape* GetAt(Long index);

	virtual Long Find(Shape* shape);
	virtual Long Find(QPoint point);
	virtual Long Find(Long x, Long y);
	virtual Long Find(QRect rect);
	virtual Long Find(SHAPE identify);
	virtual Long Find(Long fromIndex, SHAPE identify);
	virtual void Find(Long styles, Long* (*indexes), Long *count);

	virtual void Swap(Long toIndex, Long fromIndex);
	virtual void Swap(Long toIndex, Shape *shape);
	virtual void Clear();

	virtual void SelectAll();
	virtual void UnSelectAll();
	virtual void GetSelecteds(Long* (*indexes), Long *count);
	virtual Long CountSelecteds();
	virtual void AscendingSort();
	virtual void DescendingSort();

	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long GetCurrent() const;
protected:
	Array<Shape*> shapes;
	Long capacity;
	Long length;
	Long current;
};

inline Long Block::GetCapacity() const {
	return this->capacity;
}
inline Long Block::GetLength() const {
	return this->length;
}
inline Long Block::GetCurrent() const {
	return this->current;
}

#endif //_BLOCK_H