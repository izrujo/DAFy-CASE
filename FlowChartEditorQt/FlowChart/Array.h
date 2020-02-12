/******************************************************************
* 파일 이름 : Array.h
* 기능 : 배열 라이브러리 파일
* 작성자 : 송윤창
* 작성일자 : 2015년 3월 18일 
*******************************************************************/

#ifndef _ARRAY_H
#define _ARRAY_H

#include <memory>
#include <cassert>
typedef signed long int Long;

template <typename T>
class Array{
	public:
		Array(Long capacity = 1024);
		Array(const Array& source);
		~Array();

		Long Store(Long index,T object);
		Long Insert(Long index,T object);
		Long AppendFromFront(T object);
		Long AppendFromRear(T objedt);
		
		Long Delete(Long index);
		Long DeleteFromFront();
		Long DeleteFromRear();
		void Clear();
		
		Long Modify(Long index, T object);
		
		Long LinearSearchUnique(void *key, Long (*compare)(void *,void *));
		void LinearSearchDuplicate(void *key,Long *(*indexes),Long *count,Long (*compare)(void *,void*));
		Long BinarySearchUnique(void *key,Long (*compare)(void *,void*));
		void BinarySearchDuplicate(void *key,Long *(*indexes),Long *count,Long (*compare)(void *,void*));

		void SelectionSort(Long (*compare)(void *,void*));
		void InsertSort(Long (*compare)(void *,void*));
		void MergeSort(const Array& one,const Array& oher, Long (*compare)(void *,void*));

		T& GetAt(Long index);
		Array& operator=(const Array& source);
		T& operator[](Long index);

		Long GetCapacity() const;
		Long GetLength() const;

		// 20160512 추가
		void Swap( Long toIndex, Long fromIndex );

	private:
		T (*front);
		Long capacity;
		Long length;
};

template <typename T>
Array<T>::Array(Long capacity){
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;

}

