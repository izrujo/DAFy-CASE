// Visitor.cpp

#include "DrawVisitor.h"
#include "Terminal.h"
#include "Preparation.h"
#include "PunchedCard.h"
#include "InputOutput.h"
#include "Process.h"
#include "Document.h"
#include "Arrow.h"
#include "LeftDown.h"
#include "RightDown.h"
#include "Join.h"
#include "RightDownJoin.h"
#include "RepeatTrue.h"
#include "RepeatFalse.h"
#include "Decision.h"
#include "FlowChart.h"
#include "Shape.h"
#include "Template.h"
#include "Label.h"
#include "../Notepad/CharacterMetrics.h"
#include "ScrollController.h"
#include "Scrolls.h"
#include "NumberBox.h"
#include "A4Paper.h"
#include "TextRegion.h"
#include "TutorialMark.h"

DrawVisitor::DrawVisitor(Painter *painter, ScrollController *scrollController)
	:FlowChartVisitor() {
	this->painter = painter;
	this->scrollController = scrollController;
}

DrawVisitor::~DrawVisitor() {
}

void DrawVisitor::Visit(Terminal *element) {
	CRgn region;
	Long x, y, width, height, halfHeight;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();
	halfHeight = height / 2;

	POINT points[5] = { {x + halfHeight,y},{x + width - halfHeight,y},{x + width - halfHeight,y + height},{x + halfHeight,y + height},{x + halfHeight,y} };


	painter->BeginPath();
	painter->DrawArc(x, y, x + height, y + height, x + halfHeight, y, x + halfHeight, y + height);
	painter->DrawArc(x + width - height, y, x + width, y + height, x + width - halfHeight, y + height, x + width - halfHeight, y);
	painter->EndPath();

	painter->CreateFromPath(&region);

	painter->FillRegion(region, element->GetBackGroundColor());
	painter->FillBackground(points, 5, element->GetBackGroundColor());

	painter->DrawArc(x, y, x + height, y + height, x + halfHeight, y, x + halfHeight, y + height);
	painter->DrawArc(x + width - height, y, x + width, y + height, x + width - halfHeight, y + height, x + width - halfHeight, y);

	painter->DrawLine(x + halfHeight, y, x + width - halfHeight, y);
	painter->DrawLine(x + halfHeight, y + height, x + width - halfHeight, y + height);

	//입체 효과
	painter->DrawArc(x + width - height + 1, y + 1, x + width + 1, y + height + 1, x + width - halfHeight + 1, y + height + 1, x + width - halfHeight + 1, y + 1);
	painter->DrawLine(x + halfHeight - 3, y + height + 1, x + width - halfHeight + 1, y + height + 1);

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();

	RECT rect = { x, y + (height - contentsHeight) / 2, x + width, y + height };

	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Preparation *element) {
	Long x, y, width, height;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();

	Long gap = (Long)height / 2;
	POINT shapePoint[7] = { {x + gap, y},{x + width - gap, y},{x + width, y + gap},{x + width - gap,y + height},{x + gap,y + height},{x,y + gap},{x + gap,y} };
	painter->FillBackground(shapePoint, 7, element->GetBackGroundColor());

	painter->DrawPolyline(shapePoint, 7);

	painter->DrawLine(x + gap + 1, y + height + 1, x + width - gap + 1, y + height + 1);
	painter->DrawLine(x + width - gap + 1, y + height + 1, x + width + 1, y + gap + 1);

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();

	RECT rect = { x + gap, y + (height - contentsHeight) / 2, x + width - gap, y + height };

	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(PunchedCard *element) {
	Long x, y, width, height;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();

	Long gap = (Long)height / 4;
	POINT shapePoint[6] = { {x + gap,y},{x + width,y},{x + width,y + height},{x,y + height},{x,y + gap},{x + gap,y} };

	painter->FillBackground(shapePoint, 6, LTGRAY_BRUSH);

	painter->DrawPolyline(shapePoint, 6);

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();

	RECT rect = { x, y + (height - contentsHeight) / 2, x + width, y + height };

	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(InputOutput *element) {
	Long x, y, width, height;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();

	Long halfHeight = (Long)height / 2;
	POINT shapePoint[5] = { {x + halfHeight,y},{x + width,y},{x + width - halfHeight,y + height},{x,y + height},{x + halfHeight,y} };

	painter->FillBackground(shapePoint, 5, element->GetBackGroundColor());
	painter->DrawPolyline(shapePoint, 5);

	//입체효과
	painter->DrawLine(x + 1, y + height + 1, x + width - halfHeight + 1, y + height + 1);
	painter->DrawLine(x + width - halfHeight + 1, y + height + 1, x + width + 1, y + 1);

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();

	RECT rect = { x + halfHeight, y + (height - contentsHeight) / 2, x + width - halfHeight, y + height };

	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Process *element) {
	Long x, y, width, height;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();

	POINT point[5] = { {x,y},{x + width,y},{x + width,y + height},{x,y + height},{x,y} };
	painter->FillBackground(point, 5, element->GetBackGroundColor());
	painter->DrawPolyline(point, 5);

	//입체효과
	painter->DrawLine(x + 1, y + height + 1, x + width + 1, y + height + 1);
	painter->DrawLine(x + width + 1, y + height + 1, x + width + 1, y + 1);

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();

	RECT rect = { x, y + (height - contentsHeight) / 2 , x + width, y + height };

	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Decision *element) {
	Long x, y, width, height;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();
	Long halfWidth = width / 2;
	Long halfHeight = height / 2;
	POINT shapePoint[5] = { {x + halfWidth,y},{x + width,y + halfHeight},{x + halfWidth,y + height},{x,y + halfHeight},{x + halfWidth,y} };

	painter->FillBackground(shapePoint, 5, element->GetBackGroundColor());
	painter->DrawPolyline(shapePoint, 5);

	//입체 효과
	painter->DrawLine(x + halfWidth + 1, y + height + 1, x + width + 1, y + halfHeight + 1);

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();

	RECT rect = { x + halfHeight, y + (height - contentsHeight) / 2, x + width - halfHeight, y + height - halfHeight / 2 };

	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Document *element) {
	CRgn region;
	Long x, y, width, height;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();

	Long quarterWidth = width / 4;
	Long thirdHeight = height / 3;
	Long eighthHeight = height / 8;

	POINT shapePoint[4] = { {x,y + height - eighthHeight},{x,y},{x + width,y},{x + width,y + height - eighthHeight} };

	CPoint bezierPoint[4];
	bezierPoint[0].x = x;
	bezierPoint[0].y = y + height - eighthHeight;
	bezierPoint[1].x = x + quarterWidth;
	bezierPoint[1].y = y + height + thirdHeight - eighthHeight;
	bezierPoint[2].x = x + width - quarterWidth;
	bezierPoint[2].y = y + height - thirdHeight - eighthHeight;
	bezierPoint[3].x = x + width;
	bezierPoint[3].y = y + height - eighthHeight;

	painter->BeginPath();
	painter->DrawPolyline(shapePoint, 4);
	painter->DrawBezier(bezierPoint, 4);
	painter->EndPath();
	painter->CreateFromPath(&region);

	painter->FillRegion(region, LTGRAY_BRUSH);

	painter->DrawPolyline(shapePoint, 4);
	painter->DrawBezier(bezierPoint, 4);

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();

	RECT rect = { x, y + (height - contentsHeight) / 2, x + width, y + height };

	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Arrow *element) {
	Long x, y, width, height;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();

	painter->DrawLine(x, y, x, y + height - 4);

	Long quotient = height / 4;
	Long remainder = height % 4;
	if (remainder >= 2) quotient++;
	Long endLength = quotient;
	CPoint arrow[4];
	arrow[0].x = x - endLength / 2;
	arrow[0].y = y + height - endLength;
	arrow[1].x = x;
	arrow[1].y = y + height;
	arrow[2].x = x + endLength / 2;
	arrow[2].y = y + height - endLength;
	arrow[3].x = x;
	arrow[3].y = y + height - endLength / 3;
	painter->DrawPolygon(arrow, 4);
	painter->FillPolygon(arrow, 4, RGB(166, 166, 166));

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();
	Long contentsWidth = -1 * font.lfHeight * element->GetContents().GetLength();

	RECT rect = { x, y, x + contentsWidth, y + height };
	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);


	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(LeftDown *element) {
	Long x, y, width, height;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();

	painter->DrawLine(x, y, x + width, y);
	painter->DrawLine(x + width, y, x + width, y + height - 4);

	Long quotient = height / 4;
	Long remainder = height % 4;
	if (remainder >= 2) quotient++;
	Long endLength = quotient;
	POINT arrow[4];
	arrow[0].x = x + width - endLength / 2;
	arrow[0].y = y + height - endLength;
	arrow[1].x = x + width;
	arrow[1].y = y + height;
	arrow[2].x = x + width + endLength / 2;
	arrow[2].y = y + height - endLength;
	arrow[3].x = x + width;
	arrow[3].y = y + height - endLength / 3;
	
	painter->DrawPolygon(arrow, 4);

	painter->FillPolygon(arrow, 4, RGB(166, 166, 166));

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();
	Long contentsWidth = -1 * font.lfHeight * element->GetContents().GetLength();

	RECT rect = { x - contentsWidth, y - contentsHeight, x, y };
	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(RightDown *element) {
	Long x, y, width, height;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();

	painter->DrawLine(x, y, x + width, y);
	painter->DrawLine(x + width, y, x + width, y + height - 4);

	Long quotient = height / 4;
	Long remainder = height % 4;
	if (remainder >= 2) quotient++;
	Long endLength = quotient;
	POINT arrow[4];
	arrow[0].x = x + width - endLength / 2;
	arrow[0].y = y + height - endLength;
	arrow[1].x = x + width;
	arrow[1].y = y + height;
	arrow[2].x = x + width + endLength / 2;
	arrow[2].y = y + height - endLength;
	arrow[3].x = x + width;
	arrow[3].y = y + height - endLength / 3;
	painter->DrawPolygon(arrow, 4);

	painter->FillPolygon(arrow, 4, RGB(166, 166, 166));

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();
	Long contentsWidth = -1 * font.lfHeight * element->GetContents().GetLength();

	RECT rect = { x, y - contentsHeight, x + contentsWidth, y };
	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Join *element) {
	Long x, y, width, height, height2;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();
	height2 = element->GetHeight2();


	POINT points[4];
	points[0].x = x;
	points[0].y = y;
	points[1].x = x;
	points[1].y = y + height2;
	points[2].x = x + width;
	points[2].y = y + height2;
	points[3].x = x + width;
	points[3].y = y + height;

	painter->DrawPolyline(points, 4);

	// 텍스트를 출력한다.
	RECT rect = { x, y, x + width, y + height };

	painter->DrawText(18, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(RightDownJoin *element) {
	Long x, y, width, height, width2, height2;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();
	width2 = element->GetWidth2();
	height2 = element->GetHeight2();

	POINT points[5];

	points[0].x = x;
	points[0].y = y;
	points[1].x = x + width2;
	points[1].y = y;
	points[2].x = x + width2;
	points[2].y = y + height + height2;
	points[3].x = x + width;
	points[3].y = y + height + height2;
	points[4].x = x + width;
	points[4].y = y + height;

	painter->DrawPolyline(points, 5);

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();
	Long contentsWidth = -1 * font.lfHeight * element->GetContents().GetLength();

	RECT rect = { x, y - contentsHeight, x + contentsWidth, y };
	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(RepeatTrue *element) {
	Long x, y, width, height, width2, height2;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();
	width2 = element->GetWidth2();
	height2 = element->GetHeight2();

	POINT points[5];

	points[0].x = x;
	points[0].y = y;

	points[1].x = x;
	points[1].y = y + height2;

	points[2].x = x + width2;
	points[2].y = y + height2;

	points[3].x = x + width2;
	points[3].y = y + height - 10;

	points[4].x = x + width - 13;
	points[4].y = y + height - 10;
	painter->DrawPolyline(points, 5);

	Long quotient = height2 / 4;
	Long remainder = height2 % 4;
	if (remainder >= 2) quotient++;
	Long endLength = quotient;
	POINT arrow[4];
	arrow[0].x = x + width - 13 - endLength;
	arrow[0].y = y + height - 10 - endLength / 2;
	arrow[1].x = x + width - 13;
	arrow[1].y = y + height - 10;
	arrow[2].x = x + width - 13 - endLength;
	arrow[2].y = y + height - 10 + endLength / 2;
	arrow[3].x = x + width - 13 - endLength / 3;
	arrow[3].y = y + height - 10;

	painter->DrawPolygon(arrow, 4);

	painter->FillPolygon(arrow, 4, RGB(166, 166, 166));

	// 텍스트를 출력한다.
	RECT rect = { x, y, x + width, y + height };

	painter->DrawText(18, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(RepeatFalse *element) {
	Long x, y, width, height, width2, height2;

	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	x = element->GetX() - positionX;
	y = element->GetY() - positionY;
	width = element->GetWidth();
	height = element->GetHeight();
	width2 = element->GetWidth2();
	height2 = element->GetHeight2();

	POINT points[5];
	points[0].x = x;
	points[0].y = y;
	points[1].x = x + width2;
	points[1].y = y;
	points[2].x = x + width2;
	points[2].y = y + height2;
	points[3].x = x + width;
	points[3].y = y + height2;
	points[4].x = x + width;
	points[4].y = y + height - 6;
	painter->DrawPolyline(points, 5);

	Long quotient = (height - height2) / 4;
	Long remainder = (height - height2) % 4;
	if (remainder >= 2) quotient++;
	Long endLength = quotient;
	POINT arrow[4];
	arrow[0].x = x + width - endLength / 2;
	arrow[0].y = y + height - endLength;
	arrow[1].x = x + width;
	arrow[1].y = y + height;
	arrow[2].x = x + width + endLength / 2;
	arrow[2].y = y + height - endLength;
	arrow[3].x = x + width;
	arrow[3].y = y + height - endLength / 2;

	painter->DrawPolygon(arrow, 4);

	painter->FillPolygon(arrow, 4, RGB(166, 166, 166));

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = -1 * font.lfHeight * element->GetContents().CountLine();
	Long contentsWidth = -1 * font.lfHeight * element->GetContents().GetLength();

	RECT rect = { x, y - contentsHeight, x + contentsWidth, y };
	painter->DrawText(font.lfHeight, element->GetContents(), -1, &rect, DT_CENTER);

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(FlowChart *element) {
	for (Long i = 0; i < element->GetLength(); i++) {
		element->GetAt(i)->Accept(this);
	}
}

void DrawVisitor::Visit(Template *element) {
	for (Long i = 0; i < element->GetLength(); i++) {
		element->GetAt(i)->Accept(this);
	}
}

void DrawVisitor::Visit(NumberBox *numberBox) {
	Long x = numberBox->GetX();
	Long y = numberBox->GetY();
	Long width = numberBox->GetWidth();
	Long height = numberBox->GetHeight();

	POINT point[5] = { {x,y},{x + width,y},{x + width,y + height},{x,y + height},{x,y} };
	painter->FillBackground(point, 5, numberBox->GetBackGroundColor());
	painter->DrawPolyline(point, 5);

	// 텍스트를 출력한다.
	LOGFONT font = painter->GetFont();
	Long contentsHeight = font.lfHeight * numberBox->GetContents().CountLine();
	contentsHeight -= 13;

	RECT rect = { x, y , x + width, y + height };

	painter->DrawText(12, numberBox->GetContents(), -1, &rect, DT_CENTER);
}

void DrawVisitor::Visit(A4Paper *a4Paper) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = a4Paper->GetX() - positionX;
	Long y = a4Paper->GetY() - positionY;
	Long width = a4Paper->GetWidth();
	Long height = a4Paper->GetHeight();

	POINT point[5] = { {x,y},{x + width,y},{x + width,y + height},{x,y + height},{x,y} };
	painter->FillBackground(point, 5, a4Paper->GetBackGroundColor());
	painter->DrawPolyline(point, 5);

	//입체효과
	painter->DrawLine(x + 1, y + height + 1, x + width + 1, y + height + 1);
	painter->DrawLine(x + width + 1, y + height + 1, x + width + 1, y + 1);

	if (a4Paper->GetIsMarking() == true) {
		//눈금선 가로 19개 세로 39개
		painter->ChangeLineProperty(PS_SOLID, painter->GetLineWidth(), painter->GetLineCapStyle(), painter->GetLineJoinType(),
			RGB(200, 200, 200));
		Long startY = y + 1;
		Long endY = y + height - 1;
		Long interval = width / 20;
		Long startX = x + interval;
		while (startX < x + width) {
			painter->DrawLine(startX, startY, startX, endY);
			startX += interval;
		}
		startX = x + 1;
		Long endX = x + width - 1;
		interval = height / 40;
		startY = y + interval;
		while (startY < y + height) {
			painter->DrawLine(startX, startY, endX, startY);
			startY += interval;
		}
		painter->ChangeLineProperty(PS_SOLID, painter->GetLineWidth(), painter->GetLineCapStyle(), painter->GetLineJoinType(),
			RGB(0, 0, 0));
	}

	//여백 표시
	painter->ChangeLineProperty(PS_SOLID, painter->GetLineWidth(), painter->GetLineCapStyle(), painter->GetLineJoinType(),
		RGB(0, 0, 255));
	Long leftMargin = a4Paper->GetLeftMargin();
	Long rightMargin = a4Paper->GetRightMargin();
	Long topMargin = a4Paper->GetTopMargin();
	Long bottomMargin = a4Paper->GetBottomMargin();

	painter->DrawLine(x + leftMargin, y + 1, x + leftMargin, y + height - 1);
	painter->DrawLine(x + 1, y + topMargin, x + width - 1, y + topMargin);
	painter->DrawLine(x + width - rightMargin, y + 1, x + width - rightMargin, y + height - 1);
	painter->DrawLine(x + 1, y + height - bottomMargin, x + width - 1, y + height - bottomMargin);

	painter->ChangeLineProperty(PS_SOLID, painter->GetLineWidth(), painter->GetLineCapStyle(), painter->GetLineJoinType(),
		RGB(0, 0, 0));
}

void DrawVisitor::Visit(TutorialMark *tutorialMark) {
	this->painter->ChangeLineProperty(PS_DASH, 5, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(255, 0, 0));

	this->painter->DrawRectangle(tutorialMark->GetX() - 5, tutorialMark->GetY() - 5,
		tutorialMark->GetX() - 5 + tutorialMark->GetWidth() + 10, tutorialMark->GetY() - 5 + tutorialMark->GetHeight() + 10);

	painter->ChangeLineProperty(PS_SOLID, painter->GetLineWidth(), painter->GetLineCapStyle(), painter->GetLineJoinType(),
		RGB(0, 0, 0));
}