/******************************************************************
* 파일 이름 : FlowChart.cpp
* 기능 : 순서도 컨트롤 클래스
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 31일
*******************************************************************/

#include "FlowChart.h"
#include "Shape.h"

#include "Symbol.h"
#include "Line.h"

#include "Decision.h"
#include "Preparation.h"
#include "Process.h"
#include "Terminal.h"

#include "Arrow.h"
#include "Join.h"
#include "LeftDown.h"
#include "RepeatFalse.h"
#include "RepeatTrue.h"
#include "RightDown.h"
#include "RightDownJoin.h"
#include "InputOutput.h"

#include "DrawVisitor.h"

#if 0
#include <stdio.h>
#pragma warning (disable:4996)
#include "../GObject/Painter.h"

#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	FlowChart flowChart;
	NShape *shape1 = new Terminal(100, 100, 100, 100, 20, DASH, 20, "Symbol");
	NShape *shape2 = new Arrow(100, 100, 0, 100, 20, DASH, 20, "Arrow");
	NShape *shape3 = new LeftDown(100, 100, 100, 100, 20, DASH, 20, "LeftDown");
	NShape *shape4 = new Join(100, 100, 100, 100, -130, 20, DASH, 20, "Join-Right");
	NShape *shape5 = new Join(100, 100, 100, 100, -70, 20, DASH, 20, "Join-Left");
	NShape *shape6 = new RightDownJoin(100, 100, 100, 30, 30, 30, 20, DASH, 20, "RightDownJoin");
	NShape *shape7 = new RepeatTrue(5, 50, 100, 30, 30, 30, 20, DASH, 20, "RepeatTrue");
	NShape *shape8 = new RepeatFalse(5, 50, 100, 30, 30, 30, 20, DASH, 20, "RepeatFalse");

	flowChart.Attach(shape1);
	flowChart.Attach(shape2);
	flowChart.Attach(shape3);
	flowChart.Attach(shape4);
	flowChart.Attach(shape5);

	NShape *shape = flowChart.GetAt(0);
	flowChart.Move(flowChart.GetLength() - 1, shape);

	Long i;
	cout << "=======================================" << endl;
	for (i = 0; i < flowChart.GetLength(); i++) {
		cout << flowChart.GetAt(i)->GetX() << "   " << flowChart.GetAt(i)->GetY() << endl;
	}
	cout << "=======================================" << endl;

	return 0;
}
#endif 

//Long CompareShapeAddress(void *one, void *other);
/*
Long CompareShapeAddress(void *one, void *other) {
	Shape *one_ = *(static_cast<Shape * (*)>(one));
	Shape *other_ = static_cast<Shape *>(other);
	return (*one_ == *other_) ? (0) : (-1);
}
*/
/*
Long CompareCoordinateForFlowChart(void *one, void *other) {
	Shape *one_ = *(static_cast<Shape**>(one));
	Shape *other_ = static_cast<Shape*>(other);
	Long ret = -1;
	Long top;
	Long buttom;
	Long left;
	Long right;

	if (one_->GetWidth() >= 0) {
		left = one_->GetX();
		right = one_->GetX() + one_->GetWidth();
	}
	else {
		right = one_->GetX();
		left = one_->GetX() - one_->GetWidth();
	}

	if (one_->GetHeight() >= 0) {
		top = one_->GetY();
		buttom = one_->GetY() + one_->GetHeight();
	}
	else {
		buttom = one_->GetY();
		top = one_->GetY() - one_->GetHeight();
	}

	if (left <= other_->GetX() && other_->GetX() <= right &&
		top <= other_->GetY() && other_->GetY() <= buttom) {
		ret = 0;
	}

	return ret;
}
*/

FlowChart::FlowChart(Long capacity) 
	: Block(capacity) {

}

FlowChart::~FlowChart() {

}

FlowChart::FlowChart(const FlowChart& source) 
	: Block(source.capacity) {
	
}

FlowChart& FlowChart::operator=(const FlowChart& source) {
	Block::operator=(source);

	return *this;
}

