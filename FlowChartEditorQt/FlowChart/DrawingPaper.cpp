/******************************************************************
 * 파일 이름 : DrawingPaper.cpp
 * 기능 : CFrameWnd 사용
 * 작성자 : 송윤창
 * 작성일자 : 2015년 4월 06일
*******************************************************************/
#include "DrawingPaper.h"

#include "FlowChartEditor.h"
#include "FlowChartTemplate.h"
#include "Label.h"

#include "FlowChart.h"
#include "Shape.h"
#include "Painter.h"
#include "Symbol.h"

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

#include "ToolFactory.h"
#include "DrawingTool.h"
#include "MovingTool.h"
#include "ResizingTool.h"
#include "SelectingTool.h"

#include "SequenceMake.h"
#include "IterationMake.h"
#include "SelectionMake.h"
#include "SelectionMake.h"

////////////////////////////////////
//#include "Text.h" // 테스트
/////////////////////////////////////
//#include "Formatter.h"
#include "Decision.h"

#include "KeyFactory.h"
#include "AccessKey.h"

#include "DeleteKey.h"
#include "UpKey.h"
#include "DownKey.h"
#include "LeftKey.h"
#include "RightKey.h"
#include "EscapeKey.h"

// Factory Pattern
// #include "Creator.h"
// #include "Tokenizer.h"

// Save
//#include "Configuration.h"

#include "Clipboard.h"

//#include <stdio.h>
#include <string>
#include <fstream>	//save  / load
#include <afxdlgs.h> // CFileDialog
#include "File.h"

#include "FlowChartVisitor.h"
#include "DrawVisitor.h"

#include "../Notepad/Glyph.h"
#include "Creator.h"

#include "ScrollController.h"
#include "VScrollActionFactory.h"
#include "VScrollActions.h"
#include "HScrollActionFactory.h"
#include "HScrollActions.h"
#include "Scrolls.h"
#include "VariableList.h"

#include "MemoryController.h"
#include "Memory.h"
#include "Executions.h"

#include "FlowChartKeyActionFactory.h"
#include "FlowChartKeyActions.h"

#include "Zoom.h"
#include "A4Paper.h"
#include "ZoomVisitor.h"
#include "CoordinateConverter.h"

#include "FlowChartFont.h"

#include "StatusBar.h"
#include "ToolTip.h"
#include "TutorialForm.h"
#include "Tutorials.h"
#include "TutorialMark.h"
#include "TutorialMarkFactory.h"
#include "TutorialController.h"
#include "Template.h"

#pragma warning (disable : 4996)
// 메세지 맵
BEGIN_MESSAGE_MAP(DrawingPaper, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()

	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()

	ON_WM_SIZE()

	ON_WM_SETCURSOR()

	ON_COMMAND(IDM_AE_SEQUENCE, OnSequnceMenuClick)
	ON_COMMAND(IDM_AE_ITERATION, OnIterationMenuClick)
	ON_COMMAND(IDM_AE_SELECION, OnSelectionMenuClick)

	ON_COMMAND(IDM_AE_MOVEMAKE, OnMoveMakeMenuClick)
	ON_COMMAND(IDM_AE_SIZEMAKE, OnSizeMakeMenuClick)
	ON_COMMAND(IDM_AE_INTERVALMAKE, OnIntervalMakeMenuClick)

	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()

END_MESSAGE_MAP()

DrawingPaper::DrawingPaper() {
	this->templateSelected = NULL;

	this->flowChart = NULL;

	this->label = NULL;
	this->painter = NULL;
	////////////////////////////////////////////////////////////////
	this->startX = 0;
	this->startY = 0;

	this->currentX = 0;
	this->currentY = 0;

	this->tool = NULL;

	this->mode = IDLE;
	this->indexOfSelected = -1;

	this->hitCode = -1;

	this->clipboard = NULL;

	this->scrollController = NULL;

	this->memoryController = NULL;

	this->variableList = NULL;

	this->zoom = NULL;

	this->hPopup = NULL;
}

DrawingPaper::~DrawingPaper() {
	if (this->flowChart != NULL) {
		delete this->flowChart;
	}

	if (this->painter != NULL) {
		delete this->painter;
		this->painter = NULL;
	}

	if (Label::Instance() != NULL) {
		Label::Destroy();
	}
	if (DrawingTool::Instance() != NULL) {
		DrawingTool::Destroy();
	}
	if (MovingTool::Instance() != NULL) {
		MovingTool::Destroy();
	}
	if (ResizingTool::Instance() != NULL) {
		ResizingTool::Destroy();
	}
	if (SelectingTool::Instance() != NULL) {
		SelectingTool::Destroy();
	}
	///////////////////////////////이건 여기 왜?
	if (DeleteKey::Instance() != NULL) {
		DeleteKey::Destroy();
	}
	if (UpKey::Instance() != NULL) {
		UpKey::Destroy();
	}
	if (DownKey::Instance() != NULL) {
		DownKey::Destroy();
	}
	if (LeftKey::Instance() != NULL) {
		LeftKey::Destroy();
	}
	if (RightKey::Instance() != NULL) {
		RightKey::Destroy();
	}
	if (EscapeKey::Instance() != NULL) {
		EscapeKey::Destroy();
	}
	//////////////////////////////////////////
	if (this->clipboard != NULL) {
		delete this->clipboard;
	}

	if (this->templateSelected != NULL) {
		delete this->templateSelected;
	}

	if (this->scrollController != NULL) {
		delete this->scrollController;
	}

	if (this->memoryController != NULL) {
		delete this->memoryController;
	}

	if (this->variableList != NULL) {
		delete this->variableList;
	}

	if (this->zoom != NULL) {
		delete this->zoom;
	}

	if (this->a4Paper != NULL) {
		delete this->a4Paper;
	}
}

int DrawingPaper::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);

	CRect rect;
	GetClientRect(&rect);

	this->flowChart = new FlowChart;

	this->painter = new Painter(this->GetDC(), rect.Width(), rect.Height(), RGB(255, 255, 255), TRANSPARENT);

	this->SetFocus();

	this->clipboard = new Clipboard;

	this->memoryController = new MemoryController(this);

	this->variableList = new VariableList;

	this->zoom = new Zoom(100);

	this->a4Paper = new A4Paper(444, 615, 1653, 2338, RGB(255, 255, 255));
	this->zoom->Set(40);

	return 0;
}

