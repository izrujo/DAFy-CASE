#include "Historys.h"
#include "Shape.h"

//History
History::History(Long capacity)
	: shapes(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

History::History(const History& source)
	: shapes(source.shapes) {
	Long i = 0;
	while (i < source.length) {
		this->shapes.Modify(i, (const_cast<History&>(source)).shapes[i]->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
}

History::~History() {
	Long i = 0;
	while (i < this->length) {
		if (this->shapes[i] != 0) {
			delete this->shapes[i];
		}
		i++;
	}
}

History& History::operator=(const History& source) {
	Long i = 0;
	while (i < this->length) {
		if (this->shapes[i] != 0) {
			delete this->shapes[i];
		}
		i++;
	}
	this->shapes = source.shapes;
	i = 0;
	while (i < source.length) {
		this->shapes.Modify(i, (const_cast<History&>(source)).shapes[i]->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long History::Add(NShape *shape) {
	Long index;
	if (this->length < this->capacity) {
		index = this->shapes.Store(this->length, shape);
	}
	else {
		index = this->shapes.AppendFromRear(shape);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long History::Remove(Long index) {
	if (this->shapes[index] != 0) {
		delete this->shapes.GetAt(index);
	}
	this->shapes.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}

Long History::Modify(Long index, NShape *shape) {
	if (this->shapes[index] != 0) {
		delete this->shapes[index];
	}
	this->shapes[index] = shape;

	return index;
}

NShape* History::GetShape(Long index) {
	return this->shapes.GetAt(index);
}

//AddHistory
AddHistory::AddHistory(Long capacity)
	: History(capacity) {

}

AddHistory::AddHistory(const AddHistory& source)
	: History(source) {

}

AddHistory::~AddHistory() {

}

AddHistory& AddHistory::operator=(const AddHistory& source) {
	History::operator=(source);
	return *this;
}

History* AddHistory::Clone() {
	return new AddHistory(*this);
}

//RemoveHistory
RemoveHistory::RemoveHistory(Long capacity)
	: History(capacity) {

}

RemoveHistory::RemoveHistory(const RemoveHistory& source)
	: History(source) {

}

RemoveHistory::~RemoveHistory() {

}

RemoveHistory& RemoveHistory::operator=(const RemoveHistory& source) {
	History::operator=(source);
	return *this;
}

History* RemoveHistory::Clone() {
	return new RemoveHistory(*this);
}

//OtherHistory
OtherHistory::OtherHistory(Long capacity)
	: History(capacity) {

}

OtherHistory::OtherHistory(const OtherHistory& source)
	: History(source) {

}

OtherHistory::~OtherHistory() {

}

OtherHistory& OtherHistory::operator=(const OtherHistory& source) {
	History::operator=(source);
	return *this;
}

History* OtherHistory::Clone() {
	return new OtherHistory(*this);
}