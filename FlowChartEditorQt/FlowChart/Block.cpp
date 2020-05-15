#include "Block.h"

Block::Block(Long capacity)
	:shapes(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = -1;
}

Block::Block(const Block& source)
	: shapes(source.shapes) {
	Long i = 0;
	while (i < source.length) {
		this->shapes.Modify(i, (const_cast<Block&>(source)).shapes[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

Block::~Block() {
	Long i = 0;
	while (i < this->length) {
		if (this->shapes[i] != 0) {
			delete this->shapes[i];
		}
		i++;
	}
}

Block& Block::operator=(const Block& source) {
	NShape *shape;

	Long i = 0;
	while (i < this->length) {
		shape = this->shapes.GetAt(i);
		if (shape != 0) {
			delete shape;
		}
		i++;
	}

	this->shapes = source.shapes;

	i = 0;
	while (i < source.GetLength()) {
		shape = const_cast<Block&>(source).GetAt(i)->Clone();
		this->shapes.Modify(i, shape);
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	return *this;
}

NShape* Block::operator[](Long index) {
	return this->shapes[index];
}

Long Block::Attach(NShape *shape) {
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

Long Block::Insert(Long index, NShape *shape) {
	this->current = -1;
	this->current = this->shapes.Insert(index, shape);
	if (this->length >= this->capacity) {
		this->capacity += 1;
	}
	this->length++;

	return this->current;
}

Long Block::Detach(Long index) {
	if (index >= 0 && index < this->GetLength()) {
		delete this->shapes[index];
		this->current = this->shapes.Delete(index);
		this->length--;
	}
	return this->current;
}

Long Block::Detach(SHAPE identify) {
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

bool Block::DetachSelectedAll() {
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

NShape* Block::GetAt(Long index) {
	return this->shapes.GetAt(index);
}

Long Block::Find(NShape* shape) {
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

Long Block::Find(QPointF point) {
	Long index = -1;
	Long i = 0;

	while (i < length) {
		if (this->shapes[i]->IsIncluded(point)) {
			index = i;
		}
		i++;
	}
	return index;
}

Long Block::Find(float x, float y) {
	QPoint point(x, y);
	Long index = -1;
	Long i = 0;

	while (i < length) {
		if (this->shapes[i]->IsIncluded(point)) {
			index = i;
		}
		i++;
	}
	return index;
}

Long Block::Find(QRectF rect) {
	Long i = 0;
	while (i < this->length && !(this->shapes[i]->IsIncluded(rect))) {
		i++;
	}
	return (i < this->length) ? (i) : (-1);
}

Long Block::Find(SHAPE identify) {
	Long i = 0;
	while (i < this->length && !(this->shapes[i]->Identify(identify))) {
		i++;
	}
	return (i < this->length) ? (i) : (-1);
}

Long Block::Find(Long fromIndex, SHAPE identify) {
	Long i = fromIndex;
	while (i < this->length && !(this->shapes[i]->Identify(identify))) {
		i++;
	}
	return (i < this->length) ? (i) : (-1);
}

void Block::Find(Long styles, Long* (*indexes), Long *count) {
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

void Block::Swap(Long toIndex, Long fromIndex) {
	this->shapes.Swap(toIndex, fromIndex);
}

void Block::Swap(Long toIndex, NShape *shape) {
	NShape *temp;

	temp = this->shapes.GetAt(toIndex);
	if (temp != 0) {
		delete temp;
	}
	this->shapes[toIndex] = shape;
}

void Block::Clear() {
	Long i = 0;
	while (i < this->GetLength()) {
		if (this->shapes[i] != 0) {
			delete this->shapes[i];
		}
		i++;
	}

	this->shapes.Clear();
	this->capacity = 0;
	this->length = 0;
	this->current = -1;
}

void Block::SelectAll() {
	Long i = 0;
	while (i < this->length) {
		this->shapes[i]->Select(true);
		i++;
	}
}

void Block::UnSelectAll() {
	Long i = 0;
	while (i < this->length) {
		this->shapes[i]->Select(false);
		i++;
	}
}

void Block::GetSelecteds(Long* (*indexes), Long *count) {
	Long i;
	Long j = 0;
	*count = 0;
	*indexes = 0;

	if (this->length > 0) {
		*indexes = new Long[this->length];
	}
	for (i = 0; i < this->length; i++) {
		NShape *shape = this->shapes[i];
		if (shape->IsSelected()) {
			(*indexes)[j] = i;
			(*count)++;
			j++;
		}
	}
}

Long Block::CountSelecteds() {
	Long count = 0;
	Long i = 0;
	while (i < this->length) {
		if (this->shapes[i]->IsSelected()) {
			count++;
		}
		i++;
	}
	return count;
}

void Block::AscendingSort() {
	NShape *temp;
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

void Block::DescendingSort() {
	NShape *temp;
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

Long Block::FindByRegistrationNumber(SHAPE id, Long registrationNumber) {
	Long i = 0;
	while (i < this->length && 
		!(this->shapes[i]->Identify(id)) || this->registrationNumber != registrationNumber) {	
		i++;
	}
	return (i < this->length) ? (i) : (-1);
}