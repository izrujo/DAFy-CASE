// InputOutput.cpp

/******************************************************************
* 파일 이름 : InputOutput.cpp
* 기능 : 입력출력기호의 콘크리트 클래스
* 작성자 : 송윤창
* 작성일자 : 2016년 2월 22일 
*******************************************************************/

#include "InputOutput.h"
#include "Painter.h"
#include "FlowChartVisitor.h"

#pragma warning (disable : 4996)

InputOutput::InputOutput(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
:Symbol(x,y,width,height,backGroundColor,borderLine,borderColor,contents){
}

InputOutput::~InputOutput(){}

InputOutput::InputOutput(const InputOutput& source):Symbol(source){}

InputOutput& InputOutput::operator=(const InputOutput& source){
	Symbol::operator=(source);
	return *this;
}

bool InputOutput::IsEqual(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<InputOutput *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool InputOutput::IsNotEqual(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<InputOutput *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

bool InputOutput::operator ==(const Shape& other){
	bool retVo = false;
	if( dynamic_cast<InputOutput *>(const_cast<Shape *>(&other)) ){
		retVo = Shape::IsEqual(other);
	}
	return retVo;
}

bool InputOutput::operator !=(const Shape& other){
	bool retVo = false;
	if( !dynamic_cast<InputOutput *>(const_cast<Shape*>(&other)) ){
		retVo = Shape::IsNotEqual(other);
	}
	return retVo;
}

void InputOutput::Accept(FlowChartVisitor *draw){
	draw->Visit(this);
}

Shape* InputOutput::Clone(){
	return new InputOutput(*this);
}

void InputOutput::GetRegion(CDC *dc, CRgn *region){
	Long halfWidth = (Long)width/2;
	Long halfHeight = (Long)height/2;	
	POINT points[5] = {{x+halfHeight,y},{x+width,y},{x+width-halfHeight,y+height},{x,y+height},{x+halfHeight,y}};
	region->CreatePolygonRgn(points,5,WINDING);
}

void InputOutput::GetRegion(Painter *painter, CRgn *region){
	Long halfWidth = (Long)width/2;
	Long halfHeight = (Long)height/2;	
	POINT points[5] = {{x+halfHeight,y},{x+width,y},{x+width-halfHeight,y+height},{x,y+height},{x+halfHeight,y}};
	region->CreatePolygonRgn(points,5,WINDING);
}

void InputOutput::GetRegion(CDC *dc, Long thickness, CRgn *region){
	Long x_, y_, width_, height_;
	Long halfWidth_, halfHeight_;
	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness*2;
	height_ = height + thickness*2;
	halfWidth_ = width_/2;
	halfHeight_ = height_/2;
	
	POINT points[5] = {{x_+halfHeight_,y_},{x_+width_,y_},{x_+width_-halfHeight_,y_+height_},{x_,y_+height_},{x_+halfHeight_,y_}};
	region->CreatePolygonRgn(points,5,WINDING);
}

void InputOutput::GetRegion(Painter *painter, Long thickness, CRgn *region){
	Long x_, y_, width_, height_;
	Long halfWidth_, halfHeight_;
	x_ = x - thickness;
	y_ = y - thickness;
	width_ = width + thickness*2;
	height_ = height + thickness*2;
	halfWidth_ = width_/2;
	halfHeight_ = height_/2;
	
	POINT points[5] = {{x_+halfHeight_,y_},{x_+width_,y_},{x_+width_-halfHeight_,y_+height_},{x_,y_+height_},{x_+halfHeight_,y_}};
	region->CreatePolygonRgn(points,5,WINDING);
}

BOOL InputOutput::IsIncluded(CDC *dc, POINT point){
	CRgn region;
	BOOL ret;
	Long halfWidth = (Long)width/2;
	Long halfHeight = (Long)height/2;	
	POINT points[5] = {{x+halfHeight,y},{x+width,y},{x+width-halfHeight,y+height},{x,y+height},{x+halfHeight,y}};
	
	region.CreatePolygonRgn(points,5,WINDING);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL InputOutput::IsIncluded(Painter *painter, POINT point){
	CRgn region;
	BOOL ret;
	Long halfWidth = (Long)width/2;
	Long halfHeight = (Long)height/2;	
	POINT points[5] = {{x+halfHeight,y},{x+width,y},{x+width-halfHeight,y+height},{x,y+height},{x+halfHeight,y}};
	
	region.CreatePolygonRgn(points,5,WINDING);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}

BOOL InputOutput::IsIncluded(Painter *painter, const RECT& rect){
	CRgn region;
	BOOL ret;
	Long halfWidth = (Long)width/2;
	Long halfHeight = (Long)height/2;	
	POINT points[5] = {{x+halfHeight,y},{x+width,y},{x+width-halfHeight,y+height},{x,y+height},{x+halfHeight,y}};

	region.CreatePolygonRgn(points,5,WINDING);
	ret = region.RectInRegion(&rect);
	region.DeleteObject();
	return ret;
}

void InputOutput::GetAttribute(Attribute *attribute){
	attribute->vertexIn = 'Y';
	attribute->vertexOut = 'Y';	
	
	attribute->pointIn.x = x + width/2;
	attribute->pointIn.y = y;

	attribute->pointOut.x = x + width/2;
	attribute->pointOut.y = y + height;
}

void InputOutput::GetLine(char (*line)){
	String saveContents(contents);
	saveContents.Replace('\n', '\r');

	sprintf(line,"%d\t%d\t%d\t%d\t%d\t\t\t%s\n", ID_INPUTOUTPUT,x,y,width,height,saveContents);
}

bool InputOutput::IsStyle(Long style){
	bool ret = false;
	if( Shape::IsStyle(style) || Symbol::IsStyle(style) || (style>>8)%2 ){
		ret = true;
	}
	return ret;
}

void InputOutput::DrawSelectionMarkers( CDC* dc, ScrollController *scrollController){
	Shape::DrawSelectionMarkers(dc, scrollController);
}

void InputOutput::DrawSelectionMarkers( Painter* painter, ScrollController *scrollController){
	Shape::DrawSelectionMarkers(painter, scrollController);
}