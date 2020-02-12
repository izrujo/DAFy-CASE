#include "TutorialIntroForm.h"
#include "TextRegion.h"
#include "FlowChartEditor.h"
#include "Painter.h"
#include "FlowChartFont.h"
#include "TutorialForm.h"
#include "DrawingPaper.h"
#include "Zoom.h"
#include "StatusBar.h"

BEGIN_MESSAGE_MAP(TutorialIntroForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_CHAR()
END_MESSAGE_MAP()

TutorialIntroForm::TutorialIntroForm() {
	this->message = NULL;
	this->painter = NULL;
	this->font = NULL;
	this->guide = NULL;
}

void TutorialIntroForm::OnClose() {
	if (this->message != NULL) {
		delete this->message;
	}
	if (this->painter != NULL) {
		delete this->painter;
	}
	if (this->font != NULL) {
		delete this->font;
	}
	if (this->guide != NULL) {
		delete this->guide;
	}

	CFrameWnd::OnClose();
}

int TutorialIntroForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	int ret = ::SetLayeredWindowAttributes(this->m_hWnd, RGB(0, 0, 0), 90, LWA_ALPHA);
	this->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);

	CRect rect;
	FlowChartEditor *editor = (FlowChartEditor*)this->GetParent();
	editor->GetWindowRect(rect);
	this->painter = new Painter(this->GetDC(), rect.Width(), rect.Height(), RGB(0, 0, 0), TRANSPARENT);

	this->message = new TextRegion(600, 400, 1200, 100, RGB(255,255,255), DOT, RGB(52, 52, 52), String("똑같이 따라해서 만드세요."));
	this->guide = new TextRegion(780, 550, 600, 100, RGB(235, 235, 235), DOT, RGB(52, 52, 52), String("Press any key to start..."));

	LOGFONT logFont = editor->font->GetFont();
	logFont.lfHeight = -72;
	this->font = new FlowChartFont(editor, logFont, this->message->GetBackGroundColor());
	HFONT hFont = this->font->Create();
	this->painter->ChangeFont(hFont, this->font->GetColor());logFont.lfHeight = -72;
	this->message->Draw(this->painter);

	logFont.lfHeight = -40;
	this->font = new FlowChartFont(editor, logFont, this->guide->GetBackGroundColor());
	hFont = this->font->Create();
	this->painter->ChangeFont(hFont, this->font->GetColor());
	this->guide->Draw(this->painter);

	return 0;
}

void TutorialIntroForm::OnPaint() {
	CPaintDC dc(this);
	CRect rect;
	this->GetWindowRect(rect);

	FlowChartEditor *editor = (FlowChartEditor*)this->GetParent();

	this->painter->Render(&dc, 0, 0, rect.Width(), rect.Height());
}


BOOL TutorialIntroForm::OnEraseBkgnd(CDC *pDC) {
	return FALSE;
}

void TutorialIntroForm::OnLButtonUp(UINT nFlags, CPoint point) {
	//아무 데나 누르면 따라해봅시다 이 창 없어지고 튜토리얼을 진행하는 걸로 가자.
	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->GetParent());
	CRect rect;
	editor->GetWindowRect(&rect);

	TutorialForm *tutorialForm = new TutorialForm;
	editor->windows.Modify(2, tutorialForm);
	tutorialForm->Create(NULL, NULL, WS_POPUP | WS_VISIBLE | WS_CHILD,
		CRect(rect.left, rect.top, rect.Width(), rect.Height()), editor, NULL, WS_EX_LAYERED | WS_EX_CLIENTEDGE, NULL);

	Long rate = 100;
	dynamic_cast<DrawingPaper*>(editor->windows[0])->zoom->Set(rate);
	CString rateStatus;
	rateStatus.Format("%d", rate);
	rateStatus += "%";
	editor->statusBar->Modify(4, String((LPCTSTR)rateStatus));

	dynamic_cast<DrawingPaper*>(editor->windows[0])->Invalidate();


	this->OnClose();
}

void TutorialIntroForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->GetParent());
	CRect rect;
	editor->GetWindowRect(&rect);

	TutorialForm *tutorialForm = new TutorialForm;
	editor->windows.Modify(2, tutorialForm);
	tutorialForm->Create(NULL, NULL, WS_POPUP | WS_VISIBLE | WS_CHILD,
		CRect(rect.left, rect.top, rect.Width(), rect.Height()), editor, NULL, WS_EX_LAYERED | WS_EX_CLIENTEDGE, NULL);

	Long rate = 100;
	dynamic_cast<DrawingPaper*>(editor->windows[0])->zoom->Set(rate);
	CString rateStatus;
	rateStatus.Format("%d", rate);
	rateStatus += "%";
	editor->statusBar->Modify(4, String((LPCTSTR)rateStatus));

	dynamic_cast<DrawingPaper*>(editor->windows[0])->Invalidate();

	this->OnClose();
}