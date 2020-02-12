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
#include "Document.h"
#include "Preparation.h"
#include "Process.h"
#include "PunchedCard.h"
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
#include "Painter.h"

#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	FlowChart flowChart;
	Shape *shape1 = new Terminal(100, 100, 100, 100, 20, DASH, 20, "Symbol");
	Shape *shape2 = new Arrow(100, 100, 0, 100, 20, DASH, 20, "Arrow");
	Shape *shape3 = new LeftDown(100, 100, 100, 100, 20, DASH, 20, "LeftDown");
	Shape *shape4 = new Join(100, 100, 100, 100, -130, 20, DASH, 20, "Join-Right");
	Shape *shape5 = new Join(100, 100, 100, 100, -70, 20, DASH, 20, "Join-Left");
	Shape *shape6 = new RightDownJoin(100, 100, 100, 30, 30, 30, 20, DASH, 20, "RightDownJoin");
	Shape *shape7 = new RepeatTrue(5, 50, 100, 30, 30, 30, 20, DASH, 20, "RepeatTrue");
	Shape *shape8 = new RepeatFalse(5, 50, 100, 30, 30, 30, 20, DASH, 20, "RepeatFalse");

	flowChart.Attach(shape1);
	flowChart.Attach(shape2);
	flowChart.Attach(shape3);
	flowChart.Attach(shape4);
	flowChart.Attach(shape5);

	Shape *shape = flowChart.GetAt(0);
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

Long CompareShapeAddress(void *one, void *other);

FlowChart::FlowChart(Long capacity) :shapes(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
}

FlowChart::~FlowChart() {
	for (Long i = 0; i < this->shapes.GetLength(); i++) {
		if (this->shapes[i] != 0) {
			delete this->shapes[i];
		}
	}
}

FlowChart::FlowChart(const FlowChart& source) :shapes(source.capacity) {
	Shape *shape;
	Shape *temp;

	this->length = 0;
	this->capacity = source.GetCapacity();

	for (int i = 0; i < source.GetLength(); i++) {
		shape = const_cast<FlowChart&>(source).GetAt(i);

		temp = shape->Clone();

		this->shapes.Store(i, temp);
		this->length++;
	}
	this->current = source.current;
}

Long FlowChart::Insert(Long index, Shape *shape) {
	this->current = -1;
	this->current = this->shapes.Insert(index, shape);
	if (this->length >= this->capacity) {
		this->capacity += 128;
	}
	this->length++;
	return this->current;
}

Long FlowChart::InsertRear(Long index, Shape *shape) {
	this->current = -1;
	if (index + 1 <= this->length) {
		this->current = this->shapes.Insert(index + 1, shape);
	}
	else if (this->length >= this->capacity) {
		this->current = this->shapes.AppendFromRear(shape);
	}
	else {
		this->current = this->shapes.Store(index + 1, shape);
	}

	if (this->length >= this->capacity) {
		this->capacity += 128;
	}
	this->length++;
	return this->current;
}

Long FlowChart::Attach(Shape *shape) {
	if (this->length < this->capacity) {
		this->current = this->shapes.Store(this->length, shape);
	}
	else {
		this->current = this->shapes.AppendFromRear(shape);
		this->capacity++;
	}
	this->length++;
	return this->current;
}

Long CompareShapeAddress(void *one, void *other) {
	Shape *one_ = *(static_cast<Shape * (*)>(one));
	Shape *other_ = static_cast<Shape *>(other);
	return (*one_ == *other_) ? (0) : (-1);
}

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

Long FlowChart::Erase(Long index) {
	if (index >= 0 && index < this->GetLength()) {
		delete this->shapes[index];
		this->current = this->shapes.Delete(index);
		this->length--;
	}
	return this->current;
}

void FlowChart::Swap(Long toIndex, Long fromIndex) {
	this->shapes.Swap(toIndex, fromIndex);
}

void FlowChart::Swap(Long toIndex, Shape *shape) {
	Shape *temp;

	temp = this->shapes.GetAt(toIndex);
	if (temp != 0) {
		delete temp;
	}
	this->shapes[toIndex] = shape;

}

