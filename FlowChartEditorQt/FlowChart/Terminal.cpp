/******************************************************************
* 파일 이름 : Terminal.cpp
* 기능 : 단말기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일 
*******************************************************************/

#include "Terminal.h"
#include "Painter.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)

Terminal::Terminal(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
:Symbol(x,y,width,height,backGroundColor,borderLine,borderColor,contents){
}

Terminal::~Terminal(){}

Terminal::Terminal(const Terminal& source):Symbol(source){
}

Terminal& Terminal::operator =(const Terminal& source){
	Symbol::operator=(source);
	return *this;
}

bool Terminal::IsEqual(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<Terminal *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Terminal::IsNotEqual(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<Terminal *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool Terminal::operator ==(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<Terminal *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Terminal::operator !=(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<Terminal *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

void Terminal::Accept(FlowChartVisitor *draw){
	draw->Visit(this);
}

Shape* Terminal::Clone(){
	return new Terminal(*this);
}

void Terminal::GetRegion(CDC *dc, CRgn *region){
	Long halfHeight = (Long)height/2;
	POINT points[5] = {{x+halfHeight,y},{x+width-halfHeight,y},{x+width-halfHeight,y+height},{x+halfHeight,y+height},{x+halfHeight,y}};	

	dc->BeginPath();
	dc->Arc(x,y,x+height,y+height,x+halfHeight,y,x+halfHeight,y+height);	
	dc->Arc(x+width-height,y,x+width,y+height,x+width-halfHeight,y+height,x+width-halfHeight,y);
	dc->Polygon(points,5);
	dc->EndPath();

	region->CreateFromPath(dc);
}

void Terminal::GetRegion(Painter *painter, CRgn *region){
	Long halfHeight = (Long)height/2;
	POINT points[5] = {{x+halfHeight,y},{x+width-halfHeight,y},{x+width-halfHeight,y+height},{x+halfHeight,y+height},{x+halfHeight,y}};	
	painter->BeginPath();
	painter->DrawArc(x,y,x+height,y+height,x+halfHeight,y,x+halfHeight,y+height);	
	painter->DrawArc(x+width-height,y,x+width,y+height,x+width-halfHeight,y+height,x+width-halfHeight,y);
	painter->DrawPolygon(points,5);
	painter->EndPath();
	painter->CreateFromPath(region);
}

void Terminal::GetRegion(CDC *dc, Long thickness, CRgn *region){
	Long x_, y_, width_, height_;
	Long halfHeight_;
	
	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness*2;
	height_ = height + thickness*2;
	halfHeight_ = height_ /2;

	POINT points[5] = {{x_+halfHeight_,y_},{x_+width_-halfHeight_,y_},{x_+width_-halfHeight_,y_+height_},{x_+halfHeight_,y_+height_},{x_+halfHeight_,y_}};	

	dc->BeginPath();
	dc->Arc(x_,y_,x_+height_,y_+height_,x_+halfHeight_,y_,x_+halfHeight_,y_+height_);	
	dc->Arc(x_+width_-height_,y_,x_+width_,y_+height_,x_+width_-halfHeight_,y_+height_,x_+width_-halfHeight_,y_);
	dc->Polygon(points,5);
	dc->EndPath();

	region->CreateFromPath(dc);
}

void Terminal::GetRegion(Painter *painter, Long thickness, CRgn *region){
	Long x_, y_, width_, height_;
	Long halfHeight_;
	
	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness*2;
	height_ = height + thickness*2;
	halfHeight_ = height_ /2;

	POINT points[5] = {{x_+halfHeight_,y_},{x_+width_-halfHeight_,y_},{x_+width_-halfHeight_,y_+height_},{x_+halfHeight_,y_+height_},{x_+halfHeight_,y_}};	

	painter->BeginPath();
	painter->DrawArc(x_,y_,x_+height_,y_+height_,x_+halfHeight_,y_,x_+halfHeight_,y_+height_);	
	painter->DrawArc(x_+width_-height_,y_,x_+width_,y_+height_,x_+width_-halfHeight_,y_+height_,x_+width_-halfHeight_,y_);
	painter->DrawPolygon(points,5);
	painter->EndPath();
	painter->CreateFromPath(region);
}

BOOL Terminal::IsIncluded(CDC *dc, POINT point){
	CRgn region;
	BOOL ret;
	Long halfHeight = (Long)height/2;
	POINT points[5] = {{x+halfHeight,y},{x+width-halfHeight,y},{x+width-halfHeight,y+height},{x+halfHeight,y+height},{x+halfHeight,y}};	

	dc->BeginPath();
	dc->Arc(x,y,x+height,y+height,x+halfHeight,y,x+halfHeight,y+height);	
	dc->Arc(x+width-height,y,x+width,y+height,x+width-halfHeight,y+height,x+width-halfHeight,y);
	dc->Polygon(points,5);
	dc->EndPath();

	
	region.CreateFromPath(dc);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Terminal::IsIncluded(Painter *painter, POINT point){
	CRgn region;
	BOOL ret;
	Long halfHeight = (Long)height/2;
	POINT points[5] = {{x+halfHeight,y},{x+width-halfHeight,y},{x+width-halfHeight,y+height},{x+halfHeight,y+height},{x+halfHeight,y}};	

	painter->BeginPath();
	painter->DrawArc(x,y,x+height,y+height,x+halfHeight,y,x+halfHeight,y+height);
	painter->DrawArc(x+width-height,y,x+width,y+height,x+width-halfHeight,y+height,x+width-halfHeight,y);
	painter->DrawPolygon(points,5);	
	painter->EndPath();	
	
	painter->CreateFromPath(&region);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Terminal::IsIncluded(Painter *painter, const RECT& rect){
	Long halfHeight = (Long)height/2;
	POINT points[5] = {{x+halfHeight,y},{x+width-halfHeight,y},{x+width-halfHeight,y+height},{x+halfHeight,y+height},{x+halfHeight,y}};	
	CRgn region;
	BOOL ret;

	painter->BeginPath();
	painter->DrawArc(x,y,x+height,y+height,x+halfHeight,y,x+halfHeight,y+height);
	painter->DrawArc(x+width-height,y,x+width,y+height,x+width-halfHeight,y+height,x+width-halfHeight,y);
	painter->DrawPolygon(points,5);	
	painter->EndPath();	
	
	painter->CreateFromPath(&region);
	ret = region.RectInRegion(&rect);
	region.DeleteObject();
	return ret;
}

void Terminal::GetAttribute(Attribute *attribute){
	attribute->vertexIn = 'Y';	
	attribute->vertexOut = 'Y';
	
	attribute->pointIn.x = x + width/2;
	attribute->pointIn.y = y;	

	attribute->pointOut.x = x + width/2;
	attribute->pointOut.y = y + height;
}

void Terminal::GetLine(char (*line)){
	String saveContents(contents);
	saveContents.Replace('\n', '\r');

	sprintf(line,"%d\t%d\t%d\t%d\t%d\t\t\t%s\n", ID_TERMINAL,x,y,width,height,saveContents);
}

bool Terminal::IsStyle(Long style){
	bool ret = false;
	if( Shape::IsStyle(style) || Symbol::IsStyle(style) || (style>>2)%2 ){
		ret = true;
	}
	return ret;
}

void Terminal::DrawSelectionMarkers( CDC* dc, ScrollController *scrollController){
	Shape::DrawSelectionMarkers(dc, scrollController);
}

void Terminal::DrawSelectionMarkers( Painter* painter, ScrollController *scrollController){
	Shape::DrawSelectionMarkers(painter, scrollController);
}