#include "Memory.h"
#include "Executions.h"
#include "FlowChart.h"

Memory::Memory(Long capacity)
	: executions(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

Memory::Memory(const Memory& source)
	: executions(source.executions) {
	Long i = 0;
	while (i < source.length) {
		this->executions.Modify(i, (const_cast<Memory&>(source)).executions[i]->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
}

Memory::~Memory() {
	Long i = 0;
	while (i < this->length) {
		if (this->executions[i] != 0) {
			delete this->executions[i];
		}
		i++;
	}
}

Memory& Memory::operator=(const Memory& source) {
	Long i = 0;
	while (i < this->length) {
		if (this->executions[i] != 0) {
			delete this->executions[i];
		}
		i++;
	}
	this->executions = source.executions;
	i = 0;
	while (i < source.length) {
		this->executions.Modify(i, (const_cast<Memory&>(source)).executions[i]->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long Memory::Add(Execution *execution) {
	
	//20개로 제한
	if (this->length >= 20) {
		if (this->executions[0] != 0) {
			delete this->executions[0];
		}
		this->executions.Delete(0);
		this->length--;
	}
	
	Long index;
	if (this->length < this->capacity) {
		index = this->executions.Store(this->length, execution);
	}
	else {
		index = this->executions.AppendFromRear(execution);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long Memory::Remove(Long index) {
	if (this->executions[index] != 0) {
		delete this->executions[index];
	}
	this->executions.Delete(index);
	this->length--;

	return index;
}

void Memory::RemoveAll() {
	Long i = 0;
	while (i < this->length) {
		if (this->executions[0] != 0) {
			delete this->executions[0];
		}
		this->executions.Delete(0);
		i++;
	}
	this->capacity = 20;
	this->length = 0;
}

Execution* Memory::GetAt(Long index) {
	return this->executions.GetAt(index);
}

void Memory::Quadrate(Shape *flowChart) {
	//1. execution 개수만큼 반복한다.
	Long i = 0;
	while (i < this->length) {
		Execution *execution = this->executions[i];
		//1.1. shape, position의 개수만큼 반복한다.
		Long j = 0;
		while (j < execution->GetLength()) {
			//1.1.1. 실제 flowChart에서 현재 shape를 찾는다.
			Shape *shape = execution->GetShape(j);
			Long k = 0;
			while (k < dynamic_cast<FlowChart*>(flowChart)->GetLength() &&
				dynamic_cast<FlowChart*>(flowChart)->GetAt(k)->GetContents() != shape->GetContents()) {
				k++;
			}
			if (k < dynamic_cast<FlowChart*>(flowChart)->GetLength()) {
				execution->Modify(j, k); //1.1.1.1. 찾았으면 position을 고친다.
			}
			j++;
		}
		i++;
	}
}