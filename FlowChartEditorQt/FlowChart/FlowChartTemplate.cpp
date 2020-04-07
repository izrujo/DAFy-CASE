/******************************************************************
 * 파일 이름 : FlowCahrtTemplate.cpp
 * 기능 : 순서도 작성자 컨트롤
 * 작성자 : 송윤창
 * 작성일자 : 2015년 4월 10일
*******************************************************************/

#include "FlowChartTemplate.h"
#include "Template.h"
#include "Terminal.h"
#include "Shape.h"
//////////////////////////////////////////////////////////////
#include "../FlowChartEditor.h"
#include "DrawingPaper.h"

#include "Array.h"
#include "Shape.h"

#include "Symbol.h"
#include "Line.h"

#include "Decision.h"
#include "Preparation.h"
#include "Process.h"
#include "Terminal.h"
#include "InputOutput.h"

#include "Arrow.h"
#include "Join.h"
#include "LeftDown.h"
#include "RepeatFalse.h"
#include "RepeatTrue.h"
#include "RightDown.h"
#include "RightDownJoin.h"

#include "../GObject/Painter.h"
#include "DrawVisitor.h"
#include "../GObject/QtPainter.h"

//#include "StatusBar.h"
//#include "ToolTip.h"
//#include "TutorialForm.h"
//#include "Tutorials.h"
//#include "TutorialController.h"

#include "../GObject/QtGObjectFactory.h"

#include <qpainter.h>
#include <qevent.h>

FlowChartTemplate::FlowChartTemplate(QWidget *parent = Q_NULLPTR) {
	this->shapeSelected = NULL;
	this->mode = DRAWOFF;
	this->oldShapeSelected = NULL;

	this->flowChartTemplate = new Template;
	FlowChartShape::Shape *template1 = new Terminal(25, 90, 150, 50, QColor(255, 153, 153), 
		Qt::SolidLine, QColor(0, 0, 0), String("START"));
	FlowChartShape::Shape *template2 = new Preparation(25, 160, 150, 50, QColor(153, 153, 255), 
		Qt::SolidLine, QColor(0, 0, 0), String("Preparation"));
	FlowChartShape::Shape *template3 = new InputOutput(25, 230, 150, 50, QColor(255, 255, 153), 
		Qt::SolidLine, QColor(0, 0, 0), String("READ "));
	FlowChartShape::Shape *template4 = new Process(25, 300, 150, 50, QColor(153, 255, 153), 
		Qt::SolidLine, QColor(0, 0, 0), String("Process"));
	FlowChartShape::Shape *template5 = new Decision(25, 370, 150, 50, QColor(255, 153, 255), 
		Qt::SolidLine, QColor(0, 0, 0), String("Decision"));
	FlowChartShape::Shape *template6 = new InputOutput(25, 440, 150, 50, QColor(255, 255, 153), 
		Qt::SolidLine, QColor(0, 0, 0), String("PRINT "));
	FlowChartShape::Shape *template7 = new Terminal(25, 510, 150, 50, QColor(255, 153, 153), 
		Qt::SolidLine, QColor(0, 0, 0), String("STOP"));

	this->flowChartTemplate->Attach(template1);
	this->flowChartTemplate->Attach(template2);
	this->flowChartTemplate->Attach(template3);
	this->flowChartTemplate->Attach(template4);
	this->flowChartTemplate->Attach(template5);
	this->flowChartTemplate->Attach(template6);
	this->flowChartTemplate->Attach(template7);

	QRect rect = this->frameRect();
	this->painter = new QtPainter(rect.width(), rect.height());

	DrawingPaper *canvas = static_cast<DrawingPaper*>(static_cast<FlowChartEditor*>(this->parentWidget())->windows[0]);
	GObject *font = canvas->painter->CurrentObject("Font");
	this->painter->SelectObject(*font);
	this->painter->Update();
}

FlowChartTemplate::~FlowChartTemplate() {
	if (this->flowChartTemplate != NULL) {
		delete this->flowChartTemplate;
	}
	if (this->painter != NULL) {
		delete this->painter;
	}
}

