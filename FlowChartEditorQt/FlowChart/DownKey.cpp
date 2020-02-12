// DownKey.cpp
#include "DownKey.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "MemoryController.h"

DownKey* DownKey::instance = 0;

DownKey::DownKey(){}

DownKey* DownKey::Instance(){
	if( instance == 0 ){
		instance = new DownKey;
	}
	return instance;
}

void DownKey::Destroy(){
	if( instance != 0 ){
		delete instance;
		instance = 0;
	}
}

void DownKey::OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags){
	Long count;
	Long (*indexes);

	dynamic_cast<FlowChart *>(canvas->flowChart)->GetSelecteds(&indexes,&count);
	canvas->memoryController->RememberOther(indexes, count);

	for ( Long i = 0 ; i < count ; i++ ){
		Shape *shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(indexes[i]);

		Long x = shape->GetX();
		Long y = shape->GetY();
		
		shape->Move( x, y + DISTANCE);
	}

	canvas->Invalidate(true);
	if( indexes != 0 ){
		delete[] indexes;
	}
}