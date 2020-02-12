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
#include "FlowChartEditor.h"
#include "DrawingPaper.h"

#include "Array.h"
#include "Shape.h"

#include "Symbol.h"
#include "Line.h"

#include "Decision.h"
#include "Document.h"
#include "Preparation.h"
#include "Process.h"
#include "PunchedCard.h"
#include "Terminal.h"
#include "InputOutput.h"

#include "Arrow.h"
#include "Join.h"
#include "LeftDown.h"
#include "RepeatFalse.h"
#include "RepeatTrue.h"
#include "RightDown.h"
#include "RightDownJoin.h"

#include "Painter.h"
#include "DrawVisitor.h"

#include "FlowChartFont.h"
#include "StatusBar.h"
#include "ToolTip.h"
#include "TutorialForm.h"
#include "Tutorials.h"
#include "TutorialController.h"


// 메세지 맵
BEGIN_MESSAGE_MAP(FlowChartTemplate, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

FlowChartTemplate::FlowChartTemplate() {
	this->shapeSelected = NULL;
	this->flowChartTemplate = NULL;
	this->painter = NULL;
	this->mode = DRAWOFF;
	this->font = NULL;
	this->oldShapeSelected = NULL;
}

FlowChartTemplate::~FlowChartTemplate() {
	if (this->flowChartTemplate != NULL) {
		delete this->flowChartTemplate;
	}
	if (this->painter != NULL) {
		delete this->painter;
	}
	if (this->font != NULL) {
		delete this->font;
	}
}

int FlowChartTemplate::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);

	this->flowChartTemplate = new Template;
	Shape *template1 = new Terminal(25, 90, 150, 50, RGB(255, 153, 153), DOT, 20, String("START"));
	Shape *template2 = new Preparation(25, 160, 150, 50, RGB(153, 153, 255), DOT, 20, String("Preparation"));
	Shape *template3 = new InputOutput(25, 230, 150, 50, RGB(255, 255, 153), DOT, 20, String("READ "));
	Shape *template4 = new Process(25, 300, 150, 50, RGB(153, 255, 153), DOT, 20, String("Process"));
	Shape *template5 = new Decision(25, 370, 150, 50, RGB(255, 153, 255), DOT, 20, String("Decision"));
	Shape *template6 = new InputOutput(25, 440, 150, 50, RGB(255, 255, 153), DOT, 20, String("PRINT "));
	Shape *template7 = new Terminal(25, 510, 150, 50, RGB(255, 153, 153), DOT, 20, String("STOP"));

	dynamic_cast<Template*>(this->flowChartTemplate)->Register(template1);
	dynamic_cast<Template*>(this->flowChartTemplate)->Register(template2);
	dynamic_cast<Template*>(this->flowChartTemplate)->Register(template3);
	dynamic_cast<Template*>(this->flowChartTemplate)->Register(template4);
	dynamic_cast<Template*>(this->flowChartTemplate)->Register(template5);
	dynamic_cast<Template*>(this->flowChartTemplate)->Register(template6);
	dynamic_cast<Template*>(this->flowChartTemplate)->Register(template7);

	CRect rect;
	GetClientRect(&rect);
	this->painter = new Painter(this->GetDC(), rect.Width(), rect.Height(), RGB(255, 255, 255), TRANSPARENT);
	this->font = new FlowChartFont((FlowChartEditor*)this->GetParent());
	HFONT hFont = this->font->Create();
	this->painter->ChangeFont(hFont, this->font->GetColor());

	return 0;
}

void FlowChartTemplate::OnDestroy() {
	CWnd::OnDestroy();
}

