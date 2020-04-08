#ifndef _STATUSBAR_H
#define _STATUSBAR_H

#include "Array.h"
#include "String.h"
#include <afxwin.h>

class StatusBar {
public:
	StatusBar(Long capacity = 5, HWND hWndStatusBar=NULL);
	StatusBar(const StatusBar& source);
	~StatusBar();
	StatusBar& operator=(const StatusBar& source);
	
	Long Add(Long index, String content);
	Long Modify(Long index, String content);

	void Print();

	String& GetAt(Long index);
	Long GetCapacity() const;
	Long GetLength() const;
	HWND GetHandle() const;
private:
	Array<String> contents;
	Long capacity;
	Long length;
	HWND hWndStatusBar;
};

inline Long StatusBar::GetCapacity() const {
	return this->capacity;
}

inline Long StatusBar::GetLength() const {
	return this->length;
}

inline HWND StatusBar::GetHandle() const {
	return this->hWndStatusBar;
}

#endif //_STATUSBAR_H