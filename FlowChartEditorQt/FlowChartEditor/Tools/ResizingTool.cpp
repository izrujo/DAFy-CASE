#include "ResizingTool.h"
#include "SelectingTool.h"

#include "../Interface/DrawingPaper.h"
#include "../Interface/FlowChartEditor.h"
#include "../Interface/Scroll.h"
#include "../Observer/ScrollController.h"
#include "../Shapes/Shape.h"
#include "../Shapes/Symbols/Symbol.h"
#include "../Shapes/Lines/Arrow.h"
#include "../Shapes/Lines/LeftDown.h"
#include "../Shapes/Lines/RightDown.h"
#include "../Shapes/Lines/RightDownJoin.h"
#include "../Shapes/Lines/Join.h"
#include "../Shapes/Lines/RepeatTrue.h"
#include "../Shapes/Lines/RepeatFalse.h"

#include <stdio.h>

#pragma warning (disable : 4996)

ResizingTool* ResizingTool::instance = 0;

ResizingTool::ResizingTool() {
}

ResizingTool* ResizingTool::Instance() {
	if (instance == 0) {
		instance = new ResizingTool;
	}
	return instance;
}

void ResizingTool::Destroy() {
	if (instance != 0) {
		delete instance;
		instance = 0;
	}
}

void ResizingTool::OnLButtonDown(DrawingPaper *canvas, QPointF point) {
	canvas->currentX = point.x();
	canvas->currentY = point.y();

	Long count;
	Long(*indexes);
	canvas->flowChart->GetSelecteds(&indexes, &count);
	if (indexes != 0) {
		delete[] indexes;
	}
}

