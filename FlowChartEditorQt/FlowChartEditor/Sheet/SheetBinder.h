#ifndef _SHEETBINDER_H
#define _SHEETBINDER_H

#include "../../Utilities/Array.h"

class Sheet;

class SheetBinder {
public:
	SheetBinder(Long capacity = 5);
	SheetBinder(const SheetBinder& source);
	~SheetBinder();
	SheetBinder& operator=(const SheetBinder& source);

	Long Add(Sheet *sheet);
	Long Insert(Long index, Sheet *sheet);
	Long Remove(Long index);
	Sheet* GetAt(Long index);
	Long Move(Long current);

	Long GetCapacity() const;
	Long GetLength() const;
	Long GetCurrent() const;

private:
	Array<Sheet*> sheets;
	Long capacity;
	Long length;
	Long current;
};

inline Long SheetBinder::GetCapacity() const {
	return this->capacity;
}
inline Long SheetBinder::GetLength() const {
	return this->length;
}
inline Long SheetBinder::GetCurrent() const {
	return this->current;
}

#endif //_SHEETBINDER_H