// RightKey.cpp
#include "RightKey.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "MemoryController.h"

RightKey* RightKey::instance = 0;

RightKey::RightKey(){}

RightKey* RightKey::Instance(){
	if( instance == 0 ){
		instance = new RightKey;
	}
	return instance;
}

void RightKey::Destroy(){
	if( instance != 0 ){
		delete instance;
		instance = 0;
	}
}

void RightKey::OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags){
	Long count;
	Long (*indexes);

	dynamic_cast<FlowChart *>(canvas->flowChart)->GetSelecteds(&indexes,&count);
	canvas->memoryController->RememberOther(indexes, count);

	for ( Long i = 0 ; i < count ; i++ ){
		Shape *shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(indexes[i]);
		Long x = shape->GetX();
		Long y = shape->GetY();
		
		shape->Move( x + DISTANCE, y );
	}
	canvas->Invalidate(true);
	if( indexes != 0 ){
		delete[] indexes;
	}
}