void DrawingPaper::OnDestroy() {
	CWnd::OnDestroy();
}

void DrawingPaper::OnPaint() {
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	this->painter->Resize(this); // canvas size 변경
	FlowChartEditor *editor = (FlowChartEditor*)this->GetParent();
	HFONT hFont = editor->font->Create();
	this->painter->ChangeFont(hFont, editor->font->GetColor());
	this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(0, 0, 0));
	//this->painter->EraseBackground((float)0, (float)0, (float)rect.Width(), (float)rect.Height());
	POINT points[5] = { {0, 0}, {rect.right, rect.top}, {rect.right, rect.bottom}, {rect.left, rect.bottom}, {0, 0} };
	this->painter->FillBackground(points, 5, RGB(235, 235, 235));

	//Visitor 패턴 적용	
	FlowChartVisitor *drawVisitor = new DrawVisitor(this->painter, this->scrollController);
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(this->zoom);
	Shape *cloneA4 = this->a4Paper->Clone();
	cloneA4->Accept(zoomVisitor);
	cloneA4->Accept(drawVisitor);

	this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(102, 102, 102));
	Shape *cloneFlowChart = this->flowChart->Clone();
	cloneFlowChart->Accept(zoomVisitor);
	cloneFlowChart->Accept(drawVisitor);

	if (this->templateSelected != NULL && this->templateSelected->IsSelected())
	{
		this->templateSelected->Accept(drawVisitor);
	}

	this->painter->Render(&dc, 0, 0, rect.Width(), rect.Height());

	if (cloneFlowChart != NULL) {
		delete cloneFlowChart;
	}

	if (cloneA4 != NULL) {
		delete cloneA4;
	}

	if (drawVisitor != NULL) {
		delete drawVisitor;
	}
	if (zoomVisitor != NULL) {
		delete zoomVisitor;
	}

	String mode;
	switch (this->mode) {
	case IDLE:
		mode = "IDLE"; break;
	case SELECT:
		mode = "SELECT"; break;
	case DRAWING:
		mode = "DRAWING"; break;
	case MOVING:
		mode = "MOVING"; break;
	case SIZING:
		mode = "SIZING"; break;
	default: break;
	}
	editor->statusBar->Modify(1, String(mode));
	editor->statusBar->Print();

	if (editor->toolTip != NULL) {
		this->ModifyStyle(0, WS_CLIPSIBLINGS);
		editor->toolTip->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
}

