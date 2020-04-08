// IntervalMake.cpp

#include "IntervalMake.h"
#include "DrawingPaper.h"
#include "Shape.h"
#include "Symbol.h"
#include "MemoryController.h"

IntervalMake::IntervalMake(){
}

IntervalMake::~IntervalMake(){
}

void IntervalMake::Create(DrawingPaper *canvas){
	// 1. 선택된 도형들을 찾는다.
	NShape *shape;
	Long count = 0;

	Long it = canvas->flowChart->GetLength();
	NShape* (*indexes) = new NShape* [it];
	Long(*positions) = new Long[it];

	Long i = 0;	
	while ( i < it ){
		shape = canvas->flowChart->GetAt(i);
		if( shape->IsSelected()){
			//  선택된 기호들 중 연결 선을 제외한다.
			if( dynamic_cast<Symbol *>(shape) ){
				indexes[count] = shape->Clone();
				positions[count] = i;
				count++;
			}
			else{
				shape->Select(false);
			}
		}
		i++;
	}

	// 2. 도형들을 y 좌표를 기준으로 오름차순으로 정렬 한다. (삽입정렬)
	NShape *temp;	
	Long y;
	Long y_;
	Long j;
	Long k;
	for( i = 1 ; i < count; i++){		
		y = indexes[i]->GetY();		
		j = 0;		
		y_ = indexes[j]->GetY();
		while( j < i &&  y_ < y ){
			j++;
			y_ = indexes[j]->GetY();
		}

		temp = indexes[i];

		for(k = i ; k >= j+1; k--){
			indexes[k] = indexes[k-1];
		}
		indexes[k] = temp;
	}

	// 3. 도형간 간격을 구한다. 전체길이에서 도형들의 길이를 빼고 도형의 개수 - 1 으로 나눈다.
	Long height = indexes[count-1]->GetY() - indexes[0]->GetY() - indexes[0]->GetHeight();

	i = 1;
	while ( i < count-1 ){
		height = height - indexes[i]->GetHeight();
		i++;
	}
	Long interval = height/(count-1);

	// 4. 도형을 재 배치 한다.
	canvas->memoryController->RememberOther(positions, count);

	Long previousHeight; // 이전까지의 길이
	previousHeight = indexes[0]->GetY() + indexes[0]->GetHeight();
	i = 1; // 첫번 째 도형은 위치 고정
	while ( i < count ){
		indexes[i]->Move(indexes[i]->GetX(), previousHeight + interval);
		previousHeight = previousHeight + interval + indexes[i]->GetHeight();
		i++;
	}

	// 5. 순서도의 선택된 도형을 지운다.
	i = it -1;
	while ( i >= 0 ){
		shape = canvas->flowChart->GetAt(i);
		if( shape->IsSelected()){
			canvas->flowChart->Detach(i);
		}
		i--;
	}

	// 6. 순서도에 선택된 도형을 끼워 넣는다.
	i = 0;
	while ( i < count ){
		canvas->flowChart->Attach(indexes[i]);
		i++;
	}

	if ( indexes != 0 ){
		delete[] indexes;
	}

	if (positions != 0) {
		delete[] positions;
	}
}