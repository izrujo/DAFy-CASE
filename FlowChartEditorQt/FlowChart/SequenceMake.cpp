//SequenceMake.cpp

#include "SequenceMake.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "Symbol.h"
#include "Decision.h"
#include "Arrow.h"
#include "LeftDown.h"
#include "RightDown.h"
#include "Join.h"
#include "RightDownJoin.h"
#include "RepeatTrue.h"
#include "RepeatFalse.h"
#include "MemoryController.h"

SequenceMake::SequenceMake() {
}

SequenceMake::~SequenceMake() {
}

void SequenceMake::Create(DrawingPaper *canvas) {
	// 1. 배열 첨자가 가장 작은 도형을 찾는다.	
	Long(*indexes);
	Long length;
	Shape *shape;
	Shape *arrow;
	Long x, y, width, height;
	Long i, j, k;
	Long index = -1;

	dynamic_cast<FlowChart *>(canvas->flowChart)->GetSelecteds(&indexes, &length);

	FlowChart buffer(length);
	FlowChart arrows(length);

	for (i = 0; i < length; i++) {
		shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(indexes[i]);
		if (dynamic_cast<Symbol *>(shape)) {
			buffer.Attach(shape->Clone());
			if (index > indexes[i] || index == -1) {
				index = indexes[i];
			}
		}
		else if (!dynamic_cast<Arrow *>(shape)) {
			shape->Select(false);
		}
	}

	if (indexes != 0) {
		delete[] indexes;
	}

	dynamic_cast<FlowChart *>(canvas->flowChart)->EraseSelectedAll();

	buffer.AscendingSort();

	Attribute attribute;
	for (i = 0; i < buffer.GetLength() - 1; i++) {
		buffer.GetAt(i)->GetAttribute(&attribute);
		x = attribute.pointOut.x;
		y = attribute.pointOut.y;
		width = 0;
		height = buffer.GetAt(i + 1)->GetY() - attribute.pointOut.y;
		if (height > 0) {
			arrow = new Arrow(x, y, width, height, 20, DASH, 20, String(" "));
			arrow->Select(true);
			arrows.Attach(arrow);
		}
	}

	Long(*positions) = new Long[buffer.GetLength() + arrows.GetLength()];
	Long count = 0;
	i = 0;
	j = 0;
	k = 0;
	while (i < buffer.GetLength() || j < arrows.GetLength()) {
		if (i < buffer.GetLength()) {
			dynamic_cast<FlowChart *>(canvas->flowChart)->Insert(index + k, buffer.GetAt(i)->Clone());
			k++;
			i++;
		}
		if (j < arrows.GetLength()) {
			positions[j] = dynamic_cast<FlowChart *>(canvas->flowChart)->Insert(index + k, arrows.GetAt(j)->Clone());
			count++;
			k++;
			j++;
		}
	}
	canvas->memoryController->RememberAdd(positions, count);

	if (positions != 0) {
		delete[] positions;
	}

	canvas->RedrawWindow();
}