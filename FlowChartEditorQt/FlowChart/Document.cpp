/******************************************************************
* 파일 이름 : Document.cpp
* 기능 : 출력기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일 
*******************************************************************/

#include "Document.h"
#include "Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)
//#include <cmath>

Document::Document(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
:Symbol(x,y,width,height,backGroundColor,borderLine,borderColor,contents){
}

Document::~Document(){}

Document::Document(const Document& source):Symbol(source){
}

Document& Document::operator =(const Document& source){
	Symbol::operator=(source);
	return *this;
}

bool Document::IsEqual(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<Document *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Document::IsNotEqual(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<Document *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool Document::operator ==(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<Document *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Document::operator !=(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<Document *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}
/*
void Document::Draw(CDC* dc){
	CRgn region;	

	Long quarterWidth = (Long)width/4;
	Long thirdHeight = (Long)height/3;
	Long eighthHeight = (Long)height/8;

	POINT shapePoint[4] ={{x,y+height-eighthHeight},{x,y},{x+width,y},{x+width,y+height-eighthHeight}};

	CPoint bezierPoint[4];
	bezierPoint[0].x = x;
	bezierPoint[0].y = y+height-eighthHeight;
	bezierPoint[1].x = x+quarterWidth;
	bezierPoint[1].y = y+height+thirdHeight-eighthHeight;
	bezierPoint[2].x = x+width-quarterWidth;
	bezierPoint[2].y = y+height-thirdHeight-eighthHeight;
	bezierPoint[3].x = x+width;
	bezierPoint[3].y = y+height-eighthHeight;		

	dc->BeginPath();
	dc->Polyline(shapePoint,4);
	dc->PolyBezier(bezierPoint,4);
	dc->EndPath();

	region.CreateFromPath(dc);
	CBrush brush;	
	brush.CreateStockObject(LTGRAY_BRUSH);
	dc->FillRgn(&region,&brush);	
	dc->Polyline(shapePoint,4);
	dc->PolyBezier(bezierPoint,4);		

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

void Document::Draw(Painter *painter){
	CRgn region;	

	Long quarterWidth = (Long)width/4;
	Long thirdHeight = (Long)height/3;
	Long eighthHeight = (Long)height/8;

	POINT shapePoint[4] ={{x,y+height-eighthHeight},{x,y},{x+width,y},{x+width,y+height-eighthHeight}};

	CPoint bezierPoint[4];
	bezierPoint[0].x = x;
	bezierPoint[0].y = y+height-eighthHeight;
	bezierPoint[1].x = x+quarterWidth;
	bezierPoint[1].y = y+height+thirdHeight-eighthHeight;
	bezierPoint[2].x = x+width-quarterWidth;
	bezierPoint[2].y = y+height-thirdHeight-eighthHeight;
	bezierPoint[3].x = x+width;
	bezierPoint[3].y = y+height-eighthHeight;		

	painter->BeginPath();
	painter->DrawPolyline(shapePoint,4);
	painter->DrawBezier(bezierPoint,4);
	//painter->EndPath(&region);
	painter->EndPath();
	painter->CreateFromPath(&region);

	painter->FillRegion(region,LTGRAY_BRUSH);
	
	painter->DrawPolyline(shapePoint,4);
	painter->DrawBezier(bezierPoint,4);	

	
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
void Document::Accept(FlowChartVisitor *draw){
	draw->Visit(this);
}

Shape* Document::Clone(){
	return new Document(*this);
}
/*
void Document::GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom){
	Shape::GetFormattingArea(left, top, right, bottom);
}
*/
#if 0
void Document::GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom) {
	Long halfWidth = width / 2;
	Long halfHeight = height / 2;
	Long quarterHeight = halfHeight / 2;

	*left = x + quarterHeight;
	*top = y;
	*right = x + width - quarterHeight;
	*bottom = y + height;
}


void Document::GetFormattingArea(Long *left, Long *right) {
	Long halfHeight = height / 2;	

	*left = x + halfHeight;	
	*right = x + width - halfHeight;
}
#endif


void Document::GetRegion(CDC *dc, CRgn *region){
	Long quarterWidth = (Long)width/4;
	Long thirdHeight = (Long)height/3;
	Long eighthHeight = (Long)height/8;

	POINT shapePoint[4] = {{x,y+height-eighthHeight},{x,y},{x+width,y},{x+width,y+height-eighthHeight}};

	CPoint bezierPoint[4];
	bezierPoint[0].x = x;
	bezierPoint[0].y = y+height-eighthHeight;
	bezierPoint[1].x = x+quarterWidth;
	bezierPoint[1].y = y+height+thirdHeight-eighthHeight;
	bezierPoint[2].x = x+width-quarterWidth;
	bezierPoint[2].y = y+height-thirdHeight-eighthHeight;
	bezierPoint[3].x = x+width;
	bezierPoint[3].y = y+height-eighthHeight;	
	dc->BeginPath();
	dc->PolyBezier(bezierPoint,4);
	dc->Polyline(shapePoint,4);
	dc->EndPath();
	
	region->CreateFromPath(dc);
}

void Document::GetRegion(Painter *painter, CRgn *region){
	Long quarterWidth = (Long)width/4;
	Long thirdHeight = (Long)height/3;
	Long eighthHeight = (Long)height/8;	
	
	POINT shapePoint[4] = {{x,y+height-eighthHeight},{x,y},{x+width,y},{x+width,y+height-eighthHeight}};

	CPoint bezierPoint[4];
	bezierPoint[0].x = x;
	bezierPoint[0].y = y+height-eighthHeight;
	bezierPoint[1].x = x+quarterWidth;
	bezierPoint[1].y = y+height+thirdHeight-eighthHeight;
	bezierPoint[2].x = x+width-quarterWidth;
	bezierPoint[2].y = y+height-thirdHeight-eighthHeight;
	bezierPoint[3].x = x+width;
	bezierPoint[3].y = y+height-eighthHeight;	

	painter->BeginPath();
	painter->DrawBezier(bezierPoint,4);
	painter->DrawPolyline(shapePoint,4);
	//painter->EndPath(region);
	painter->EndPath();
	painter->CreateFromPath(region);
}

void Document::GetRegion(CDC *dc, Long thickness, CRgn *region){
	Long x_, y_, width_, height_;
	Long quarterWidth_, thirdHeight_, eighthHeight_;

	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness*2;
	height_ = height + thickness*2;

	quarterWidth_ = width_ /4;
	thirdHeight_ = height_ /3;
	eighthHeight_ = height_ /8;

	POINT shapePoint[4] = {{x_,y_+height_-eighthHeight_},{x_,y_},{x_+width_,y_},{x_+width_,y_+height_-eighthHeight_}};

	CPoint bezierPoint[4];
	bezierPoint[0].x = x_;
	bezierPoint[0].y = y_+height_-eighthHeight_;
	bezierPoint[1].x = x_+quarterWidth_;
	bezierPoint[1].y = y_+height_+thirdHeight_-eighthHeight_;
	bezierPoint[2].x = x_+width_-quarterWidth_;
	bezierPoint[2].y = y_+height_-thirdHeight_-eighthHeight_;
	bezierPoint[3].x = x_+width_;
	bezierPoint[3].y = y_+height_-eighthHeight_;

	dc->BeginPath();
	dc->PolyBezier(bezierPoint,4);
	dc->Polyline(shapePoint,4);
	dc->EndPath();
	
	region->CreateFromPath(dc);
}

void Document::GetRegion(Painter *painter, Long thickness, CRgn *region){
	Long x_, y_, width_, height_;
	Long quarterWidth_, thirdHeight_, eighthHeight_;

	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness*2;
	height_ = height + thickness*2;

	quarterWidth_ = width_ /4;
	thirdHeight_ = height_ /3;
	eighthHeight_ = height_ /8;

	POINT shapePoint[4] = {{x_,y_+height_-eighthHeight_},{x_,y_},{x_+width_,y_},{x_+width_,y_+height_-eighthHeight_}};

	CPoint bezierPoint[4];
	bezierPoint[0].x = x_;
	bezierPoint[0].y = y_+height_-eighthHeight_;
	bezierPoint[1].x = x_+quarterWidth_;
	bezierPoint[1].y = y_+height_+thirdHeight_-eighthHeight_;
	bezierPoint[2].x = x_+width_-quarterWidth_;
	bezierPoint[2].y = y_+height_-thirdHeight_-eighthHeight_;
	bezierPoint[3].x = x_+width_;
	bezierPoint[3].y = y_+height_-eighthHeight_;

	painter->BeginPath();
	painter->DrawBezier(bezierPoint,4);
	painter->DrawPolyline(shapePoint,4);
	//painter->EndPath(region);
	painter->EndPath();
	painter->CreateFromPath(region);
}

BOOL Document::IsIncluded(CDC *dc, POINT point){
	CRgn region;
	BOOL ret;
	Long quarterWidth = (Long)width/4;
	Long thirdHeight = (Long)height/3;
	Long eighthHeight = (Long)height/8;

	POINT shapePoint[4] ={{x,y+height-eighthHeight},{x,y},{x+width,y},{x+width,y+height-eighthHeight}};	
	POINT shapePoint2[4] = {{x,y+height-eighthHeight},{x,y},{x+width,y},{x+width,y+height-eighthHeight}};

	CPoint bezierPoint[4];
	bezierPoint[0].x = x;
	bezierPoint[0].y = y+height-eighthHeight;
	bezierPoint[1].x = x+quarterWidth;
	bezierPoint[1].y = y+height+thirdHeight-eighthHeight;
	bezierPoint[2].x = x+width-quarterWidth;
	bezierPoint[2].y = y+height-thirdHeight-eighthHeight;
	bezierPoint[3].x = x+width;
	bezierPoint[3].y = y+height-eighthHeight;	
	dc->BeginPath();
	dc->PolyBezier(bezierPoint,4);
	dc->Polyline(shapePoint2,4);
	dc->EndPath();
	
	region.CreateFromPath(dc);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Document::IsIncluded(Painter *painter, POINT point){
	CRgn region;
	BOOL ret;
	Long quarterWidth = (Long)width/4;
	Long thirdHeight = (Long)height/3;
	Long eighthHeight = (Long)height/8;

	POINT shapePoint[4] ={{x,y+height-eighthHeight},{x,y},{x+width,y},{x+width,y+height-eighthHeight}};	
	POINT shapePoint2[4] = {{x,y+height-eighthHeight},{x,y},{x+width,y},{x+width,y+height-eighthHeight}};

	CPoint bezierPoint[4];
	bezierPoint[0].x = x;
	bezierPoint[0].y = y+height-eighthHeight;
	bezierPoint[1].x = x+quarterWidth;
	bezierPoint[1].y = y+height+thirdHeight-eighthHeight;
	bezierPoint[2].x = x+width-quarterWidth;
	bezierPoint[2].y = y+height-thirdHeight-eighthHeight;
	bezierPoint[3].x = x+width;
	bezierPoint[3].y = y+height-eighthHeight;	
	painter->BeginPath();
	
	painter->DrawBezier(bezierPoint,4);
	painter->DrawPolyline(shapePoint2,4);
	painter->EndPath();
		
	painter->CreateFromPath(&region);	
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Document::IsIncluded(Painter *painter, const RECT& rect){
	CRgn region;
	BOOL ret;
	Long quarterWidth = (Long)width/4;
	Long thirdHeight = (Long)height/3;
	Long eighthHeight = (Long)height/8;

	POINT shapePoint[4] ={{x,y+height-eighthHeight},{x,y},{x+width,y},{x+width,y+height-eighthHeight}};	
	POINT shapePoint2[4] = {{x,y+height-eighthHeight},{x,y},{x+width,y},{x+width,y+height-eighthHeight}};

	CPoint bezierPoint[4];
	bezierPoint[0].x = x;
	bezierPoint[0].y = y+height-eighthHeight;
	bezierPoint[1].x = x+quarterWidth;
	bezierPoint[1].y = y+height+thirdHeight-eighthHeight;
	bezierPoint[2].x = x+width-quarterWidth;
	bezierPoint[2].y = y+height-thirdHeight-eighthHeight;
	bezierPoint[3].x = x+width;
	bezierPoint[3].y = y+height-eighthHeight;	
	painter->BeginPath();
	
	painter->DrawBezier(bezierPoint,4);
	painter->DrawPolyline(shapePoint2,4);
	painter->EndPath();
	
	painter->CreateFromPath(&region);	
	ret =  region.RectInRegion(&rect);
	region.DeleteObject();
	return ret;
}

void Document::GetAttribute(Attribute *attribute){
	attribute->vertexIn = 'Y';	
	attribute->vertexOut = 'Y';
	
	attribute->pointIn.x = x + width/2;
	attribute->pointIn.y = y;	

	attribute->pointOut.x = x + width/2;
	attribute->pointOut.y = y + height;
}

void Document::GetLine(char (*line)){
	String saveContents(contents);
	saveContents.Replace('\n', '\r');

	sprintf(line,"%d\t%d\t%d\t%d\t%d\t\t\t%s\n", ID_DOCUMENT,x,y,width,height, saveContents);
}

bool Document::IsStyle(Long style){
	bool ret = false;	
	if( Shape::IsStyle(style) || Symbol::IsStyle(style) || (style>>7)%2 ){
		ret = true;
	}
	return ret;
}

void Document::DrawSelectionMarkers( CDC* dc, ScrollController *scrollController){
	Shape::DrawSelectionMarkers(dc, scrollController);
}

void Document::DrawSelectionMarkers( Painter* painter, ScrollController *scrollController){
	Shape::DrawSelectionMarkers(painter, scrollController);
}