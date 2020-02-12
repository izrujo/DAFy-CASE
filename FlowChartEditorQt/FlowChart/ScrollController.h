#ifndef _SCROLLCONTROLLER_H
#define _SCROLLCONTROLLER_H

#include "../Notepad/Array.h"
class DrawingPaper;
class Scroll;

class ScrollController {
public:
	ScrollController(DrawingPaper *drawingPaper = 0);
	ScrollController(const ScrollController& source);
	~ScrollController();
	ScrollController& operator=(const ScrollController& source);

	void Update();
	
	Long Up();
	Long Down();
	Long PageUp();
	Long PageDown();
	Long Left();
	Long Right();
	Long PageLeft();
	Long PageRight();
	Long MoveVerticalScroll(Long position);
	Long MoveHorizontalScroll(Long position);
	Long Rotate(short delta);

	Scroll* GetScroll(Long index);
	Long GetWidth() const;
	Long GetHeight() const;
private:
	DrawingPaper *drawingPaper;
	Long width;
	Long height;
	Array<Scroll*> scrolls;
};

inline Scroll* ScrollController::GetScroll(Long index) {
	return this->scrolls[index];
}

inline Long ScrollController::GetWidth() const {
	return this->width;
}

inline Long ScrollController::GetHeight() const {
	return this->height;
}

#endif //_SCROLLCONTROLLER_H