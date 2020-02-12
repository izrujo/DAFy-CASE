/******************************************************************
* 파일 이름 : Preparation.cpp
* 기능 : 준비기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 30일 
*******************************************************************/

#include "Preparation.h"
#include "Painter.h"
#include "Preparation.h"
#include "FlowChartVisitor.h"
#pragma warning (disable : 4996)


Preparation::Preparation(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
:Symbol(x,y,width,height,backGroundColor,borderLine,borderColor,contents){
}

Preparation::~Preparation(){}

Preparation::Preparation(const Preparation& source):Symbol(source){
}

Preparation Preparation::operator =(const Preparation& source){
	Symbol::operator=(source);
	return *this;
}

bool Preparation::IsEqual(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<Preparation *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Preparation::IsNotEqual(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<Preparation *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool Preparation::operator ==(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<Preparation *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool Preparation::operator !=(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<Preparation *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

void Preparation::Accept(FlowChartVisitor *draw){
	draw->Visit(this);	
}

Shape* Preparation::Clone(){
	return new Preparation(*this);
}

void Preparation::GetRegion(CDC *dc, CRgn *region){
	Long gap = (Long)height/2;
	POINT shapePoints[7] ={{x+gap,y},{x+width-gap,y},{x+width,y+gap},{x+width-gap,y+height},{x+gap,y+height},{x,y+gap},{x+gap,y}};
	region->CreatePolygonRgn(shapePoints,7,WINDING);
}

void Preparation::GetRegion(Painter *painter, CRgn *region){
	Long gap = (Long)height/2;
	POINT shapePoints[7] ={{x+gap,y},{x+width-gap,y},{x+width,y+gap},{x+width-gap,y+height},{x+gap,y+height},{x,y+gap},{x+gap,y}};
	region->CreatePolygonRgn(shapePoints,7,WINDING);
}

void Preparation::GetRegion(CDC *dc, Long thickness, CRgn *region){
	Long x_, y_, width_, height_;
	Long gap_;

	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness*2;
	height_ = height + thickness*2;
	gap_ = height_/2;

	POINT shapePoints[7] ={{x_+gap_,y_},{x_+width_-gap_,y_},{x_+width_,y_+gap_},{x_+width_-gap_,y_+height_},{x_+gap_,y_+height_},{x_,y_+gap_},{x_+gap_,y_}};
	region->CreatePolygonRgn(shapePoints,7,WINDING);
}

void Preparation::GetRegion(Painter *painter, Long thickness, CRgn *region){
	Long x_, y_, width_, height_;
	Long gap_;

	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness*2;
	height_ = height + thickness*2;
	gap_ = height_/2;

	POINT shapePoints[7] ={{x_+gap_,y_},{x_+width_-gap_,y_},{x_+width_,y_+gap_},{x_+width_-gap_,y_+height_},{x_+gap_,y_+height_},{x_,y_+gap_},{x_+gap_,y_}};
	region->CreatePolygonRgn(shapePoints,7,WINDING);
}

BOOL Preparation::IsIncluded(CDC *dc, POINT point){
	CRgn region;
	BOOL ret;
	Long gap = (Long)height/2;
	POINT shapePoints[7] ={{x+gap,y},{x+width-gap,y},{x+width,y+gap},{x+width-gap,y+height},{x+gap,y+height},{x,y+gap},{x+gap,y}};	
	
	region.CreatePolygonRgn(shapePoints,7,WINDING);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Preparation::IsIncluded(Painter *painter, POINT point){
	CRgn region;
	BOOL ret;
	Long gap = (Long)height/2;
	POINT shapePoints[7] ={{x+gap,y},{x+width-gap,y},{x+width,y+gap},{x+width-gap,y+height},{x+gap,y+height},{x,y+gap},{x+gap,y}};	
	
	region.CreatePolygonRgn(shapePoints,7,WINDING);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL Preparation::IsIncluded(Painter *painter, const RECT& rect){
	CRgn region;
	BOOL ret;
	Long gap = (Long)height/2;
	POINT shapePoints[7] ={{x+gap,y},{x+width-gap,y},{x+width,y+gap},{x+width-gap,y+height},{x+gap,y+height},{x,y+gap},{x+gap,y}};
	
	region.CreatePolygonRgn(shapePoints,7,WINDING);
	ret = region.RectInRegion(&rect);
	region.DeleteObject();
	return ret;
}

void Preparation::GetAttribute(Attribute *attribute){
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';
	
	attribute->pointIn.x = x + width/2;
	attribute->pointIn.y = y;
	
	attribute->pointOut.x = x + width/2;
	attribute->pointOut.y = y + height;
}

void Preparation::GetLine(char (*line)){
	String saveContents(contents);
	saveContents.Replace('\n', '\r');

	sprintf(line,"%d\t%d\t%d\t%d\t%d\t\t\t%s\n", ID_PREPARATION,x,y,width,height,saveContents);
}


bool Preparation::IsStyle(Long style){
	bool ret = false;
	if( Shape::IsStyle(style) || Symbol::IsStyle(style) || (style>>3)%2 ){
		ret = true;
	}
	return ret;
}

void Preparation::DrawSelectionMarkers( CDC* dc, ScrollController *scrollController){
	Shape::DrawSelectionMarkers(dc, scrollController);
}

void Preparation::DrawSelectionMarkers( Painter* painter, ScrollController *scrollController){
	Shape::DrawSelectionMarkers(painter, scrollController);
}