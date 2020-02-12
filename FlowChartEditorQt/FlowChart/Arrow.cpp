/******************************************************************
* 파일 이름 : Arrow.cpp
* 기능 : 연결선 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일 
*******************************************************************/

#include "Arrow.h"
#include "Painter.h"
#pragma warning (disable : 4996)
#include "FlowChartVisitor.h"

#include "ScrollController.h"
#include "Scrolls.h"

Arrow::Arrow(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
:Line(x,y,width,height,backGroundColor,borderLine,borderColor,contents){
}

Arrow::~Arrow(){}

Arrow::Arrow(const Arrow& source):Line(source){
}

Arrow& Arrow::operator =(const Arrow& source){
	Line::operator=(source);
	return *this;
}

bool Arrow::IsEqual(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<Arrow *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Arrow::IsNotEqual(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<Arrow *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool Arrow::operator ==(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<Arrow *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Arrow::operator !=(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<Arrow *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}
/*
void Arrow::Draw(CDC* dc){

	dc->MoveTo(x,y);
	dc->LineTo(x,y+height-6);

	POINT arrow[4];
	
	arrow[0].x = x - 2;
	arrow[0].y = y+height - 8;
	arrow[1].x = x;
	arrow[1].y = y+height - 6;
	arrow[2].x = x +2;
	arrow[2].y = y+height - 8;
	arrow[3].x = x;
	arrow[3].y = y+height - 4;
	dc->Polygon(arrow,4);

	CRgn region;
	region.CreatePolygonRgn(arrow,4,ALTERNATE);
	dc->PaintRgn(&region);
	region.DeleteObject();

	// 텍스트를 출력한다.
	Long left, top, right, bottom;

	GetFormattingArea(&left, &top, &right, &bottom);
	RECT rect = { left , top, right, bottom };

	dc->DrawText( contents.operator char *(), -1, &rect, DT_CENTER );
	
	if(this->isSelected == true){
		DrawSelectionMarkers(dc);
	}
}

void Arrow::Draw(Painter *painter){	

	painter->DrawLine(x,y,x,y+height - 4);
	
	CPoint arrow[4];
	arrow[0].x = x - 2;
	arrow[0].y = y+height - 6;
	arrow[1].x = x;
	arrow[1].y = y+height - 4;
	arrow[2].x = x + 2;
	arrow[2].y = y+height - 6;
	arrow[3].x = x;
	arrow[3].y = y+height - 2;
	painter->DrawPolygon(arrow,4);
	painter->FillPolygon(arrow,4,RGB(166,166,166));

	
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
void Arrow::Accept(FlowChartVisitor *draw){
	draw->Visit(this);
}

void Arrow::DrawActiveShape(CDC *dc){
	dc->MoveTo(x,y);
	dc->LineTo(x+width,y+height);
}

void Arrow::DrawActiveShape(Painter *painter){
	painter->DrawLine(x,y,x+width,y+height);
}
/*
void Arrow::GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom){
	HWND hWnd = ::GetActiveWindow();
	CWnd *cWnd = CWnd::FromHandle(hWnd);
	Formatter *formatter = new Formatter(cWnd);
	RECT rect;
	formatter->GetFormattingArea( contents.operator char *(), &rect );	
	
	*left = x + 10;
	*top = y + 5;
	
	*right = *left + rect.right;
	*bottom = *top + rect.bottom;
	delete formatter;
}
*/
Shape* Arrow::Clone(){
	return new Arrow(*this);
}

void Arrow::GetRegion(CDC *dc, CRgn *region){
	region->CreateRectRgn(x-LINETHICKNESS,y,x+LINETHICKNESS,y+height);	
}

void Arrow::GetRegion(Painter *painter, CRgn *region){
	region->CreateRectRgn(x-LINETHICKNESS,y,x+LINETHICKNESS,y+height);
}

void Arrow::GetRegion(CDC *dc, Long thickness, CRgn *region){
	region->CreateRectRgn(x-thickness,y,x+thickness,y+height);	
}

void Arrow::GetRegion(Painter *painter, Long thickness, CRgn *region){
	region->CreateRectRgn(x-thickness,y,x+thickness,y+height);
}

BOOL Arrow::IsIncluded(CDC *dc, POINT point){
	CRgn region;
	BOOL ret;
	region.CreateRectRgn(x-LINETHICKNESS,y,x+LINETHICKNESS,y+height);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Arrow::IsIncluded(Painter *painter, POINT point){
	CRgn region;
	BOOL ret;
	region.CreateRectRgn(x-LINETHICKNESS,y,x+LINETHICKNESS,y+height);	
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Arrow::IsIncluded(Painter *painter, const RECT& rect){
	CRgn region;
	BOOL ret;

	region.CreateRectRgn(x-LINETHICKNESS,y,x+LINETHICKNESS,y+height);	
	ret = region.RectInRegion(&rect);
	region.DeleteObject();
	return ret;
}

int Arrow::GetHitCode( Painter *painter, const CPoint& point, const CRgn& region ){
	int result = HIT_NONE;
	if( region.PtInRegion(point)){
		result = HIT_BODY;
	}
	CRect rectSelect;
	GetSelectionMarkerRect( HIT_IN, &rectSelect );
	if( rectSelect.PtInRect( point ) ) {
		result = HIT_IN;
	}
	GetSelectionMarkerRect( HIT_OUT, &rectSelect );
	if( rectSelect.PtInRect( point ) ) {
		result = HIT_OUT;
	}
	return result;
}

void Arrow::GetSelectionMarkerRect( UINT marker, CRect *rect ){
	int x_;
	int y_;

	switch (marker) {
		case HIT_IN: // 매크로 LEFTTOP
			x_ = x;
			y_ = y;
		break;

		case HIT_OUT:
			x_ = x;
			y_ = y + height;
		break;
	}

	rect->left = x_ - 4;
	rect->top = y_ - 4;
	rect->right = x_ + 5;
	rect->bottom = y_ + 5;
}

void Arrow::GetSelectionMarkerAllRegion( CRgn *region ){
	Long x_, y_;
	CRgn region1;
	x_ = x;
	y_ = y;
	//region->CreateRectRgn( x_ - 4 , y_ - 4, x_ + 5, y_ + 5 );
	region->CreateRectRgn( x_ - 6 , y_ - 6, x_ + 7, y_ + 7 );
	
	x_ = x;
	y_ = y + height;
	//region1.CreateRectRgn( x_ - 4 , y_ - 4, x_ + 5, y_ + 5 );
	region1.CreateRectRgn( x_ - 6 , y_ - 6, x_ + 7, y_ + 7 );
	region->CombineRgn(region,&region1,RGN_OR);
	region1.DeleteObject();
}

void Arrow::DrawSelectionMarkers( CDC* dc, ScrollController *scrollController){
	CRect rectSelect;
	CBrush brush;
	CBrush *oldBrush;
	//dc->SelectStockObject( BLACK_BRUSH );
	brush.CreateSolidBrush(RGB(0,0,255));
	oldBrush = dc->SelectObject( &brush );
			
	GetSelectionMarkerRect( HIT_IN, &rectSelect );
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

	dc->SelectObject( oldBrush );
	brush.DeleteObject();
}

void Arrow::DrawSelectionMarkers( Painter* painter, ScrollController *scrollController){
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

	GetSelectionMarkerRect( HIT_OUT, &rectSelect );
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle( rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom );
}

void Arrow::GetAttribute(Attribute *attribute){
	attribute->vertexIn = 'Y';	
	attribute->vertexOut = 'Y';
	
	attribute->pointIn.x = x;
	attribute->pointIn.y = y;	

	attribute->pointOut.x = x;
	attribute->pointOut.y = y + height;
}

void Arrow::GetLine(char (*line)){
	sprintf(line,"%d\t%d\t%d\t%d\t%d\t\t\t%s\n", ID_ARROW,x,y,width,height,contents);
}

bool Arrow::IsStyle(Long style){
	bool ret = false;	
	if( Shape::IsStyle(style) || Line::IsStyle(style) || (style>>9)%2 ){
		ret = true;
	}
	return ret;
}