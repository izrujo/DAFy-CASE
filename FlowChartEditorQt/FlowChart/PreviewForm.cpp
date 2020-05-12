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
#include "../GObject/QtPainter.h"
#include "../GObject/QtGObjectFactory.h"

#include <qpainter.h>
#include <qtoolbar.h>
#include <qdebug.h>
#include <QtPrintSupport/qprintdialog.h>
#include <QtPrintSupport/qprinter.h>

PreviewForm::PreviewForm(QWidget *parent, NShape *flowChart)
	: QFrame() {
	ui.setupUi(this);

	this->editor = static_cast<FlowChartEditor *>(parent);

	this->setWindowTitle(QString::fromLocal8Bit("인쇄 미리 보기"));

	this->flowChart = flowChart;
	Long length = this->flowChart->GetLength();

	QRect rect = this->frameRect();
	this->painter = new QtPainter(rect.width(), rect.height());

	Zoom zoom;
	zoom.Set(100);
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(&zoom);

	DrawingPaper *canvas = static_cast<DrawingPaper *>(this->editor->windows[0]);
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

	Zoom zoom;
	zoom.Set(30);

	//this->painter->Resize(this);
	//POINT points[5] = { {rect.left, rect.top}, {rect.right, rect.top}, {rect.right, rect.bottom}, {rect.left, rect.bottom}, {rect.left, rect.top} };
	//this->painter->FillBackground(points, 5, RGB(235, 235, 235));
	//this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(0, 0, 0));

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(0, 0, 0)), 2);
	GObject *oldPen = this->painter->SelectObject(*pen);

	//폰트 설정
	DrawingPaper *canvas = static_cast<DrawingPaper *>(this->editor->windows[0]);
	GObject *font = canvas->painter->CurrentObject("Font")->Clone();
	int size = font->GetPointSize() * zoom.GetRate() / 100;
	dynamic_cast<QFont *>(font)->setPointSize(size);
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
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(&zoom);

	NShape *cloneA4 = this->a4Paper->Clone();
	cloneA4->Accept(zoomVisitor);
	cloneA4->Move(cloneA4->GetX() - 670, cloneA4->GetY() - 1347);
	dynamic_cast<A4Paper *>(cloneA4)->SetIsMarking(false);
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

void PreviewForm::CreateToolBar() {
	this->toolBar = new QToolBar(this);

	this->print = this->toolBar->addAction("Print");
	connect(this->print, &QAction::triggered, this, [=]() { this->CommandRange("Print"); });
	this->exit = this->toolBar->addAction("Exit");
	connect(this->exit, &QAction::triggered, this, &QFrame::close);
}

/* 이거는 인쇄시 좌표 찾기 위해 임시 구현한 부분
void PreviewForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CString message;
	message.Format("%d, %d", point.x, point.y);
	AfxMessageBox(message);
}
*/

void PreviewForm::CommandRange(string text) {
	if (text == "Print") {
		QPrinter printer;

		QPrintDialog printDialog(&printer);

		int ret = printDialog.exec();
		if (ret == QDialog::Accepted) {
			Zoom zoom(72);
			FlowChartVisitor *zoomVisitor = new ZoomVisitor(&zoom);
			NShape *cloneA4 = this->a4Paper->Clone();
			cloneA4->Accept(zoomVisitor);
			
			printer.setPageMargins(dynamic_cast<A4Paper*>(cloneA4)->GetLeftMargin(), 
				dynamic_cast<A4Paper*>(cloneA4)->GetTopMargin(),
				dynamic_cast<A4Paper*>(cloneA4)->GetRightMargin(),
				dynamic_cast<A4Paper *>(cloneA4)->GetBottomMargin(), QPrinter::DevicePixel);
			
			NShape *cloneFlowChart = this->flowChart->Clone();
			cloneFlowChart->Accept(zoomVisitor);

			// actually do some printing
			GObject *printPainter = new QtPainter(cloneA4->GetWidth(), cloneA4->GetHeight());
			//폰트 설정
			DrawingPaper *canvas = static_cast<DrawingPaper *>(this->editor->windows[0]);
			GObject *font = canvas->painter->CurrentObject("Font")->Clone();
			int size = font->GetPointSize() * zoom.GetRate() / 100;
			dynamic_cast<QFont *>(font)->setPointSize(size);
			GObject *pen = canvas->painter->CurrentObject("Pen")->Clone();
			printPainter->SelectObject(*font);
			printPainter->SelectObject(*pen);
			printPainter->Update();

			NShape *shape;
			Long i = 0;
			while (i < dynamic_cast<FlowChart *>(cloneFlowChart)->GetLength()) {
				shape = dynamic_cast<FlowChart *>(cloneFlowChart)->GetAt(i);
				//가로는 6mm, 세로는 5mm 빼주기.
				shape->Move(shape->GetX() - this->a4Paper->GetX() - 265, shape->GetY() - this->a4Paper->GetY() - 355);
				i++;
			}

			FlowChartVisitor *drawVisitor = new DrawVisitor(printPainter);
			cloneFlowChart->Accept(drawVisitor);
			printPainter->Render(&QPainter(&printer), 0, 0);

			if (cloneA4 != NULL) {
				delete cloneA4;
			}
			if (cloneFlowChart != NULL) {
				delete cloneFlowChart;
			}
			if (zoomVisitor != NULL) {
				delete zoomVisitor;
			}
			if (drawVisitor != NULL) {
				delete drawVisitor;
			}
			if (printPainter != 0) {
				delete printPainter;
			}
		}
	}
}
