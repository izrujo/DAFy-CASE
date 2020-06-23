// Tokenizer.cpp
#include "Tokenizer.h"
#define TOKENSIZE 256

#if 0
#include <iostream>
using namespace std;

int main ( int argc , char *argv[] ){
	Long i;
	Tokenizer tokenizer;

	// contents는 사용자가 여러줄을 입력 할 수 있다.
	tokenizer.Scan("40001\t430\t10\t133\t25\t0\t0\tnumber <= \n\r 1000000000000\n\0",'\t');

	i = 0;
	while( i < tokenizer.GetLength() ){
		cout << tokenizer.GetAt(i).GetString() << endl;
		i++;
	}
	return 0;
}
#endif


Tokenizer::Tokenizer()
	:tokens(TOKENSIZE)
{
	this->capacity = TOKENSIZE;
	this->length = 0;	
}

Tokenizer::~Tokenizer(){

}

void Tokenizer::Scan(char (*line), char delimiter){
	String temp;
	Long i = 0;
	Long j;

	this->tokens.Clear();
	this->capacity = 0;
	this->length = 0;

	while ( line[i] != '\0' ){
		j = 0;
		while( line[i] != delimiter && line[i] != '\0' ){
			temp.Store(j,line[i]);
			j++;
			i++;
		}
		
#if 0
		// 저장시 마지막 확장열이 줄바꿈이라서 그 마지막에 줄 바꿈 빼기 위한 처리하려 했으나 \n을 안읽어 옴.. 
		if( line[i] == '\0' ){
			j--;
			temp.Delete(j,1); // 마지막에 종료문자 자동 삽입
			j++;
		}
#endif

		if( this->length < this->capacity ){
			this->tokens.Store(this->length, temp);
			this->length++;
		}
		else{
			this->tokens.AppendFromRear(temp);
			this->capacity++;
			this->length++; 
		}
		i++;
		temp.Empty();
	}
}

String& Tokenizer::GetAt(Long index)
{
	return this->tokens[index];
}