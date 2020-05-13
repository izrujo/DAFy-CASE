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

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(0, 0, 0)), 2);
	GObject *oldPen = this->painter->SelectObject(*pen);

	//폰트 설정
	DrawingPaper *canvas = static_cast<DrawingPaper *>(this->editor->windows[0]);
	GObject *font = canvas->painter->CurrentObject("Font")->Clone();
	int size = font->GetPointSize() * zoom.GetRate() / 100;
	dynamic_cast<QFont *>(font)->setPointSize(size);
	GObject *oldFont = this->painter->SelectObject(*font);
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
	Long width = this->width();
	Long height= this->toolBar->height() * 2;
	this->toolBar->resize(width, height);
	
	float size = height / 16.0F;

	QColor color(255, 255, 255);
	color.setAlpha(0);

	QPixmap pixmap1(height, height);
	pixmap1.fill(color);
	QPainter painter1(&pixmap1);

	painter1.setPen(QColor(0, 0, 0));
	painter1.setBrush(QBrush(QColor(255, 255, 255)));
	painter1.drawRect(QRectF((qreal)size * 4, (qreal)size * 2, (qreal)size * 8, (qreal)size * 4));
	
	painter1.setBrush(QBrush(QColor(0, 0, 0)));
	QPointF points1[8];
	points1[0] = QPointF((qreal)size * 2, (qreal)size * 6);
	points1[1] = QPointF((qreal)size * 14, (qreal)size * 6);
	points1[2] = QPointF((qreal)size * 14, (qreal)size * 10);
	points1[3] = QPointF((qreal)size * 12, (qreal)size * 10);
	points1[4] = QPointF((qreal)size * 12, (qreal)size * 8);
	points1[5] = QPointF((qreal)size * 4, (qreal)size * 8);
	points1[6] = QPointF((qreal)size * 4, (qreal)size * 10);
	points1[7] = QPointF((qreal)size * 2, (qreal)size * 10);
	painter1.drawPolygon(points1, 8);

	painter1.setBrush(QBrush(QColor(255, 255, 255)));
	painter1.drawRect(QRectF((qreal)size * 4, (qreal)size * 8, (qreal)size * 8, (qreal)size * 6));

	QPointF points2[6];
	points2[0] = QPointF((qreal)size * 5, (qreal)size * 9);
	points2[1] = QPointF((qreal)size * 10, (qreal)size * 9);
	points2[2] = QPointF((qreal)size * 5, (qreal)size * 11);
	points2[3] = QPointF((qreal)size * 8, (qreal)size * 11);
	points2[4] = QPointF((qreal)size * 5, (qreal)size * 13);
	points2[5] = QPointF((qreal)size * 6, (qreal)size * 13);
	painter1.drawLines(points2, 6);

	QIcon printIcon(pixmap1);
	this->print = this->toolBar->addAction(printIcon, "Print");
	connect(this->print, &QAction::triggered, this, [=]() { this->CommandRange("Print"); });

	QPixmap pixmap2(height, height);
	pixmap2.fill(color);
	QPainter painter2(&pixmap2);

	painter2.setPen(QColor(0, 0, 0));
	QPointF points3[10];
	points3[0] = QPointF((qreal)size * 12, (qreal)size * 5);
	points3[1] = QPointF((qreal)size * 12, (qreal)size * 2);
	points3[2] = QPointF((qreal)size * 12, (qreal)size * 2);
	points3[3] = QPointF((qreal)size * 4, (qreal)size * 2);
	points3[4] = QPointF((qreal)size * 4, (qreal)size * 2);
	points3[5] = QPointF((qreal)size * 4, (qreal)size * 14);
	points3[6] = QPointF((qreal)size * 4, (qreal)size * 14);
	points3[7] = QPointF((qreal)size * 12, (qreal)size * 14);
	points3[8] = QPointF((qreal)size * 12, (qreal)size * 14);
	points3[9] = QPointF((qreal)size * 12, (qreal)size * 11);
	painter2.drawLines(points3, 10);

	painter2.setBrush(QBrush(QColor(0, 0, 0)));
	QVector<QPointF> points4;
	points4.append(QPointF((qreal)size * 6, (qreal)size * 7));
	points4.append(QPointF((qreal)size * 10, (qreal)size * 7));
	points4.append(QPointF((qreal)size * 10, (qreal)size * 5));
	points4.append(QPointF((qreal)size * 13, (qreal)size * 8));
	points4.append(QPointF((qreal)size * 10, (qreal)size * 11));
	points4.append(QPointF((qreal)size * 10, (qreal)size * 9));
	points4.append(QPointF((qreal)size * 6, (qreal)size * 9));
	points4.append(QPointF((qreal)size * 6, (qreal)size * 7));
	QPolygonF polygon(points4);
	QPainterPath path;
	path.addPolygon(polygon);
	painter2.fillPath(path, QBrush(QColor(0, 0, 0)));

	QIcon exitIcon(pixmap2);
	this->exit = this->toolBar->addAction(exitIcon, "Exit");
	connect(this->exit, &QAction::triggered, this, &QFrame::close);
}

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
