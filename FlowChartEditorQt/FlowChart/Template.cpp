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

Template::Template(Long capacity):templates(capacity){
	this->capacity = capacity;
	this->length = 0;
}

Template::~Template(){
	Long  i = 0;

	Shape *template_;
	while(i < this->templates.GetLength()){
		template_ = this->templates.GetAt(i);

		if(template_ != 0){
			delete template_;
			template_ = 0;
		}
		i++;
	}
}

Template::Template(const Template& source):templates(source.capacity){
	Shape *template_;	
	Shape *temp;
	
	this->length = 0;
	this->capacity = source.GetCapacity();

	for(int i = 0; i < source.GetLength(); i++){
		template_ = const_cast<Template&>(source).GetAt(i);

		temp = template_->Clone();

		this->templates.Store(i,temp);
		this->length++;
	}
}

Long Template::Register(Shape *shape){	
	Long index = -1;
	if(this->length < this->capacity) {
		index = this->templates.Store(this->length,shape);
	}
	else {
		index = this->templates.AppendFromRear(shape);
		this->capacity += 1;
	}
	this->length++;
	return index;
}

Long Template::UnRegister(Long index){
	Shape* template_;
	Long index_;
	if( index >= 0 && index < this->GetLength()){

		template_ = this->templates.GetAt(index);

		delete template_;
		
		index_ = this->templates.Delete(index);
		this->length--;
	}
	return index_;
}

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

void Template::Clear(){
	Shape *template_;

	for(int j = 0; this->GetLength(); j++){
		template_ = this->templates.GetAt(j);
		if(template_ != 0){
			delete template_;
			template_ = 0;
		}
	}

	this->templates.Clear();
	this->capacity = 0;
	this->length = 0;
}

Template& Template::operator =(const Template& source){
	Shape *template_;
	Shape *temp;	

	this->capacity = source.GetCapacity();
	this->length = 0;

	for(int j = 0; this->GetLength(); j++){
		template_ = this->templates.GetAt(j);
		if(template_ != 0){
			delete template_;
			template_ = 0;
		}
	}

	this->templates = source.templates;	

	for(int i = 0; i < source.GetLength(); i++){
		this->templates.Delete(i);

		template_ = const_cast<Template&>(source).GetAt(i);

		temp = template_->Clone();

		temp->Move(template_->GetX(),template_->GetY());
		temp->ReSize(template_->GetWidth(),template_->GetHeight());
		temp->Paint(template_->GetBackGroundColor(),template_->GetBorderLine(),template_->GetBorderColor());

		this->templates.Store(i,temp);
		this->length++;
	}	
	return *this;	
}

Shape* Template::GetAt(Long index){
	return this->templates.GetAt(index);
}

Long Template::Find(CDC *dc, CPoint point){
	Long index = -1;
	Long i = 0;
	BOOL ret;
	Shape *shape;
	while( i < length){
		shape = this->templates[i];
		ret = shape->IsIncluded(dc, point);
		if( ret ){
			index = i;
		}
		i++;
	}
	return index;
}

void Template::Accept(FlowChartVisitor *draw){
	draw->Visit(this);
}

Shape* Template::Clone(){
	return new Template (*this);
}