void FlowChart::DrawActiveShape(GObject *painter){
	Long i = 0;
	while (i < this->length) {
		this->shapes[i]->DrawActiveShape(painter);
		i++;
	}
}

void FlowChart::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

NShape* FlowChart::Clone() {
	return new FlowChart(*this);
}

QRect FlowChart::GetRange() {
	QRect rect;
	rect.setCoords(0, 0, 0, 0);

	Long top = 0;
	Long bottom = 0;
	Long left = 0;
	Long right = 0;

	Long i = 0;
	while (i < this->GetLength()) {
		if (dynamic_cast<LeftDown *>(this->GetAt(i))) {
			left = this->GetAt(i)->GetX() + this->GetAt(i)->GetWidth();
			top = this->GetAt(i)->GetY();
			right = this->GetAt(i)->GetX();
			bottom = this->GetAt(i)->GetY() + this->GetAt(i)->GetHeight();
		}
		else if (dynamic_cast<RightDownJoin *>(this->GetAt(i))) {
			left = this->GetAt(i)->GetX() + this->GetAt(i)->GetWidth();
			top = this->GetAt(i)->GetY();
			right = this->GetAt(i)->GetX() + dynamic_cast<RightDownJoin *>(this->GetAt(i))->GetWidth2();
			bottom = this->GetAt(i)->GetY() + this->GetAt(i)->GetHeight();
		}
		else if (dynamic_cast<Join *>(this->GetAt(i))) {
			if (this->GetAt(i)->GetWidth() > 0) {
				left = this->GetAt(i)->GetX();
				right = this->GetAt(i)->GetX() + this->GetAt(i)->GetWidth();
			}
			else {
				left = this->GetAt(i)->GetX() + this->GetAt(i)->GetWidth();
				right = this->GetAt(i)->GetX();
			}

			if (this->GetAt(i)->GetHeight() >= dynamic_cast<Join *>(this->GetAt(i))->GetHeight2()) {
				top = this->GetAt(i)->GetY();
			}
			else {
				top = this->GetAt(i)->GetY() + this->GetAt(i)->GetHeight() + dynamic_cast<Join *>(this->GetAt(i))->GetHeight2();
			}
			bottom = this->GetAt(i)->GetY() + this->GetAt(i)->GetHeight();
		}
		else if (dynamic_cast<RepeatTrue *>(this->GetAt(i))) {
			left = this->GetAt(i)->GetX() + dynamic_cast<RepeatTrue *>(this->GetAt(i))->GetWidth2();
			top = this->GetAt(i)->GetY() + this->GetAt(i)->GetHeight();
			if (this->GetAt(i)->GetWidth() > 0) {
				right = this->GetAt(i)->GetX() + this->GetAt(i)->GetWidth();
			}
			else {
				right = this->GetAt(i)->GetX();
			}
			bottom = this->GetAt(i)->GetY() + dynamic_cast<RepeatTrue *>(this->GetAt(i))->GetHeight2();
		}
		else if (dynamic_cast<RepeatFalse *>(this->GetAt(i))) {
			left = this->GetAt(i)->GetX() + this->GetAt(i)->GetWidth();
			top = this->GetAt(i)->GetY();
			right = this->GetAt(i)->GetX() + dynamic_cast<RepeatFalse *>(this->GetAt(i))->GetWidth2();
			bottom = this->GetAt(i)->GetY() + this->GetAt(i)->GetHeight();
		}
		else {
			left = this->GetAt(i)->GetX();
			top = this->GetAt(i)->GetY();
			right = this->GetAt(i)->GetX() + this->GetAt(i)->GetWidth();
			bottom = this->GetAt(i)->GetY() + this->GetAt(i)->GetHeight();
		}
		if (left < rect.left() || rect.left() == 0) {
			rect.setLeft(left);
		}
		if (right > rect.right()) {
			rect.setRight(right);
		}
		if (top < rect.top() || rect.top() == 0) {
			rect.setTop(top);
		}
		if (bottom > rect.bottom()) {
			rect.setBottom(bottom);
		}
		i++;
	}
	return rect;
}