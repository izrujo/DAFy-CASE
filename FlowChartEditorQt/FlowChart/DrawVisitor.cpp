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
#include "Scroll.h"
#include "NumberBox.h"
#include "A4Paper.h"
#include "TextRegion.h"
#include "../GObject/GObject.h"
#include "../GObject/QtGObjectFactory.h"
#include "WindowTitle.h"
#include "WindowPin.h"
#include "WindowClose.h"

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
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();
	QRectF rect(x, y, width, height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	GObject *brush = factory.MakeBrush(element->GetBackGroundColor());
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	float radius = width / 5.0F;
	this->painter->DrawRoundedRect(rect, radius, radius);

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
	this->painter->DrawTextQ(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(this->painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Preparation *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();
	float halfHeight = height / 2.0F;

	QPointF points[6];
	points[0] = QPointF(x, y + halfHeight);
	points[1] = QPointF(x + halfHeight, y);
	points[2] = QPointF(x + width - halfHeight, y);
	points[3] = QPointF(x + width, y + halfHeight);
	points[4] = QPointF(x + width - halfHeight, y + height);
	points[5] = QPointF(x + halfHeight, y + height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
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
	QRectF rect(x + halfHeight, y, width - height, height);
	this->painter->DrawTextQ(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(InputOutput *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();
	float halfHeight = height / 2.0F;

	QPointF points[4];
	points[0] = QPointF(x + halfHeight, y);
	points[1] = QPointF(x + width, y);
	points[2] = QPointF(x + width - halfHeight, y + height);
	points[3] = QPointF(x, y + height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
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
	QRectF rect(x + halfHeight, y, width - height, height);
	this->painter->DrawTextQ(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Process *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();

	QRectF rect(x, y, width, height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
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
	this->painter->DrawTextQ(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Decision *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();
	float halfWidth = width / 2.0F;
	float halfHeight = height / 2.0F;

	QPoint points[4];
	points[0] = QPoint(x + halfWidth, y);
	points[1] = QPoint(x + width, y + halfHeight);
	points[2] = QPoint(x + halfWidth, y + height);
	points[3] = QPoint(x, y + halfHeight);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
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
	QRectF rect(x + halfWidth / 2, y + halfHeight / 2, halfWidth, halfHeight);
	this->painter->DrawTextQ(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Arrow *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	this->painter->DrawLine(QPointF(x, y), QPointF(x, y + height - 6));

	GObject *brush = factory.MakeBrush(QColor(166, 166, 166));
	GObject *oldBrush = painter->SelectObject(*brush);
	this->painter->Update();

	float arrowSize = element->GetArrowSize();
	QPointF arrow[4];
	arrow[0] = QPointF(x - arrowSize / 2.0F, y + height - arrowSize);
	arrow[1] = QPointF(x, y + height);
	arrow[2] = QPointF(x + arrowSize / 2.0F, y + height - arrowSize);
	arrow[3] = QPointF(x, y + height - arrowSize / 3.0F);
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

	QRectF rect(x + arrowSize / 2.0F, y, height * 2.0F, height);
	this->painter->DrawTextQ(rect, Qt::AlignLeft | Qt::AlignVCenter, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(LeftDown *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	this->painter->DrawLine(QPointF(x, y), QPointF(x + width, y));
	this->painter->DrawLine(QPointF(x + width, y), QPointF(x + width, y + height - 6));

	GObject *brush = factory.MakeBrush(QColor(166, 166, 166));
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	float arrowSize = element->GetArrowSize();
	QPointF arrow[4];
	arrow[0] = QPointF(x + width - arrowSize / 2.0F, y + height - arrowSize);
	arrow[1] = QPointF(x + width, y + height);
	arrow[2] = QPointF(x + width + arrowSize / 2.0F, y + height - arrowSize);
	arrow[3] = QPointF(x + width, y + height - arrowSize / 3.0F);
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

	QRectF rect(x + width * 2.0F, y - height, -width * 2.0F, height);
	this->painter->DrawTextQ(rect, Qt::AlignRight | Qt::AlignBottom, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(RightDown *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	this->painter->DrawLine(QPointF(x, y), QPointF(x + width, y));
	this->painter->DrawLine(QPointF(x + width, y), QPointF(x + width, y + height - 6));

	GObject *brush = factory.MakeBrush(QColor(166, 166, 166), Qt::SolidPattern);
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	float arrowSize = element->GetArrowSize();
	QPointF arrow[4];
	arrow[0] = QPointF(x + width - arrowSize / 2.0F, y + height - arrowSize);
	arrow[1] = QPointF(x + width, y + height);
	arrow[2] = QPointF(x + width + arrowSize / 2.0F, y + height - arrowSize);
	arrow[3] = QPointF(x + width, y + height - arrowSize / 3.0F);
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
	QRectF rect(x, y - height, width * 2.0F, height);
	this->painter->DrawTextQ(rect, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(Join *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();
	float height2 = element->GetHeight2();

	QPointF points[4];
	points[0] = QPointF(x, y);
	points[1] = QPointF(x, y + height2);
	points[2] = QPointF(x + width, y + height2);
	points[3] = QPointF(x + width, y + height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	this->painter->DrawPolyline(points, 4);

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
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();
	float width2 = element->GetWidth2();
	float height2 = element->GetHeight2();

	QPointF points[5];
	points[0] = QPointF(x, y);
	points[1] = QPointF(x + width2, y);
	points[2] = QPointF(x + width2, y + height + height2);
	points[3] = QPointF(x + width, y + height + height2);
	points[4] = QPointF(x + width, y + height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	this->painter->DrawPolyline(points, 5);

	this->painter->SelectObject(*oldPen);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}

	// 텍스트를 출력한다.
	String contents = element->GetContents();
	QRectF rect(x, y - height2, width2 - width, height2);
	this->painter->DrawTextQ(rect, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit(contents));

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(RepeatTrue *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();
	float width2 = element->GetWidth2();
	float height2 = element->GetHeight2();

	QPointF points[5];
	points[0] = QPointF(x, y);
	points[1] = QPointF(x, y + height2);
	points[2] = QPointF(x + width2, y + height2);
	points[3] = QPointF(x + width2, y + height);
	points[4] = QPointF(x + width, y + height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	this->painter->DrawPolyline(points, 5);

	GObject *brush = factory.MakeBrush(QColor(166, 166, 166), Qt::SolidPattern);
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	float arrowSize = element->GetArrowSize();
	QPointF arrow[4];
	arrow[0] = QPointF(x + width - arrowSize, y + height - arrowSize / 2.0F);
	arrow[1] = QPointF(x + width, y + height);
	arrow[2] = QPointF(x + width - arrowSize, y + height + arrowSize / 2.0F);
	arrow[3] = QPointF(x + width - arrowSize / 3.0F, y + height);
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

	// 텍스트를 '안' 출력한다.

	if (element->IsSelected() == true) {
		element->DrawSelectionMarkers(painter, this->scrollController);
	}
}

void DrawVisitor::Visit(RepeatFalse *element) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = element->GetX() - positionX;
	float y = element->GetY() - positionY;
	float width = element->GetWidth();
	float height = element->GetHeight();
	float width2 = element->GetWidth2();
	float height2 = element->GetHeight2();

	QPointF points[5];
	points[0] = QPointF(x, y);
	points[1] = QPointF(x + width2, y);
	points[2] = QPointF(x + width2, y + height2);
	points[3] = QPointF(x + width, y + height2);
	points[4] = QPointF(x + width, y + height - 6);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(element->GetBorderColor()), BORDERWIDTH, element->GetBorderLine());
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	painter->DrawPolyline(points, 5);

	GObject *brush = factory.MakeBrush(QColor(166, 166, 166), Qt::SolidPattern);
	GObject *oldBrush = painter->SelectObject(*brush);
	this->painter->Update();

	float arrowSize = element->GetArrowSize();
	QPointF arrow[4];
	arrow[0] = QPointF(x + width - arrowSize / 2.0F, y + height - arrowSize);
	arrow[1] = QPointF(x + width, y + height);
	arrow[2] = QPointF(x + width + arrowSize / 2.0F, y + height - arrowSize);
	arrow[3] = QPointF(x + width, y + height - arrowSize / 2.0F);
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
	QRectF rect(x, y - height2, width2 - width, height2);
	this->painter->DrawTextQ(rect, Qt::AlignLeft | Qt::AlignBottom, QString::fromLocal8Bit(contents));

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
	float x = numberBox->GetX();
	float y = numberBox->GetY();
	float width = numberBox->GetWidth();
	float height = numberBox->GetHeight();
	/*
	QPoint points[4];
	points[0] = QPoint(x, y);
	points[1] = QPoint(x + width, y);
	points[2] = QPoint(x + width, y + height);
	points[3] = QPoint(x, y + height);
	this->painter->DrawPolygon(points, 4);
	*/
	QtGObjectFactory factory;
	GObject *brush = factory.MakeBrush(numberBox->GetBackGroundColor());
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	QRectF rect(x, y, width, height);

	this->painter->DrawRect(rect);

	// 텍스트를 출력한다.
	//정해진 폰트 사이즈임.
	GObject *pen = factory.MakePen(QBrush(numberBox->GetBorderColor()), 1);
	GObject *oldPen = this->painter->SelectObject(*pen);
	GObject *font = factory.MakeFont("Malgun Gothic"/*관리중인 서체 가져오기*/, 8/*조정요망*/, 50, false);
	GObject *oldFont = this->painter->SelectObject(*font);
	this->painter->Update();

	String contents = numberBox->GetContents();
	this->painter->DrawTextQ(rect, Qt::AlignCenter, QString::fromLocal8Bit(contents));

	//페인터 설정 복구
	this->painter->SelectObject(*oldBrush);
	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldFont);
	this->painter->Update();
	if (brush != 0) {
		delete brush;
	}
	if (pen != 0) {
		delete pen;
	}
	if (font != 0) {
		delete font;
	}
}

void DrawVisitor::Visit(A4Paper *a4Paper) {
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		Scroll *horizontal = this->scrollController->GetScroll(1);
		Scroll *vertical = this->scrollController->GetScroll(0);
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}

	float x = a4Paper->GetX() - positionX;
	float y = a4Paper->GetY() - positionY;
	float width = a4Paper->GetWidth();
	float height = a4Paper->GetHeight();
	QRectF rect(x, y, width, height);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(a4Paper->GetBorderColor()), BORDERWIDTH, a4Paper->GetBorderLine());
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
		pen = factory.MakePen(QBrush(QColor(200, 200, 200)), 1, a4Paper->GetBorderLine()); //점선으로?
		oldPen = this->painter->SelectObject(*pen);
		this->painter->Update();

		float startY = y + 2;
		float endY = y + height - 2;
		float interval = width / 20;
		float startX = x + interval;
		while (startX < x + width) {
			this->painter->DrawLine(QPointF(startX, startY), QPointF(startX, endY));
			startX += interval;
		}
		startX = x + 2;
		float endX = x + width - 2;
		interval = height / 40;
		startY = y + interval;
		while (startY < y + height) {
			this->painter->DrawLine(QPointF(startX, startY), QPointF(endX, startY));
			startY += interval;
		}

		this->painter->SelectObject(*oldPen);
		this->painter->Update();
		if (pen != NULL) {
			delete pen;
		}
	}

	//여백 표시
	pen = factory.MakePen(QBrush(QColor(0, 0, 255)), 1, a4Paper->GetBorderLine()); //점선으로?
	oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	float leftMargin = a4Paper->GetLeftMargin();
	float rightMargin = a4Paper->GetRightMargin();
	float topMargin = a4Paper->GetTopMargin();
	float bottomMargin = a4Paper->GetBottomMargin();

	painter->DrawLine(QPointF(x + leftMargin, y + 2), QPointF(x + leftMargin, y + height - 2));
	painter->DrawLine(QPointF(x + 2, y + topMargin), QPointF(x + width - 2, y + topMargin));
	painter->DrawLine(QPointF(x + width - rightMargin, y + 2), QPointF(x + width - rightMargin, y + height - 2));
	painter->DrawLine(QPointF(x + 2, y + height - bottomMargin), QPointF(x + width - 2, y + height - bottomMargin));

	this->painter->SelectObject(*oldPen);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
}

void DrawVisitor::Visit(WindowTitle *windowTitle) {
	QtGObjectFactory factory;

	//====속성
	float x = windowTitle->GetX();
	float y = windowTitle->GetY();
	float width = windowTitle->GetWidth();
	float height = windowTitle->GetHeight();
	Long borderWidth = 1;
	QColor fillColor = windowTitle->GetBackGroundColor();
	QColor borderColor = windowTitle->GetBorderColor();
	String content = windowTitle->GetContents();

	//====사각형
	//GObject 설정
	GObject *pen = factory.MakePen(QBrush(borderColor), borderWidth);
	GObject *oldPen = this->painter->SelectObject(*pen);
	GObject *brush = factory.MakeBrush(fillColor);
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	//그리기
	QRectF rect(x, y, width, height);
	this->painter->DrawRect(rect);

	//펜 복구
	this->painter->SelectObject(*oldPen);
	this->painter->Update();
	if (pen != 0) {
		delete pen;
	}

	//====텍스트
	//GObject 설정
	GObject *oldFont = this->painter->CurrentObject("Font");
	GObject *font = factory.MakeFont(oldFont->GetFamily(), 5, oldFont->GetWeight(), oldFont->GetItalic());

	//그리기
	if (windowTitle->GetIsFocusedAndPinned()) {
		pen = factory.MakePen(QBrush(QColor(255, 255, 255)), 2);
		oldPen = this->painter->SelectObject(*pen);
		this->painter->Update();
		this->painter->DrawTextQ(rect, Qt::AlignLeft | Qt::AlignVCenter, QString::fromLocal8Bit(content));
	}
	else {
		pen = factory.MakePen(QBrush(windowTitle->GetBorderColor()), 2);
		oldPen = this->painter->SelectObject(*pen);
		this->painter->Update();
		QString verticalContent = QString::fromLocal8Bit(content);
		verticalContent.remove(QChar(' '));
		Long i = 1;
		while (i < verticalContent.size()) {
			verticalContent.insert(i, '\n');
			i += 2;
		}
		rect.setX(rect.x() + 3);
		this->painter->DrawTextQ(rect, 0, verticalContent);
	}

	//====painter 복구
	this->painter->SelectObject(*oldBrush);
	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldFont);
	this->painter->Update();
	if (brush != 0) {
		delete brush;
	}
	if (font != 0) {
		delete font;
	}
	if (pen != 0) {
		delete pen;
	}
}

void DrawVisitor::Visit(WindowPin *windowPin) {
	float x = windowPin->GetX();
	float y = windowPin->GetY();
	float width = windowPin->GetWidth();
	float height = windowPin->GetHeight();
	float hhhWidth = width / 8.0F; //half of half of half of width
	float hhhHeight = height / 8.0F;
	QColor fillColor = windowPin->GetBackGroundColor();
	QColor borderColor = windowPin->GetBorderColor();

	QtGObjectFactory factory;

	QRectF fillRect(x, y, width, height);
	GObject *brush = factory.MakeBrush(fillColor);
	this->painter->FillRect(fillRect, *brush);
	if (brush != 0) {
		delete brush;
	}

	GObject *pen = factory.MakePen(QBrush(borderColor), 1);
	GObject *oldPen = this->painter->SelectObject(*pen);
	brush = factory.MakeBrush(borderColor);
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	bool isPinned = windowPin->GetIsPinned();
	QRectF rect;
	QPointF point1;
	QPointF point2;
	if (isPinned == true) {
		rect.setX(x + hhhWidth * 3);
		rect.setY(y + hhhHeight * 2);
		rect.setWidth(hhhWidth * 2);
		rect.setHeight(hhhHeight * 2);
		this->painter->DrawRect(rect);

		point1 = QPointF(x + hhhWidth * 2, y + hhhHeight * 4);
		point2 = QPointF(x + hhhWidth * 6, y + hhhHeight * 4);
		this->painter->DrawLine(point1, point2);

		point1 = QPointF(x + hhhWidth * 4, y + hhhHeight * 4);
		point2 = QPointF(x + hhhWidth * 4, y + hhhHeight * 6);
		this->painter->DrawLine(point1, point2);
	}
	else {
		rect.setX(x + hhhWidth * 4);
		rect.setY(y + hhhHeight * 3);
		rect.setWidth(hhhWidth * 2);
		rect.setHeight(hhhHeight * 2);
		this->painter->DrawRect(rect);

		point1 = QPointF(x + hhhWidth * 4, y + hhhHeight * 2);
		point2 = QPointF(x + hhhWidth * 4, y + hhhHeight * 6);
		this->painter->DrawLine(point1, point2);

		point1 = QPointF(x + hhhWidth * 2, y + hhhHeight * 4);
		point2 = QPointF(x + hhhWidth * 4, y + hhhHeight * 4);
		this->painter->DrawLine(point1, point2);
	}

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != 0) {
		delete pen;
	}
	if (brush != 0) {
		delete brush;
	}
}

void DrawVisitor::Visit(WindowClose *windowClose) {
	float x = windowClose->GetX();
	float y = windowClose->GetY();
	float width = windowClose->GetWidth();
	float height = windowClose->GetHeight();
	float hhhWidth = width / 8.0F; //half of half of half of width
	float hhhHeight = height / 8.0F;
	QColor fillColor = windowClose->GetBackGroundColor();
	QColor borderColor = windowClose->GetBorderColor();

	QtGObjectFactory factory;

	QRectF fillRect(x, y, width, height);
	GObject *brush = factory.MakeBrush(fillColor);
	this->painter->FillRect(fillRect, *brush);
	if (brush != 0) {
		delete brush;
	}

	GObject *pen = factory.MakePen(QBrush(borderColor), 2);
	GObject *oldPen = this->painter->SelectObject(*pen);
	brush = factory.MakeBrush(borderColor);
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	QPointF point1;
	QPointF point2;

	point1 = QPointF(x + hhhWidth * 2, y + hhhHeight * 2);
	point2 = QPointF(x + hhhWidth * 6, y + hhhHeight * 6);
	this->painter->DrawLine(point1, point2);

	point1 = QPointF(x + hhhWidth * 6, y + hhhHeight * 2);
	point2 = QPointF(x + hhhWidth * 2, y + hhhHeight * 6);
	this->painter->DrawLine(point1, point2);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != 0) {
		delete pen;
	}
	if (brush != 0) {
		delete brush;
	}
}

/*
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
*/