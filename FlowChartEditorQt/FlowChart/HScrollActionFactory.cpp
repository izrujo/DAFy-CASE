#include "HScrollActionFactory.h"
#include "DrawingPaper.h"
#include "HScrollActions.h"

HScrollActionFactory::HScrollActionFactory(DrawingPaper *drawingPaper) {
	this->drawingPaper = drawingPaper;
}

HScrollActionFactory::HScrollActionFactory(const HScrollActionFactory& source) {
	this->drawingPaper = source.drawingPaper;
}

HScrollActionFactory::~HScrollActionFactory() {

}

HScrollAction* HScrollActionFactory::Make(UINT nSBCode) {
	HScrollAction *hScrollAction = 0;

	switch (nSBCode) {
	case SB_LINELEFT:
		hScrollAction = new LineLeftAction(this->drawingPaper);
		break;
	case SB_LINERIGHT:
		hScrollAction = new LineRightAction(this->drawingPaper);
		break;
	case SB_PAGELEFT:
		hScrollAction = new PageLeftAction(this->drawingPaper);
		break;
	case SB_PAGERIGHT:
		hScrollAction = new PageRightAction(this->drawingPaper);
		break;
	case SB_THUMBTRACK:
		hScrollAction = new ThumbTrackHScrollAction(this->drawingPaper);
		break;
	default:
		break;
	}

	return hScrollAction;
}

HScrollActionFactory& HScrollActionFactory::operator=(const HScrollActionFactory& source) {
	this->drawingPaper = source.drawingPaper;

	return *this;
}