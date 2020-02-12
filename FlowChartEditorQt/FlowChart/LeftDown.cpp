/******************************************************************
* 파일 이름 : LeftDown.cpp
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#include "LeftDown.h"
#include "Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

#include "ScrollController.h"
#include "Scrolls.h"

LeftDown::LeftDown(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
	:Line(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
}

LeftDown::~LeftDown() {}

LeftDown::LeftDown(const LeftDown& source) : Line(source) {
}

LeftDown& LeftDown::operator =(const LeftDown& source) {
	Line::operator=(source);
	return *this;
}

bool LeftDown::IsEqual(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<LeftDown *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool LeftDown::IsNotEqual(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<LeftDown *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool LeftDown::operator ==(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<LeftDown *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool LeftDown::operator !=(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<LeftDown *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

void LeftDown::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

Shape* LeftDown::Clone() {
	return new LeftDown(*this);
}

void LeftDown::DrawActiveShape(CDC *dc) {
	dc->MoveTo(x, y);
	dc->LineTo(x + width, y);
	dc->LineTo(x + width, y + height - ARROW_SIZE);

	POINT arrow[3];
	arrow[0].x = x + width;
	arrow[0].y = y + height;
	arrow[1].x = x + width - ARROW_SIZE / 2;
	arrow[1].y = y + height - ARROW_SIZE;
	arrow[2].x = x + width + ARROW_SIZE / 2;
	arrow[2].y = y + height - ARROW_SIZE;
	dc->Polygon(arrow, 3);
}

void LeftDown::DrawActiveShape(Painter *painter) {
	painter->DrawLine(x, y, x + width, y);
	painter->DrawLine(x + width, y, x + width, y + height - ARROW_SIZE);

	POINT arrow[3];
	arrow[0].x = x + width;
	arrow[0].y = y + height;
	arrow[1].x = x + width - ARROW_SIZE / 2;
	arrow[1].y = y + height - ARROW_SIZE;
	arrow[2].x = x + width + ARROW_SIZE / 2;
	arrow[2].y = y + height - ARROW_SIZE;
	painter->DrawPolygon(arrow, 3);
}

void LeftDown::GetRegion(CDC *dc, CRgn *region) {
	CRgn region1;

	region->CreateRectRgn(x, y - LINETHICKNESS, x + width, y + LINETHICKNESS);
	region1.CreateRectRgn(x + width - LINETHICKNESS, y, x + width + LINETHICKNESS, y + height);

	region->CombineRgn(region, &region1, RGN_OR);

	region1.DeleteObject();
}

void LeftDown::GetRegion(Painter *painter, CRgn *region) {
	CRgn region1;

	region->CreateRectRgn(x, y - LINETHICKNESS, x + width, y + LINETHICKNESS);
	region1.CreateRectRgn(x + width - LINETHICKNESS, y, x + width + LINETHICKNESS, y + height);

	region->CombineRgn(region, &region1, RGN_OR);

	region1.DeleteObject();
}

void LeftDown::GetRegion(CDC *dc, Long thickness, CRgn *region) {
	CRgn region1;

	region->CreateRectRgn(x, y - thickness, x + width, y + thickness);
	region1.CreateRectRgn(x + width - thickness, y, x + width + thickness, y + height);

	region->CombineRgn(region, &region1, RGN_OR);

	region1.DeleteObject();
}

void LeftDown::GetRegion(Painter *painter, Long thickness, CRgn *region) {
	CRgn region1;

	region->CreateRectRgn(x, y - thickness, x + width, y + thickness);
	region1.CreateRectRgn(x + width - thickness, y, x + width + thickness, y + height);

	region->CombineRgn(region, &region1, RGN_OR);

	region1.DeleteObject();
}

BOOL LeftDown::IsIncluded(CDC *dc, POINT point) {
	CRgn region;
	CRgn region1;
	BOOL ret;

	region.CreateRectRgn(x, y - LINETHICKNESS, x + width, y + LINETHICKNESS);
	region1.CreateRectRgn(x + width - LINETHICKNESS, y, x + width + LINETHICKNESS, y + height);

	region.CombineRgn(&region, &region1, RGN_OR);
	ret = region.PtInRegion(point);

	region.DeleteObject();
	region1.DeleteObject();
	return ret;
}

BOOL LeftDown::IsIncluded(Painter *painter, POINT point) {
	CRgn region;
	CRgn region1;
	BOOL ret;

	region.CreateRectRgn(x, y - LINETHICKNESS, x + width, y + LINETHICKNESS);
	region1.CreateRectRgn(x + width - LINETHICKNESS, y, x + width + LINETHICKNESS, y + height);

	region.CombineRgn(&region, &region1, RGN_OR);

	ret = region.PtInRegion(point);

	region.DeleteObject();
	region1.DeleteObject();
	return ret;
}

BOOL LeftDown::IsIncluded(Painter *painter, const RECT& rect) {
	CRgn region;
	CRgn region1;
	BOOL ret;

	region.CreateRectRgn(x, y - LINETHICKNESS, x + width, y + LINETHICKNESS);
	region1.CreateRectRgn(x + width - LINETHICKNESS, y, x + width + LINETHICKNESS, y + height);

	region.CombineRgn(&region, &region1, RGN_OR);
	ret = region.RectInRegion(&rect);

	region.DeleteObject();
	region1.DeleteObject();
	return ret;
}

void LeftDown::GetSelectionMarkerRect(UINT marker, CRect *rect) {
	int x_;
	int y_;

	switch (marker) {
	case HIT_IN:
		x_ = x;
		y_ = y;
		break;

	case HIT_OUT:
		x_ = x + width;
		y_ = y + height;
		break;
	}

	rect->left = x_ - 4;
	rect->top = y_ - 4;
	rect->right = x_ + 5;
	rect->bottom = y_ + 5;
}

void LeftDown::GetSelectionMarkerAllRegion(CRgn *region) {
	Long x_, y_;
	CRgn region1;
	x_ = x;
	y_ = y;
	region->CreateRectRgn(x_ - 6, y_ - 6, x_ + 7, y_ + 7);

	x_ = x + width;
	y_ = y + height;
	region1.CreateRectRgn(x_ - 6, y_ - 6, x_ + 7, y_ + 7);
	region->CombineRgn(region, &region1, RGN_OR);
	region1.DeleteObject();
}

int LeftDown::GetHitCode(Painter *painter, const CPoint& point, const CRgn& region) {
	int result = HIT_NONE;

	if (region.PtInRegion(point)) {
		result = HIT_BODY;
	}

	CRect rectSelect;
	GetSelectionMarkerRect(HIT_IN, &rectSelect);
	if (rectSelect.PtInRect(point)) {
		result = HIT_IN;
	}

	GetSelectionMarkerRect(HIT_OUT, &rectSelect);
	if (rectSelect.PtInRect(point)) {
		result = HIT_OUT;
	}
	return result;
}

void LeftDown::DrawSelectionMarkers(CDC* dc, ScrollController *scrollController) {
	CRect rectSelect;
	CBrush brush;
	CBrush *oldBrush;

	brush.CreateSolidBrush(RGB(0, 0, 255));
	oldBrush = dc->SelectObject(&brush);

	GetSelectionMarkerRect(HIT_IN, &rectSelect);
	Long positionX = scrollController->GetScroll(1)->GetPosition();
	Long positionY = scrollController->GetScroll(0)->GetPosition();
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle(rectSelect);

	GetSelectionMarkerRect(HIT_OUT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle(rectSelect);

	dc->SelectObject(oldBrush);
	brush.DeleteObject();
}

void LeftDown::DrawSelectionMarkers(Painter* painter, ScrollController *scrollController) {
	CRect rectSelect;

	painter->ChangePlaneProperty(BS_SOLID, RGB(0, 0, 255));

	GetSelectionMarkerRect(HIT_IN, &rectSelect);
	Long positionX = scrollController->GetScroll(1)->GetPosition();
	Long positionY = scrollController->GetScroll(0)->GetPosition();
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_OUT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);
}

void LeftDown::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.x = x;
	attribute->pointIn.y = y;

	attribute->pointOut.x = x + width;
	attribute->pointOut.y = y + height;
}

void LeftDown::GetLine(char(*line)) {
	sprintf(line, "%d\t%d\t%d\t%d\t%d\t\t\t%s\n", ID_LEFTDOWN, x, y, width, height, contents);
}

bool LeftDown::IsStyle(Long style) {
	bool ret = false;
	if (Shape::IsStyle(style) || Line::IsStyle(style) || (style >> 10) % 2) {
		ret = true;
	}
	return ret;
}