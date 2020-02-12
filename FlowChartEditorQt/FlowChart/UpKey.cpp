// UpKey.cpp
#include "UpKey.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "MemoryController.h"

UpKey* UpKey::instance = 0;

UpKey::UpKey(){}

UpKey* UpKey::Instance() {
	if(instance == 0) {
		instance = new UpKey;
	}
	return instance;
}

void UpKey::Destroy() {
	if(instance != 0) {
		delete instance;
		instance = 0;
	}
}

void UpKey::OnKeyDown(DrawingPaper *canvas, UINT nChar, UINT nRepCnt, UINT nFlags){
	Long count;
	Long (*indexes);

	dynamic_cast<FlowChart *>(canvas->flowChart)->GetSelecteds(&indexes,&count);
	canvas->memoryController->RememberOther(indexes, count);
	for ( Long i = 0 ; i < count ; i++ ){
		Shape *shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(indexes[i]);
		Long x = shape->GetX();
		Long y = shape->GetY();

		shape->Move( x, y - DISTANCE);
	}
	canvas->Invalidate(true);
	if( indexes != 0 ){
		delete[] indexes;
	}
}