void FlowChartTemplate::paintEvent(QPaintEvent *event) {
	QPainter dc(this);

	int oldMode = this->painter->GetBackgroundMode();
	this->painter->SetBackgroundMode(Qt::TransparentMode);
	this->painter->SetCompositionMode(QPainter::RasterOp_NotSourceXorDestination);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(0, 0, 0)), 2);
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	QRect rect = this->frameRect();

	this->painter->Resize(rect.width(), rect.height()); // canvas size 변경

	//=======창 제목========
	FlowChartEditor *editor = (FlowChartEditor*)this->parentWidget();
	//QRect rect2 = rect;

	//POINT backPoints[7] = { {0, 0}, {rect.right, rect.top}, {rect.right, rect2.top + 40}, {rect2.right - 40, rect2.top + 40},
	//{rect2.right - 40, rect2.top + 13}, {rect2.left, rect2.top + 13}, {0, 0} };
	//CRgn region;
	//region.CreatePolygonRgn(backPoints, 7, ALTERNATE);
	//this->painter->FillRegion(region, RGB(235, 235, 235));

	//this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(102, 102, 102));
	//this->painter->DrawLine(rect2.left, rect2.top + 10, rect2.right - 50, rect2.top + 10);
	//this->painter->DrawLine(rect2.left, rect2.top + 13, rect2.right - 40, rect2.top + 13);
	//this->painter->DrawLine(rect2.right - 40, rect2.top + 13, rect2.right - 40, rect2.top + 40);
	//this->painter->DrawLine(rect2.left, rect2.top + 40, rect2.right, rect2.top + 40);

	//rect2.top += 15;

	//this->painter->DrawTextA(-20, " Template", -1, &rect2, DT_LEFT | DT_TOP);
	//======================
	FlowChartVisitor *visitor = new DrawVisitor(this->painter);
	this->flowChartTemplate->Accept(visitor);
	this->painter->Render(&dc, 0, 0);

	this->painter->SelectObject(*oldPen);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}

	/*
	bool ret;
	if (editor->toolTip != NULL) {
		this->ModifyStyle(0, WS_CLIPSIBLINGS);
		ret = editor->toolTip->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
	*/
}

void FlowChartTemplate::mousePressEvent(QMouseEvent *event) {
	FlowChartEditor* editor;

	editor = static_cast<FlowChartEditor*>(this->parentWidget());

	Long index = -1;

	index = this->flowChartTemplate->Find(event->pos());
	if (index != -1) {

		this->shapeSelected = this->flowChartTemplate->GetAt(index);

		static_cast<DrawingPaper*>(editor->windows[0])->mode = DrawingPaper::DRAWING;
	/*
		editor->statusBar->Modify(1, String("DRAWING"));
		String style;
		switch (this->shapeSelected->GetSymbolID()) {
		case ID_TERMINAL:
			style = "    단말 기호"; break;
		case ID_PREPARATION:
			style = "    준비 기호"; break;
		case ID_INPUTOUTPUT:
			style = "    입출력 기호"; break;
		case ID_PROCESS:
			style = "    처리 기호"; break;
		case ID_DECISION:
			style = "    판단 기호"; break;
		}
		editor->statusBar->Modify(0, style);
		editor->statusBar->Print();
	*/
	}
	else {
		this->shapeSelected = NULL;
	}
}

void FlowChartTemplate::mouseMoveEvent(QMouseEvent *event) {
	Long index = -1;

	QColor selectedColor(235, 235, 235);
	FlowChartShape::Shape *shape;
	Long i = 0;
	while (i < this->flowChartTemplate->GetLength()) {
		shape = this->flowChartTemplate->GetAt(i);
		if (shape->GetBackGroundColor() == selectedColor && this->oldShapeSelected != NULL) {
			shape->Paint(this->oldShapeSelected->GetBackGroundColor(), shape->GetBorderLine(), shape->GetBorderColor());
		}
		i++;
	}

	index = this->flowChartTemplate->Find(event->pos());

	if (index != -1) {
		shape = this->flowChartTemplate->GetAt(index);
		this->oldShapeSelected = shape->Clone();
		shape->Paint(selectedColor, shape->GetBorderLine(), shape->GetBorderColor());
	}

	this->repaint();
}