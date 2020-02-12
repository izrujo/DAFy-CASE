#include "VScrollActions.h"
#include "DrawingPaper.h"
#include "ScrollController.h"
#include "Scrolls.h"

VScrollAction::VScrollAction(DrawingPaper *drawingPaper) {
	this->drawingPaper = drawingPaper;
}

VScrollAction::VScrollAction(const VScrollAction& source) {
	this->drawingPaper = source.drawingPaper;
}

VScrollAction::~VScrollAction() {

}

VScrollAction& VScrollAction::operator=(const VScrollAction& source) {
	this->drawingPaper = source.drawingPaper;
	
	return *this;
}

// LineUpAction

LineUpAction::LineUpAction(DrawingPaper *drawingPaper)
	:VScrollAction(drawingPaper) {

}

LineUpAction::LineUpAction(const LineUpAction& source)
	: VScrollAction(source) {

}

LineUpAction::~LineUpAction() {

}

void LineUpAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long position = this->drawingPaper->scrollController->Up();
	int previous = this->drawingPaper->SetScrollPos(SB_VERT, position, TRUE);
	position = this->drawingPaper->GetScrollPos(SB_VERT);
	this->drawingPaper->scrollController->MoveVerticalScroll(position);
	this->drawingPaper->ScrollWindow(0, previous - position);
}

LineUpAction& LineUpAction::operator=(const LineUpAction& source) {
	VScrollAction::operator=(source);

	return *this;
}

// LineDownAction

LineDownAction::LineDownAction(DrawingPaper *drawingPaper)
	:VScrollAction(drawingPaper) {

}

LineDownAction::LineDownAction(const LineDownAction& source)
	: VScrollAction(source) {

}

LineDownAction::~LineDownAction() {

}

void LineDownAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long position = this->drawingPaper->scrollController->Down();
	int previous = this->drawingPaper->SetScrollPos(SB_VERT, position, TRUE);
	position = this->drawingPaper->GetScrollPos(SB_VERT);
	this->drawingPaper->scrollController->MoveVerticalScroll(position);
	this->drawingPaper->ScrollWindow(0, previous - position);
}

LineDownAction& LineDownAction::operator=(const LineDownAction& source) {
	VScrollAction::operator=(source);

	return *this;
}

// PageUpAction

PageUpAction::PageUpAction(DrawingPaper *drawingPaper)
	:VScrollAction(drawingPaper) {

}

PageUpAction::PageUpAction(const PageUpAction& source)
	: VScrollAction(source) {

}

PageUpAction::~PageUpAction() {

}

void PageUpAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long position = this->drawingPaper->scrollController->PageUp();
	int previous = this->drawingPaper->SetScrollPos(SB_VERT, position, TRUE);
	position = this->drawingPaper->GetScrollPos(SB_VERT);
	this->drawingPaper->scrollController->MoveVerticalScroll(position);
	this->drawingPaper->ScrollWindow(0, previous - position);
}

PageUpAction& PageUpAction::operator=(const PageUpAction& source) {
	VScrollAction::operator=(source);

	return *this;
}

// PageDownAction
PageDownAction::PageDownAction(DrawingPaper *drawingPaper)
	:VScrollAction(drawingPaper) {

}

PageDownAction::PageDownAction(const PageDownAction& source)
	: VScrollAction(source) {

}

PageDownAction::~PageDownAction() {

}

void PageDownAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long position = this->drawingPaper->scrollController->PageDown();
	int previous = this->drawingPaper->SetScrollPos(SB_VERT, position, TRUE);
	position = this->drawingPaper->GetScrollPos(SB_VERT);
	this->drawingPaper->scrollController->MoveVerticalScroll(position);
	this->drawingPaper->ScrollWindow(0, previous - position);
}

PageDownAction& PageDownAction::operator=(const PageDownAction& source) {
	VScrollAction::operator=(source);

	return *this;
}

// ThumbTrackVScrollAction

ThumbTrackVScrollAction::ThumbTrackVScrollAction(DrawingPaper *drawingPaper)
	:VScrollAction(drawingPaper) {

}

ThumbTrackVScrollAction::ThumbTrackVScrollAction(const ThumbTrackVScrollAction& source)
	: VScrollAction(source) {

}

ThumbTrackVScrollAction::~ThumbTrackVScrollAction() {

}

void ThumbTrackVScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long position = this->drawingPaper->scrollController->MoveVerticalScroll(nPos);
	int previous = this->drawingPaper->SetScrollPos(SB_VERT, position, TRUE);
	position = this->drawingPaper->GetScrollPos(SB_VERT);
	this->drawingPaper->scrollController->MoveVerticalScroll(position);
	this->drawingPaper->ScrollWindow(0, previous - position);
}

ThumbTrackVScrollAction& ThumbTrackVScrollAction::operator=(const ThumbTrackVScrollAction& source) {
	VScrollAction::operator=(source);

	return *this;
}