/*
파일명 : Block.h
기능 : Shape의 Composite 클래스
작성자 : 김찬형
작성일 : 20.02.18
*/


#ifndef _BLOCK_H
#define _BLOCK_H

#include "../Shape.h"
#include "../../../Utilities/Array.h"

class Block : public NShape {
public:
	Block(Long capacity = 30);
	Block(const Block& source);
	virtual ~Block() = 0;
	Block& operator=(const Block& source);
	NShape* operator[](Long index);

	virtual bool IsSame(const NShape& other);

	virtual Long Attach(NShape *shape);
	virtual Long Insert(Long index, NShape *shape);
	virtual Long Detach(Long index);
	virtual Long Detach(SHAPE identify);
	virtual bool DetachSelectedAll();
	virtual NShape* GetAt(Long index);

	virtual Long Find(NShape* shape);
	virtual Long Find(QPointF point);
	virtual Long Find(float x, float y);
	virtual Long Find(QRectF rect);
	virtual Long Find(SHAPE identify);
	virtual Long Find(Long fromIndex, SHAPE identify);
	virtual void Find(Long styles, Long* (*indexes), Long *count);

	virtual void Swap(Long toIndex, Long fromIndex);
	virtual void Swap(Long toIndex, NShape *shape);
	virtual void Clear();

	virtual void SelectAll();
	virtual void UnSelectAll();
	virtual void GetSelecteds(Long* (*indexes), Long *count);
	virtual Long CountSelecteds();
	virtual void AscendingSort();
	virtual void DescendingSort();

	//200515 실행 취소 관련
	virtual Long FindByRegistrationNumber(SHAPE id, Long registrationNumber);

	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long GetCurrent() const;
protected:
	Array<NShape*> shapes;
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