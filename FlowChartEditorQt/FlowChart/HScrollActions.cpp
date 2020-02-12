#include "HScrollActions.h"
#include "DrawingPaper.h"
#include "ScrollController.h"
#include "Scrolls.h"

HScrollAction::HScrollAction(DrawingPaper *drawingPaper) {
	this->drawingPaper = drawingPaper;
}

HScrollAction::HScrollAction(const HScrollAction& source) {
	this->drawingPaper = source.drawingPaper;
}

HScrollAction::~HScrollAction() {

}

HScrollAction& HScrollAction::operator=(const HScrollAction& source) {
	this->drawingPaper = source.drawingPaper;

	return *this;
}

// LineLeftAction

LineLeftAction::LineLeftAction(DrawingPaper *drawingPaper)
	:HScrollAction(drawingPaper) {

}

LineLeftAction::LineLeftAction(const LineLeftAction& source)
	: HScrollAction(source) {

}

LineLeftAction::~LineLeftAction() {

}

void LineLeftAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long position = this->drawingPaper->scrollController->Left();
	int previous = this->drawingPaper->SetScrollPos(SB_HORZ, position, TRUE);//
	position = this->drawingPaper->GetScrollPos(SB_HORZ);
	this->drawingPaper->scrollController->MoveHorizontalScroll(position);
	this->drawingPaper->ScrollWindow(previous - position, 0);
}

LineLeftAction& LineLeftAction::operator=(const LineLeftAction& source) {
	HScrollAction::operator=(source);

	return *this;
}

// LineRightAction

LineRightAction::LineRightAction(DrawingPaper *drawingPaper)
	:HScrollAction(drawingPaper) {

}

LineRightAction::LineRightAction(const LineRightAction& source)
	: HScrollAction(source) {

}

LineRightAction::~LineRightAction() {

}

void LineRightAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long position = this->drawingPaper->scrollController->Right();
	Long previous = this->drawingPaper->SetScrollPos(SB_HORZ, position, TRUE);
	position = this->drawingPaper->GetScrollPos(SB_HORZ);
	this->drawingPaper->scrollController->MoveHorizontalScroll(position);
	this->drawingPaper->ScrollWindow(previous-position, 0);

}

LineRightAction& LineRightAction::operator=(const LineRightAction& source) {
	HScrollAction::operator=(source);

	return *this;
}

// PageLeftAction

PageLeftAction::PageLeftAction(DrawingPaper *drawingPaper)
	:HScrollAction(drawingPaper) {

}

PageLeftAction::PageLeftAction(const PageLeftAction& source)
	: HScrollAction(source) {

}

PageLeftAction::~PageLeftAction() {

}

void PageLeftAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long position = this->drawingPaper->scrollController->PageLeft();
	int previous = this->drawingPaper->SetScrollPos(SB_HORZ, position, TRUE);
	position = this->drawingPaper->GetScrollPos(SB_HORZ);
	this->drawingPaper->scrollController->MoveHorizontalScroll(position);
	this->drawingPaper->ScrollWindow(previous - position, 0);
}

PageLeftAction& PageLeftAction::operator=(const PageLeftAction& source) {
	HScrollAction::operator=(source);

	return *this;
}

// PageRightAction

PageRightAction::PageRightAction(DrawingPaper *drawingPaper)
	:HScrollAction(drawingPaper) {

}

PageRightAction::PageRightAction(const PageRightAction& source)
	: HScrollAction(source) {

}

PageRightAction::~PageRightAction() {

}

void PageRightAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long position = this->drawingPaper->scrollController->PageRight();
	int previous = this->drawingPaper->SetScrollPos(SB_HORZ, position, TRUE);
	position = this->drawingPaper->GetScrollPos(SB_HORZ);
	this->drawingPaper->scrollController->MoveHorizontalScroll(position);
	this->drawingPaper->ScrollWindow(previous - position, 0);
}

PageRightAction& PageRightAction::operator=(const PageRightAction& source) {
	HScrollAction::operator=(source);

	return *this;
}

// ThumbTrackHScrollAction

ThumbTrackHScrollAction::ThumbTrackHScrollAction(DrawingPaper *drawingPaper)
	:HScrollAction(drawingPaper) {

}

ThumbTrackHScrollAction::ThumbTrackHScrollAction(const ThumbTrackHScrollAction& source)
	: HScrollAction(source) {

}

ThumbTrackHScrollAction::~ThumbTrackHScrollAction() {

}

void ThumbTrackHScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long position = this->drawingPaper->scrollController->MoveHorizontalScroll(nPos);
	int previous = this->drawingPaper->SetScrollPos(SB_HORZ, position, TRUE);
	position = this->drawingPaper->GetScrollPos(SB_HORZ);
	this->drawingPaper->scrollController->MoveHorizontalScroll(position);
	this->drawingPaper->ScrollWindow(previous - position, 0);
}

ThumbTrackHScrollAction& ThumbTrackHScrollAction::operator=(const ThumbTrackHScrollAction& source) {
	HScrollAction::operator=(source);

	return *this;
}