void FlowChart::Clear() {

	for (Long i = 0; i < this->GetLength(); i++) {
		if (this->shapes[i] != 0) {
			delete this->shapes[i];
		}
	}

	this->shapes.Clear();
	this->capacity = 0;
	this->length = 0;
	this->current = -1;
}

FlowChart& FlowChart::operator =(const FlowChart& source) {
	Shape *shape;
	Shape *temp;

	this->capacity = source.GetCapacity();
	this->length = 0;

	for (int j = 0; this->GetLength(); j++) {
		shape = this->shapes.GetAt(j);
		if (shape != 0) {
			delete shape;
			shape = 0;
		}
	}

	this->shapes = source.shapes;

	for (int i = 0; i < source.GetLength(); i++) {
		this->shapes.Delete(i);

		shape = const_cast<FlowChart&>(source).GetAt(i);

		temp = shape->Clone();

		temp->Move(shape->GetX(), shape->GetY());
		temp->ReSize(shape->GetWidth(), shape->GetHeight());
		temp->Paint(shape->GetBackGroundColor(), shape->GetBorderLine(), shape->GetBorderColor());

		this->shapes.Store(i, temp);
		this->length++;
	}

	this->current = source.current;

	return *this;
}

Shape* FlowChart::GetAt(Long index) {
	return this->shapes[index];
}

void FlowChart::DrawActiveShape(CDC *dc) {
	Long i = 0;
	while (i < this->length) {
		this->shapes[i]->DrawActiveShape(dc);
		i++;
	}
}

void FlowChart::Accept(FlowChartVisitor *draw) {
	draw->Visit(this);
}

Long FlowChart::Find(Shape *shape) {
	Long index = -1;
	Long i = 0;
	while (i < this->length && index == -1) {
		if (this->shapes[i]->IsEqual(*shape)) {
			index = i;
		}
		i++;
	}
	return index;
}

Long FlowChart::Find(CDC *dc, CPoint point) {
	Long index = -1;
	Long i = 0;

	while (i < length) {
		if (this->shapes[i]->IsIncluded(dc, point)) {
			index = i;
		}
		i++;
	}
	return index;
}

Long FlowChart::Find(CDC *dc, int x, int y) {
	POINT point = { x,y };
	Long index = -1;
	Long i = 0;

	while (i < length) {
		if (this->shapes[i]->IsIncluded(dc, point)) {
			index = i;
		}
		i++;
	}
	return index;
}

Long FlowChart::Find(Painter *painter, CPoint point) {
	Long index = -1;
	Long i = 0;

	while (i < length) {
		if (this->shapes[i]->IsIncluded(painter, point)) {
			index = i;
		}
		i++;
	}
	return index;
}

Long FlowChart::Find(Painter *painter, int x, int y) {
	POINT point = { x,y };
	Long index = -1;
	Long i = 0;

	while (i < length) {
		if (this->shapes[i]->IsIncluded(painter, point)) {
			index = i;
		}
		i++;
	}
	return index;
}

Long FlowChart::Find(Painter *painter, RECT &rect) {
	Long i = 0;
	while (i < this->length && !(this->shapes[i]->IsIncluded(painter, rect))) {
		i++;
	}
	return (i < this->length) ? (i) : (-1);
}

Long FlowChart::Find(SHAPE identify) {
	Long i = 0;
	while (i < this->length && !(this->shapes[i]->Identify(identify))) {
		i++;
	}
	return (i < this->length) ? (i) : (-1);
}

Long FlowChart::Find(Long fromIndex, SHAPE identify) {
	Long i = fromIndex;
	while (i < this->length && !(this->shapes[i]->Identify(identify))) {
		i++;
	}
	return (i < this->length) ? (i) : (-1);
}

void FlowChart::Find(Long styles, Long *(*indexes), Long *count) {
	Long i = 0;
	Long j = 0;
	*count = 0;
	if (this->length > 0) {
		*indexes = new Long[this->length];
	}

	while (i < this->length) {
		if (this->shapes[i]->IsStyle(styles)) {
			(*indexes)[j] = i;
			(*count)++;
			j++;
		}
		i++;
	}
}

