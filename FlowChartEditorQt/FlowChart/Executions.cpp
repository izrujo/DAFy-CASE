#include "Executions.h"
#include "Shape.h"

//Execution
Execution::Execution(Long capacity)
	: shapes(capacity), positions(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

Execution::Execution(const Execution& source)
	: shapes(source.shapes), positions(source.positions) {
	Long i = 0;
	while (i < source.length) {
		this->shapes.Modify(i, (const_cast<Execution&>(source)).shapes[i]->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
}

Execution::~Execution() {
	Long i = 0;
	while (i < this->length) {
		if (this->shapes[i] != 0) {
			delete this->shapes[i];
		}
		i++;
	}
}

Execution& Execution::operator=(const Execution& source) {
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
		this->shapes.Modify(i, (const_cast<Execution&>(source)).shapes[i]->Clone());
		i++;
	}

	this->positions = source.positions;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long Execution::Add(NShape *shape, Long position) {
	Long index;
	if (this->length < this->capacity) {
		index = this->shapes.Store(this->length, shape);
		index = this->positions.Store(this->length, position);
	}
	else {
		index = this->shapes.AppendFromRear(shape);
		index = this->positions.AppendFromRear(position);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long Execution::Remove(Long index) {
	if (this->shapes[index] != 0) {
		delete this->shapes.GetAt(index);
	}
	this->shapes.Delete(index);
	index = this->positions.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}

Long Execution::Modify(Long index, Long position) {
	return this->positions.Modify(index, position);
}

NShape* Execution::GetShape(Long index) {
	return this->shapes.GetAt(index);
}

Long Execution::GetPosition(Long index) {
	return this->positions.GetAt(index);
}

//AddExecution
AddExecution::AddExecution(Long capacity)
	: Execution(capacity) {

}

AddExecution::AddExecution(const AddExecution& source)
	: Execution(source) {

}

AddExecution::~AddExecution() {

}

AddExecution& AddExecution::operator=(const AddExecution& source) {
	Execution::operator=(source);
	return *this;
}

Execution* AddExecution::Clone() {
	return new AddExecution(*this);
}

//RemoveExecution
RemoveExecution::RemoveExecution(Long capacity)
	: Execution(capacity) {

}

RemoveExecution::RemoveExecution(const RemoveExecution& source)
	: Execution(source) {

}

RemoveExecution::~RemoveExecution() {

}

RemoveExecution& RemoveExecution::operator=(const RemoveExecution& source) {
	Execution::operator=(source);
	return *this;
}

Execution* RemoveExecution::Clone() {
	return new RemoveExecution(*this);
}

//OtherExecution
OtherExecution::OtherExecution(Long capacity)
	: Execution(capacity) {

}

OtherExecution::OtherExecution(const OtherExecution& source)
	: Execution(source) {

}

OtherExecution::~OtherExecution() {

}

OtherExecution& OtherExecution::operator=(const OtherExecution& source) {
	Execution::operator=(source);
	return *this;
}

Execution* OtherExecution::Clone() {
	return new OtherExecution(*this);
}