void FlowChartTemplate::OnPaint() {
	CPaintDC dc(this);
	CPen pen;
	CPen *oldPen;

	int oldmode = dc.SetBkMode(TRANSPARENT);
	dc.SetROP2(R2_NOTXORPEN);

	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldPen = dc.SelectObject(&pen);

	CRect rect;
	this->GetClientRect(&rect);

	this->painter->Resize(this); // canvas size 변경
	this->painter->EraseBackground((float)0, (float)0, (float)rect.Width(), (float)rect.Height());
	this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(0, 0, 0));
	POINT points[5] = { {0, 0}, {rect.right, rect.top}, {rect.right, rect.bottom}, {rect.left, rect.bottom}, {0, 0} };

	//=======창 제목========
	FlowChartEditor *editor = (FlowChartEditor*)this->GetParent();
	CRect rect2 = rect;

	POINT backPoints[7] = { {0, 0}, {rect.right, rect.top}, {rect.right, rect2.top + 40}, {rect2.right - 40, rect2.top + 40},
	{rect2.right - 40, rect2.top + 13}, {rect2.left, rect2.top + 13}, {0, 0} };
	CRgn region;
	region.CreatePolygonRgn(backPoints, 7, ALTERNATE);
	this->painter->FillRegion(region, RGB(235, 235, 235));

	this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(102, 102, 102));
	this->painter->DrawLine(rect2.left, rect2.top + 10, rect2.right - 50, rect2.top + 10);
	this->painter->DrawLine(rect2.left, rect2.top + 13, rect2.right - 40, rect2.top + 13);
	this->painter->DrawLine(rect2.right - 40, rect2.top + 13, rect2.right - 40, rect2.top + 40);
	this->painter->DrawLine(rect2.left, rect2.top + 40, rect2.right, rect2.top + 40);

	rect2.top += 15;

	this->painter->DrawTextA(-20, " Template", -1, &rect2, DT_LEFT | DT_TOP);
	//======================
	FlowChartVisitor *visitor = new DrawVisitor(this->painter);
	this->flowChartTemplate->Accept(visitor);
	this->painter->Render(&dc, 0, 0, rect.Width(), rect.Height());

	dc.SelectObject(oldPen);
	dc.SetBkMode(oldmode);
	oldPen->DeleteObject();

	BOOL ret;
	if (editor->toolTip != NULL) {
		this->ModifyStyle(0, WS_CLIPSIBLINGS);
		ret = editor->toolTip->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
}

void FlowChartTemplate::OnLButtonDown(UINT nFlags, CPoint point) {
	FlowChartEditor* editor;

	editor = static_cast<FlowChartEditor*>(this->GetParent());

	Long index = -1;

	CDC *dc = this->GetDC();

	index = static_cast<Template *>(this->flowChartTemplate)->Find(dc, point);

	if (index != -1) {
		static_cast<DrawingPaper*>(editor->windows[0])->mode = DrawingPaper::DRAWING;
		dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Modify(1, String("DRAWING"));

		this->shapeSelected = static_cast<Template*>(this->flowChartTemplate)->GetAt(index);

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

		TutorialForm *tutorialForm = (TutorialForm*)editor->windows[2];
		if (tutorialForm != NULL) {
			tutorialForm->tutorialController->Update();
		}
	}
	else {
		this->shapeSelected = NULL;
	}

	this->ReleaseDC(dc);
}

void FlowChartTemplate::OnMouseMove(UINT nFlags, CPoint point) {
	Long index = -1;

	CDC *dc = this->GetDC();

	COLORREF selectedColor = RGB(235, 235, 235);
	Shape *shape;
	Long i = 0;
	while (i < static_cast<Template *>(this->flowChartTemplate)->GetLength()) {
		shape = static_cast<Template*>(this->flowChartTemplate)->GetAt(i);
		if (shape->GetBackGroundColor() == selectedColor && this->oldShapeSelected != NULL) {
			shape->Paint(this->oldShapeSelected->GetBackGroundColor(), shape->GetBorderLine(), shape->GetBorderColor());
		}
		i++;
	}

	index = static_cast<Template *>(this->flowChartTemplate)->Find(dc, point);

	if (index != -1) {
		shape = static_cast<Template*>(this->flowChartTemplate)->GetAt(index);
		this->oldShapeSelected = shape->Clone();
		shape->Paint(selectedColor, shape->GetBorderLine(), shape->GetBorderColor());
	}

	this->Invalidate();
}