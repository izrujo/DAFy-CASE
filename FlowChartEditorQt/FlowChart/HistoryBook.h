#ifndef _HISTORYBOOK_H
#define _HISTORYBOOK_H

#include "Array.h"
class History;

class HistoryBook {
public:
	HistoryBook(Long capacity = 50);
	HistoryBook(const HistoryBook& source);
	~HistoryBook();
	HistoryBook& operator=(const HistoryBook& source);

	Long Add(History *history);
	Long Remove(Long index);
	void RemoveAll();

	History* GetAt(Long index);

	HistoryBook* Clone();

	Long GetCapacity() const;
	Long GetLength() const;
private:
	Array<History*> historys;
	Long capacity;
	Long length;
};

inline Long HistoryBook::GetCapacity() const {
	return this->capacity;
}
inline Long HistoryBook::GetLength() const {
	return this->length;
}

#endif //_HistoryBook_H