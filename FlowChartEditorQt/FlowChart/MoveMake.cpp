//MoveMake.cpp

#include "MoveMake.h"
#include "DrawingPaper.h"
#include "Shape.h"
#include "RightDown.h"
#include "LeftDown.h"
#include "RightDownJoin.h"
#include "Join.h"
#include "RepeatFalse.h"
#include "MemoryController.h"

MoveMake::MoveMake(){
}

MoveMake::~MoveMake(){
}

void MoveMake::Create(DrawingPaper *canvas){
	Long i;
	Long j = 0;
	Long count = 0;
	Long it;
	NShape *shape;
	NShape* (*indexes) = 0;

	// 1. 선택된 기호들을 찾는다.
	i = 0;
	it = canvas->flowChart->GetLength();
	indexes = new NShape*[it];

	Long(*positions) = new Long[it];

	while ( i < it ){
		shape = canvas->flowChart->GetAt(i);
		if( shape->IsSelected() ){
			indexes[j] = shape->Clone();
			positions[j] = i;
			count++;
			j++;
		}
		i++;
	}

	canvas->memoryController->RememberOther(positions, count);

	// 2. 가장 상단의 기호를 찾는다.	
	float y = 0;
	Long index;
	i = 0;
	while ( i < count ){
		if( indexes[i]->GetY() < y || y == 0.0F ){
			y = indexes[i]->GetY();
			index = i;
		}
		i++;
	}

	// 3. 상단의 위치를 기억한다.
	float x;
	Attribute attribute;
	Attribute attribute2;
	float distance;
	indexes[index]->GetAttribute(&attribute);	

	// 4. 선택된 기호들을 기준에 맞게 이동한다.
	i = 0;
	while ( i < count ){
		y = indexes[i]->GetY();
		x = indexes[i]->GetX();
		indexes[i]->GetAttribute(&attribute2);
		distance = attribute2.pointIn.x() -attribute.pointIn.x();
		indexes[i]->Move(x-distance,y);
		i++;
	}

	// 5. 순서도의 기호를 지우다.
	i = it -1;
	while ( i >= 0 ){
		shape = canvas->flowChart->GetAt(i);
		if( shape->IsSelected()){
			canvas->flowChart->Detach(i);
		}
		i--;
	}

	// 6. 선택된 도형을 순서도에 끼워넣는다.
	i = 0;
	while( i < count ){
		canvas->flowChart->Attach(indexes[i]);
		i++;
	}

	// 7. Indexes 해제
	if (indexes != 0) {
		delete[] indexes;
	}

	if (positions != 0) {
		delete[] positions;
	}
}