#include "ScrollController.h"
#include "Scrolls.h"
#include "DrawingPaper.h"
#include "FlowChart.h"

ScrollController::ScrollController(DrawingPaper *drawingPaper) {
	this->drawingPaper = drawingPaper;

	this->height = this->drawingPaper->a4Paper->GetY()*2 + this->drawingPaper->a4Paper->GetHeight();
	this->width = this->drawingPaper->a4Paper->GetX()*2 + this->drawingPaper->a4Paper->GetWidth();

	RECT rect;
	this->drawingPaper->GetClientRect(&rect);
	Long clientWidth = rect.right - rect.left;
	Long clientHeight = rect.bottom - rect.top;

	Long maximum = this->height - clientHeight;
	Long pageSize = clientHeight;
	Long lineSize = 100;
	Scroll *scroll = new VerticalScroll(0, maximum, pageSize, lineSize, 0);
	this->scrolls.Store(this->scrolls.GetLength(), scroll);

	maximum = this->width - clientWidth;
	pageSize = clientWidth;
	lineSize = 150;
	scroll = new HorizontalScroll(0, maximum, pageSize, lineSize, 0);
	this->scrolls.Store(this->scrolls.GetLength(), scroll);
}

ScrollController::ScrollController(const ScrollController& source)
	: scrolls(source.scrolls) {
	Long i = 0;
	while (i < 2) {
		Scroll *scroll = this->scrolls.GetAt(i);
		if (dynamic_cast<VerticalScroll*>(scroll)) {
			scroll = new VerticalScroll(*(dynamic_cast<VerticalScroll*>(scroll)));
		}
		else if (dynamic_cast<HorizontalScroll*>(scroll)) {
			scroll = new HorizontalScroll(*(dynamic_cast<HorizontalScroll*>(scroll)));
		}
		this->scrolls.Modify(i, scroll);
		i++;
	}

	this->drawingPaper = source.drawingPaper;
	this->width = source.width;
	this->height = source.height;
}

ScrollController::~ScrollController() {
	Long i = 0;
	while (i < 2) {
		delete this->scrolls[i];
		i++;
	}
}

ScrollController& ScrollController::operator=(const ScrollController& source) {
	this->scrolls = source.scrolls;
	Long i = 0;
	while (i < 2) {
		Scroll *scroll = this->scrolls.GetAt(i);
		if (dynamic_cast<VerticalScroll*>(scroll)) {
			scroll = new VerticalScroll(*(dynamic_cast<VerticalScroll*>(scroll)));
		}
		else if (dynamic_cast<HorizontalScroll*>(scroll)) {
			scroll = new HorizontalScroll(*(dynamic_cast<HorizontalScroll*>(scroll)));
		}
		this->scrolls.Modify(i, scroll);
		i++;
	}

	this->drawingPaper = source.drawingPaper;
	this->width = source.width;
	this->height = source.height;

	return *this;
}

void ScrollController::Update() {
	Long minimum;
	Long maximum;
	Long pageSize;
	Long lineSize;
	Long position;
	SCROLLINFO scrollInfo;
	RECT rect;
	RECT clientRect;
	this->drawingPaper->GetClientRect(&clientRect);
	LONG style = ::GetWindowLong(this->drawingPaper->m_hWnd, GWL_STYLE);

	//=====================수직 스크롤 생성========================
	//1. 전체 영역의 높이를 구하다.
	this->height = this->drawingPaper->a4Paper->GetY()*2 + this->drawingPaper->a4Paper->GetHeight();
	//2. 클라이언트 영역의 높이를 구하다.
	Long clientHeight = clientRect.bottom - clientRect.top;
	//3. 클라이언트 영역 높이가 전체 영역 높이보다 작으면 스크롤을 생성한다.
	if (clientHeight < this->height) {
		style = style | WS_VSCROLL;
		minimum = this->scrolls.GetAt(0)->GetMinimum();
		maximum = this->height; //여유공간 200
		pageSize = clientHeight;
		lineSize = 100;
		position = this->scrolls.GetAt(0)->GetPosition();
		if (this->scrolls.GetAt(0) != NULL) {
			this->scrolls.Delete(0);
		}
		Scroll *scroll = new VerticalScroll(minimum, maximum, pageSize, lineSize, position);
		this->scrolls.Insert(0, scroll);
		scrollInfo = scroll->GetScrollInfo();
	}
	else {
		style = style & ~WS_VSCROLL;
		if (this->scrolls.GetAt(0) != 0) {
			this->scrolls.Delete(0);
			Scroll *scroll = new VerticalScroll(0, 0, 0, 0, 0);
			this->scrolls.Insert(0, scroll);
			scrollInfo = scroll->GetScrollInfo();
		}
	}
	this->drawingPaper->SetScrollInfo(SB_VERT, &scrollInfo, TRUE);

	//=====================수평 스크롤 생성========================
	//1. 전체 영역의 너비를 구하다.
	this->width = this->drawingPaper->a4Paper->GetX()*2 + this->drawingPaper->a4Paper->GetWidth();
	//2. 클라이언트 영역의 너비를 구하다.
	Long clientWidth = clientRect.right - clientRect.left;
	//3. 클라이언트 영역 너비가 전체 영역 너비보다 작으면 스크롤을 생성한다.
	if (clientWidth < this->width) {
		style = style | WS_HSCROLL;
		minimum = this->scrolls.GetAt(1)->GetMinimum();
		maximum = this->width;
		pageSize = clientWidth;
		lineSize = 150;
		position = this->scrolls.GetAt(1)->GetPosition();
		if (this->scrolls.GetAt(1) != NULL) {
			this->scrolls.Delete(1);
		}
		Scroll *scroll = new HorizontalScroll(minimum, maximum, pageSize, lineSize, position);
		this->scrolls.Insert(1, scroll);
		scrollInfo = scroll->GetScrollInfo();
	}
	else {
		style = style & ~WS_HSCROLL;
		if (this->scrolls.GetAt(1) != 0) {
			this->scrolls.Delete(1);
			Scroll *scroll = new HorizontalScroll(0, 0, 0, 0, 0);
			this->scrolls.Insert(1, scroll);
			scrollInfo = scroll->GetScrollInfo();
		}
	}
	this->drawingPaper->SetScrollInfo(SB_HORZ, &scrollInfo, TRUE);

	::SetWindowLong(this->drawingPaper->m_hWnd, GWL_STYLE, style);
	this->drawingPaper->RedrawWindow();
}

Long ScrollController::Up() {
	return this->scrolls.GetAt(0)->Down();
}

Long ScrollController::Down() {
	return this->scrolls.GetAt(0)->Up();
}

Long ScrollController::PageUp() {
	return this->scrolls.GetAt(0)->PageDown();
}

Long ScrollController::PageDown() {
	return this->scrolls.GetAt(0)->PageUp();
}

Long ScrollController::Left() {
	return this->scrolls.GetAt(1)->Down();
}

Long ScrollController::Right() {
	return this->scrolls.GetAt(1)->Up();
}

Long ScrollController::PageLeft() {
	return this->scrolls.GetAt(1)->PageDown();
}

Long ScrollController::PageRight() {
	return this->scrolls.GetAt(1)->PageUp();
}

Long ScrollController::MoveHorizontalScroll(Long position) {
	return this->scrolls.GetAt(1)->Move(position);
}

Long ScrollController::MoveVerticalScroll(Long position) {
	return this->scrolls.GetAt(0)->Move(position);
}

Long ScrollController::Rotate(short delta) {
	return this->scrolls.GetAt(0)->Rotate(delta);
}