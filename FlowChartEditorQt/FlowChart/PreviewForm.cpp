#include "PreviewForm.h"
#include "FlowChartVisitor.h"
#include "ZoomVisitor.h"
#include "Zoom.h"
#include "drawVisitor.h"
#include "../GObject/Painter.h"
#include "../FlowChartEditor.h"
#include "FlowChart.h"
#include "DrawingPaper.h"
#include "RightDownJoin.h"
#include "RepeatTrue.h"
#include "RepeatFalse.h"
#include "Join.h"
#include "A4Paper.h"
#include "ResolutionVisitor.h"
#include "../GObject/QtPainter.h"
#include "../GObject/QtGObjectFactory.h"

#include <qpainter.h>
#include <qtoolbar.h>
#include <qdebug.h>

PreviewForm::PreviewForm(QWidget *parent, NShape *flowChart) 
	: QFrame() {
	ui.setupUi(this);

	this->editor = static_cast<FlowChartEditor*>(parent);

	this->setWindowTitle(QString::fromLocal8Bit("인쇄 미리 보기"));

	this->flowChart = flowChart;
	Long length = this->flowChart->GetLength();

	QRect rect = this->frameRect();
	this->painter = new QtPainter(rect.width(), rect.height());

	Zoom zoom;
	zoom.Set(300);
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(&zoom);

	DrawingPaper *canvas = static_cast<DrawingPaper*>(this->editor->windows[0]);
	this->a4Paper = canvas->a4Paper->Clone();

	this->a4Paper->Accept(zoomVisitor);
	this->flowChart->Accept(zoomVisitor);

	this->toolBar = NULL;

	this->CreateToolBar();
}

void PreviewForm::closeEvent(QCloseEvent *event) {
	if (this->flowChart != NULL) {
		delete this->flowChart;
	}

	if (this->painter != NULL) {
		delete this->painter;
		this->painter = NULL;
	}

	if (this->a4Paper != NULL) {
		delete this->a4Paper;
	}

	if (this->toolBar != NULL) {
		delete this->toolBar;
	}
}

void PreviewForm::paintEvent(QPaintEvent *event) {
	QPainter dc(this);
	QRect rect = this->frameRect();

	this->flowChart->UnSelectAll();
	
	//this->painter->Resize(this);
	//POINT points[5] = { {rect.left, rect.top}, {rect.right, rect.top}, {rect.right, rect.bottom}, {rect.left, rect.bottom}, {rect.left, rect.top} };
	//this->painter->FillBackground(points, 5, RGB(235, 235, 235));
	//this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(0, 0, 0));

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(0, 0, 0)), 2);
	GObject *oldPen = this->painter->SelectObject(*pen);

	//폰트 설정
	GObject *font = factory.MakeFont("Terminal", 6, 40, false);
	GObject *oldFont = this->painter->SelectObject(*font);
	//LOGFONT logFont = this->editor->font->GetFont();
	//logFont.lfHeight = -6;
	//logFont.lfWidth = -6;
	//strcpy(logFont.lfFaceName, _T("Terminal"));
	//COLORREF color = this->editor->font->GetColor();
	//this->font = new FlowChartFont(this->editor, logFont, color);
	//HFONT hFont = this->font->Create();
	//this->painter->ChangeFont(hFont, this->font->GetColor());
	
	this->painter->Update();

	//Visitor 패턴 적용	
	FlowChartVisitor *drawVisitor = new DrawVisitor(this->painter);
	Zoom zoom;
	zoom.Set(10);
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(&zoom);

	NShape *cloneA4 = this->a4Paper->Clone();
	cloneA4->Accept(zoomVisitor);
	cloneA4->Move(cloneA4->GetX() - 670, cloneA4->GetY() - 1347);
	dynamic_cast<A4Paper*>(cloneA4)->SetIsMarking(false);
	cloneA4->Accept(drawVisitor);

	NShape *cloneFlowChart = this->flowChart->Clone();
	cloneFlowChart->Accept(zoomVisitor);

	NShape *shape;
	Long i = 0;
	while (i < cloneFlowChart->GetLength()) {
		shape = cloneFlowChart->GetAt(i);
		shape->Move(shape->GetX() - 670, shape->GetY() - 1347);
		i++;
	}
	cloneFlowChart->Accept(drawVisitor);

	this->painter->Render(&dc, 0, 0);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldFont);
	this->painter->Update();

	if (pen != NULL) {
		delete pen;
	}
	if (font != NULL) {
		delete font;
	}

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
}

