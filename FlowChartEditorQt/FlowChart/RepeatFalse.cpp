/******************************************************************
* 파일 이름 : RepeatFalse.h
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일 
*******************************************************************/

#include "RepeatFalse.h"
#include "Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

#include "ScrollController.h"
#include "Scrolls.h"

RepeatFalse::RepeatFalse(Long x, Long y, Long width, Long height, Long width2,Long height2, DWORD backGroundColor, PenStyle borderLine, 
	DWORD borderColor, String contents):Line(x,y,width,height,backGroundColor,borderLine,borderColor,contents)
{
	this->width2 = width2;
	this->height2 = height2;
}

RepeatFalse::~RepeatFalse(){}

RepeatFalse::RepeatFalse(const RepeatFalse& source):Line(source){
	this->width2 = source.width2;
	this->height2 = source.height2;
}

RepeatFalse& RepeatFalse::operator=(const RepeatFalse& source){
	Line::operator=(source);

	this->width2 = source.width2;
	this->height2 = source.height2;

	return *this;
}

bool RepeatFalse::IsEqual(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<RepeatFalse *>(const_cast<Shape *>(&other)) &&
		dynamic_cast<RepeatFalse *>(const_cast<Shape *>(&other))->width2 == this->width2 &&
		dynamic_cast<RepeatFalse *>(const_cast<Shape *>(&other))->height2 == this->height2){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool RepeatFalse::IsNotEqual(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<RepeatFalse *>(const_cast<Shape *>(&other)) ||
		dynamic_cast<RepeatFalse *>(const_cast<Shape *>(&other))->width2 != this->width2 ||
		dynamic_cast<RepeatFalse *>(const_cast<Shape *>(&other))->height2 != this->height2){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool RepeatFalse::operator ==(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<RepeatFalse *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool RepeatFalse::operator !=(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<RepeatFalse *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

void RepeatFalse::Accept(FlowChartVisitor *draw){
	draw->Visit(this);
}

void RepeatFalse::DrawActiveShape(CDC *dc){
	POINT points[5];
	points[0].x = x;
	points[0].y = y;
	points[1].x = x + width2;
	points[1].y = y;
	points[2].x = x + width2;
	points[2].y = y + height2;
	points[3].x = x + width;
	points[3].y = y + height2;
	points[4].x = x + width;
	points[4].y = y + height;
	dc->Polyline(points,5);

	POINT arrow[3];
	arrow[0].x = x + width - ARROW_SIZE/2;
	arrow[0].y = y + height - ARROW_SIZE;
	arrow[1].x = x + width;
	arrow[1].y = y + height;
	arrow[2].x = x + width + ARROW_SIZE/2;
	arrow[2].y = y + height - ARROW_SIZE;
	dc->Polygon(arrow,3);	
}

void RepeatFalse::DrawActiveShape(Painter *painter){
	POINT points[5];
	points[0].x = x;
	points[0].y = y;
	points[1].x = x + width2;
	points[1].y = y;
	points[2].x = x + width2;
	points[2].y = y + height2;
	points[3].x = x + width;
	points[3].y = y + height2;
	points[4].x = x + width;
	points[4].y = y + height;
	painter->DrawPolyline(points,5);	

	POINT arrow[3];
	arrow[0].x = x + width - ARROW_SIZE/2;
	arrow[0].y = y + height - ARROW_SIZE;
	arrow[1].x = x + width;
	arrow[1].y = y + height;
	arrow[2].x = x + width + ARROW_SIZE/2;
	arrow[2].y = y + height - ARROW_SIZE;
	painter->DrawPolygon(arrow,3);	
}

Shape* RepeatFalse::Clone(){
	return new RepeatFalse(*this);
}

void RepeatFalse::GetRegion(CDC *dc, CRgn *region) {
	CRgn region1;	
	CRgn region2;	
	CRgn region3;

	region->CreateRectRgn(x , y - LINETHICKNESS, x + width2 + 1, y + LINETHICKNESS);

	region1.CreateRectRgn(x + width2 - LINETHICKNESS, y, x + width2 + LINETHICKNESS, y+height2);
	region->CombineRgn(region,&region1,RGN_OR);	
	
	region2.CreateRectRgn(x + width2, y + height2 - LINETHICKNESS, x + width, y + height2 + LINETHICKNESS);
	region->CombineRgn(region,&region2,RGN_OR);

	region3.CreateRectRgn(x + width - LINETHICKNESS, y + height2 - 1, x + width + LINETHICKNESS, y + height);
	region->CombineRgn(region,&region3,RGN_OR);

	region1.DeleteObject();
	region2.DeleteObject();
	region3.DeleteObject();
}

void RepeatFalse::GetRegion(Painter *painter, CRgn *region) {
	CRgn region1;	
	CRgn region2;	
	CRgn region3;

	region->CreateRectRgn(x , y - LINETHICKNESS, x + width2 + 1, y + LINETHICKNESS);

	region1.CreateRectRgn(x + width2 - LINETHICKNESS, y, x + width2 + LINETHICKNESS, y+height2);
	region->CombineRgn(region,&region1,RGN_OR);	
	
	region2.CreateRectRgn(x + width2, y + height2 - LINETHICKNESS, x + width, y + height2 + LINETHICKNESS);
	region->CombineRgn(region,&region2,RGN_OR);

	region3.CreateRectRgn(x + width - LINETHICKNESS, y + height2 - 1, x + width + LINETHICKNESS, y + height);
	region->CombineRgn(region,&region3,RGN_OR);

	region1.DeleteObject();
	region2.DeleteObject();
	region3.DeleteObject();
}

void RepeatFalse::GetRegion(CDC *dc, Long thickness, CRgn *region){
	CRgn region1;	
	CRgn region2;	
	CRgn region3;

	region->CreateRectRgn(x , y - thickness, x + width2 + 1, y + thickness);

	region1.CreateRectRgn(x + width2 - thickness, y, x + width2 + thickness, y+height2);
	region->CombineRgn(region,&region1,RGN_OR);	
	
	region2.CreateRectRgn(x + width2, y + height2 - thickness, x + width, y + height2 + thickness);
	region->CombineRgn(region,&region2,RGN_OR);

	region3.CreateRectRgn(x + width - thickness, y + height2 - 1, x + width + thickness, y + height);
	region->CombineRgn(region,&region3,RGN_OR);

	region1.DeleteObject();
	region2.DeleteObject();
	region3.DeleteObject();
}

void RepeatFalse::GetRegion(Painter *painter, Long thickness, CRgn *region){
	CRgn region1;	
	CRgn region2;	
	CRgn region3;

	region->CreateRectRgn(x , y - thickness, x + width2 + 1, y + thickness);

	region1.CreateRectRgn(x + width2 - thickness, y, x + width2 + thickness, y+height2);
	region->CombineRgn(region,&region1,RGN_OR);	
	
	region2.CreateRectRgn(x + width2, y + height2 - thickness, x + width, y + height2 + thickness);
	region->CombineRgn(region,&region2,RGN_OR);

	region3.CreateRectRgn(x + width - thickness, y + height2 - 1, x + width + thickness, y + height);
	region->CombineRgn(region,&region3,RGN_OR);

	region1.DeleteObject();
	region2.DeleteObject();
	region3.DeleteObject();
}

void RepeatFalse::ReSize(Long _width, Long _height, Long _width2, Long _height2){
	width = _width;
	height = _height;
	width2 = _width2;
	height2 = _height2;
}

BOOL RepeatFalse::IsIncluded(CDC *dc, POINT point){
	CRgn region;
	CRgn region1;	
	CRgn region2;	
	CRgn region3;
	BOOL ret;

	region.CreateRectRgn(x , y - LINETHICKNESS, x + width2, y + LINETHICKNESS);

	region1.CreateRectRgn(x + width2 - LINETHICKNESS, y, x + width2 + LINETHICKNESS, y+height2);
	region.CombineRgn(&region,&region1,RGN_OR);	
	
	region2.CreateRectRgn(x + width2, y + height2 - LINETHICKNESS, x + width, y + height2 + LINETHICKNESS);
	region.CombineRgn(&region,&region2,RGN_OR);

	region3.CreateRectRgn(x + width - LINETHICKNESS, y + height2, x + width + LINETHICKNESS, y + height);
	region.CombineRgn(&region,&region3,RGN_OR);

	ret = region.PtInRegion(point);

	region.DeleteObject();
	region1.DeleteObject();
	region2.DeleteObject();
	region3.DeleteObject();	
	return ret;
}

BOOL RepeatFalse::IsIncluded(Painter *painter, POINT point){
	CRgn region;
	CRgn region1;	
	CRgn region2;	
	CRgn region3;
	BOOL ret;

	region.CreateRectRgn(x , y - LINETHICKNESS, x + width2, y + LINETHICKNESS);

	region1.CreateRectRgn(x + width2 - LINETHICKNESS, y, x + width2 + LINETHICKNESS, y+height2);
	region.CombineRgn(&region,&region1,RGN_OR);	
	
	region2.CreateRectRgn(x + width2, y + height2 - LINETHICKNESS, x + width, y + height2 + LINETHICKNESS);
	region.CombineRgn(&region,&region2,RGN_OR);

	region3.CreateRectRgn(x + width - LINETHICKNESS, y + height2, x + width + LINETHICKNESS, y + height);
	region.CombineRgn(&region,&region3,RGN_OR);

	ret = region.PtInRegion(point);

	region.DeleteObject();
	region1.DeleteObject();
	region2.DeleteObject();
	region3.DeleteObject();	
	return ret;
}

BOOL RepeatFalse::IsIncluded(Painter *painter, const RECT& rect){
	CRgn region;
	CRgn region1;	
	CRgn region2;	
	CRgn region3;
	BOOL ret;

	region.CreateRectRgn(x , y - LINETHICKNESS, x + width2, y + LINETHICKNESS);

	region1.CreateRectRgn(x + width2 - LINETHICKNESS, y, x + width2 + LINETHICKNESS, y+height2);
	region.CombineRgn(&region,&region1,RGN_OR);	
	
	region2.CreateRectRgn(x + width2, y + height2 - LINETHICKNESS, x + width, y + height2 + LINETHICKNESS);
	region.CombineRgn(&region,&region2,RGN_OR);

	region3.CreateRectRgn(x + width - LINETHICKNESS, y + height2, x + width + LINETHICKNESS, y + height);
	region.CombineRgn(&region,&region3,RGN_OR);

	ret = region.RectInRegion(&rect);

	region.DeleteObject();
	region1.DeleteObject();
	region2.DeleteObject();
	region3.DeleteObject();	
	return ret;
}

void RepeatFalse::Copy(Shape *object){
	x = object->GetX();
	y = object->GetY();
	width = object->GetWidth();
	height = object->GetHeight();
	backGroundColor = object->GetBackGroundColor();
	borderLine = object->GetBorderLine();
	borderColor = object->GetBorderColor();
	contents = object->GetContents();
	width2 = dynamic_cast<RepeatFalse *>(object)->GetWidth2();
	height2 = dynamic_cast<RepeatFalse *>(object)->GetHeight2();
	isSelected = object->IsSelected();
}

void RepeatFalse::GetSelectionMarkerRect( UINT marker, CRect *rect ){
	int x_;
	int y_;

	switch (marker) {
		case HIT_IN: 
			x_ = x;
			y_ = y;
		break;

		case HIT_HANDLE:
			x_ = x + width2;
			y_ = y + height2;
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

void RepeatFalse::GetSelectionMarkerAllRegion( CRgn *region ){
	Long x_, y_;
	CRgn region1;
	x_ = x;
	y_ = y;
	region->CreateRectRgn( x_ - 6 , y_ - 6, x_ + 7, y_ + 7 );
	
	x_ = x + width2;
	y_ = y + height2;
	region1.CreateRectRgn( x_ - 6 , y_ - 6, x_ + 7, y_ + 7 );
	region->CombineRgn(region,&region1,RGN_OR);
	region1.DeleteObject();

	x_ = x + width;
	y_ = y + height;
	region1.CreateRectRgn( x_ - 6 , y_ - 6, x_ + 7, y_ + 7 );
	region->CombineRgn(region,&region1,RGN_OR);
	region1.DeleteObject();
}

int RepeatFalse::GetHitCode( Painter *painter, const CPoint& point, const CRgn& region ){
	int result = HIT_NONE;

	if( region.PtInRegion(point)){
		result = HIT_BODY;
	}

	CRect rectSelect;
	GetSelectionMarkerRect( HIT_IN, &rectSelect );
	if( rectSelect.PtInRect( point ) ) {
		result = HIT_IN;
	}

	GetSelectionMarkerRect( HIT_HANDLE, &rectSelect );
	if( rectSelect.PtInRect( point ) ) {
		result = HIT_HANDLE;
	}

	GetSelectionMarkerRect( HIT_OUT, &rectSelect );
	if( rectSelect.PtInRect( point ) ) {
		result = HIT_OUT;
	}
	return result;
}

void RepeatFalse::DrawSelectionMarkers( CDC* dc, ScrollController *scrollController ){
	CRect rectSelect;
	CBrush brush;
	CBrush *oldBrush;
	
	brush.CreateSolidBrush(RGB(0,0,255));
	oldBrush = dc->SelectObject(&brush);
			
	GetSelectionMarkerRect( HIT_IN, &rectSelect );
	Long positionX = scrollController->GetScroll(1)->GetPosition();
	Long positionY = scrollController->GetScroll(0)->GetPosition();
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle( rectSelect );

	GetSelectionMarkerRect( HIT_HANDLE, &rectSelect );
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle( rectSelect );

	GetSelectionMarkerRect( HIT_OUT, &rectSelect );
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle( rectSelect );

	dc->SelectObject(oldBrush);
	brush.DeleteObject();
}

void RepeatFalse::DrawSelectionMarkers( Painter* painter, ScrollController *scrollController ){
	CRect rectSelect;

	painter->ChangePlaneProperty(BS_SOLID, RGB(0, 0, 255));
	
	GetSelectionMarkerRect( HIT_IN, &rectSelect );
	Long positionX = scrollController->GetScroll(1)->GetPosition();
	Long positionY = scrollController->GetScroll(0)->GetPosition();
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle( rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom );

	GetSelectionMarkerRect( HIT_HANDLE, &rectSelect );
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle( rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom );

	GetSelectionMarkerRect( HIT_OUT, &rectSelect );
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle( rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom );
}

void RepeatFalse::GetAttribute(Attribute *attribute){
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';		
	
	attribute->pointIn.x = x;
	attribute->pointIn.y = y;	

	attribute->pointOut.x = x + width;
	attribute->pointOut.y = y + height;
}

void RepeatFalse::GetLine(char (*line)){
	sprintf(line,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n", ID_REPEATFALSE,x,y,width,height,width2,height2,contents);
}

bool RepeatFalse::IsStyle(Long style){
	bool ret = false;
	if( Shape::IsStyle(style) || Line::IsStyle(style) || (style>>14)%2 ){
		ret = true;
	}
	return ret;
}