 /******************************************************************
* 파일 이름 : PunchedCard.cpp
* 기능 : 입력기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일 
*******************************************************************/

#include "PunchedCard.h"
#include "Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

PunchedCard::PunchedCard(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
:Symbol(x,y,width,height,backGroundColor,borderLine,borderColor,contents){
}

PunchedCard::~PunchedCard(){};

PunchedCard::PunchedCard(const PunchedCard& source):Symbol(source){
}

PunchedCard& PunchedCard::operator =(const PunchedCard& source){
	Symbol::operator=(source);
	return *this;
}

bool PunchedCard::IsEqual(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<PunchedCard *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool PunchedCard::IsNotEqual(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<PunchedCard *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool PunchedCard::operator ==(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<PunchedCard *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool PunchedCard::operator !=(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<PunchedCard *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}
/*
void PunchedCard::Draw(CDC* dc){
	CRgn region;
	CBrush brush;
	Long gap = (Long)height/4;
	POINT shapePoint[6] ={{x+gap,y},{x+width,y},{x+width,y+height},{x,y+height},{x,y+gap},{x+gap,y}};	

	region.CreatePolygonRgn(shapePoint, 6, WINDING);	
	
	brush.CreateStockObject(LTGRAY_BRUSH);
	dc->FillRgn(&region, &brush);	
	dc->Polyline(shapePoint,6);

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

void PunchedCard::Draw(Painter *painter){
	Long gap = (Long)height/4;
	POINT shapePoint[6] ={{x+gap,y},{x+width,y},{x+width,y+height},{x,y+height},{x,y+gap},{x+gap,y}};
	
	painter->FillBackground(shapePoint,6,LTGRAY_BRUSH);

	painter->DrawPolyline(shapePoint,6);

	
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
void PunchedCard::Accept(FlowChartVisitor *draw){
	draw->Visit(this);
}

Shape* PunchedCard::Clone(){
	return new PunchedCard(*this);
}
/*
void PunchedCard::GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom){
	Shape::GetFormattingArea(left, top, right, bottom);
}
*/
#if 0
void PunchedCard::GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom) {
	Long halfWidth = width / 2;
	Long halfHeight = height / 2;
	Long quarterHeight = halfHeight / 2;

	*left = x + quarterHeight;
	*top = y;
	*right = x + width - quarterHeight;
	*bottom = y + height;
}

void PunchedCard::GetFormattingArea(Long *left, Long *right) {
	Long halfHeight = height / 2;	

	*left = x + halfHeight;	
	*right = x + width - halfHeight;
}
#endif

void PunchedCard::GetRegion(CDC *dc, CRgn *region){
	Long gap = (Long)height/4;
	POINT shapePoint[6] ={{x+gap,y},{x+width,y},{x+width,y+height},{x,y+height},{x,y+gap},{x+gap,y}};

	region->CreatePolygonRgn(shapePoint, 6, WINDING);
}

void PunchedCard::GetRegion(Painter *painter, CRgn *region){
	Long gap = (Long)height/4;
	POINT shapePoint[6] ={{x+gap,y},{x+width,y},{x+width,y+height},{x,y+height},{x,y+gap},{x+gap,y}};

	region->CreatePolygonRgn(shapePoint, 6, WINDING);  
}

void PunchedCard::GetRegion(CDC *dc, Long thickness, CRgn *region){
	Long x_, y_, width_, height_;
	Long gap_;
	
	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness*2;
	height_ = height +thickness*2;
	gap_ = height_/4;

	POINT shapePoint[6] ={{x_+gap_,y_},{x_+width_,y_},{x_+width_,y_+height_},{x_,y_+height_},{x_,y_+gap_},{x_+gap_,y_}};
	region->CreatePolygonRgn(shapePoint, 6, WINDING);
}

void PunchedCard::GetRegion(Painter *painter, Long thickness, CRgn *region){
	Long x_, y_, width_, height_;
	Long gap_;
	
	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness*2;
	height_ = height +thickness*2;
	gap_ = height_/4;

	POINT shapePoint[6] ={{x_+gap_,y_},{x_+width_,y_},{x_+width_,y_+height_},{x_,y_+height_},{x_,y_+gap_},{x_+gap_,y_}};
	region->CreatePolygonRgn(shapePoint, 6, WINDING);
}

BOOL PunchedCard::IsIncluded(CDC *dc, POINT point){
	Long gap = (Long)height/4;
	POINT shapePoint[6] ={{x+gap,y},{x+width,y},{x+width,y+height},{x,y+height},{x,y+gap},{x+gap,y}};
	CRgn region;
	BOOL ret;
	region.CreatePolygonRgn(shapePoint, 6, WINDING);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL PunchedCard::IsIncluded(Painter *painter, POINT point){
	Long gap = (Long)height/4;
	POINT shapePoint[6] ={{x+gap,y},{x+width,y},{x+width,y+height},{x,y+height},{x,y+gap},{x+gap,y}};

	CRgn region;
	BOOL ret;
	
	region.CreatePolygonRgn(shapePoint, 6, WINDING);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	
	return ret;
}

BOOL PunchedCard::IsIncluded(Painter *painter, const RECT& rect){
	Long gap = (Long)height/4;
	POINT shapePoint[6] ={{x+gap,y},{x+width,y},{x+width,y+height},{x,y+height},{x,y+gap},{x+gap,y}};

	CRgn region;
	BOOL ret;
	
	region.CreatePolygonRgn(shapePoint, 6, WINDING);
	ret = region.RectInRegion(&rect);
	region.DeleteObject();
	return ret;
}

void PunchedCard::GetAttribute(Attribute *attribute){
	attribute->vertexIn = 'Y';	
	attribute->vertexOut = 'Y';
	
	attribute->pointIn.x = x + width/2;
	attribute->pointIn.y = y;	

	attribute->pointOut.x = x + width/2;
	attribute->pointOut.y = y + height;
}

void PunchedCard::GetLine(char (*line)){
	String saveContents(contents);
	saveContents.Replace('\n', '\r');

	sprintf(line,"%d\t%d\t%d\t%d\t%d\t\t\t%s\n", ID_PUNCHEDCARD,x,y,width,height,contents);
}

bool PunchedCard::IsStyle(Long style){
	bool ret = false;
	if( Shape::IsStyle(style) || Symbol::IsStyle(style) || (style>>4)%2 ){
		ret = true;
	}
	return ret;
}

void PunchedCard::DrawSelectionMarkers( CDC* dc, ScrollController *scrollController ){
	Shape::DrawSelectionMarkers(dc, scrollController);
}

void PunchedCard::DrawSelectionMarkers( Painter* painter, ScrollController *scrollController ){
	Shape::DrawSelectionMarkers(painter, scrollController);
}

