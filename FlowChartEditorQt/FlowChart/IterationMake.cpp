#include "IterationMake.h"
#include "DrawingPaper.h"
#include "Shape.h"
#include "FlowChart.h"
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
	NShape *shape;
	NShape *top, *repeatTrue;
	Long topIndex = -1;
	float x, y, width, height, width2, height2;
	Long i, j;
	Long index = -1;
	Long index_;
	Attribute attribute, initAttribute;
	QRectF rect;
	QRectF bufferRange;

	

	FlowChart buffer(canvas->flowChart->GetCapacity());

	canvas->flowChart->GetSelecteds(&indexes, &length);
	for (i = 0; i < length; i++) {
		shape = canvas->flowChart->GetAt(indexes[i]);
		buffer.Attach(shape->Clone());
		if (index > indexes[i] || index == -1) {
			index = indexes[i];
		}
	}
	if (indexes != 0) {
		delete[] indexes;
	}
	canvas->flowChart->DetachSelectedAll();

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
	buffer.Detach(topIndex);
	buffer.Insert(0, top);

	// top에 붙어 있는 선들을 모두 지운다.
	buffer.Find(ARROW | REPEATTRUE | REPEATFALSE, &indexes, &length);
	for (i = length - 1; i >= 0; i--) {
		attribute = initAttribute;
		if (dynamic_cast<RepeatTrue *>(buffer.GetAt(indexes[i]))) {
			buffer.GetAt(indexes[i])->GetAttribute(&attribute);
			NShape::MakeRectToPoint(attribute.pointOut, &rect);
		}
		else {
			buffer.GetAt(indexes[i])->GetAttribute(&attribute);
			NShape::MakeRectToPoint(attribute.pointIn, &rect);
		}
		if (top->IsIncluded(rect)) {
			buffer.Detach(indexes[i]);
		}
	}

	FlowChart temp(buffer);
	temp.AscendingSort();

	// Arrow를 그린다.
	attribute = initAttribute;
	top->GetAttribute(&attribute);
	x = attribute.pointOut.x();
	y = attribute.pointOut.y();
	width = 0;
	height = temp.GetAt(1)->GetY() - y;
	shape = new Arrow(x, y, width, height, QColor(0, 0, 0), Qt::SolidLine, QColor(0, 0, 0), String("TRUE"));
	shape->Select(true);
	Long position = buffer.Insert(1, shape);

	// 마지막이 Arrow이면 지운다.
	j = temp.GetLength() - 1;
	if (dynamic_cast<Arrow *>(temp.GetAt(j))) {
		index_ = buffer.Find(temp.GetAt(j));
		buffer.Detach(index_);
		temp.Detach(j);
		j--;
	}

	// RepeatTrue를 그린다.	
	attribute = initAttribute;
	temp.GetAt(j)->GetAttribute(&attribute);
	x = attribute.pointOut.x();
	y = attribute.pointOut.y();

	attribute = initAttribute;
	top->GetAttribute(&attribute);
	width = attribute.pointIn.x() - x - 10;
	height = attribute.pointIn.y() - y - 10;

	// 새로 만들 반복선의 범위를 구한다.
	bufferRange = buffer.GetRange();
	width2 = bufferRange.left() - 20 - x;
	height2 = y - bufferRange.bottom() + 40;
	repeatTrue = new RepeatTrue(x, y, width, height, width2, height2, QColor(0, 0, 0), Qt::SolidLine, QColor(0, 0, 0), String(" "));
	repeatTrue->Select(true);
	buffer.Attach(repeatTrue);

	attribute = initAttribute;
	top->GetAttribute(&attribute);
	x = attribute.pointFalse.x();
	y = attribute.pointFalse.y();
	width = repeatTrue->GetX() - x;
	width2 = bufferRange.right() - x + 20;
	height2 = repeatTrue->GetY() + dynamic_cast<RepeatTrue *>(repeatTrue)->GetHeight2() - y + 35;
	height = height2 + 40;

	shape = new RepeatFalse(x, y, width, height, width2, height2, 
		QColor(0, 0, 0), Qt::SolidLine, QColor(0, 0, 0), String("FALSE"));
	shape->Select(true);
	buffer.Attach(shape);

	Long(*positions) = new Long[buffer.GetLength()];
	j = 0;
	Long count = 0;

	for (i = 0; i < buffer.GetLength(); i++) {
		Long position = canvas->flowChart->Insert(index + i, buffer.GetAt(i)->Clone());
		if (dynamic_cast<Line*>(buffer.GetAt(i))) {
			positions[j++] = position;
			count++;
		}
	}
	canvas->memoryController->RememberAdd(positions, count);

	if (positions != 0) {
		delete[] positions;
	}

	canvas->repaint();
}