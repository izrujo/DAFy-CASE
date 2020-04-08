/******************************************************************
* 파일 이름 : Template.cpp
* 기능 : 순서도 작성자 컨트롤 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 4월 13일
*******************************************************************/
#include "Template.h"
#include "Terminal.h"
#include "Decision.h"
#include "FlowChartVisitor.h"

/*
Long CompareCoordinateForTemplate(void *one, void *other){
	Shape *one_ = *(static_cast<Shape**>(one));
	Shape *other_ = static_cast<Shape*>(other);
	Long ret =-1;
	Long top;
	Long buttom;
	Long left;
	Long right;

	if(one_->GetWidth() >= 0){
		left = one_->GetX();
		right = one_->GetX() + one_->GetWidth();
	}
	else{
		right = one_->GetX();
		left = one_->GetX() - one_->GetWidth();
	}

	if(one_->GetHeight() >= 0){
		top = one_->GetY();
		buttom = one_->GetY() + one_->GetHeight();
	}
	else{
		buttom = one_->GetY();
		top = one_->GetY() - one_->GetHeight();
	}

	if( left <= other_->GetX() && other_->GetX() <= right &&
		top <= other_->GetY() && other_->GetY() <= buttom){
		ret = 0;
	}

	return ret;
}
*/ //왜있는걸까?

Template::Template(Long capacity)
	: Block(capacity) {

}

Template::~Template() {

}

Template::Template(const Template& source)
	: Block(source) {

}

Template& Template::operator =(const Template& source) {
	Block::operator=(source);

	return *this;
}

void Template::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* Template::Clone() {
	return new Template(*this);
}