#include "DrawVisitor.h"
#include "Terminal.h"
#include "Preparation.h"
#include "InputOutput.h"
#include "Process.h"
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
#include "GObject.h"

#include "QtGObjectFactory.h"

#include <qfont.h>

#define BORDERWIDTH 3

DrawVisitor::DrawVisitor(GObject *painter, ScrollController *scrollController)
	:FlowChartVisitor() {
	this->painter = painter;
	this->scrollController = scrollController;
}

DrawVisitor::~DrawVisitor() {

}

void DrawVisitor::Visit(Terminal *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	QRect rect(x, y, width, height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	GObject *brush = factory.MakeBrush(element->GetBackGroundColor());
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	this->painter->DrawRoundedRect(rect, 50.0, 50.0);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}

	//입체효과

	// 텍스트를 출력한다.
	String contents = element->GetContents();
	this->painter->DrawTextW(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(this->painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Preparation *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long halfHeight = (Long)height / 2;

	QPoint points[6];
	points[0] = QPoint(x, y + halfHeight);
	points[1] = QPoint(x + halfHeight, y);
	points[2] = QPoint(x + width - halfHeight, y);
	points[3] = QPoint(x + width, y + halfHeight);
	points[4] = QPoint(x + width - halfHeight, y + height);
	points[5] = QPoint(x + halfHeight, y + height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	GObject *brush = factory.MakeBrush(element->GetBackGroundColor());
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	this->painter->DrawPolygon(points, 6);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}

	//입체 효과

	// 텍스트를 출력한다.
	String contents = element->GetContents();
	QRect rect(x + halfHeight, y, width - height, height);
	this->painter->DrawTextW(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(InputOutput *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long halfHeight = (Long)height / 2;

	QPoint points[4];
	points[0] = QPoint(x + halfHeight, y);
	points[1] = QPoint(x + width, y);
	points[2] = QPoint(x + width - halfHeight, y + height);
	points[3] = QPoint(x, y + height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	GObject *brush = factory.MakeBrush(element->GetBackGroundColor());
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	this->painter->DrawPolygon(points, 4);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}

	//입체효과

	// 텍스트를 출력한다.
	String contents = element->GetContents();
	QRect rect(x + halfHeight, y, width - height, height);
	this->painter->DrawTextW(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Process *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();

	QRect rect(x, y, width, height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	GObject *brush = factory.MakeBrush(element->GetBackGroundColor());
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	this->painter->DrawRect(rect);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}

	//입체효과

	// 텍스트를 출력한다.
	String contents = element->GetContents();
	this->painter->DrawTextW(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Decision *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long halfWidth = width / 2;
	Long halfHeight = height / 2;

	QPoint points[4];
	points[0] = QPoint(x + halfWidth, y);
	points[1] = QPoint(x + width, y + halfHeight);
	points[2] = QPoint(x + halfWidth, y + height);
	points[3] = QPoint(x, y + halfHeight);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	GObject *brush = factory.MakeBrush(element->GetBackGroundColor());
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	this->painter->DrawPolygon(points, 4);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}

	//입체 효과

	// 텍스트를 출력한다.
	String contents = element->GetContents();
	QRect rect(x + halfWidth / 2, y + halfHeight / 2, halfWidth, halfHeight);
	this->painter->DrawTextW(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Arrow *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	this->painter->DrawLine(QPoint(x, y), QPoint(x, y + height - 4));

	GObject *brush = factory.MakeBrush(QColor(166, 166, 166));
	GObject *oldBrush = painter->SelectObject(*brush);
	this->painter->Update();

	Long quotient = height / 4;
	Long remainder = height % 4;
	if (remainder >= 2) quotient++;
	Long endLength = quotient;
	QPoint arrow[4];
	arrow[0] = QPoint(x - endLength / 2, y + height - endLength);
	arrow[1] = QPoint(x, y + height);
	arrow[2] = QPoint(x + endLength / 2, y + height - endLength);
	arrow[3] = QPoint(x, y + height - endLength / 3);
	this->painter->DrawPolygon(arrow, 4);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}

	// 텍스트를 출력한다.
	String contents = element->GetContents();

	QRect rect(x + endLength / 2, y, height * 2, height);
	this->painter->DrawTextW(rect, Qt::AlignLeft | Qt::AlignVCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(LeftDown *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	painter->DrawLine(QPoint(x, y), QPoint(x + width, y));
	painter->DrawLine(QPoint(x + width, y), QPoint(x + width, y + height - 4));

	GObject *brush = factory.MakeBrush(QColor(166, 166, 166), Qt::SolidPattern);
	GObject *oldBrush = painter->SelectObject(*brush);
	this->painter->Update();

	Long quotient = height / 4;
	Long remainder = height % 4;
	if (remainder >= 2) quotient++;
	Long endLength = quotient;
	QPoint arrow[4];
	arrow[0] = QPoint(x + width - endLength / 2, y + height - endLength);
	arrow[1] = QPoint(x + width, y + height);
	arrow[2] = QPoint(x + width + endLength / 2, y + height - endLength);
	arrow[3] = QPoint(x + width, y + height - endLength / 3);
	painter->DrawPolygon(arrow, 4);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}

	// 텍스트를 출력한다.
	String contents = element->GetContents();

	QRect rect(x - width, y - height, width, height);
	this->painter->DrawTextW(rect, Qt::AlignRight | Qt::AlignBottom, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(RightDown *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	painter->DrawLine(QPoint(x, y), QPoint(x + width, y));
	painter->DrawLine(QPoint(x + width, y), QPoint(x + width, y + height - 4));

	GObject *brush = factory.MakeBrush(QColor(166, 166, 166), Qt::SolidPattern);
	GObject *oldBrush = painter->SelectObject(*brush);
	this->painter->Update();

	Long quotient = height / 4;
	Long remainder = height % 4;
	if (remainder >= 2) quotient++;
	Long endLength = quotient;
	QPoint arrow[4];
	arrow[0] = QPoint(x + width - endLength / 2, y + height - endLength);
	arrow[1] = QPoint(x + width, y + height);
	arrow[2] = QPoint(x + width + endLength / 2, y + height - endLength);
	arrow[3] = QPoint(x + width, y + height - endLength / 3);
	painter->DrawPolygon(arrow, 4);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}

	// 텍스트를 출력한다.
	String contents = element->GetContents();
	QRect rect(x, y - height, width, height);
	this->painter->DrawTextW(rect, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Join *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long height2 = element->GetHeight2();

	QPoint points[4];
	points[0] = QPoint(x, y);
	points[1] = QPoint(x, y + height2);
	points[2] = QPoint(x + width, y + height2);
	points[3] = QPoint(x + width, y + height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	painter->DrawPolyline(points, 4);

	this->painter->SelectObject(*oldPen);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}

	// 텍스트를 '안' 출력한다.

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(RightDownJoin *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long width2 = element->GetWidth2();
	Long height2 = element->GetHeight2();

	QPoint points[5];
	points[0] = QPoint(x, y);
	points[1] = QPoint(x + width2, y);
	points[2] = QPoint(x + width2, y + height + height2);
	points[3] = QPoint(x + width, y + height + height2);
	points[4] = QPoint(x + width, y + height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	painter->DrawPolyline(points, 5);

	this->painter->SelectObject(*oldPen);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}

	// 텍스트를 출력한다.
	String contents = element->GetContents();
	QRect rect(x, y - height2, width2, height2);
	this->painter->DrawTextW(rect, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(RepeatTrue *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long width2 = element->GetWidth2();
	Long height2 = element->GetHeight2();

	QPoint points[5];
	points[0] = QPoint(x, y);
	points[1] = QPoint(x, y + height2);
	points[2] = QPoint(x + width2, y + height2);
	points[3] = QPoint(x + width2, y + height - 10);
	points[4] = QPoint(x + width - 13, y + height - 10);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	painter->DrawPolyline(points, 5);

	GObject *brush = factory.MakeBrush(QColor(166, 166, 166), Qt::SolidPattern);
	GObject *oldBrush = painter->SelectObject(*brush);
	this->painter->Update();

	Long quotient = height2 / 4;
	Long remainder = height2 % 4;
	if (remainder >= 2) quotient++;
	Long endLength = quotient;
	QPoint arrow[4];
	arrow[0] = QPoint(x + width - 13 - endLength, y + height - 10 - endLength / 2);
	arrow[1] = QPoint(x + width - 13, y + height - 10);
	arrow[2] = QPoint(x + width - 13 - endLength, y + height - 10 + endLength / 2);
	arrow[3] = QPoint(x + width - 13 - endLength / 3, y + height - 10);
	painter->DrawPolygon(arrow, 4);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}

	// 텍스트를 '안' 출력한다.
	
	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(RepeatFalse *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}

	Long x = element->GetX() - positionX;
	Long y = element->GetY() - positionY;
	Long width = element->GetWidth();
	Long height = element->GetHeight();
	Long width2 = element->GetWidth2();
	Long height2 = element->GetHeight2();

	QPoint points[5];
	points[0] = QPoint(x, y);
	points[1] = QPoint(x + width2, y);
	points[2] = QPoint(x + width2, y + height2);
	points[3] = QPoint(x + width, y + height2);
	points[4] = QPoint(x + width, y + height - 6);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	painter->DrawPolyline(points, 5);

	GObject *brush = factory.MakeBrush(QColor(166, 166, 166), Qt::SolidPattern);
	GObject *oldBrush = painter->SelectObject(*brush);
	this->painter->Update();

	Long quotient = (height - height2) / 4;
	Long remainder = (height - height2) % 4;
	if (remainder >= 2) quotient++;
	Long endLength = quotient;
	QPoint arrow[4];
	arrow[0] = QPoint(x + width - endLength / 2, y + height - endLength);
	arrow[1] = QPoint(x + width, y + height);
	arrow[2] = QPoint(x + width + endLength / 2, y + height - endLength);
	arrow[3] = QPoint(x + width, y + height - endLength / 2);
	painter->DrawPolygon(arrow, 4);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}

	// 텍스트를 출력한다.
	String contents = element->GetContents();
	QRect rect(x, y - height2, width2, height2);
	this->painter->DrawTextW(rect, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit(contents));

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

	QPoint points[4];
	points[0] = QPoint(x, y);
	points[1] = QPoint(x + width, y);
	points[2] = QPoint(x + width, y + height);
	points[3] = QPoint(x, y + height);

	this->painter->DrawPolygon(points, 5);

	// 텍스트를 출력한다.
	//정해진 폰트 사이즈임.
	QtGObjectFactory factory;
	GObject *font = factory.MakeFont("Malgun Gothic"/*관리중인 서체 가져오기*/, 5/*조정요망*/, 50, false);

	String contents = numberBox->GetContents();
	QRect rect(x, y, width, height);
	this->painter->DrawTextW(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));
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
	QRect rect(x, y, width, height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(a4Paper->GetBorderColor), BORDERWIDTH, a4Paper->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	GObject *brush = factory.MakeBrush(a4Paper->GetBackGroundColor());
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	this->painter->DrawRect(rect);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}
	
	//입체효과

	if (a4Paper->GetIsMarking() == true) {
		//눈금선 가로 19개 세로 39개
		QtGObjectFactory factory;
		GObject *pen = factory.MakePen(QBrush(QColor(200,200,200)), BORDERWIDTH, a4Paper->GetBorderLine()); //점선으로?
		GObject *oldPen = this->painter->SelectObject(*pen);
		this->painter->Update();

		Long startY = y + 1;
		Long endY = y + height - 1;
		Long interval = width / 20;
		Long startX = x + interval;
		while (startX < x + width) {
			this->painter->DrawLine(QPoint(startX, startY), QPoint(startX, endY));
			startX += interval;
		}
		startX = x + 1;
		Long endX = x + width - 1;
		interval = height / 40;
		startY = y + interval;
		while (startY < y + height) {
			this->painter->DrawLine(QPoint(startX, startY), QPoint(endX, startY));
			startY += interval;
		}

		this->painter->SelectObject(*oldPen);
		this->painter->Update();
		if (pen != NULL) {
			delete pen;
		}
	}

	//여백 표시
	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(0, 0, 255)), BORDERWIDTH, a4Paper->GetBorderLine()); //점선으로?
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	Long leftMargin = a4Paper->GetLeftMargin();
	Long rightMargin = a4Paper->GetRightMargin();
	Long topMargin = a4Paper->GetTopMargin();
	Long bottomMargin = a4Paper->GetBottomMargin();

	painter->DrawLine(QPoint(x + leftMargin, y + 1), QPoint(x + leftMargin, y + height - 1));
	painter->DrawLine(QPoint(x + 1, y + topMargin), QPoint(x + width - 1, y + topMargin));
	painter->DrawLine(QPoint(x + width - rightMargin, y + 1), QPoint(x + width - rightMargin, y + height - 1));
	painter->DrawLine(QPoint(x + 1, y + height - bottomMargin), QPoint(x + width - 1, y + height - bottomMargin));

	this->painter->SelectObject(*oldPen);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
}

void DrawVisitor::Visit(TutorialMark *tutorialMark) {
	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(255, 0, 0)), BORDERWIDTH, Qt::DashDotLine);
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	Long x = tutorialMark->GetX() - 5;
	Long y = tutorialMark->GetY() - 5;
	Long width = tutorialMark->GetWidth() + 10;
	Long height = tutorialMark->GetHeight() + 10;

	QPoint point1[4];
	point1[0] = QPoint(x, y);
	point1[1] = QPoint(x + width, y);
	point1[2] = QPoint(x + width, y + height);
	point1[3] = QPoint(x, y + height);
	QPoint point2[4];
	point2[0] = QPoint(x + width, y);
	point2[1] = QPoint(x + width, y + height);
	point2[2] = QPoint(x, y + height);
	point2[3] = QPoint(x, y);
	this->painter->DrawLines(point1, point2, 4);

	this->painter->SelectObject(*oldPen);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
}