void DrawingPaper::OnLButtonDown(UINT nFlags, CPoint point) {
	this->SetFocus();

	if (this->label != NULL)
	{
		//19.09.03 Label의 (편집된)내용을 기호 안의 실제 데이터로 넣는 처리==================
		string content = this->label->note->GetContent();
		String contents(content);

		Shape *shape = static_cast<FlowChart*>(this->flowChart)->GetAt(this->indexOfSelected);

		shape->Rewrite(contents);
		//=====================intellisense========================
		if (dynamic_cast<Preparation*>(shape)) {
			if (this->variableList != NULL) {
				delete this->variableList;
			}
			this->variableList = new VariableList;
			this->variableList->Add(shape->GetContents());
		}
		//=========================================================

		this->label->Destroy();
		this->label = NULL;

		FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->GetParent());
		TutorialForm *tutorialForm = (TutorialForm*)editor->windows[2];
		if (tutorialForm != NULL) {
			tutorialForm->tutorialController->Update();
		}
	}
	this->tool = ToolFactory::Create(this, point);

	if (this->tool != NULL) {
		this->tool->OnLButtonDown(this, nFlags, point);
		this->SetCapture();
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void DrawingPaper::OnMouseMove(UINT nFlags, CPoint point) {
	if (this->tool != NULL) {
		this->tool->OnMouseMove(this, nFlags, point);
	}
	CString x;
	x.Format("X : %d", point.x);
	dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Modify(2, String((LPCTSTR)x));
	CString y;
	y.Format("Y : %d", point.y);
	dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Modify(3, String((LPCTSTR)y));
	dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Print();

	//템플릿 창 기호에 마우스 올릴 때 효과가 마우스가 떠나도 지속되는 오류 때문에 넣음.
	FlowChartTemplate *templateWnd = static_cast<FlowChartTemplate*>(static_cast<FlowChartEditor*>(this->GetParent())->windows[1]);
	COLORREF selectedColor = RGB(235, 235, 235);
	Shape *shape;
	Long i = 0;
	while (i < static_cast<Template *>(templateWnd->flowChartTemplate)->GetLength()) {
		shape = static_cast<Template*>(templateWnd->flowChartTemplate)->GetAt(i);
		if (shape->GetBackGroundColor() == selectedColor && templateWnd->oldShapeSelected != NULL) {
			shape->Paint(templateWnd->oldShapeSelected->GetBackGroundColor(), shape->GetBorderLine(), shape->GetBorderColor());
		}
		i++;
	}
	templateWnd->Invalidate();

	CWnd::OnMouseMove(nFlags, point);
}

void DrawingPaper::OnLButtonUp(UINT nFlags, CPoint point) {
	dynamic_cast<FlowChart*>(this->flowChart)->AscendingSort();

	if (this->tool != NULL) {
		this->tool->OnLButtonUp(this, nFlags, point);
		ReleaseCapture();
	}
	if (this->scrollController != NULL) {
		this->scrollController->Update();
	}

	this->memoryController->Quadrate();

	CWnd::OnLButtonUp(nFlags, point);
}

void DrawingPaper::OnLButtonDblClk(UINT nFlags, CPoint point) {
	// 상태 패턴 : 텍스트 조작자 Manipulator
	Shape *shape;
	Long left, top, right, bottom, halfHeight;

	CDC *dc = this->GetDC();
	RECT rect;
	this->GetClientRect(&rect);
	Long positionX;
	Long positionY;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->GetPosition();
		positionY = this->scrollController->GetScroll(0)->GetPosition();
	}
	point.x += positionX;
	point.y += positionY;
	Shape *holdA4Paper = this->a4Paper->Clone();
	Shape *holdFlowChart = this->flowChart->Clone();
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(this->zoom);
	holdA4Paper->Accept(zoomVisitor);
	holdFlowChart->Accept(zoomVisitor);

	this->indexOfSelected = static_cast<FlowChart*>(holdFlowChart)->Find(dc, point);

	shape = static_cast<FlowChart*>(holdFlowChart)->GetAt(this->indexOfSelected);

	if (this->indexOfSelected != -1 &&
		((point.x > shape->GetX() + 5 && point.x < shape->GetX() + shape->GetWidth() - 5) ||
		(point.y > shape->GetY() + 5 && point.y < shape->GetY() + shape->GetHeight() - 5))) {

		this->SendMessage(WM_KILLFOCUS, 0, 0);

		COLORREF color = shape->GetBackGroundColor();
		this->label = Label::Instance(&(shape->GetContents()), color);

		halfHeight = shape->GetHeight() / 2;
		left = shape->GetX() + halfHeight - positionX;
		top = shape->GetY() + 1 - positionY;
		right = shape->GetX() + shape->GetWidth() - halfHeight + 5 - positionX;
		bottom = shape->GetY() + shape->GetHeight() - 1 - positionY;

		this->label->Open(left, top, right - left, bottom - top, &(shape->GetContents()));
		this->label->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), this, -1);

		Long(*indexes) = new Long[dynamic_cast<FlowChart*>(this->flowChart)->GetLength()];
		indexes[0] = this->indexOfSelected;
		this->memoryController->RememberOther(indexes, 1);

		shape = static_cast<FlowChart*>(this->flowChart)->GetAt(this->indexOfSelected);
		shape->Rewrite(String(""));
		this->label->SetFocus();

		if (indexes != 0) {
			delete[] indexes;
		}

		FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->GetParent());
		TutorialForm *tutorialForm = static_cast<TutorialForm*>(editor->windows[2]);
		if (tutorialForm != NULL) {
			tutorialForm->MoveWindow(1230, 70, 660, 940, TRUE);
		}
	}
}

void DrawingPaper::OnSize(UINT nType, int cx, int cy) {
	if (this->scrollController == NULL) {
		this->scrollController = new ScrollController(this);

		Long position = this->scrollController->MoveVerticalScroll(1311);
		Long previousPosition = this->SetScrollPos(SB_VERT, position, TRUE);
		//position = this->GetScrollPos(SB_VERT);
		this->scrollController->MoveVerticalScroll(position);
		this->ScrollWindow(0, previousPosition - position);

		position = this->scrollController->MoveHorizontalScroll(427);
		previousPosition = this->SetScrollPos(SB_HORZ, position, TRUE);
		//position = this->GetScrollPos(SB_HORZ);
		this->scrollController->MoveHorizontalScroll(position);
		this->ScrollWindow(previousPosition - position, 0);

		this->scrollController->Update();
	}
	if (this->flowChart != NULL) {
		this->scrollController->Update();
	}

	CRect rect;
	GetClientRect(&rect);
	this->InvalidateRect(rect, TRUE);
}

