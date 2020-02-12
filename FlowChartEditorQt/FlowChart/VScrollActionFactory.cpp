#include "VScrollActionFactory.h"
#include "DrawingPaper.h"
#include "VScrollActions.h"

VScrollActionFactory::VScrollActionFactory(DrawingPaper *drawingPaper) {
	this->drawingPaper = drawingPaper;
}

VScrollActionFactory::VScrollActionFactory(const VScrollActionFactory& source) {
	this->drawingPaper = source.drawingPaper;
}

VScrollActionFactory::~VScrollActionFactory() {

}

VScrollAction* VScrollActionFactory::Make(UINT nSBCode) {
	VScrollAction *vScrollAction = 0;

	switch (nSBCode) {
	case SB_LINEUP:
		vScrollAction = new LineUpAction(this->drawingPaper);
		break;
	case SB_LINEDOWN:
		vScrollAction = new LineDownAction(this->drawingPaper);
		break;
	case SB_PAGEUP:
		vScrollAction = new PageUpAction(this->drawingPaper);
		break;
	case SB_PAGEDOWN:
		vScrollAction = new PageDownAction(this->drawingPaper);
		break;
	case SB_THUMBTRACK:
		vScrollAction = new ThumbTrackVScrollAction(this->drawingPaper);
		break;
	default:
		break;
	}

	return vScrollAction;
}

VScrollActionFactory& VScrollActionFactory::operator=(const VScrollActionFactory& source) {
	this->drawingPaper = source.drawingPaper;

	return *this;
}