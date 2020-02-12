#ifndef _HSCROLLFACTORY_H
#define _HSCROLLFACTORY_H

#include <afxwin.h>

class HScrollAction;
class DrawingPaper;
class HScrollActionFactory {
public:
	HScrollActionFactory(DrawingPaper *drawingPaper = 0);
	HScrollActionFactory(const HScrollActionFactory& source);
	~HScrollActionFactory();
	HScrollAction* Make(UINT nSBCode);
	HScrollActionFactory& operator=(const HScrollActionFactory& source);
private:
	DrawingPaper *drawingPaper;
};

#endif // !_HSCROLLFACTORY_H
