// SizeMake.h
#include "SizeMake.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "Symbol.h"

SizeMake::SizeMake() {
}

SizeMake::~SizeMake() {
}

void SizeMake::Create(DrawingPaper *canvas) {
	canvas->flowChart->AscendingSort();

	Long i;
	Long j = 0;
	NShape *shape;
	//NShape* (*indexes) = 0;

	// 1. 선택된 기호들을 찾는다.
	Long count;
	Long(*indexes);
	canvas->flowChart->GetSelecteds(&indexes, &count);
#if 0
	Long it = canvas->flowChart->GetLength();

	if (it > 0) {
		indexes = new NShape*[it];
	}

	i = 0;
	while (i < it) {
		shape = canvas->flowChart->GetAt(i);
		if (shape->IsSelected()) {
			if (dynamic_cast<Symbol *>(shape)) {
				indexes[j] = shape->Clone();
				count++;
				j++;
			}
			else {
				shape->Select(false);
			}
		}
		i++;
	}
	// 2. 가장 상단의 기호를 찾는다.
	Long index;
	Long y = 0;
	i = 0;
	while (i < count) {
		if (indexes[i]->GetY() < y || y == 0) {
			y = indexes[i]->GetY();
			index = i;
		}
		i++;
	}
#endif

	// 3. 상단의 기호의 크기를 기억한다.
	float width;
	float height;
	shape = canvas->flowChart->GetAt(indexes[0]);
	width = shape->GetWidth();
	height = shape->GetHeight();

	// 4. 선택된 기호들의 크기를 기준에 맞게 한다.
	i = 1;
	while (i < count) {
		shape = canvas->flowChart->GetAt(indexes[i]);
		shape->ReSize(width, height);
		i++;
	}
#if 0
	// 5. 순서도의 기호를 지우다.
	i = it - 1;
	while (i >= 0) {
		shape = canvas->flowChart->GetAt(i);
		if (shape->IsSelected()) {
			canvas->flowChart->Detach(i);
		}
		i--;
	}

	// 6. 선택된 도형을 순서도에 끼워넣는다.
	i = 0;
	while (i < count) {
		canvas->flowChart->Attach(indexes[i]);
		i++;
	}
#endif
	// 7. Indexes 해제
	if (indexes != 0) {
		delete[] indexes;
	}
}