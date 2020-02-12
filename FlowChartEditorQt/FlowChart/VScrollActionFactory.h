#ifndef _VSCROLLFACTORY_H
#define _VSCROLLFACTORY_H

#include <afxwin.h>

class VScrollAction;
class DrawingPaper;
class VScrollActionFactory {
public:
	VScrollActionFactory(DrawingPaper *drawingPaper = 0);
	VScrollActionFactory(const VScrollActionFactory& source);
	~VScrollActionFactory();
	VScrollAction* Make(UINT nSBCode);
	VScrollActionFactory& operator=(const VScrollActionFactory& source);
private:
	DrawingPaper *drawingPaper;
};

#endif // !_VSCROLLFACTORY_H