void DrawingPaper::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	VScrollActionFactory vScrollActionFactory(this);

	VScrollAction *vScrollAction = vScrollActionFactory.Make(nSBCode);
	if (vScrollAction != NULL) {
		vScrollAction->OnVScroll(nSBCode, nPos, pScrollBar);
		delete vScrollAction;
	}
	this->Invalidate();
}

void DrawingPaper::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	HScrollActionFactory hScrollFactory(this);
	HScrollAction *hScrollAction = hScrollFactory.Make(nSBCode);
	if (hScrollAction != NULL) {
		hScrollAction->OnHScroll(nSBCode, nPos, pScrollBar);
		delete hScrollAction;
	}
	this->Invalidate();
}

BOOL DrawingPaper::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {

	LONG style = this->GetStyle();

	SHORT isCtrl = GetKeyState(VK_CONTROL) & 0X8000;

	if (isCtrl && (style & WS_VSCROLL) != 0) { //zoom
		Long oldRate = this->zoom->GetRate();
		Long rate;
		CString rateStatus;
		if (zDelta > 0 && oldRate < 150) {
			rate = oldRate + 10;
			this->zoom->Set(rate);
			rateStatus.Format("%d", rate);
			rateStatus += "%";
			dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Modify(4, String((LPCTSTR)rateStatus));
		}
		else if (zDelta < 0 && oldRate > 40) {
			rate = oldRate - 10;
			this->zoom->Set(rate);
			rateStatus.Format("%d", rate);
			rateStatus += "%";
			dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Modify(4, String((LPCTSTR)rateStatus));
		}
		dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Print();
		this->scrollController->Update();
	}
	else if ((style & WS_VSCROLL) != 0) {
		Long position = this->scrollController->Rotate(zDelta);
		Long previousPosition = this->SetScrollPos(SB_VERT, position, TRUE);
		position = this->GetScrollPos(SB_VERT);
		this->scrollController->MoveVerticalScroll(position);
		this->ScrollWindow(0, previousPosition - position);
		this->scrollController->Update();
	}
	return TRUE;
}

void DrawingPaper::DrawTemporaryObject(Shape *entity) {
	// 사용안함
	CDC *dc = this->GetDC();
	RECT rect = { entity->GetX(), entity->GetY(), entity->GetX() + entity->GetWidth(), entity->GetY() + entity->GetHeight() };

	//this->painter->Resize(this); // canvas size 변경
	this->painter->Resize(this, rect.left, rect.top, rect.right, rect.bottom);
	this->painter->SetBkMode(TRANSPARENT);

	this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(166, 166, 166));
	this->painter->EraseBackground((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom);

	//entity->Draw(this->painter);
	FlowChartVisitor *visitor = new DrawVisitor(this->painter);
	entity->Accept(visitor);

	this->painter->Render(dc, rect.left, rect.top, rect.right, rect.bottom);
}

void DrawingPaper::DrawTemporaryObjects(Long(*indexes), Long count) {
	// 사용안함	
	CRgn region;
	//DrawObjects(indexes, count);
	GetObjectsRgn(indexes, count, &region);
	this->InvalidateRgn(&region, true);
	//this->InvalidateRgn(this->drawingRegion, true);		
	region.DeleteObject();
}

void DrawingPaper::DrawObjects(Long(*indexes), Long count) {
	CDC *dc = this->GetDC();
	CFont font;
	CPen pen;
	CBrush brush;

	CFont *oldFont;
	CPen *oldPen;
	CBrush *oldBrush;

	pen.CreatePen(PS_SOLID, 2, RGB(166, 166, 166));
	oldPen = dc->SelectObject(&pen);

	brush.CreateSolidBrush(RGB(0, 0, 255));
	oldBrush = dc->SelectObject(&brush);

	font.CreateFont(FONT_HEIGHT, 0, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "System");
	oldFont = dc->SelectObject(&font);

	FlowChartVisitor *visitor = new DrawVisitor(this->painter);

	Shape *shape;
	for (Long i = 0; i < count; i++) {
		shape = dynamic_cast<FlowChart *>(this->flowChart)->GetAt(indexes[i]);
		shape->Accept(visitor);
	}

	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);
	dc->SelectObject(oldFont);

	DeleteObject(pen);
	DeleteObject(brush);
	DeleteObject(font);

	this->ReleaseDC(dc);
}

