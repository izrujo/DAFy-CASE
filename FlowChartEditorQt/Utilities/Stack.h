// Stack.h

#ifndef _STACK_H
#define _STACK_H

#include <memory.h>
#include <assert.h>

typedef signed long int Long;

template <typename T>
class Stack{
public:
	Stack( Long capacity);
	Stack( const Stack& source );
	~Stack();
	Stack& operator=( const Stack& source );
	Long Push( T item );
	T Pop();
	T Top();
	bool Empty();
	bool IsFull();

	Long GetTop() const;
	Long GetCapacity() const;
	Long GetLength() const;

private:
	T (*bottom); // 시작 위치
	Long top; // 삽입/삭제 위치
	Long capacity; // 요소 수용량
	Long length; // 요소의 개수
};

template <typename T>
Stack<T>::Stack( Long capacity){
	
	this->bottom = new T [capacity];
	assert( this->bottom != 0 );
	this->top = -1;
	this->capacity = capacity;
	this->length = 0;
}

template <typename T>
Stack<T>::Stack( const Stack& source ){

	this->bottom = new T [source.capacity];
	this->capacity = source.capacity;	

	if ( source.length > 0){
		memcpy(this->bottom, source.bottom, sizeof(T)*source.length);	
	}
	this->length = source.length;
	this->top = source.top;
}

template <typename T>
Stack<T>& Stack<T>::operator=( const Stack& source ){
	if( this->bottom != 0){
		delete[] bottom;
	}

	this->bottom = new T [source.capacity];
	this->capacity = source.capacity;	

	if ( source.length > 0){
		memcpy(this->bottom, source.bottom, sizeof(T)*source.length);	
	}
	this->length = source.length;
	this->top = source.top;
	return *this;	
}

template <typename T>
Stack<T>::~Stack(){
	if( this->bottom != 0){
		delete [] this->bottom;
	}
	this->bottom = 0;
	this->length = 0;
	this->capacity = 0;
	this->top = -1;
}

template <typename T>
Long Stack<T>::Push( T item ){
	assert( this->top <this->capacity -1);
	this->bottom[this->top+1] = item;
	this->top++;
	this->length++;
	return this->top;
}

template <typename T>
T Stack<T>::Pop(){
	T item;
	assert(this->top != -1);
	item = this->bottom[this->top];
	this->top--;
	this->length--;
	return item;	
}

template <typename T>
T Stack<T>::Top(){
	T item;
	assert(this->top != -1);
	item = this->bottom[this->top]; 
	return item;
}

template <typename T>
bool Stack<T>::Empty(){

	if( this->bottom != 0){
		delete [] this->bottom;
		this->bottom = 0;
		this->top = -1;
		this->length = 0;
		this->capacity = 0;		
	}
	return true;
}

template <typename T>
bool Stack<T>::IsFull(){
	bool ret = false;	
	if( this->length == this->capacity )
	{
		ret = true;
	}
	return ret;
}

template <typename T>
inline Long Stack<T>::GetTop() const{
	return this->top;
}

template <typename T>
inline Long Stack<T>::GetCapacity() const{
	return this->capacity;
}

template <typename T>
inline Long Stack<T>::GetLength() const{
	return this->length;
}

#endif _STACK_H