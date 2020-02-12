#ifndef _ARRAY_H
#define _ARRAY_H

typedef signed long int Long;
template <typename T>

class Array {
public:
	Array(Long capacity = 256);
	Array(const Array& source);
	~Array();
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	Long Modify(Long index, T object);
	Long LinearSearchUnique(void *key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void *key, Long* (*indexes), Long *count, int(*compare)(void*, void*));
	Long BinarySearchUnique(void *key, int(*compare)(void*, void*));
	void BinarySearchDuplicate(void *key, Long* (*indexes), Long *count, int(*compare)(void*, void*));
	void BubbleSort(int(*compare)(void*, void*));
	void SelectionSort(int(*compare)(void*, void*));
	void InsertionSort(int(*compare)(void*, void*));
	void Merge(const Array& one, const Array& other, int(*compare)(void*, void*));
	T& GetAt(Long index);

	T& operator [](Long index);
	T* operator +(Long index);
	Array& operator =(const Array& source);
	
	Long GetCapacity() const;
	Long GetLength() const;

private:
	T(*front);
	Long capacity;
	Long length;
};

template <typename T>
inline Long Array<T>::GetCapacity() const {
	return this->capacity;
}
template <typename T>
inline Long Array<T>::GetLength() const {
	return this->length;
}

//함수 정의
template <typename T>
Array<T>::Array(Long capacity) {
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}

template <typename T>
Array<T>::Array(const Array& source) {
	this->front = new T[source.capacity];
	this->capacity = source.capacity;
	Long i = 0;
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->length = source.length;
}

template <typename T>
Array<T>::~Array() {
	if (this->front != 0) {
		delete[] this->front;
	}
}