void DrawingPaper::GetObjectsRgn(Long(*indexes), Long count, CRgn *region) {
	CRgn shapeRegion;
	CRgn textRegion;
	CRgn selectionMarksRegion;
	Long left, top, right, bottom;
	Shape *shape;

	if (count > 0) {
		shape = dynamic_cast<FlowChart *>(this->flowChart)->GetAt(indexes[0]);
		shape->GetRegion(this->painter, 10, region);
		shape->GetSelectionMarkerAllRegion(&selectionMarksRegion);
		region->CombineRgn(region, &selectionMarksRegion, RGN_OR);

		//shape->GetFormattingArea(&left, &top, &right, &bottom);
		left = shape->GetX();
		top = shape->GetY();
		right = left + shape->GetWidth();
		bottom = top + shape->GetHeight();

		textRegion.CreateRectRgn(left, top - 10, right, bottom + 10);
		region->CombineRgn(region, &textRegion, RGN_OR);

		textRegion.DeleteObject();
		selectionMarksRegion.DeleteObject();
	}

	for (Long i = 1; i < count; i++) {
		shape = dynamic_cast<FlowChart *>(this->flowChart)->GetAt(indexes[i]);
		shape->GetRegion(this->painter, 10, &shapeRegion);
		shape->GetSelectionMarkerAllRegion(&selectionMarksRegion);
		shapeRegion.CombineRgn(&shapeRegion, &selectionMarksRegion, RGN_OR);

		//shape->GetFormattingArea(&left, &top, &right, &bottom);
		left = shape->GetX();
		top = shape->GetY();
		right = left + shape->GetWidth();
		bottom = top + shape->GetHeight();

		textRegion.CreateRectRgn(left, top - 10, right, bottom + 10);
		shapeRegion.CombineRgn(&shapeRegion, &textRegion, RGN_OR);

		region->CombineRgn(region, &shapeRegion, RGN_OR);

		shapeRegion.DeleteObject();
		textRegion.DeleteObject();
		selectionMarksRegion.DeleteObject();
	}
}

void DrawingPaper::DrawSelectingArea() {
	CDC *dc = this->GetDC();
	CPen pen;
	CPen *oldPen;

	dc->SetROP2(R2_NOTXORPEN);

	pen.CreatePen(PS_DOT, 1, RGB(166, 166, 166));

	oldPen = dc->SelectObject(&pen);

	dc->Rectangle(this->startX, this->startY, this->currentX, this->currentY);

	dc->SelectObject(oldPen);
	this->ReleaseDC(dc);

	DeleteObject(pen);
}

void DrawingPaper::DrawActiveShape(Shape *entity) {
	CRect rect;
	CPen pen;
	CPen *oldPen;
	CBrush *oldBrush;

	CDC *dc = this->GetDC();
	GetClientRect(&rect);
	int oldmode = dc->SetBkMode(TRANSPARENT);

	dc->SetROP2(R2_NOTXORPEN);
	//pen.CreatePen(PS_DOT,1,RGB(59,219,22));
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 255));
	oldPen = dc->SelectObject(&pen);

	oldBrush = dc->SelectObject((CBrush*)dc->SelectStockObject(NULL_BRUSH));

	entity->DrawActiveShape(dc);

	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);

	dc->SetBkMode(oldmode);
	this->ReleaseDC(dc);

	DeleteObject(pen);
}

void DrawingPaper::DrawActiveShape2(Shape *entity) {
	LONG oldMode;
	LineProperty oldLineProperty(this->painter->GetLineStyle(), this->painter->GetLineWidth(), this->painter->GetLineCapStyle(),
		this->painter->GetLineJoinType(), this->painter->GetLineColor());

	PlaneProperty oldPlaneProperty(this->painter->GetPlaneStyle(), this->painter->GetPlanColor());

	oldMode = this->painter->SetBkMode(TRANSPARENT);
	//this->painter->ChangeLineProperty(PS_DOT,1,PS_ENDCAP_SQUARE,PS_JOIN_MITER,RGB(0,0,255));
	this->painter->ChangeLineProperty(PS_DASH, 1, PS_ENDCAP_SQUARE, PS_JOIN_MITER, RGB(0, 0, 255));
	this->painter->ChangePlaneProperty(BS_NULL, RGB(0, 0, 255));

	entity->DrawActiveShape(painter);

	this->painter->ChangeLineProperty(oldLineProperty.GetStyle(), oldLineProperty.GetWidth(),
		oldLineProperty.GetCapStyle(), oldLineProperty.GetJoinType(), oldLineProperty.GetColor());
	this->painter->ChangePlaneProperty(oldPlaneProperty.GetStyle(), oldPlaneProperty.GetColor());
	this->painter->SetBkMode(oldMode);
}

void DrawingPaper::DrawSelectionMark(POINT(*points), Long count) {
	CDC *dc = this->GetDC();
	CRect rect;
	GetClientRect(&rect);
	CPen pen;
	CPen *oldPen;
	CBrush *oldBrush;

	int oldmode = dc->SetBkMode(TRANSPARENT);

	dc->SetROP2(R2_NOTXORPEN);
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	oldPen = dc->SelectObject(&pen);

	oldBrush = dc->SelectObject((CBrush*)dc->SelectStockObject(NULL_BRUSH));

	POINT selectionMarkPoints[BOXVERTECIES];
	Long i = 0;
	while (i < count) {
		selectionMarkPoints[0].x = points[i].x - BOXLENGTH;
		selectionMarkPoints[1].x = points[i].x + BOXLENGTH;
		selectionMarkPoints[2].x = points[i].x + BOXLENGTH;
		selectionMarkPoints[3].x = points[i].x - BOXLENGTH;

		selectionMarkPoints[0].y = points[i].y - BOXLENGTH;
		selectionMarkPoints[1].y = points[i].y - BOXLENGTH;
		selectionMarkPoints[2].y = points[i].y + BOXLENGTH;
		selectionMarkPoints[3].y = points[i].y + BOXLENGTH;

		dc->Polygon(selectionMarkPoints, BOXVERTECIES);
		i++;
	}

	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);

	dc->SetBkMode(oldmode);
	this->ReleaseDC(dc);

	pen.DeleteObject();
}