Shape* FlowChart::Clone() {
	return new FlowChart(*this);
}

void FlowChart::SelectAll() {
	int i = 0;
	while (i < this->length) {
		this->shapes[i]->Select(true);
		i++;
	}
}

void FlowChart::UnSelectAll() {
	int i = 0;
	while (i < this->length) {
		this->shapes[i]->Select(false);
		i++;
	}
}

void FlowChart::AscendingSort() {
	Shape *temp;
	Long i;
	Long j;
	Long k;
	Long y;

	//1. 두 번째부터 개수만큼 반복하다.
	for (i = 1; i < this->length; i++) {
		//1.1. 현재 shape를 가져오다.
		temp = this->shapes[i]->Clone();
		y = temp->CenterOfGravityY();
		//1.2. 현재 shape의 위치만큼 반복하면서 현재 shape의 y좌표보다 큰 이전 shape를 찾다.
		j = 0;
		while (j < i && this->GetAt(j)->CenterOfGravityY() < y) {
			j++;
		}
		//1.3. 현재 shape의 y좌표보다 큰 이전 shape가 있으면 위치를 바꾸다.
		k = i;
		while (k > j) {
			if (this->shapes[k] != 0) {
				delete this->shapes[k];
			}
			this->shapes[k] = this->shapes[k - 1]->Clone();
			k--;
		}

		if (this->shapes[j] != 0) {
			delete this->shapes[j];
		}
		this->shapes[j] = temp->Clone();
	}
}

void FlowChart::DescendingSort() {
	Shape *temp;
	Long i;
	Long j;
	Long k;
	Long y;

	for (i = 1; i < this->length; i++) {
		temp = this->shapes[i]->Clone();
		y = temp->CenterOfGravityY();

		j = 0;
		while (j < i && this->GetAt(j)->CenterOfGravityY() > y) {
			j++;
		}

		k = i;
		while (k > j) {
			if (this->shapes[k] != 0) {
				delete this->shapes[k];
			}
			this->shapes[k] = this->shapes[k - 1]->Clone();
			k--;
		}

		if (this->shapes[j] != 0) {
			delete this->shapes[j];
		}
		this->shapes[j] = temp->Clone();
	}
}

void FlowChart::GetSelecteds(Long *(*indexes), Long *count) {
	Long i;
	Long j = 0;
	*count = 0;
	*indexes = 0;

	if (this->length > 0) {
		*indexes = new Long[this->length];
	}
	for (i = 0; i < this->length; i++) {
		Shape *shape = this->shapes[i];
		if (shape->IsSelected()) {
			(*indexes)[j] = i;
			(*count)++;
			j++;
		}
	}
}

Long FlowChart::CountSelecteds() {
	Long count = 0;
	for (Long i = 0; i < this->length; i++) {
		if (this->shapes[i]->IsSelected()) {
			count++;
		}
	}
	return count;
}

Long FlowChart::Erase(SHAPE identify) {
	Long count = 0;
	Long i = this->length;
	while (i > 0) {
		if (this->shapes[i - 1]->Identify(identify)) {
			delete this->shapes[i - 1];
			this->shapes.Delete(i - 1);
			this->length--;
			count++;
		}
		i--;
	}
	return count;
}

bool FlowChart::EraseSelectedAll() {
	bool ret = false;
	Long i = this->length;
	while (i > 0) {
		if (this->shapes[i - 1]->IsSelected()) {
			delete this->shapes[i - 1];
			this->shapes.Delete(i - 1);
			this->length--;
			ret = true;
		}
		i--;
	}
	return ret;
}

void FlowChart::GetRange(RECT *rect) {
	Long top = 0;
	Long bottom = 0;
	Long left = 0;
	Long right = 0;
	Long i = 0;

	rect->top = 0;
	rect->bottom = 0;
	rect->left = 0;
	rect->right = 0;

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
		if (left < rect->left || rect->left == 0) {
			rect->left = left;
		}
		if (right > rect->right) {
			rect->right = right;
		}
		if (top < rect->top || rect->top == 0) {
			rect->top = top;
		}
		if (bottom > rect->bottom) {
			rect->bottom = bottom;
		}
		i++;
	}
}