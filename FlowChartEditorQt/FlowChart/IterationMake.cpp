#include "IterationMake.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "Decision.h"
#include "Arrow.h"
#include "RepeatTrue.h"
#include "RepeatFalse.h"
#include "Process.h"
#include "RightDownJoin.h"
#include "Join.h"
#include "MemoryController.h"

IterationMake::IterationMake() {
}

IterationMake::~IterationMake() {
}

void IterationMake::Create(DrawingPaper *canvas) {
	// 1. 배열 첨자가 가장 작은 도형을 찾는다.
	Long(*indexes);
	Long length;
	Shape *shape;
	Shape *top, *repeatTrue;
	Long topIndex = -1;
	Long x, y, width, height, width2, height2;
	Long i, j;
	Long index = -1;
	Long index_;
	Attribute attribute, initAttribute;
	RECT rect;
	RECT bufferRange;

	

	FlowChart buffer((dynamic_cast<FlowChart *>(canvas->flowChart))->GetCapacity());

	dynamic_cast<FlowChart *>(canvas->flowChart)->GetSelecteds(&indexes, &length);
	for (i = 0; i < length; i++) {
		shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(indexes[i]);
		buffer.Attach(shape->Clone());
		if (index > indexes[i] || index == -1) {
			index = indexes[i];
		}
	}
	if (indexes != 0) {
		delete[] indexes;
	}
	dynamic_cast<FlowChart *>(canvas->flowChart)->EraseSelectedAll();

	i = 0;
	while (i < buffer.GetLength()) {
		if (dynamic_cast<Decision *>(buffer.GetAt(i))) {
			if (topIndex == -1 || buffer.GetAt(i)->GetY() < buffer.GetAt(topIndex)->GetY()) {
				topIndex = i;
			}
		}
		i++;
	}

	top = buffer.GetAt(topIndex)->Clone();
	buffer.Erase(topIndex);
	buffer.Insert(0, top);

	// top에 붙어 있는 선들을 모두 지운다.
	buffer.Find(ARROW | REPEATTRUE | REPEATFALSE, &indexes, &length);
	for (i = length - 1; i >= 0; i--) {
		attribute = initAttribute;
		if (dynamic_cast<RepeatTrue *>(buffer.GetAt(indexes[i]))) {
			buffer.GetAt(indexes[i])->GetAttribute(&attribute);
			Shape::MakeRectToPoint(attribute.pointOut, &rect);
		}
		else {
			buffer.GetAt(indexes[i])->GetAttribute(&attribute);
			Shape::MakeRectToPoint(attribute.pointIn, &rect);
		}
		if (top->IsIncluded(canvas->painter, rect)) {
			buffer.Erase(indexes[i]);
		}
	}

	FlowChart temp(buffer);
	temp.AscendingSort();

	// Arrow를 그린다.
	attribute = initAttribute;
	top->GetAttribute(&attribute);
	x = attribute.pointOut.x;
	y = attribute.pointOut.y;
	width = 0;
	height = temp.GetAt(1)->GetY() - y;
	shape = new Arrow(x, y, width, height, 20, DASH, 20, String("TRUE"));
	shape->Select(true);
	Long position = buffer.Insert(1, shape);

	// 마지막이 Arrow이면 지운다.
	j = temp.GetLength() - 1;
	if (dynamic_cast<Arrow *>(temp.GetAt(j))) {
		index_ = buffer.Find(temp.GetAt(j));
		buffer.Erase(index_);
		temp.Erase(j);
		j--;
	}

	// RepeatTrue를 그린다.	
	attribute = initAttribute;
	temp.GetAt(j)->GetAttribute(&attribute);
	x = attribute.pointOut.x;
	y = attribute.pointOut.y;

	attribute = initAttribute;
	top->GetAttribute(&attribute);
	width = attribute.pointIn.x - x;
	height = attribute.pointIn.y - y;

	// 새로 만들 반복선의 범위를 구한다.
	buffer.GetRange(&bufferRange);
	width2 = bufferRange.left - 20 - x;
	height2 = y - bufferRange.bottom + 40;
	repeatTrue = new RepeatTrue(x, y, width, height, width2, height2, 20, DASH, 20, String(" "));
	repeatTrue->Select(true);
	buffer.Attach(repeatTrue);

	attribute = initAttribute;
	top->GetAttribute(&attribute);
	x = attribute.pointFalse.x;
	y = attribute.pointFalse.y;
	width = repeatTrue->GetX() - x;
	width2 = bufferRange.right - x + 20;
	height2 = repeatTrue->GetY() + dynamic_cast<RepeatTrue *>(repeatTrue)->GetHeight2() - y + 35;
	height = height2 + 20;

	shape = new RepeatFalse(x, y, width, height, width2, height2, 20, DASH, 20, String("FALSE"));
	shape->Select(true);
	buffer.Attach(shape);

	Long(*positions) = new Long[buffer.GetLength()];
	j = 0;
	Long count = 0;

	for (i = 0; i < buffer.GetLength(); i++) {
		Long position = dynamic_cast<FlowChart *>(canvas->flowChart)->Insert(index + i, buffer.GetAt(i)->Clone());
		if (dynamic_cast<Line*>(buffer.GetAt(i))) {
			positions[j++] = position;
			count++;
		}
	}
	canvas->memoryController->RememberAdd(positions, count);

	if (positions != 0) {
		delete[] positions;
	}

	canvas->RedrawWindow();
}