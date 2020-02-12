/******************************************************************
* 파일 이름 : Decision.cpp
* 기능 : 판단기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일
*******************************************************************/

#include "Decision.h"
#include "Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

Decision::Decision(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
	:Symbol(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
}

Decision::~Decision() {}

Decision::Decision(const Decision& source) : Symbol(source) {}

Decision& Decision::operator =(const Decision& source) {
	Symbol::operator=(source);
	return *this;
}

bool Decision::IsEqual(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<Decision *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Decision::IsNotEqual(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<Decision *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool Decision::operator ==(const Shape& other) {
	bool retVo = false;
	if (dynamic_cast<Decision *>(const_cast<Shape *>(&other))) {
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Decision::operator !=(const Shape& other) {
	bool retVo = false;
	if (!dynamic_cast<Decision *>(const_cast<Shape*>(&other))) {
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}
/*
void Decision::Draw(CDC* dc){
	CRgn region;
	CBrush brush;
	Long halfWidth = (Long)width/2;
	Long halfHeight = (Long)height/2;
	POINT shapePoint[5] ={{x+halfWidth,y},{x+width,y+halfHeight},{x+halfWidth,y+height},{x,y+halfHeight},{x+halfWidth,y}};

	brush.CreateStockObject(LTGRAY_BRUSH);
	region.CreatePolygonRgn(shapePoint, 5, WINDING);
	dc->FillRgn(&region, &brush);

	dc->Polyline(shapePoint,5);

	brush.DeleteObject();

	// 텍스트를 출력한다.
	Long left, top, right, bottom;

	GetFormattingArea(&left, &top, &right, &bottom);
	RECT rect = { left , top, right, bottom };

	dc->DrawText( contents.operator char *(), -1, &rect, DT_CENTER );

	if(this->isSelected == true){
		DrawSelectionMarkers(dc);
	}
}

void Decision::Draw(Painter *painter){
	Long halfWidth = (Long)width/2;
	Long halfHeight = (Long)height/2;
	POINT shapePoint[5] ={{x+halfWidth,y},{x+width,y+halfHeight},{x+halfWidth,y+height},{x,y+halfHeight},{x+halfWidth,y}};

	painter->FillBackground(shapePoint,5,LTGRAY_BRUSH);
	painter->DrawPolyline(shapePoint,5);


	// 텍스트를 출력한다.
	Long left, top, right, bottom;

	HWND hWnd = ::GetActiveWindow();
	CWnd *cWnd = CWnd::FromHandle(hWnd);
	Formatter formatter(cWnd);

	GetFormattingArea(&left, &top, &right, &bottom);
	RECT rect = { left , top, right, bottom };

	painter->DrawText(formatter.GetHeightOfCharacter(), contents.operator char *(), -1, &rect, DT_CENTER );
	if(this->isSelected == true){
		DrawSelectionMarkers(painter);
	}
}
*/

Shape* Decision::Clone() {
	return new Decision(*this);
}

void Decision::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}
/*
void Decision::GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom){
	Shape::GetFormattingArea( left, top, right, bottom );
}
*/
#if 0
void Decision::GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom) {
	Long halfWidth = width / 2;
	Long halfHeight = height / 2;
	Long quarterHeight = halfHeight / 2;

	*left = x + quarterHeight;
	*top = y;
	*right = x + width - quarterHeight;
	*bottom = y + height;
}

void Decision::GetFormattingArea(Long *left, Long *right) {
	Long halfHeight = height / 2;

	*left = x + halfHeight;
	*right = x + width - halfHeight;
}
#endif

void Decision::GetRegion(CDC *dc, CRgn *region) {
	Long halfWidth = (Long)width / 2;
	Long halfHeight = (Long)height / 2;
	POINT points[5] = { {x + halfWidth,y},{x + width,y + halfHeight},{x + halfWidth,y + height},{x,y + halfHeight},{x + halfWidth,y} };
	region->CreatePolygonRgn(points, 5, WINDING);
}

void Decision::GetRegion(Painter *painter, CRgn *region) {
	Long halfWidth = (Long)width / 2;
	Long halfHeight = (Long)height / 2;
	POINT points[5] = { {x + halfWidth,y},{x + width,y + halfHeight},{x + halfWidth,y + height},{x,y + halfHeight},{x + halfWidth,y} };
	region->CreatePolygonRgn(points, 5, WINDING);
}

void Decision::GetRegion(CDC *dc, Long thickness, CRgn *region) {
	Long x_, y_, width_, height_;
	Long halfWidth_, halfHeight_;

	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness * 2;
	height_ = height + thickness * 2;
	halfWidth_ = width_ / 2;
	halfHeight_ = height_ / 2;

	POINT points[5] = { {x_ + halfWidth_,y_},{x_ + width_,y_ + halfHeight_},{x_ + halfWidth_,y_ + height_},{x_,y_ + halfHeight_},{x_ + halfWidth_,y_} };
	region->CreatePolygonRgn(points, 5, WINDING);
}

void Decision::GetRegion(Painter *painter, Long thickness, CRgn *region) {
	Long x_, y_, width_, height_;
	Long halfWidth_, halfHeight_;

	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness * 2;
	height_ = height + thickness * 2;
	halfWidth_ = width_ / 2;
	halfHeight_ = height_ / 2;

	POINT points[5] = { {x_ + halfWidth_,y_},{x_ + width_,y_ + halfHeight_},{x_ + halfWidth_,y_ + height_},{x_,y_ + halfHeight_},{x_ + halfWidth_,y_} };
	region->CreatePolygonRgn(points, 5, WINDING);
}

BOOL Decision::IsIncluded(CDC *dc, POINT point) {
	CRgn region;
	BOOL ret;
	Long halfWidth = (Long)width / 2;
	Long halfHeight = (Long)height / 2;
	POINT points[5] = { {x + halfWidth,y},{x + width,y + halfHeight},{x + halfWidth,y + height},{x,y + halfHeight},{x + halfWidth,y} };

	region.CreatePolygonRgn(points, 5, WINDING);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Decision::IsIncluded(Painter *painter, POINT point) {
	CRgn region;
	BOOL ret;

	Long halfWidth = (Long)width / 2;
	Long halfHeight = (Long)height / 2;
	POINT points[5] = { {x + halfWidth,y},{x + width,y + halfHeight},{x + halfWidth,y + height},{x,y + halfHeight},{x + halfWidth,y} };

	region.CreatePolygonRgn(points, 5, WINDING);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Decision::IsIncluded(Painter *painter, const RECT& rect) {
	CRgn region;
	BOOL ret;
	Long halfWidth = (Long)width / 2;
	Long halfHeight = (Long)height / 2;
	POINT points[5] = { {x + halfWidth,y},{x + width,y + halfHeight},{x + halfWidth,y + height},{x,y + halfHeight},{x + halfWidth,y} };

	region.CreatePolygonRgn(points, 5, WINDING);
	ret = region.RectInRegion(&rect);
	region.DeleteObject();
	return ret;
}

void Decision::GetAttribute(Attribute *attribute) {
	attribute->vertexIn = 'Y';
	attribute->vertexTrue = 'Y';
	attribute->vertexFalse = 'Y';
	attribute->vertexOut = 'Y';

	attribute->pointIn.x = x + width / 2;
	attribute->pointIn.y = y;

	attribute->pointTrue.x = x;
	attribute->pointTrue.y = y + height / 2;

	attribute->pointFalse.x = x + width;
	attribute->pointFalse.y = y + height / 2;

	attribute->pointOut.x = x + width / 2;
	attribute->pointOut.y = y + height;
}

void Decision::GetLine(char(*line)) {
	String saveContents(contents);
	saveContents.Replace('\n', '\r');

	sprintf(line, "%d\t%d\t%d\t%d\t%d\t\t\t%s\n", ID_DECISION, x, y, width, height, saveContents);
}

bool Decision::IsStyle(Long style) {
	bool ret = false;
	if (Shape::IsStyle(style) || Symbol::IsStyle(style) || (style >> 6) % 2) {
		ret = true;
	}
	return ret;
}

void Decision::DrawSelectionMarkers(CDC* dc, ScrollController *scrollController) {
	Shape::DrawSelectionMarkers(dc, scrollController);
}

void Decision::DrawSelectionMarkers(Painter* painter, ScrollController *scrollController) {
	Shape::DrawSelectionMarkers(painter, scrollController);
}

DecisionForSelection::DecisionForSelection(Long x, Long y, Long width, Long height, DWORD backGroundColor,
	PenStyle borderLine, DWORD borderColor, String contents)
	:Decision(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
}

DecisionForSelection::DecisionForSelection(const Decision& other) : Decision(other) {
}

DecisionForSelection::~DecisionForSelection() {
}

DecisionForIteration::DecisionForIteration(Long x, Long y, Long width, Long height, DWORD backGroundColor,
	PenStyle borderLine, DWORD borderColor, String contents)
	:Decision(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
}

DecisionForIteration::DecisionForIteration(const Decision& other) : Decision(other) {
}

DecisionForIteration::~DecisionForIteration() {
}