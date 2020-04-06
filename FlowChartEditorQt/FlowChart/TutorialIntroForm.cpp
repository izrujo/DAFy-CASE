#include "TutorialIntroForm.h"
#include "TextRegion.h"
#include "../FlowChartEditor.h"
#include "GObject.h"
#include "TutorialForm.h"
#include "DrawingPaper.h"
#include "Zoom.h"
#include "StatusBar.h"
#include "QtPainter.h"
#include "QtGObjectFactory.h"

#include <qpainter.h>

TutorialIntroForm::TutorialIntroForm(QWidget *parent) {
	this->message = NULL;
	this->painter = NULL;
	this->guide = NULL;

	//int ret = ::SetLayeredWindowAttributes(this->m_hWnd, RGB(0, 0, 0), 90, LWA_ALPHA);
	//this->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);

	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->parentWidget());
	DrawingPaper *canvas = static_cast<DrawingPaper*>(editor->windows[0]);
	QRect rect = editor->frameRect();
	this->painter = new QtPainter(rect.width(), rect.height());

	this->message = new TextRegion(600, 400, 1200, 100, QColor(255, 255, 255), Qt::SolidLine, QColor(52, 52, 52), String("똑같이 따라해서 만드세요."));
	this->guide = new TextRegion(780, 550, 600, 100, QColor(235, 235, 235), Qt::SolidLine, QColor(52, 52, 52), String("Press any key to start..."));

	QtGObjectFactory factory;
	GObject *originFont = canvas->painter->CurrentObject("Font");

	GObject *font = factory.MakeFont(originFont->GetFamily(), 72, 70, false);
	this->painter->SelectObject(*font);
	GObject *pen = factory.MakePen(QBrush(this->message->GetBackGroundColor()), 1); 
	//Qt에서는 글씨 색깔이 QPen의 색으로 결정? 이렇게 하면 되는지 확인 필요
	this->painter->SelectObject(*pen);
	this->painter->Update();

	this->message->Draw(this->painter);

	GObject *font = factory.MakeFont(originFont->GetFamily(), 40, 70, false);
	this->painter->SelectObject(*font);
	GObject *pen = factory.MakePen(QBrush(this->guide->GetBackGroundColor()), 1); 
	this->painter->SelectObject(*pen);
	this->painter->Update();

	this->guide->Draw(this->painter);
}

void TutorialIntroForm::closeEvent(QCloseEvent *event) {
	if (this->message != NULL) {
		delete this->message;
	}
	if (this->painter != NULL) {
		delete this->painter;
	}
	if (this->guide != NULL) {
		delete this->guide;
	}
}

void TutorialIntroForm::paintEvent(QPaintEvent *event) {
	QPainter dc(this);

	this->painter->Render(&dc, 0, 0);
}

/*
BOOL TutorialIntroForm::OnEraseBkgnd(CDC *pDC) {
	return FALSE;
}
*/

void TutorialIntroForm::mouseReleaseEvent(QMouseEvent *event) {
	//아무 데나 누르면 따라해봅시다 이 창 없어지고 튜토리얼을 진행하는 걸로 가자.
	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->parentWidget());
	QRect rect = editor->frameRect();

	TutorialForm *tutorialForm = new TutorialForm(editor);
	editor->windows.Modify(2, tutorialForm);
	//tutorialForm->Create(NULL, NULL, WS_POPUP | WS_VISIBLE | WS_CHILD,
		//CRect(rect.left, rect.top, rect.Width(), rect.Height()), editor, NULL, WS_EX_LAYERED | WS_EX_CLIENTEDGE, NULL);
	tutorialForm->setWindowState(tutorialForm->windowState() ^ Qt::WindowFullScreen);
	tutorialForm->show();
	/*
	Long rate = 100;
	dynamic_cast<DrawingPaper*>(editor->windows[0])->zoom->Set(rate);
	CString rateStatus;
	rateStatus.Format("%d", rate);
	rateStatus += "%";
	editor->statusBar->Modify(4, String((LPCTSTR)rateStatus));

	dynamic_cast<DrawingPaper*>(editor->windows[0])->Invalidate();
	*/


	this->close();
}

void TutorialIntroForm::keyPressEvent(QKeyEvent *event) {
	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->parentWidget());
	QRect rect = editor->frameRect();

	TutorialForm *tutorialForm = new TutorialForm(editor);
	editor->windows.Modify(2, tutorialForm);
	//tutorialForm->Create(NULL, NULL, WS_POPUP | WS_VISIBLE | WS_CHILD,
		//CRect(rect.left, rect.top, rect.Width(), rect.Height()), editor, NULL, WS_EX_LAYERED | WS_EX_CLIENTEDGE, NULL);
	tutorialForm->setWindowState(tutorialForm->windowState() ^ Qt::WindowFullScreen);
	tutorialForm->show();
	/*
	Long rate = 100;
	dynamic_cast<DrawingPaper*>(editor->windows[0])->zoom->Set(rate);
	CString rateStatus;
	rateStatus.Format("%d", rate);
	rateStatus += "%";
	editor->statusBar->Modify(4, String((LPCTSTR)rateStatus));

	dynamic_cast<DrawingPaper*>(editor->windows[0])->Invalidate();
	*/

	this->close();
}
