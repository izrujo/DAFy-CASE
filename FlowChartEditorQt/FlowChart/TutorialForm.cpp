#include "TutorialForm.h"
#include "Painter.h"
#include "FlowChartEditor.h"
#include "TextRegion.h"
#include "Template.h"
#include "Tutorials.h"
#include "TutorialMarkFactory.h"
#include "RectangleRegion.h"
#include "FlowChart.h"
#include "DrawingPaper.h"
#include "FlowChartVisitor.h"
#include "DrawVisitor.h"
#include "File.h"
#include "ZoomVisitor.h"
#include "Zoom.h"
#include "FlowChartFont.h"
#include "Line.h"
#include "ToolTip.h"
#include "NumberBox.h"
#include "TutorialMark.h"
#include "TutorialController.h"

BEGIN_MESSAGE_MAP(TutorialForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

TutorialForm::TutorialForm() {
	this->lists = NULL;
	this->painter = NULL;
	this->sample = NULL;
	this->font = NULL;
	this->main = NULL;
	this->current = NULL;
	this->lastConcrete = NULL;
	this->tutorialController = NULL;
}

int TutorialForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	int ret = ::SetLayeredWindowAttributes(this->m_hWnd, RGB(0, 0, 0), 90, LWA_ALPHA);
	this->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);

	CRect rect;
	FlowChartEditor *editor = (FlowChartEditor*)this->GetParent();
	editor->GetWindowRect(rect);
	this->painter = new Painter(this->GetDC(), rect.Width(), rect.Height(), RGB(0, 0, 0), TRANSPARENT);

	this->lists = new Template(1);

	TextRegion *textRegion;
	textRegion = new TextRegion(560, 880, 100, 50, RGB(255, 255, 255), DOT, RGB(52, 52, 52), String("종료"));
	this->lists->Register(textRegion);

	File file;
	file.Load(static_cast<DrawingPaper*>(editor->windows[0]), "sample.txt");
	this->sample = new FlowChart(*(dynamic_cast<FlowChart*>((static_cast<DrawingPaper*>(editor->windows[0]))->flowChart)));
	dynamic_cast<FlowChart*>((static_cast<DrawingPaper*>(editor->windows[0]))->flowChart)->Clear();

	//튜토리얼 구성
	this->main = new MainTutorial(17);
	Tutorial *detail;

	//STOP
	Tutorial *seventeenth = new SeveralTutorial(3);
	detail = new DrawTutorial(editor);
	seventeenth->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	seventeenth->Add(detail);
	this->main->Add(seventeenth);

	//Iteration
	Tutorial *sixteenth = new SeveralTutorial(3);
	detail = new IterationMakeTutorial(editor);
	sixteenth->Add(detail);
	detail = new ContextMenuTutorial(editor);
	sixteenth->Add(detail);
	detail = new GroupTutorial(editor);
	sixteenth->Add(detail);
	this->main->Add(sixteenth);

	//Sequence, Position, Interval
	Tutorial *fifteenth = new SeveralTutorial(4);
	detail = new SequenceMakeTutorial(editor);
	fifteenth->Add(detail);
	detail = new PositionTutorial(editor);
	fifteenth->Add(detail);
	detail = new ContextMenuTutorial(editor);
	fifteenth->Add(detail);
	detail = new GroupTutorial(editor);
	fifteenth->Add(detail);
	this->main->Add(fifteenth);

	//READ
	Tutorial *fourteenth = new SeveralTutorial(6);
	detail = new MoveTutorial(editor);
	fourteenth->Add(detail);
	detail = new ReSizeTutorial(editor);
	fourteenth->Add(detail);
	detail = new EditContentsTutorial(editor);
	fourteenth->Add(detail);
	detail = new DrawTutorial(editor);
	fourteenth->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	fourteenth->Add(detail);
	this->main->Add(fourteenth);

	//PRINT
	Tutorial *thirteenth = new SeveralTutorial(6);
	detail = new MoveTutorial(editor);
	thirteenth->Add(detail);
	detail = new ReSizeTutorial(editor);
	thirteenth->Add(detail);
	detail = new EditContentsTutorial(editor);
	thirteenth->Add(detail);
	detail = new DrawTutorial(editor);
	thirteenth->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	thirteenth->Add(detail);
	this->main->Add(thirteenth);

	//Selection
	Tutorial *twelfth = new SeveralTutorial(3);
	detail = new SelectionMakeTutorial(editor);
	twelfth->Add(detail);
	detail = new ContextMenuTutorial(editor);
	twelfth->Add(detail);
	detail = new GroupTutorial(editor);
	twelfth->Add(detail);
	this->main->Add(twelfth);

	//FAIL
	Tutorial *eleventh = new SeveralTutorial(6);
	detail = new MoveTutorial(editor);
	eleventh->Add(detail);
	detail = new ReSizeTutorial(editor);
	eleventh->Add(detail);
	detail = new EditContentsTutorial(editor);
	eleventh->Add(detail);
	detail = new DrawTutorial(editor);
	eleventh->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	eleventh->Add(detail);
	this->main->Add(eleventh);

	//PASS
	Tutorial *tenth = new SeveralTutorial(6);
	detail = new MoveTutorial(editor);
	tenth->Add(detail);
	detail = new ReSizeTutorial(editor);
	tenth->Add(detail);
	detail = new EditContentsTutorial(editor);
	tenth->Add(detail);
	detail = new DrawTutorial(editor);
	tenth->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	tenth->Add(detail);
	this->main->Add(tenth);

	//Sequence, Position, Interval
	Tutorial *ninth = new SeveralTutorial(5);
	detail = new SequenceMakeTutorial(editor);
	ninth->Add(detail);
	detail = new IntervalTutorial(editor);
	ninth->Add(detail);
	detail = new PositionTutorial(editor);
	ninth->Add(detail);
	detail = new ContextMenuTutorial(editor);
	ninth->Add(detail);
	detail = new GroupTutorial(editor);
	ninth->Add(detail);
	this->main->Add(ninth);

	//PASSINGAVERAGE
	Tutorial *eighth = new SeveralTutorial(6);
	detail = new MoveTutorial(editor);
	eighth->Add(detail);
	detail = new ReSizeTutorial(editor);
	eighth->Add(detail);
	detail = new EditContentsTutorial(editor);
	eighth->Add(detail);
	detail = new DrawTutorial(editor);
	eighth->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	eighth->Add(detail);
	this->main->Add(eighth);

	//average
	Tutorial *seventh = new SeveralTutorial(6);
	detail = new MoveTutorial(editor);
	seventh->Add(detail);
	detail = new ReSizeTutorial(editor);
	seventh->Add(detail);
	detail = new EditContentsTutorial(editor);
	seventh->Add(detail);
	detail = new DrawTutorial(editor);
	seventh->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	seventh->Add(detail);
	this->main->Add(seventh);

	//sum
	Tutorial *sixth = new SeveralTutorial(6);
	detail = new MoveTutorial(editor);
	sixth->Add(detail);
	detail = new ReSizeTutorial(editor);
	sixth->Add(detail);
	detail = new EditContentsTutorial(editor);
	sixth->Add(detail);
	detail = new DrawTutorial(editor);
	sixth->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	sixth->Add(detail);
	this->main->Add(sixth);

	//number++
	Tutorial *fifth = new SeveralTutorial(6);
	detail = new MoveTutorial(editor);
	fifth->Add(detail);
	detail = new ReSizeTutorial(editor);
	fifth->Add(detail);
	detail = new EditContentsTutorial(editor);
	fifth->Add(detail);
	detail = new DrawTutorial(editor);
	fifth->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	fifth->Add(detail);
	this->main->Add(fifth);

	//NOT EOF
	Tutorial *fourth = new SeveralTutorial(6);
	detail = new MoveTutorial(editor);
	fourth->Add(detail);
	detail = new ReSizeTutorial(editor);
	fourth->Add(detail);
	detail = new EditContentsTutorial(editor);
	fourth->Add(detail);
	detail = new DrawTutorial(editor);
	fourth->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	fourth->Add(detail);
	this->main->Add(fourth);

	//READ
	Tutorial *third = new SeveralTutorial(6);
	detail = new MoveTutorial(editor);
	third->Add(detail);
	detail = new ReSizeTutorial(editor);
	third->Add(detail);
	detail = new EditContentsTutorial(editor);
	third->Add(detail);
	detail = new DrawTutorial(editor);
	third->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	third->Add(detail);
	this->main->Add(third);

	//Preparation
	Tutorial *second = new SeveralTutorial(6);
	detail = new MoveTutorial(editor);
	second->Add(detail);
	detail = new ReSizeTutorial(editor);
	second->Add(detail);
	detail = new EditContentsTutorial(editor);
	second->Add(detail);
	detail = new DrawTutorial(editor);
	second->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	second->Add(detail);
	this->main->Add(second);

	//START
	Tutorial *first = new SeveralTutorial(5);
	detail = new MoveTutorial(editor);
	first->Add(detail);
	detail = new ReSizeTutorial(editor);
	first->Add(detail);
	detail = new DrawTutorial(editor);
	first->Add(detail);
	detail = new SymbolSelectTutorial(editor);
	first->Add(detail);
	this->main->Add(first);

	//미리 그리기
	editor->GetWindowRect(&rect);
	this->MoveWindow(1230, 70, 660, 940, TRUE);
	this->GetWindowRect(&rect);

	Zoom zoom(40);
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(&zoom);


	this->sample->Accept(zoomVisitor);
	Shape *shape;
	Long i = 0;
	while (i < dynamic_cast<FlowChart*>(this->sample)->GetLength()) {
		shape = dynamic_cast<FlowChart*>(this->sample)->GetAt(i);
		shape->Move(shape->GetX() - 181, shape->GetY() - 246);
		i++;
	}

	if (zoomVisitor != NULL) {
		delete zoomVisitor;
	}

	if (this->current != NULL) {
		delete this->current;
	}
	TutorialMarkFactory factory(this->sample);
	this->current = factory.Make(this->main->GetLength());

	this->main->Execute();
	if (this->lastConcrete != NULL) {
		delete this->lastConcrete;
	}
	this->lastConcrete = this->main->Top()->TakeOut();
	this->Invalidate();

	this->tutorialController = new TutorialController(this);

	return 0;
}