void ResizingTool::OnMouseMove(DrawingPaper *canvas, QPointF point) {
	float x, y, width, height, width2, height2;
	NShape *shape;
	shape = canvas->flowChart->GetAt(canvas->indexOfSelected);
	
	Long(*indexes)=new Long[canvas->flowChart->GetLength()];
	indexes[0] = canvas->indexOfSelected;

	if (dynamic_cast<Symbol *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_TOPLEFT:
			x = shape->GetLeft() + point.x() - canvas->currentX;
			y = shape->GetTop() + point.y() - canvas->currentY;
			width = shape->GetRight() - x;
			height = shape->GetBottom() - y;
			break;

		case HIT_TOPMIDDLE:
			x = shape->GetLeft();
			y = shape->GetTop() + point.y() - canvas->currentY;
			width = shape->GetRight() - x;
			height = shape->GetBottom() - y;
			break;

		case HIT_TOPRIGHT:
			x = shape->GetLeft();
			y = shape->GetTop() + point.y() - canvas->currentY;
			width = shape->GetRight() + point.x() - canvas->currentX - x;
			height = shape->GetBottom() - y;
			break;

		case HIT_LEFTMIDDLE:
			x = shape->GetLeft() + point.x() - canvas->currentX;
			y = shape->GetTop();
			width = shape->GetRight() - x;
			height = shape->GetBottom() - y;
			break;

		case HIT_RIGHTMIDDLE:
			x = shape->GetLeft();
			y = shape->GetTop();
			width = shape->GetRight() + point.x() - canvas->currentX - x;
			height = shape->GetBottom() - y;
			break;

		case HIT_BOTTOMLEFT:
			x = shape->GetLeft() + point.x() - canvas->currentX;
			y = shape->GetTop();
			width = shape->GetRight() - x;
			height = shape->GetBottom() + point.y() - canvas->currentY - y;
			break;

		case HIT_BOTTOMMIDDLE:
			x = shape->GetLeft();
			y = shape->GetTop();
			width = shape->GetRight() - x;
			height = shape->GetBottom() + point.y() - canvas->currentY - y;
			break;

		case HIT_BOTTOMRIGHT:
			x = shape->GetLeft();
			y = shape->GetTop();
			width = shape->GetRight() + point.x() - canvas->currentX - x;
			height = shape->GetBottom() + point.y() - canvas->currentY - y;
			break;
		}
		if (width >= 150.0F && height >= 50.0F) {
			shape->Move(x, y);
			shape->ReSize(width, height);
		}
	}
	else if (dynamic_cast<Arrow *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_IN:
			x = shape->GetX();
			y = shape->GetY() + point.y() - canvas->currentY;
			width = shape->GetWidth();
			height = shape->GetBottom() - y;
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth();
			height = shape->GetHeight() + point.y() - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		shape->ReSize(width, height);
	}
	else if (dynamic_cast<LeftDown *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_IN:
			x = shape->GetX() + point.x() - canvas->currentX;
			y = shape->GetY() + point.y() - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x() - canvas->currentX;
			height = shape->GetHeight() + point.y() - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		shape->ReSize(width, height);
	}
	else if (dynamic_cast<RightDown *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_IN:
			x = shape->GetX() + point.x() - canvas->currentX;
			y = shape->GetY() + point.y() - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x() - canvas->currentX;
			height = shape->GetHeight() + point.y() - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		shape->ReSize(width, height);
	}
	else if (dynamic_cast<Join *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_TRUE:
			x = shape->GetX() + point.x() - canvas->currentX;
			y = shape->GetY() + point.y() - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			height2 = dynamic_cast<Join *>(shape)->GetHeight2();
			break;
		case HIT_FALSE:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x() - canvas->currentX;
			height = shape->GetHeight() + point.y() - canvas->currentY;
			height2 = dynamic_cast<Join *>(shape)->GetHeight2();
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth();
			height = shape->GetHeight();
			height2 = dynamic_cast<Join *>(shape)->GetHeight2() + point.y() - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		dynamic_cast<Join *>(shape)->ReSize(width, height, height2);
	}
	else if (dynamic_cast<RightDownJoin *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_FALSE:
			x = shape->GetX() + point.x() - canvas->currentX;
			y = shape->GetY() + point.y() - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			width2 = dynamic_cast<RightDownJoin *>(shape)->GetWidth2();
			height2 = dynamic_cast<RightDownJoin *>(shape)->GetHeight2();
			break;
		case HIT_HANDLE:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth();
			height = shape->GetHeight();
			width2 = dynamic_cast<RightDownJoin *>(shape)->GetWidth2() + point.x() - canvas->currentX;
			height2 = dynamic_cast<RightDownJoin *>(shape)->GetHeight2() + point.y() - canvas->currentY;
			break;
		case HIT_TRUE:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x() - canvas->currentX;
			height = shape->GetHeight() + point.y() - canvas->currentY;
			width2 = dynamic_cast<RightDownJoin *>(shape)->GetWidth2();
			height2 = dynamic_cast<RightDownJoin *>(shape)->GetHeight2();
			break;
		}
		shape->Move(x, y);
		dynamic_cast<RightDownJoin *>(shape)->ReSize(width, height, width2, height2);
	}
	else if (dynamic_cast<RepeatTrue *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_IN:
			x = shape->GetX() + point.x() - canvas->currentX;
			y = shape->GetY() + point.y() - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			width2 = dynamic_cast<RepeatTrue *>(shape)->GetWidth2();
			height2 = dynamic_cast<RepeatTrue *>(shape)->GetHeight2();
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x() - canvas->currentX;
			height = shape->GetHeight() + point.y() - canvas->currentY;
			width2 = dynamic_cast<RepeatTrue *>(shape)->GetWidth2();
			height2 = dynamic_cast<RepeatTrue *>(shape)->GetHeight2();
			break;
		case HIT_HANDLE:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth();
			height = shape->GetHeight();
			width2 = dynamic_cast<RepeatTrue *>(shape)->GetWidth2() + point.x() - canvas->currentX;
			height2 = dynamic_cast<RepeatTrue *>(shape)->GetHeight2() + point.y() - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		dynamic_cast<RepeatTrue *>(shape)->ReSize(width, height, width2, height2);

	}
	else if (dynamic_cast<RepeatFalse *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_IN:
			x = shape->GetX() + point.x() - canvas->currentX;
			y = shape->GetY() + point.y() - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			width2 = dynamic_cast<RepeatFalse *>(shape)->GetWidth2();
			height2 = dynamic_cast<RepeatFalse *>(shape)->GetHeight2();
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x() - canvas->currentX;
			height = shape->GetHeight() + point.y() - canvas->currentY;
			width2 = dynamic_cast<RepeatFalse *>(shape)->GetWidth2();
			height2 = dynamic_cast<RepeatFalse *>(shape)->GetHeight2();
			break;
		case HIT_HANDLE:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth();
			height = shape->GetHeight();
			width2 = dynamic_cast<RepeatFalse *>(shape)->GetWidth2() + point.x() - canvas->currentX;
			height2 = dynamic_cast<RepeatFalse *>(shape)->GetHeight2() + point.y() - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		dynamic_cast<RepeatFalse *>(shape)->ReSize(width, height, width2, height2);
	}
	canvas->currentX = point.x();
	canvas->currentY = point.y();
	canvas->repaint();

	if (indexes != 0) {
		delete[] indexes;
	}
}

void ResizingTool::OnLButtonUp(DrawingPaper *canvas, QPointF point) {
	// 20160720 도형 크기 변경시 삽입하는 방식으로 수정
	canvas->mode = DrawingPaper::SELECT;
	canvas->tool = SelectingTool::Instance();
	canvas->repaint();
}