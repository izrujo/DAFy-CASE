/******************************************************************
* 파일 이름 : Join.cpp
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일 
*******************************************************************/

#include "Join.h"
#include "Painter.h"
#include "Join.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

#include "ScrollController.h"
#include "Scrolls.h"

Join::Join(Long x, Long y, Long width, Long height,Long height2, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
:Line(x,y,width,height,backGroundColor,borderLine,borderColor,contents)
{
	this->height2 = height2;
}

Join::~Join(){}

Join::Join(const Join& source):Line(source){
	this->height2 = source.height2;
}

Join& Join::operator =(const Join& source){
	Line::operator=(source);
	this->height2 = source.height2;
	return *this;
}

bool Join::IsEqual(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<Join *>(const_cast<Shape *>(&other)) && 
		dynamic_cast<Join *>(const_cast<Shape *>(&other))->height2 == this->height2){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Join::IsNotEqual(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<Join *>(const_cast<Shape *>(&other)) || 
		dynamic_cast<Join *>(const_cast<Shape *>(&other))->height2 != this->height2){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool Join::operator ==(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<Join *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Join::operator !=(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<Join *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

void Join::DrawActiveShape(CDC *dc){
	POINT points[4];
	points[0].x = x;
	points[0].y = y;
	points[1].x = x;
	points[1].y = y + height2;
	points[2].x = x + width;
	points[2].y = y + height2;
	points[3].x = x + width;
	points[3].y = y + height;

	dc->Polyline(points,4);
}

Shape* Join::Clone(){
	return new Join(*this);
}

void Join::Accept(FlowChartVisitor *draw){
	draw->Visit(this);
}

void Join::DrawActiveShape(Painter *painter){
	POINT points[4];
	points[0].x = x;
	points[0].y = y;
	points[1].x = x;
	points[1].y = y + height2;
	points[2].x = x + width;
	points[2].y = y + height2;
	points[3].x = x + width;
	points[3].y = y + height;

	painter->DrawPolyline(points,4);
}

void Join::GetRegion(CDC *dc, CRgn *region){
	CRgn region1;	
	CRgn region2;	
	
	region->CreateRectRgn(x - LINETHICKNESS, y, x + LINETHICKNESS, y + height2);
	region1.CreateRectRgn(x - LINETHICKNESS , y + height2 - LINETHICKNESS, x + width + LINETHICKNESS, y + height2 + LINETHICKNESS);
	region->CombineRgn(region,&region1,RGN_OR);
	region2.CreateRectRgn(x + width- LINETHICKNESS , y + height2, x + width + LINETHICKNESS, y + height);
	region->CombineRgn(region,&region2,RGN_OR);

	region1.DeleteObject();
	region2.DeleteObject();
}

void Join::GetRegion(Painter *painter, CRgn *region){
	CRgn region1;	
	CRgn region2;	

	region->CreateRectRgn(x - LINETHICKNESS, y, x + LINETHICKNESS, y + height2);
	region1.CreateRectRgn(x - LINETHICKNESS , y + height2 - LINETHICKNESS, x + width + LINETHICKNESS, y + height2 + LINETHICKNESS);
	region->CombineRgn(region,&region1,RGN_OR);
	region2.CreateRectRgn(x + width- LINETHICKNESS , y + height2, x + width + LINETHICKNESS, y + height);
	region->CombineRgn(region,&region2,RGN_OR);

	region1.DeleteObject();
	region2.DeleteObject();
}

void Join::GetRegion(CDC *dc, Long thickness, CRgn *region){
	CRgn region1;	
	CRgn region2;	

	region->CreateRectRgn(x - thickness, y, x + thickness, y + height2);
	region1.CreateRectRgn(x - thickness , y + height2 - thickness, x + width + thickness, y + height2 + thickness);
	region->CombineRgn(region,&region1,RGN_OR);
	region2.CreateRectRgn(x + width - thickness , y + height2, x + width + thickness, y + height );
	region->CombineRgn(region,&region2,RGN_OR);

	region1.DeleteObject();
	region2.DeleteObject();
}

void Join::GetRegion(Painter *painter, Long thickness, CRgn *region){
	CRgn region1;	
	CRgn region2;	

	region->CreateRectRgn(x - thickness, y, x + thickness, y + height2);
	region1.CreateRectRgn(x - thickness , y + height2 - thickness, x + width + thickness, y + height2 + thickness);
	region->CombineRgn(region,&region1,RGN_OR);
	region2.CreateRectRgn(x + width - thickness , y + height2, x + width + thickness, y + height );
	region->CombineRgn(region,&region2,RGN_OR);

	region1.DeleteObject();
	region2.DeleteObject();
}

void Join::ReSize( Long _width, Long _height, Long _height2){
	width = _width;
	height = _height;
	this->height2 = _height2;
}

BOOL Join::IsIncluded(CDC *dc, POINT point){
	CRgn region;
	CRgn region1;	
	CRgn region2;	
	BOOL ret;

	region.CreateRectRgn(x - LINETHICKNESS, y, x + LINETHICKNESS, y + height2);
	region1.CreateRectRgn(x - LINETHICKNESS , y + height2 - LINETHICKNESS, x + width + LINETHICKNESS, y + height2 + LINETHICKNESS);
	region.CombineRgn(&region,&region1,RGN_OR);
	region2.CreateRectRgn(x + width- LINETHICKNESS , y + height2 + LINETHICKNESS, x + width + LINETHICKNESS, y + height + LINETHICKNESS);
	region.CombineRgn(&region,&region2,RGN_OR);

	ret =  region.PtInRegion(point);

	region.DeleteObject();
	region1.DeleteObject();
	region2.DeleteObject();
	return ret;
}

BOOL Join::IsIncluded(Painter *painter, POINT point){
	CRgn region;
	CRgn region1;	
	CRgn region2;	
	BOOL ret;

	region.CreateRectRgn(x - LINETHICKNESS, y, x + LINETHICKNESS, y + height2);
	region1.CreateRectRgn(x - LINETHICKNESS , y + height2 - LINETHICKNESS, x + width + LINETHICKNESS, y + height2 + LINETHICKNESS);
	region.CombineRgn(&region,&region1,RGN_OR);
	region2.CreateRectRgn(x + width- LINETHICKNESS , y + height2 + LINETHICKNESS, x + width + LINETHICKNESS, y + height + LINETHICKNESS);
	region.CombineRgn(&region,&region2,RGN_OR);

	ret =  region.PtInRegion(point);

	region.DeleteObject();
	region1.DeleteObject();
	region2.DeleteObject();
	return ret;
}

BOOL Join::IsIncluded(Painter *painter, const RECT& rect){
	CRgn region;
	CRgn region1;	
	CRgn region2;	
	BOOL ret;

	region.CreateRectRgn(x - LINETHICKNESS, y, x + LINETHICKNESS, y + height2);
	region1.CreateRectRgn(x - LINETHICKNESS , y + height2 - LINETHICKNESS, x + width + LINETHICKNESS, y + height2 + LINETHICKNESS);
	region.CombineRgn(&region,&region1,RGN_OR);
	region2.CreateRectRgn(x + width- LINETHICKNESS , y + height2 + LINETHICKNESS, x + width + LINETHICKNESS, y + height + LINETHICKNESS);
	region.CombineRgn(&region,&region2,RGN_OR);

	ret =  region.RectInRegion(&rect);

	region.DeleteObject();
	region1.DeleteObject();
	region2.DeleteObject();
	return ret;
}

void Join::Copy(Shape *object){
	x = object->GetX();
	y = object->GetY();
	width = object->GetWidth();
	height = object->GetHeight();
	backGroundColor = object->GetBackGroundColor();
	borderLine = object->GetBorderLine();
	borderColor = object->GetBorderColor();
	contents = object->GetContents();	
	height2 = dynamic_cast<Join *>(object)->GetHeight2();
	isSelected = object->IsSelected();
}

void Join::GetSelectionMarkerRect( UINT marker, CRect *rect ){
	int x_;
	int y_;

	switch (marker) {
		case HIT_TRUE: 
			x_ = x;
			y_ = y;
		break;

		case HIT_OUT:
			x_ = x + width/2;
			y_ = y + height2;
		break;

		case HIT_FALSE: 
			x_ = x + width;
			y_ = y + height;
		break;
	}

	rect->left = x_ - 4;
	rect->top = y_ - 4;
	rect->right = x_ + 5;
	rect->bottom = y_ + 5;
}

void Join::GetSelectionMarkerAllRegion( CRgn *region ){
	Long x_, y_;
	CRgn region1;
	x_ = x;
	y_ = y;
	region->CreateRectRgn( x_ - 5 , y_ - 5, x_ + 6, y_ + 6 );
	
	x_ = x + width/2;
	y_ = y + height2;
	region1.CreateRectRgn( x_ - 5 , y_ - 5, x_ + 6, y_ + 6 );
	region->CombineRgn(region,&region1,RGN_OR);
	region1.DeleteObject();

	x_ = x + width;
	y_ = y + height;
	region1.CreateRectRgn( x_ - 5 , y_ - 5, x_ + 6, y_ + 6 );
	region->CombineRgn(region,&region1,RGN_OR);
	region1.DeleteObject();
}

int Join::GetHitCode( Painter *painter, const CPoint& point, const CRgn& region ){
	int result = HIT_NONE;

	if( region.PtInRegion(point)){
		result = HIT_BODY;
	}

	CRect rectSelect;
	GetSelectionMarkerRect( HIT_TRUE, &rectSelect );
	if( rectSelect.PtInRect( point ) ) {
		result = HIT_TRUE;
	}

	GetSelectionMarkerRect( HIT_OUT, &rectSelect );
	if( rectSelect.PtInRect( point ) ) {
		result = HIT_OUT;
	}

	GetSelectionMarkerRect( HIT_FALSE, &rectSelect );
	if( rectSelect.PtInRect( point ) ) {
		result = HIT_FALSE;
	}
	return result;
}

void Join::DrawSelectionMarkers( CDC* dc, ScrollController *scrollController){
	CRect rectSelect;
	CBrush brush;
	CBrush *oldBrush;
	brush.CreateSolidBrush(RGB(0,0,255));
	oldBrush = dc->SelectObject(&brush);
			
	GetSelectionMarkerRect( HIT_TRUE, &rectSelect );
	Long positionX = scrollController->GetScroll(1)->GetPosition();
	Long positionY = scrollController->GetScroll(0)->GetPosition();
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

	GetSelectionMarkerRect( HIT_FALSE, &rectSelect );
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle( rectSelect );

	dc->SelectObject(oldBrush);
	brush.DeleteObject();
}

void Join::DrawSelectionMarkers( Painter* painter, ScrollController *scrollController){
	CRect rectSelect;

	painter->ChangePlaneProperty(BS_SOLID, RGB(0, 0, 255));
	
	GetSelectionMarkerRect( HIT_TRUE, &rectSelect );
	Long positionX = scrollController->GetScroll(1)->GetPosition();
	Long positionY = scrollController->GetScroll(0)->GetPosition();
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

	GetSelectionMarkerRect( HIT_FALSE, &rectSelect );
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle( rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom );
}

void Join::GetAttribute(Attribute *attribute){
	attribute->vertexOut = 'Y';	
	attribute->vertexTrue = 'Y';
	attribute->vertexFalse = 'Y';
	
	attribute->pointOut.x = x + width/2;
	attribute->pointOut.y = y + height2;

	attribute->pointTrue.x = x;
	attribute->pointTrue.y = y;	

	attribute->pointFalse.x = x + width;
	attribute->pointFalse.y = y + height;	
}

void Join::GetLine(char (*line)){
	sprintf(line,"%d\t%d\t%d\t%d\t%d\t\t%d\t%s\n", ID_JOIN,x,y,width,height,height2,contents);
}


bool Join::IsStyle(Long style){
	bool ret = false;
	if( Shape::IsStyle(style) || Line::IsStyle(style) || (style>>12)%2 ){
		ret = true;
	}
	return ret;
}