template <typename T>
Long Array<T>::Store(Long index, T object) {
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::Insert(Long index, T object) {
	T(*objects);
	Long i;
	Long j = 0;

	objects = new T[this->capacity + 1];
	i = 0;
	while (i < index) {
		objects[j] = this->front[i];
		j++;
		i++;
	}
	j++;
	while (i < this->length) {
		objects[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = objects;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::AppendFromFront(T object) {
	Long index = 0;
	T(*objects);
	Long i = 0;
	objects = new T[this->capacity + 1];
	while (i < this->length) {
		objects[i + 1] = this->front[i];
		i++;
	}

	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = objects;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::AppendFromRear(T object) {
	Long index;
	T(*objects);
	Long i = 0;
	objects = new T[this->capacity + 1];
	while (i < this->length) {
		objects[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = objects;
	this->capacity++;
	index = this->capacity - 1;
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::Delete(Long index) {
	T(*objects) = 0;
	Long i = 0;
	if (this->capacity > 1) {
		objects = new T[this->capacity - 1];
	}
	while (i < index) {
		objects[i] = this->front[i];
		i++;
	}
	i = index + 1;
	while (i < this->length) {
		objects[i - 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = objects;
	}

	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

template <typename T>
Long Array<T>::DeleteFromFront() {
	T(*objects) = 0;
	Long i = 1;
	if (this->capacity > 1) {
		objects = new T[this->capacity - 1];
	}
	while (i < this->length) {
		objects[i - 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}

	if (this->capacity > 1) {
		this->front = objects;
	}
	this->capacity--;
	this->length--;
	return -1;
}

template<typename T>
Long Array<T>::DeleteFromRear()
{
	T(*objects) = 0;
	Long i = 0;

	if (this->capacity > 1)
	{
		objects = new T[this->capacity - 1];
	}

	while (i < this->length - 1)
	{
		objects[i] = this->front[i];
		i++;
	}

	if (this->capacity > 1)
	{
		this->front = objects;
	}

	this->capacity--;
	this->length--;

	return -1;
}

template<typename T>
void Array<T>::Clear()
{
	if (this->front != 0)
	{
		delete[] this->front;
		this->front = 0;
	}

	this->capacity = 0;
	this->length = 0;
}

template<typename T>
Long Array<T>::Modify(Long index, T object)
{
	this->front[index] = object;

	return index;
}

template<typename T>
Long Array<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*))
{
	Long index = -1;
	Long i = 0;

	while (i < this->length && compare(this->front + i, key) != 0)
	{
		i++;
	}

	if (i < this->length)
	{
		index = i;
	}

	return index;
}

template<typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*))
{
	Long i = 0;
	Long j = 0;
	*count = 0;

	*indexes = new Long[this->length];

	while (i < this->length)
	{
		if (compare(this->front + i, key) == 0)
		{
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}

		i++;
	}
}

template<typename T>
Long Array<T>::BinarySearchUnique(void *key, int(*compare)(void*, void*))
{
	Long index = -1;
	Long first = 0;
	Long last;
	Long mid;

	last = this->length - 1;
	mid = (first + last) / 2;
	while (first <= last && compare(this->front + mid, key) != 0)
	{
		if (compare(this->front + mid, key) < 0)
		{
			first = mid + 1;
		}
		else
		{
			last = mid - 1;
		}

		mid = (first + last) / 2;
	}

	if (first <= last)
	{
		index = mid;
	}

	return index;
}

template <typename T>
void Array<T>::BinarySearchDuplicate(void *key, Long* (*indexes), Long *count, int(*compare)(void*, void*)) {
	Long first = 0;
	Long last;
	Long mid;
	Long i;
	Long j = 0;
	*count = 0;

	*indexes = new Long[this->length];
	last = this->length - 1;
	mid = (first + last) / 2;
	while (first <= last && compare(this->front + mid, key) != 0) {
		if (compare(this->front + mid, key) < 0) {
			first = mid + 1;
		}
		else {
			last = mid - 1;
		}
		mid = (first + last) / 2;
	}
	i = mid - 1;
	while (i >= first && compare(this->front + i, key) == 0) {
		i--;
	}
	first = i + 1;
	i = first;
	while (i <= last && compare(this->front + i, key) == 0) {
		(*indexes)[j] = i;
		j++;
		(*count)++;
		i++;
	}
}

template <typename T>
void Array<T>::BubbleSort(int(*compare)(void*, void*)) {
	Long i = 0;
	Long j;
	T temp;
	Long check = 1;

	while (i < this->length - 1 && check == 1) {
		check = 0;
		j = 0;
		while (j < this->length - i - 1) {
			if (compare(this->front + j, this->front + (j + 1)) > 0) {
				temp = this->front[j];
				this->front[j] = this->front[j + 1];
				this->front[j + 1] = temp;
				check = 1;
			}
			j++;
		}
		i++;
	}
}

template <typename T>
void Array<T>::SelectionSort(int(*compare)(void*, void*)) {
	Long i = 0;
	Long j;
	T min;
	Long minIndex;

	while (i < this->length - 1) {
		minIndex = i;
		min = this->front[minIndex];
		j = i + 1;
		while (j < this->length) {
			if (compare(&min, this->front + j) > 0) {
				minIndex = j;
				min = this->front[minIndex];
			}
			j++;
		}
		this->front[minIndex] = this->front[i];
		this->front[i] = min;
		i++;
	}
}

template <typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)) {
	Long i = 1;
	Long j;
	T temp;

	while (i < this->length) {
		temp = this->front[i];
		j = i - 1;
		while (j >= 0 && compare(this->front + j, &temp) > 0) {
			this->front[j + 1] = this->front[j];
			j--;
		}
		this->front[j + 1] = temp;
		i++;
	}
}

template <typename T>
void Array<T>::Merge(const Array& one, const Array& other, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;

	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = new T[one.length + other.length];
	this->capacity = one.length + other.length;
	this->length = 0;
	while (i < one.length && j < other.length) {
		if (compare(one.front + i, other.front + j) < 0) {
			this->front[k] = one.front[i];
			k++;
			this->length++;
			i++;
		}
		else {
			this->front[k] = other.front[j];
			k++;
			this->length++;
			j++;
		}
	}
	while (i < one.length) {
		this->front[k] = one.front[i];
		k++;
		this->length++;
		i++;
	}
	while (j < other.length) {
		this->front[k] = other.front[j];
		k++;
		this->length++;
		j++;
	}
}

template <typename T>
T& Array<T>::GetAt(Long index) {
	return this->front[index];
}

template <typename T>
T& Array<T>::operator [](Long index) {
	return this->front[index];
}

template <typename T>
T* Array<T>::operator +(Long index) {
	return (this->front + index);
}

template <typename T>
Array<T>& Array<T>::operator =(const Array& source) {
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = new T[source.capacity];
	this->capacity = source.capacity;
	Long i = 0;
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->length = source.length;

	return *this;
}

#endif //_ARRAY_H