void DrawingPaper::DrawSelectionMark2(POINT(*points), Long count) {
	LONG oldMode;

	LineProperty oldLineProperty(this->painter->GetLineStyle(), this->painter->GetLineWidth(), this->painter->GetLineCapStyle(),
		this->painter->GetLineJoinType(), this->painter->GetLineColor());

	PlaneProperty oldPlaneProperty(this->painter->GetPlaneStyle(), this->painter->GetPlanColor());

	oldMode = this->painter->SetBkMode(OPAQUE);

	this->painter->ChangeLineProperty(PS_SOLID, 1, PS_ENDCAP_SQUARE, PS_JOIN_MITER, RGB(0, 0, 255));
	this->painter->ChangePlaneProperty(BS_NULL, RGB(0, 0, 255));

	POINT selectionMarkPoints[BOXVERTECIES];
	Long i = 0;
	while (i < count) {
		selectionMarkPoints[0].x = points[i].x - BOXLENGTH;
		selectionMarkPoints[1].x = points[i].x + BOXLENGTH;
		selectionMarkPoints[2].x = points[i].x + BOXLENGTH;
		selectionMarkPoints[3].x = points[i].x - BOXLENGTH;

		selectionMarkPoints[0].y = points[i].y - BOXLENGTH;
		selectionMarkPoints[1].y = points[i].y - BOXLENGTH;
		selectionMarkPoints[2].y = points[i].y + BOXLENGTH;
		selectionMarkPoints[3].y = points[i].y + BOXLENGTH;

		this->painter->DrawPolygon(selectionMarkPoints, BOXVERTECIES);
		i++;
	}

	this->painter->ChangeLineProperty(oldLineProperty.GetStyle(), oldLineProperty.GetWidth(), oldLineProperty.GetCapStyle(),
		oldLineProperty.GetJoinType(), oldLineProperty.GetColor());
	this->painter->ChangePlaneProperty(oldPlaneProperty.GetStyle(), oldPlaneProperty.GetColor());
	this->painter->SetBkMode(oldMode);
}

void DrawingPaper::FillSelectionMark(POINT point) {
	CDC *dc = this->GetDC();
	CRect rect;
	GetClientRect(&rect);
	CPen pen;
	CPen *oldPen;
	CBrush brush;
	CBrush *oldBrush;

	int oldmode = dc->SetBkMode(OPAQUE);
	dc->SetROP2(R2_NOTXORPEN);

	//pen.CreatePen(PS_SOLID, 1, RGB(59,219,22));
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	oldPen = dc->SelectObject(&pen);

	//brush.CreateSolidBrush(RGB(59,219,22));
	brush.CreateSolidBrush(RGB(0, 0, 255));
	oldBrush = dc->SelectObject(&brush);

	CRect selectionMark;
	selectionMark.left = point.x + 1 - MARKLENGTH;
	selectionMark.top = point.y + 1 - MARKLENGTH;
	selectionMark.right = point.x + MARKLENGTH;
	selectionMark.bottom = point.y + MARKLENGTH;
	//dc->FillRect(&selectionMark, &brush);
	dc->Rectangle(selectionMark);

	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);
	dc->SetBkMode(oldmode);

	pen.DeleteObject();
	brush.DeleteObject();
	this->ReleaseDC(dc);
}

void DrawingPaper::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
	CDC *pDC = CWnd::GetDC();
	AccessKey *accessKey;
	accessKey = KeyFactory::Create(this, nChar, nRepCnt, nFlags);
	if (accessKey != NULL) {
		accessKey->OnKeyDown(this, nChar, nRepCnt, nFlags);
	}

	FlowChartEditor *editor = (FlowChartEditor*)this->GetParent();
	FlowChartKeyActionFactory keyActionFactory(editor);
	FlowChartKeyAction *keyAction = keyActionFactory.Make(nChar);

	if (keyAction != 0) {
		keyAction->OnKeyDown(nChar, nRepCnt, nFlags);
		delete keyAction;
	}
	CDC *dc = editor->GetDC();
	editor->ReleaseDC(dc);
	editor->windows[1]->Invalidate();

	this->RedrawWindow();
}