void PreviewForm::CommandRange(string text) {
	if (text == "Print") {

	}
	else if (text == "Exit") {

	}
	qDebug() << QString::fromLocal8Bit(text.c_str());
}

void PreviewForm::CreateToolBar() {
	this->toolBar = new QToolBar(this);

	this->print = this->toolBar->addAction("Print");
	connect(this->print, &QAction::triggered, this, [=]() { this->CommandRange("Print"); });
	this->exit = this->toolBar->addAction("Exit");
	connect(this->exit, &QAction::triggered, this, [=]() { this->CommandRange("Exit"); });
}

/* 이거는 인쇄시 좌표 찾기 위해 임시 구현한 부분
void PreviewForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CString message;
	message.Format("%d, %d", point.x, point.y);
	AfxMessageBox(message);
}
*/

/*
void PreviewForm::OnCommandRange(UINT uID) {
	if (uID == IDT_BUTTON_PRINT) {
		CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS | PD_HIDEPRINTTOFILE | PD_NOSELECTION,
			this);

		int ret = printDialog.DoModal();
		if (ret == IDOK) {
			HDC hdcPrinter = printDialog.GetPrinterDC();
			if (hdcPrinter == NULL) {
				MessageBox(_T("Buy a printer!"));
			}
			else {
				CDC printerDC;
				printerDC.Attach(hdcPrinter);
				// if it fails, complain and exit gracefully
				if (printerDC.StartDocA(this->editor->fileOpenPath) < 0) {
					AfxMessageBox(_T("Printer wouldn't initialize"));
				}
				else {
					// start a page
					if (printerDC.StartPage() < 0) {
						AfxMessageBox(_T("Could not start page"));
						printerDC.AbortDoc();
					}
					else {
						// actually do some printing
						Painter printPainter(&printerDC, this->a4Paper->GetWidth(), this->a4Paper->GetHeight(), RGB(255, 255, 255), TRANSPARENT);
						//폰트 설정
						LOGFONT logFont = this->editor->font->GetFont();
						logFont.lfHeight *= 3;
						COLORREF color = this->editor->font->GetColor();
						this->font = new FlowChartFont(this->editor, logFont, color);
						HFONT hFont = this->font->Create();
						printPainter.ChangeFont(hFont, this->font->GetColor());

						Shape *cloneFlowChart = this->flowChart->Clone();
						Shape *shape;
						Long i = 0;
						while (i < dynamic_cast<FlowChart*>(cloneFlowChart)->GetLength()) {
							shape = dynamic_cast<FlowChart*>(cloneFlowChart)->GetAt(i);
							//가로는 6mm, 세로는 5mm 빼주기.
							shape->Move(shape->GetX() - this->a4Paper->GetX()-142, shape->GetY() - this->a4Paper->GetY()-118);
							i++;
						}

						FlowChartVisitor *drawVisitor = new DrawVisitor(&printPainter);
						cloneFlowChart->Accept(drawVisitor);
						printPainter.Render(&printerDC, 0, 0, this->a4Paper->GetWidth(), this->a4Paper->GetHeight());
						if (drawVisitor != NULL) {
							delete drawVisitor;
						}

						int result = printerDC.EndPage();
						result = printerDC.EndDoc();
					}
				}
			}
			CDC::FromHandle(hdcPrinter)->DeleteDC();
		}
	}
	else if (uID == IDT_BUTTON_EXIT) {
		this->OnClose();
	}
}
*/