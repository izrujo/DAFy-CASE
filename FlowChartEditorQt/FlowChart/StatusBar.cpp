#include "StatusBar.h"

StatusBar::StatusBar(Long capacity, HWND hWndStatusBar)
	: contents(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->hWndStatusBar = hWndStatusBar;
}

StatusBar::StatusBar(const StatusBar& source)
	: contents(source.contents) {
	Long i = 0;
	while (i < source.length) {
		this->contents.Modify(i, String((const_cast<StatusBar&>(source)).contents[i]));
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->hWndStatusBar = hWndStatusBar;
}

StatusBar::~StatusBar() {

}

StatusBar& StatusBar::operator=(const StatusBar& source) {
	this->contents = source.contents;
	Long i = 0;
	while (i < source.length) {
		this->contents.Modify(i, String((const_cast<StatusBar&>(source)).contents[i]));
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->hWndStatusBar = hWndStatusBar;

	return *this;
}

Long StatusBar::Add(Long index, String content) {
	if (this->length < this->capacity) {
		index = this->contents.Store(index, content);
	}
	else {
		index = this->contents.AppendFromRear(content);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long StatusBar::Modify(Long index, String content) {
	return this->contents.Modify(index, content);
}

String& StatusBar::GetAt(Long index) {
	return this->contents.GetAt(index);
}

void StatusBar::Print() {
	Long i = 0;
	while (i < this->length) {
		::SendMessage(this->hWndStatusBar, SB_SETTEXT, (WPARAM)i, (LPARAM)this->contents[i].GetString());
		i++;
	}
}