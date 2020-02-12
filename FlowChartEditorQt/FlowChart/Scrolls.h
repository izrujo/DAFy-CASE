#ifndef _SCROLLS_H
#define _SCROLLS_H
#include <afxwin.h>

typedef signed long int Long;

class Scroll {
public:
	Scroll();
	Scroll(Long minimum, Long maximum, Long pageSize, Long lineSize, Long position);
	Scroll(const Scroll& source);
	virtual ~Scroll() = 0;

	Long Up();
	Long Down();
	Long PageUp();
	Long PageDown();
	Long Move(Long position);
	Long Rotate(short delta);

	Scroll& operator=(const Scroll& source);

	SCROLLINFO GetScrollInfo();
	Long GetMinimum() const;
	Long GetMaximum() const;
	Long GetPageSize() const;
	Long GetLineSize() const;
	Long GetPosition() const;
private:
	Long minimum;
	Long maximum;
	Long pageSize;
	Long lineSize;
	Long position;
};

inline Long Scroll::GetMinimum() const {
	return this->minimum;
}

inline Long Scroll::GetMaximum() const {
	return this->maximum;
}

inline Long Scroll::GetPageSize() const {
	return this->pageSize;
}

inline Long Scroll::GetLineSize() const {
	return this->lineSize;
}

inline Long Scroll::GetPosition() const {
	return this->position;
}

class VerticalScroll : public Scroll {
public:
	VerticalScroll();
	VerticalScroll(Long minimum, Long maximum, Long pageSize, Long lineSize, Long position);
	VerticalScroll(const VerticalScroll& source);
	virtual ~VerticalScroll();
	VerticalScroll& operator=(const VerticalScroll& source);
};

class HorizontalScroll :public Scroll {
public:
	HorizontalScroll();
	HorizontalScroll(Long minimum, Long maximum, Long pageSize, Long lineSize, Long position);
	HorizontalScroll(const HorizontalScroll& source);
	virtual ~HorizontalScroll();
	HorizontalScroll& operator=(const HorizontalScroll& source);
};

#endif // !_SCROLLS_H
