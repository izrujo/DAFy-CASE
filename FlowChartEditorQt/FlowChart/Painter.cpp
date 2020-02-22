#include "Painter.h"

Painter::Painter(Long capacity)
	: GObject(), objects(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

Painter::Painter(const Painter& source)
	: GObject(source), objects(source.objects) {
	Long i = 0;
	while (i < source.length) {
		this->objects.Modify(i, (const_cast<Painter&>(source)).objects[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

Painter::~Painter() {
	Long i = 0;
	while (i < this->length) {
		if (this->objects[i] != 0) {
			delete this->objects[i];
		}
		i++;
	}
}

Painter& Painter::operator=(const Painter& source) {
	GObject *object;

	Long i = 0;
	while (i < this->length) {
		object = this->objects.GetAt(i);
		if (object != 0) {
			delete object;
		}
		i++;
	}

	this->objects = source.objects;

	i = 0;
	while (i < source.GetLength()) {
		object = const_cast<Painter&>(source).GetAt(i)->Clone();
		this->objects.Modify(i, object);
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

void Painter::SelectObject(const GObject& object, GObject *previous, Long *index) {
	//1. 첫 번째 그래픽 객체를 가져오다.
	previous = this->objects.GetAt(0);
	//2. 바꿀 그래픽 객체의 정체성을 가져오다.
	string identify = const_cast<GObject&>(object).GetIdentify();
	//3. 첫 번째 그래픽 객체의 정체성을 가져오다.
	string previousIdenfity = previous->GetIdentify();

	//4. 사용량만큼 그리고 현재 그래픽 객체의 정체성과 바꿀 그래픽 객체의 정체성이 다를 동안 반복한다.
	Long i = 1;
	while (i < this->length && previousIdenfity != identify) {
		//4.1. 현재 그래픽 객체를 가져오다.
		previous = this->objects.GetAt(i);
		//4.2. 현재 그래픽 객체의 정체성을 가져오다.
		previousIdenfity = previous->GetIdentify();
		i++;
	}
	*index = i - 1;
	//5. 바꿀 그래픽 객체와 같은 종류의 그래픽 객체를 배열에서 찾았으면
	if (*index < this->length) {
		//5.1. 현재 그래픽 객체를 가져와서 복사하다.
		previous = this->objects.GetAt(*index)->Clone();
		//5.2. 현재 위치에 바꿀 그래픽 객체로 수정하다.
		this->objects.Modify(*index, &const_cast<GObject&>(object));
	}
	//6. 원래 그래픽 객체를 출력하다.
	//7. 현재 위치를 출력하다.
}

GObject* Painter::CurrentObject(string identify) {
	Long index = -1;
	//1. 첫 번째 그래픽 객체를 가져오다.
	GObject *current = this->objects.GetAt(0);
	//2. 첫 번째 그래픽 객체의 정체성을 가져오다.
	string currentIdenfity = current->GetIdentify();

	//3. 사용량만큼 그리고 현재 그래픽 객체의 정체성과 찾을 정체성이 다를 동안 반복한다.
	Long i = 1;
	while (i < this->length && currentIdenfity != identify) {
		//3.1. 현재 그래픽 객체를 가져오다.
		current = this->objects.GetAt(i);
		//3.2. 현재 그래픽 객체의 정체성을 가져오다.
		currentIdenfity = current->GetIdentify();
		i++;
	}
	Long index = i - 1;
	if (index < this->length) { //4. 찾았으면 현재 그래픽 객체를 출력한다.
		current = this->objects.GetAt(index);
	}
}

GObject* Painter::GetAt(Long index) {
	return this->objects.GetAt(index);
}