void DrawingPaper::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CWnd::OnChar(nChar, nRepCnt, nFlags);

	switch (nChar) {
	case 1: // SELECT ALL ( Ctrl + a )
		(dynamic_cast<FlowChart *>(this->flowChart))->SelectAll();
		if (dynamic_cast<FlowChart *>(this->flowChart)->GetLength() > 0) {
			this->mode = SELECT;
		}
		break;
	case 3: // COPY ( Ctrl + c )
		this->clipboard->Copy(this); break;
	case 22: // PASETE (Ctrl + v )
		this->clipboard->Paste(this); break;
	case 24: // CUT ( Ctrl + x )
		this->clipboard->Cut(this); break;
	case 26: // UNDO ( Ctrl + z )
		if (this->memoryController->GetUndoMemory()->GetLength() > 0) {
			this->memoryController->RememberUndo();
			this->memoryController->Undo();
			dynamic_cast<FlowChart*>(this->flowChart)->AscendingSort();
			this->memoryController->Quadrate();
		}
		break;
	case 25: // REDO ( Ctrl + y )
		if (this->memoryController->GetRedoMemory()->GetLength() > 0) {
			this->memoryController->RememberRedo();
			this->memoryController->Redo();
			dynamic_cast<FlowChart*>(this->flowChart)->AscendingSort();
			this->memoryController->Quadrate();
		}
		break;
	}

	this->RedrawWindow();
}

void DrawingPaper::OnKillFocus(CWnd* pNewWnd) {
	CWnd::OnKillFocus(pNewWnd);
}

void DrawingPaper::OnSetFocus(CWnd* pOldWnd) {
	CWnd::OnSetFocus(pOldWnd);
}

BOOL DrawingPaper::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {

	BOOL res = TRUE;
	HCURSOR cursor = GetCursor();
	if (cursor)
		::SetCursor(cursor);
	else
		res = CWnd::OnSetCursor(pWnd, nHitTest, message);
	return res;
}

HCURSOR DrawingPaper::GetCursor() {
	HCURSOR result = NULL;
	Long i = 0;
	Long end;
	Shape *shape;

	if (this->mode == SELECT) {

		const MSG* msg = GetCurrentMessage();
		CPoint point(msg->pt);
		ScreenToClient(&point);

		Long positionX = this->scrollController->GetScroll(1)->GetPosition();
		Long positionY = this->scrollController->GetScroll(0)->GetPosition();
		point.x += positionX;
		point.y += positionY;

		Shape *holdA4Paper = this->a4Paper->Clone();
		FlowChartVisitor *zoomVisitor = new ZoomVisitor(this->zoom);
		holdA4Paper->Accept(zoomVisitor);

		Long quotient;
		Long remainder;

		POINT currentReal = { point.x, point.y };
		POINT currentVirtual = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertVirtual(currentReal);

		quotient = currentVirtual.x * 100 / this->zoom->GetRate();
		remainder = currentVirtual.x * 100 % this->zoom->GetRate();
		if (remainder >= 50) quotient++;
		currentVirtual.x = quotient;

		quotient = currentVirtual.y * 100 / this->zoom->GetRate();
		remainder = currentVirtual.y * 100 % this->zoom->GetRate();
		if (remainder >= 50) quotient++;
		currentVirtual.y = quotient;

		currentReal = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertReal(currentVirtual);

		point.x = currentReal.x;
		point.y = currentReal.y;

		end = (dynamic_cast<FlowChart *>(this->flowChart))->GetLength();
		while (i < end) {
			shape = (dynamic_cast<FlowChart *>(this->flowChart))->GetAt(i);
			if (shape->IsSelected()) {
				int hitCode = shape->GetHitCode(this->painter, point);
				if (hitCode != HIT_NONE && hitCode != HIT_BODY) {
					result = shape->GetCursor(hitCode);
				}
			}
			i++;
		}
	}
	else if (this->mode == DRAWING) {
		result = LoadCursor(NULL, IDC_CROSS);
	}


	return result;
}

void DrawingPaper::OnSequnceMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->SequenceMake(this);

	this->zoom->Set(rate);

	this->RedrawWindow();

	TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(this->GetParent())->windows[2];
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
}

void DrawingPaper::OnIterationMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->IterationMake(this);

	this->zoom->Set(rate);

	this->RedrawWindow();

	TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(this->GetParent())->windows[2];
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
}

void DrawingPaper::OnSelectionMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->SelectionMake(this);

	this->zoom->Set(rate);

	this->RedrawWindow();

	TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(this->GetParent())->windows[2];
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
}

void DrawingPaper::OnMoveMakeMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->MoveMake(this);

	this->zoom->Set(rate);

	this->RedrawWindow();

	TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(this->GetParent())->windows[2];
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
}

void DrawingPaper::OnSizeMakeMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->SizeMake(this);

	this->zoom->Set(rate);

	this->RedrawWindow();
}

void DrawingPaper::OnIntervalMakeMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->IntervalMake(this);

	this->zoom->Set(rate);

	this->RedrawWindow();

	TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(this->GetParent())->windows[2];
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
}