void TutorialForm::OnClose() {
	if (this->lists != NULL) {
		delete this->lists;
	}
	if (this->painter != NULL) {
		delete this->painter;
	}
	if (this->font != NULL) {
		delete this->font;
	}
	if (this->main != NULL) {
		delete this->main;
	}
	if (dynamic_cast<FlowChartEditor*>(this->GetParent())->toolTip != NULL) {
		dynamic_cast<FlowChartEditor*>(this->GetParent())->toolTip->Destroy();
		dynamic_cast<FlowChartEditor*>(this->GetParent())->toolTip = NULL;
	}
	if (this->lastConcrete != NULL) {
		delete this->lastConcrete;
	}
	if (this->tutorialController != NULL) {
		delete this->tutorialController;
	}
	if (dynamic_cast<FlowChartEditor*>(this->GetParent())->windows[2] != NULL) {
		dynamic_cast<FlowChartEditor*>(this->GetParent())->windows[2] = NULL;
	}


	CFrameWnd::OnClose();
}

void TutorialForm::OnPaint() {
	CPaintDC dc(this);
	CRect rect;
	this->GetWindowRect(rect);
	this->painter->Resize(this, RGB(0, 0, 0));

	FlowChartEditor *editor = (FlowChartEditor*)this->GetParent();

	LOGFONT logFont = editor->font->GetFont();
	logFont.lfHeight = -18;
	COLORREF color = RGB(0, 0, 0);
	if (this->font != NULL) {
		delete this->font;
	}
	this->font = new FlowChartFont(editor, logFont, color);
	HFONT hFont = this->font->Create();
	this->painter->ChangeFont(hFont, this->font->GetColor());
	this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(102, 102, 102));

	FlowChartVisitor *drawVisitor = new DrawVisitor(this->painter);
	this->sample->Accept(drawVisitor);

	if (this->current != NULL) {
		this->current->Accept(drawVisitor);
	}

	logFont = editor->font->GetFont();
	logFont.lfHeight = -30;
	color = RGB(255, 255, 255);
	if (this->font != NULL) {
		delete this->font;
	}
	this->font = new FlowChartFont(editor, logFont, color);
	hFont = this->font->Create();
	this->painter->ChangeFont(hFont, this->font->GetColor());

	dynamic_cast<TextRegion*>(this->lists->GetAt(0))->Draw(this->painter);

	this->painter->Render(&dc, 0, 0, rect.Width(), rect.Height());

	if (drawVisitor != NULL) {
		delete drawVisitor;
	}
}

void TutorialForm::OnLButtonUp(UINT nFlags, CPoint point) {
	CDC *dc = this->GetDC();
	Long selectedIndex = this->lists->Find(dc, point);
	FlowChartEditor *editor = (FlowChartEditor*)this->GetParent();

	if (selectedIndex != -1) {
		TextRegion *textRegion = (TextRegion*)this->lists->GetAt(selectedIndex);
		if (textRegion->GetContents() == "종료") {
			if (editor->toolTip != NULL) {
				editor->toolTip->Destroy();
			}
			this->OnClose();
		}
	}
}

BOOL TutorialForm::OnEraseBkgnd(CDC *pDC) {
	return FALSE;
}

void TutorialForm::OnKillFocus(CWnd* pNewWnd) {
	CRect rect;
	this->GetWindowRect(rect);
	Long width = 40;

	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->GetParent());
	DrawingPaper *canvas = static_cast<DrawingPaper*>(editor->windows[0]);
	if (canvas->label == NULL) {
		this->MoveWindow(rect.right - width, rect.top, width, width, TRUE);
	}
}

void TutorialForm::OnSetFocus(CWnd* pOldWnd) {
	this->MoveWindow(1230, 70, 660, 940, TRUE);
}