template <typename T>
Array<T>::Array(const Array& source){
	this->front = new T[source.capacity];

	if ( source.length > 0){
		memcpy(this->front, source.front, sizeof(T)*source.length);	
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

template <typename T>
Array<T>::~Array(){
	if(this->front != 0 ){
		delete[] this->front;
	}
}
template <typename T>
Long Array<T>::Store(Long index,T object){
	//memcpy(this->front+index, &object, sizeof(T));	
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::Insert(Long index,T object){
	T (*temp);

	if( this->length >= this->capacity ){
		temp = new T[this->capacity + 128];

		memcpy( temp, this->front, sizeof(T)*(this->length) );
		//memcpy(temp, this->front, sizeof(T)*(index-1));

		if( this->front != 0 ){
			delete[] this->front;
			this->front = 0;
		}
		this->front = temp;	
		this->capacity += 128;
	}

	if( index < this->length ){
		memmove( this->front+index+1, this->front+index,sizeof(T)*(this->length -index) );
	}	

	this->front[index]=object;
	this->length++;	
	
	return index;
}

template <typename T>
Long Array<T>::AppendFromFront(T object){
	Long index= 0;
	T (*temp);

	temp = new T[this->capacity + 128];
	
	if( this->length > 0 ){
		memcpy( temp + 1, this->front, sizeof(T)*(this->length));
	}
	
	if(this->front != 0){
		delete[] this->front;
	}
	
	this->front = temp;
	this->capacity += 128;	
	
	memcpy(this->front + index, &object, sizeof(T));
	this->length++;
	
	return index;
}

template <typename T>
Long Array<T>::AppendFromRear(T object){
#if 0
	Long index =0;
	T (*temp);	

	temp = new T[this->capacity + 128];

	if(this->capacity > 0){
		memcpy(temp, this->front, sizeof(T)*(this->length));

		if(this->front != 0){
			delete[] this->front;
			this->front = 0;
		}
		index = this->capacity;
	}
	
	this->front = temp;
	this->capacity += 128;	
	
	this->front[index] = object;
	//memcpy(this->front +index, &object, sizeof(T));
	this->length++;
#endif
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
Long Array<T>::Delete(Long index){
#if 0
	T (*temp);
	
	if(this->capacity>1){
		temp = new T[this->capacity-1];
	}

	if( index != 0)	{
		memcpy( temp, this->front, sizeof(T)*(index));
	}
	if( index < this->length){
		memcpy( temp+(index), this->front+index+1, sizeof(T)*(this->length -index -1));
	}

	if(this->front != 0){
		delete[] this->front;
		this->front = 0;
	}
	if(this->capacity > 1){
		this->front = temp;
	}

	this->capacity--;
#endif

	if(this->length > 0){
		memmove(this->front+index, this->front+index+1, sizeof(T)*(this->length - ( index + 1 )));
		this->length--;
		index = -1;
	}

	return index;
}

template <typename T>
Long Array<T>::DeleteFromFront(){
	Long index = 0;
	T (*temp);

	if(this->capacity>1){
		temp = new T[this->capacity-1];
	}

	if( this->length > 1){
	memcpy( temp, this->front+1, sizeof(T)*(this->length-1));
	}

	if(this->front != 0 ){
		delete[] this->front;
		this->front = 0;
	}
	if(this->capacity > 1){
		this->front = temp;
	}

	this->capacity--;
	this->length--;
	index=-1;
	
	return index;
	
}

template <typename T>
Long Array<T>::DeleteFromRear(){
	Long index;
	T (*temp);

	if(this->capacity > 1){
		temp = new T[this->capacity-1];
	}

	if( this->length > 1)	{
		memcpy( temp, this->front, sizeof(T)*(this->length-1));
	}
	if(this->front != 0){
		delete[] this->front;
		this->front = 0;
	}
	if(this->capacity > 1){
		this->front = temp;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;

}

template <typename T>
void Array<T>::Clear(){
	if(this->front != 0){
		delete[] this->front;
		this->front=0;
	}
	this->length=0;
	this->capacity=0;
}

template <typename T>		
Long Array<T>::Modify(Long index, T object){
	//memcpy(this->front+index, &object, sizeof(T));
	this->front[index] = object;
	return index;
}

template <typename T>
Long Array<T>::LinearSearchUnique(void *key, Long (*compare)(void *,void *)){
	Long index = -1;
	Long i = 0;

	while(i<this->length && compare(this->front+i,key)!=0){
		i++;
	}
	if(i<this->length){
		index = i;
	}
	return index;
}

template <typename T>
void Array<T>::LinearSearchDuplicate(void *key,Long *(*indexes),Long *count,Long (*compare)(void *,void*)){
	Long i=0;
	Long j=0;
	
	*count=0;
	*indexes = new Long[this->length];
	while(i<this->length){
		if(compare(this->front+i,key)==0){
			(*indexes)[j] = i;
			(*count)++;
			j++;
		}
		i++;
	}
}

template <typename T>
Long Array<T>::BinarySearchUnique(void *key,Long (*compare)(void *,void*)){
	Long low;
	Long high;
	Long mid;
	Long index;

	low = 0;
	high = this->length-1;
	mid = (low+high)/2;

	while(low<=high && compare(this->front+mid,key)!=0){
		if(compare(this->front+mid,key)<0){
			low = mid+1;
		}
		else{
			high = mid-1;
		}
		mid = (low+high)/2;
	}
	if(low<=high){
		index = mid;
	}
	else{
		index = -1;
	}
	return index;

}

template <typename T>
void Array<T>::BinarySearchDuplicate(void *key,Long *(*indexes),Long *count,Long (*compare)(void *,void*)){
	Long low;
	Long mid;
	Long high;
	Long lowIndex;
	Long highIndex;
	Long i;
	Long j;
	*count=0;
	low=0;
	high = this->length-1;
	mid=(low+high)/2;
	while(low<=high && compare(this->front+mid,key) != 0){
		if(compare(this->front+mid,key)<0){
			low = mid+1;
		}
		else{
			high = mid-1;
		}
		mid = (low+high)/2;

	}
	if(low <= high){
		i = mid -1;
		j = mid +1;
		lowIndex=mid;
		highIndex=mid;

		while(i >= 0 && compare(this->front+i,key)==0){
			lowIndex = i;
			i--;
		}
		while(j < this->length && compare(this->front+j,key)==0){
			highIndex = j;
			j++;
		}
		*count = highIndex - lowIndex+1;
		*indexes = new Long[*count];
		i=lowIndex;
		j=0;
		while(j < *count){
			(*indexes)[j]=i;
			i++;
			j++;
		}
	}
}

template <typename T>		
void Array<T>::SelectionSort(Long (*compare)(void *,void*)){
	Long i=0;
	Long j;
	T temp;

	while(i<this->length-1){
		j=i+1;
		while(j<this->length){
			if(compare(this->front+i, this->front+j)>0){
				temp = this->front[i];
				this->front[i]= this->front[j];
				this->front[j]= temp;
			}
			j++;
		}
		i++;
	}
}
	
template <typename T>	
void Array<T>::InsertSort(Long (*compare)(void *,void*)){
	Long i=1;
	Long k;
	T temp;

	while(i<this->length){
		
		temp = this->front[i];

		k=i-1;
		while( k >= 0 && compare(this->front+k,reinterpret_cast<void *>(&temp))>0 ){
			this->front[k+1] = this->front[k];
			k--;
		}
		this->front[k+1] = temp;
		i++;
	}
}

template <typename T>
void Array<T>::MergeSort(const Array& one,const Array& other, Long (*compare)(void *,void*)){
	Long i=0;
	Long j=0;
	Long k=0;

	if(this->front !=0){
		delete[] this->front;
	}
	this->front = new T[(one.length)+(other.length)];

	while(i < one.length && j < other.length )
	{
		if(compare(one.front+i,other.front+j) < 0)
		{
			this->front[k]= one.front[i];
			i++;
		}
		else
		{
			this->front[k]=other.front[j];
			j++;
		}
		k++;
	}
	while(i<one.length){
		this->front[k] = one.front[i];
		k++;
		i++;
	}
	while(j<other.length){
		this->front[k] = other.front[j];
		k++;
		j++;
	}
	this->capacity = one.capacity+other.capacity;
	this->length = one.length+other.length;
}

template <typename T>
T& Array<T>::GetAt(Long index){
	return this->front[index];
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& source){
	if(this->front != 0) {
		delete[] this->front;
	}

	this->front = new T[source.capacity];

	if ( source.length > 0){
		memcpy(this->front, source.front, sizeof(T)*source.length);	
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}
template <typename T>
T& Array<T>::operator[](Long index){
	return this->front[index];
}
template <typename T>
inline Long Array<T>::GetCapacity() const{
	return this->capacity;
}

template <typename T>
inline Long Array<T>::GetLength() const{
	return this->length;
}

template <typename T>
void Array<T>::Swap( Long toIndex, Long fromIndex ){
	assert( toIndex >= 0 && toIndex < this->length );
	assert( fromIndex >= 0 && fromIndex < this->length );
	assert( toIndex != fromIndex );
	
	T object = this->front[fromIndex];
	Long count;
	if( fromIndex > toIndex ){
		count=fromIndex-toIndex;
		memmove( this->front+toIndex+1, this->front+toIndex,sizeof(T)*count);
	}
	else{
		count=toIndex-fromIndex;
		memmove( this->front+fromIndex, this->front+fromIndex+1,sizeof(T)*count);
	}
	this->front[toIndex] = object;	
}

#endif //_ARRRAY_H