void DrawingPaper::OnContextMenu(CWnd* pWnd, CPoint pos) {
	//HMENU hPopup;
	this->hPopup = ::CreatePopupMenu();

	::AppendMenu(hPopup, MF_STRING, IDM_AE_MOVEMAKE, "기호 위치 같게");
	::AppendMenu(hPopup, MF_STRING, IDM_AE_SIZEMAKE, "기호 크기 같게");
	::AppendMenu(hPopup, MF_STRING, IDM_AE_INTERVALMAKE, "기호 간격 같게");

	::AppendMenu(hPopup, MF_STRING, IDM_AE_SEQUENCE, "순차구조");
	::AppendMenu(hPopup, MF_STRING, IDM_AE_ITERATION, "반복구조");
	::AppendMenu(hPopup, MF_STRING, IDM_AE_SELECION, "선택구조");

	::EnableMenuItem(hPopup, IDM_AE_MOVEMAKE, MF_BYCOMMAND | MF_GRAYED);
	::EnableMenuItem(hPopup, IDM_AE_SIZEMAKE, MF_BYCOMMAND | MF_GRAYED);
	::EnableMenuItem(hPopup, IDM_AE_INTERVALMAKE, MF_BYCOMMAND | MF_GRAYED);

	::EnableMenuItem(hPopup, IDM_AE_SEQUENCE, MF_BYCOMMAND | MF_GRAYED);
	::EnableMenuItem(hPopup, IDM_AE_ITERATION, MF_BYCOMMAND | MF_GRAYED);
	::EnableMenuItem(hPopup, IDM_AE_SELECION, MF_BYCOMMAND | MF_GRAYED);

	Long(*indexes);
	Long count;
	Shape *shape;
	(dynamic_cast<FlowChart *>(this->flowChart))->GetSelecteds(&indexes, &count);

	if (count > 1) {
		::EnableMenuItem(hPopup, IDM_AE_MOVEMAKE, MF_BYCOMMAND | MF_ENABLED);
		::EnableMenuItem(hPopup, IDM_AE_SIZEMAKE, MF_BYCOMMAND | MF_ENABLED);
		::EnableMenuItem(hPopup, IDM_AE_INTERVALMAKE, MF_BYCOMMAND | MF_ENABLED);

		::EnableMenuItem(hPopup, IDM_AE_SEQUENCE, MF_BYCOMMAND | MF_ENABLED);

		shape = (dynamic_cast<FlowChart *>(this->flowChart))->GetAt(indexes[0]);
		if (dynamic_cast<Decision *>(shape)) {
			::EnableMenuItem(hPopup, IDM_AE_ITERATION, MF_BYCOMMAND | MF_ENABLED);
			//19.09.16 판단기호 왼쪽에 처리할 내용이 없으면 선택 기호 메뉴 활성화X
			Long leftCount = 0;
			Long i = 1;
			while (i < count) {
				Shape *left = (dynamic_cast<FlowChart *>(this->flowChart))->GetAt(indexes[i]);
				if (left->CenterOfGravityX() < shape->CenterOfGravityX()) {
					leftCount++;
				}
				i++;
			}
			if (leftCount > 0) {
				::EnableMenuItem(hPopup, IDM_AE_SELECION, MF_BYCOMMAND | MF_ENABLED);
			}
		}
	}

	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->GetParent());
	TutorialForm *tutorialForm = static_cast<TutorialForm*>(editor->windows[2]);
	if (tutorialForm != NULL) {
		if (dynamic_cast<ContextMenuTutorial*>(tutorialForm->lastConcrete)) { //직전에 수행한 튜토리얼이 콘텍스트메뉴일 경우에만 다음걸 수행한다. 아니면 이 이벤트에서 시나리오 진행 안함.
			tutorialForm->tutorialController->Update();
		}
	}

	if (indexes != 0)
	{
		delete[] indexes;
	}

	::TrackPopupMenu(hPopup, TPM_LEFTALIGN, pos.x, pos.y, 0, pWnd->operator HWND(), NULL);
	BOOL ret = ::DestroyMenu(hPopup);
	if (ret == TRUE) this->hPopup = NULL;
}

void DrawingPaper::New() {
	CString fileName;

	FlowChartEditor *editor = static_cast<FlowChartEditor *>(this->GetParent());
	int mId = MessageBox("변경내용을 저장하시겠습니까?", "새로만들기", MB_ICONQUESTION | MB_YESNOCANCEL);
	if (mId == IDYES) {
		static char BASED_CODE szFilter[] = "txt Files (*.txt)|*.txt||";
		CFileDialog dlg(FALSE, "*.txt", "*.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
		if (dlg.DoModal() == IDOK) {
			editor->fileOpenPath = dlg.GetPathName();
			Save(editor->fileOpenPath);
		}
		(dynamic_cast<FlowChart *>(this->flowChart))->Clear();
		editor->SetWindowText("제목없음 - FlowChart");
		this->mode = IDLE;
		this->indexOfSelected = -1;
	}
	else if (mId == IDNO) {
		(dynamic_cast<FlowChart *>(this->flowChart))->Clear();
		editor->SetWindowText("제목없음 - FlowChart");
		this->mode = IDLE;
		this->indexOfSelected = -1;
	}
}

Long DrawingPaper::Save(const char(*fileName)) {
	File file;
	return file.Save(this, fileName);
}

Long DrawingPaper::Load(const char(*fileName)) {
	File file;
	return file.Load(this, fileName);
}