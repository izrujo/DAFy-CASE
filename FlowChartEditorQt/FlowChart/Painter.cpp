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

GObject* Painter::SelectObject(const GObject& object) {
	GObject *previous;
	string previousIdenfity = "";
	if (this->length > 0) {
		previous = this->objects.GetAt(0);
		previousIdenfity = previous->GetIdentify();
	}
	string identify = const_cast<GObject&>(object).GetIdentify();

	Long i = 1;
	while (i < this->length && previousIdenfity != identify) {
		previous = this->objects.GetAt(i);
		previousIdenfity = previous->GetIdentify();
		i++;
	}

	previous = 0;
	Long index = i - 1;
	if (index < this->length) { //찾았으면 수정한다.
		previous = this->objects.GetAt(index)->Clone();
		this->objects.Modify(index, &const_cast<GObject&>(object));
	}
	else if (this->length < this->capacity) { //못찾았으면 추가한다.
		this->objects.Store(this->length, &const_cast<GObject&>(object));
		this->length++;
	}
	else {
		this->objects.AppendFromRear(&const_cast<GObject&>(object));
		this->capacity++;
		this->length++;
	}

	return previous;
}

GObject* Painter::CurrentObject(string identify) {
	Long index = -1;
	GObject *current;
	string currentIdentify = "";
	
	if (this->length > 0) {
		current = this->objects.GetAt(0);
		currentIdentify = current->GetIdentify();
	}

	Long i = 1;
	while (i < this->length && currentIdentify != identify) {
		current = this->objects.GetAt(i);
		currentIdentify = current->GetIdentify();
		i++;
	}

	current = 0;
	index = i - 1;
	if (index < this->length) {
		current = this->objects.GetAt(index);
	}

	return current;
}

void Painter::Update() {
	//virtual
}

GObject* Painter::GetAt(Long index) {
	return this->objects.GetAt(index);
}