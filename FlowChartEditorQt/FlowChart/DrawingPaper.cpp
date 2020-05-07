#include "DrawingPaper.h"
#include "../FlowChartEditor.h"
#include "FlowChart.h"
#include "Clipboard.h"
#include "MemoryController.h"
#include "Zoom.h"
#include "A4Paper.h"
#include "../GObject/QtPainter.h"
#include "DrawingTool.h"
#include "MovingTool.h"
#include "ResizingTool.h"
#include "SelectingTool.h"
#include "DrawVisitor.h"
#include "ZoomVisitor.h"
#include "Label.h"
#include "Preparation.h"
#include "ToolFactory.h"
#include "../Notepad/Note.h"
#include "FlowChartTemplate.h"
#include "ScrollController.h"
#include "Scroll.h"
#include "../GObject/QtGObjectFactory.h"
#include "../GObject/GObject.h"
#include "FlowChartKeyActionFactory.h"
#include "FlowChartKeyActions.h"
#include "CoordinateConverter.h"
#include "Decision.h"
#include "File.h"
#include "WindowTitle.h"
#include "SketchBook.h"
#include "Memory.h"
#include "VariableList.h"
#include "Line.h"

#include <qscrollbar.h>
#include <qpainter.h>
#include <qevent.h>
#include <qmenu.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qlabel.h>
#include <qstatusbar.h>

DrawingPaper::DrawingPaper(QWidget *parent)
	: QFrame(parent) {

	this->setFocusPolicy(Qt::WheelFocus);

	this->setContextMenuPolicy(Qt::CustomContextMenu);

	this->windowBorderColor = QColor(102, 204, 204);

	this->templateSelected = NULL;

	this->flowChart = NULL;

	this->label = NULL;
	this->painter = NULL;

	this->startX = 0.0F;
	this->startY = 0.0F;

	this->currentX = 0.0F;
	this->currentY = 0.0F;

	this->tool = NULL;

	this->mode = IDLE;
	this->indexOfSelected = -1;

	this->hitCode = -1;

	this->clipboard = NULL;

	this->scrollController = NULL;

	this->memoryController = NULL;


	this->zoom = NULL;

	this->popup = NULL;

	this->drawSelectingAreaFlag = false;

	QRect frameRect = this->frameRect();

	this->flowChart = new FlowChart;

	this->painter = new QtPainter(frameRect.width(), frameRect.height()); //트리플 버퍼링 유지하자.

	this->clipboard = new Clipboard;

	this->memoryController = new MemoryController(this);

	this->zoom = new Zoom(100);

	this->a4Paper = new A4Paper(444, 615, 1653, 2338);
	this->zoom->Set(40);

	this->variableList = new VariableList;

	connect(this, &QWidget::customContextMenuRequested, this, &DrawingPaper::OnContextMenu);

	this->setFocus();
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

	if (this->zoom != NULL) {
		delete this->zoom;
	}

	if (this->a4Paper != NULL) {
		delete this->a4Paper;
	}
	if (this->popup != NULL) {
		delete this->popup;
		this->popup = NULL;
	}

	if (this->variableList != NULL) {
		delete this->variableList;
	}
}

void DrawingPaper::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	QRect rect = this->frameRect();

	FlowChartEditor *editor = (FlowChartEditor*)this->parent();

	this->painter->Resize(rect.width(), rect.height(), QColor(250, 250, 250));

	//Visitor 패턴 적용	
	FlowChartVisitor *drawVisitor = new DrawVisitor(this->painter, this->scrollController);
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(this->zoom);
	NShape *cloneA4 = this->a4Paper->Clone();
	cloneA4->Accept(zoomVisitor);
	cloneA4->Accept(drawVisitor);

	//this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(102, 102, 102));
	NShape *cloneFlowChart = this->flowChart->Clone();
	cloneFlowChart->Accept(zoomVisitor);
	cloneFlowChart->Accept(drawVisitor);

	if (this->templateSelected != NULL && this->templateSelected->IsSelected())
	{
		NShape *cloneSelected = this->templateSelected->Clone();
		cloneSelected->Accept(zoomVisitor);
		cloneSelected->Accept(drawVisitor);
	}

	if (this->drawSelectingAreaFlag == true) {
		this->DrawSelectingArea();
	}

	this->painter->Render(&painter, 0, 0);

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

void DrawingPaper::mousePressEvent(QMouseEvent *event) {
	//this->setFocus();

	QPointF point = event->localPos();
	this->tool = ToolFactory::Create(this, point);

	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->parentWidget());
	QString mode = this->GetCurrentMode();
	editor->modeStatus->setText(mode);
	editor->statusBar->repaint();

	if (this->tool != NULL) {
		this->tool->OnLButtonDown(this, point);
		//this->SetCapture();
	}

	this->setMouseTracking(false);
}

void DrawingPaper::mouseMoveEvent(QMouseEvent *event) {
	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->parentWidget());
	editor->windowClose->Paint(QColor(102, 204, 204), Qt::SolidLine, editor->windowClose->GetBorderColor());
	editor->repaint();

	QPointF point = event->localPos();
	if (this->hasMouseTracking() == false) { //마우스가 암거나 눌렸을 때
		if (this->tool != NULL) {
			this->tool->OnMouseMove(this, point);
		}
	}
	else { //마우스가 암것도 안누르고 그냥 있는 상태일 때
		//OnSetCursor 부분
		QCursor cursor = this->GetCursor(event->pos());
		this->setCursor(cursor);

		QString x = "X: ";
		QString xPoint = QString::number(point.x());
		x += xPoint;
		editor->xStatus->setText(x);
		QString y = "Y: ";
		QString yPoint = QString::number(point.y());
		y += yPoint;
		editor->yStatus->setText(y);
		editor->statusBar->repaint();

	}
}

void DrawingPaper::mouseReleaseEvent(QMouseEvent *event) {
	this->flowChart->AscendingSort();

	QPointF point = event->localPos();


	if (this->tool != NULL) {
		FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->parentWidget());
		//기호를 그리는 것이면
		if (this->variableList != NULL && dynamic_cast<DrawingTool*>(this->tool)) {
			//준비기호를 찾는다.
			Long index = this->flowChart->Find(SHAPE::PREPARATION);
			
			//준비기호가 있으면 준비기호를 그릴 수 없고 준비기호가 없으면 준비기호만 그릴 수가 있다.
			//위에서 단말 기호는 예외이다. 준비 기호가 있거나 없거나 상관 없다.
			//준비기호를 찾았고 준비 기호를 그리는 것이 아니거나(준비 기호는 하나만)
			//준비기호를 못찾았고 준비기호를 그리려는 것이거나
			//단말 기호를 그리려는 것이면
			if ((index != -1 && this->templateSelected->GetSymbolID() != ID_PREPARATION) ||
				(index == -1 && this->templateSelected->GetSymbolID() == ID_PREPARATION) ||
				this->templateSelected->GetSymbolID() == ID_TERMINAL) {

				this->tool->OnLButtonUp(this, point);
				ReleaseCapture();

				QString mode = this->GetCurrentMode();
				editor->modeStatus->setText(mode);
				editor->statusBar->repaint();
			}
			//준비 기호를 못찾았거나 준비기호를 그리려는 것이고
			//준비기호를 찾았거나 준비기호를 그리려는 것이 아니고
			//단말 기호를 그리려는 것이 아니면
			else {
				QString message;
				if (this->templateSelected->GetSymbolID() != ID_PREPARATION) {
					message = QString::fromLocal8Bit("    준비 기호를 그리십시오.");
				}
				else {
					message = QString::fromLocal8Bit("    준비 기호는 하나만 그릴 수 있습니다.");
				}
				editor->messageStatus->setText(message);
				editor->statusBar->repaint();
				if (this->templateSelected != NULL) {
					delete this->templateSelected;
					this->templateSelected = NULL;
				}
				this->mode = IDLE;
			}
		}
		else {
			this->tool->OnLButtonUp(this, point);
			ReleaseCapture();

			QString mode = this->GetCurrentMode();
			editor->modeStatus->setText(mode);
			editor->statusBar->repaint();
		}
	}
	if (this->scrollController != NULL) {
		this->scrollController->Update();
	}

	this->memoryController->Quadrate();

	this->setMouseTracking(true);
}

void DrawingPaper::mouseDoubleClickEvent(QMouseEvent *event) {
	// 상태 패턴 : 텍스트 조작자 Manipulator
	NShape *shape;
	float left, top, right, bottom, halfHeight;

	QRectF rect = this->frameRect();
	QPointF point = event->localPos();
	Long positionX = 0;
	Long positionY = 0;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}
	point.setX(point.x() + positionX);
	point.setY(point.y() + positionY);
	NShape *holdA4Paper = this->a4Paper->Clone();
	NShape *holdFlowChart = this->flowChart->Clone();
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(this->zoom);
	holdA4Paper->Accept(zoomVisitor);
	holdFlowChart->Accept(zoomVisitor);

	this->indexOfSelected = holdFlowChart->Find(point);

	shape = holdFlowChart->GetAt(this->indexOfSelected);

	if (this->indexOfSelected != -1 && 
		(shape->GetSymbolID() != ID_TERMINAL && !dynamic_cast<Line*>(shape)) &&
		((point.x() > shape->GetX() + 5 && point.x() < shape->GetX() + shape->GetWidth() - 5) ||
		(point.y() > shape->GetY() + 5 && point.y() < shape->GetY() + shape->GetHeight() - 5))) {

		this->clearFocus();

		QColor color = shape->GetBackGroundColor();
		this->label = Label::Instance(&(shape->GetContents()), color, this);

		halfHeight = shape->GetHeight() / 2;
		left = shape->GetX() + halfHeight - positionX;
		top = shape->GetY() + 1 - positionY;
		right = shape->GetX() + shape->GetWidth() - halfHeight + 5 - positionX;
		bottom = shape->GetY() + shape->GetHeight() - 1 - positionY;

		this->label->Open(left, top, right - left, bottom - top);
		this->label->show();

		Long(*indexes) = new Long[this->flowChart->GetLength()];
		indexes[0] = this->indexOfSelected;
		this->memoryController->RememberOther(indexes, 1);

		shape = this->flowChart->GetAt(this->indexOfSelected);
		shape->Rewrite(String(""));
		this->label->setFocus();

		if (indexes != 0) {
			delete[] indexes;
		}
	}
}

void DrawingPaper::resizeEvent(QResizeEvent *event) {
	//========================캔버스 타이틀 들========================
	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->parentWidget());
	SketchBook *sketchBook = editor->sketchBook;
	NShape *canvasTitle;
	float width = 0;
	Long i = 0;
	while (i < sketchBook->GetLength()) {
		canvasTitle = sketchBook->GetCanvas(i);
		canvasTitle->Move(this->x() + width, canvasTitle->GetY());
		width += canvasTitle->GetWidth();
		i++;
	}
	NShape *currentTitle = sketchBook->GetCanvas(sketchBook->GetCurrent());
	float windowCloseX = currentTitle->GetX() + currentTitle->GetWidth() - 26 - 3; //24=사각형길이,3=여유공간
	float windowCloseY = currentTitle->GetY() + 4;
	editor->windowClose->Move(windowCloseX, windowCloseY);
	editor->update();
	//========================캔버스 타이틀 들========================

	QRect frameRect = this->frameRect();
	if (this->painter != NULL) {
		delete this->painter;
		this->painter = new QtPainter(frameRect.width(), frameRect.height());
	}

	if (this->scrollController == NULL) {
		this->scrollController = new ScrollController(this);

		this->scrollController->GetScroll(0)->setValue(1283);
		//Long previousPosition = this->SetScrollPos(SB_VERT, position, TRUE);
		//position = this->GetScrollPos(SB_VERT);
		//this->scrollController->MoveVerticalScroll(position);
		//this->ScrollWindow(0, previousPosition - position);

		this->scrollController->GetScroll(1)->setValue(427);
		//previousPosition = this->SetScrollPos(SB_HORZ, position, TRUE);
		//position = this->GetScrollPos(SB_HORZ);
		//this->scrollController->MoveHorizontalScroll(position);
		//this->ScrollWindow(previousPosition - position, 0);

		this->scrollController->Update();
	}
	if (this->flowChart != NULL) {
		this->scrollController->Update();
	}

	this->repaint();
}

void DrawingPaper::wheelEvent(QWheelEvent *event) {
	QPoint delta = event->angleDelta();
	bool isControlPressed = ((::GetKeyState(VK_CONTROL) & 0x8000) != 0);
	if (isControlPressed && this->scrollController->GetScroll(0) != NULL) { //zoom
		Long oldRate = this->zoom->GetRate();
		Long rate;
		QString rateStatus;
		if (delta.y() > 0 && oldRate < 150) {
			rate = oldRate + 10;
			this->zoom->Set(rate);

			rateStatus = QString::number(rate);
			rateStatus += "%";
			dynamic_cast<FlowChartEditor*>(this->parentWidget())->zoomStatus->setText(rateStatus);
		}
		else if (delta.y() < 0 && oldRate > 40) {
			rate = oldRate - 10;
			this->zoom->Set(rate);

			rateStatus = QString::number(rate);
			rateStatus += "%";
			dynamic_cast<FlowChartEditor*>(this->parentWidget())->zoomStatus->setText(rateStatus);
		}
		dynamic_cast<FlowChartEditor*>(this->parentWidget())->statusBar->repaint();
		this->scrollController->Update();
	}
	else {
		Long value = this->scrollController->Rotate(delta);
		this->repaint();
	}
}

void DrawingPaper::keyPressEvent(QKeyEvent *event) {
	//CDC *pDC = CWnd::GetDC();

	FlowChartEditor *editor = (FlowChartEditor*)this->parentWidget();
	FlowChartKeyActionFactory keyActionFactory(editor);
	FlowChartKeyAction *keyAction = keyActionFactory.Make(event->modifiers(), event->key());
	if (keyAction != 0) {
		keyAction->OnKeyDown();
		delete keyAction;

		QString mode = this->GetCurrentMode();
		editor->modeStatus->setText(mode);
		editor->statusBar->repaint();
	}
	editor->windows[1]->repaint(); //왜?

	this->repaint();
}

void DrawingPaper::focusOutEvent(QFocusEvent *event) {
	QFrame::focusOutEvent(event);
}

void DrawingPaper::focusInEvent(QFocusEvent *event) {
	QFrame::focusInEvent(event);
}

void DrawingPaper::OnContextMenu(const QPoint& pos) {
	//HMENU hPopup;
	this->popup = new QMenu(this);

	QAction *moveMake = this->popup->addAction(QString::fromLocal8Bit("기호 위치 같게"), this, &DrawingPaper::OnMoveMakeMenuClick);
	//connect(moveMake, &QAction::triggered, this, &DrawingPaper::OnMoveMakeMenuClick);
	QAction *sizeMake = this->popup->addAction(QString::fromLocal8Bit("기호 크기 같게"), this, &DrawingPaper::OnSizeMakeMenuClick);
	QAction *intervalMake = this->popup->addAction(QString::fromLocal8Bit("기호 간격 같게"), this, &DrawingPaper::OnIntervalMakeMenuClick);
	QAction *sequence = this->popup->addAction(QString::fromLocal8Bit("순차구조"), this, &DrawingPaper::OnSequenceMenuClick);
	QAction *iteration = this->popup->addAction(QString::fromLocal8Bit("반복구조"), this, &DrawingPaper::OnIterationMenuClick);
	QAction *selection = this->popup->addAction(QString::fromLocal8Bit("선택구조"), this, &DrawingPaper::OnSelectionMenuClick);

	moveMake->setEnabled(false);
	sizeMake->setEnabled(false);
	intervalMake->setEnabled(false);
	sequence->setEnabled(false);
	iteration->setEnabled(false);
	selection->setEnabled(false);


	Long(*indexes);
	Long count;
	NShape *shape;
	this->flowChart->GetSelecteds(&indexes, &count);

	if (count > 1) {
		moveMake->setEnabled(true);
		sizeMake->setEnabled(true);
		intervalMake->setEnabled(true);
		sequence->setEnabled(true);

		shape = this->flowChart->GetAt(indexes[0]);
		if (dynamic_cast<Decision *>(shape)) {
			iteration->setEnabled(true);
			//19.09.16 판단기호 왼쪽에 처리할 내용이 없으면 선택 기호 메뉴 활성화X
			Long leftCount = 0;
			Long i = 1;
			while (i < count) {
				NShape *left = this->flowChart->GetAt(indexes[i]);
				if (left->CenterOfGravityX() < shape->CenterOfGravityX()) {
					leftCount++;
				}
				i++;
			}
			if (leftCount > 0) {
				selection->setEnabled(true);
			}
		}
	}

	if (indexes != 0)
	{
		delete[] indexes;
	}

	this->popup->popup(this->mapToGlobal(pos));
}

void DrawingPaper::DrawSelectingArea() {
	int compositionMode = this->painter->GetCompositionMode();
	this->painter->SetCompositionMode(QPainter::RasterOp_NotSourceXorDestination);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(166, 166, 166)), 1, Qt::DotLine);
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	float x = this->startX;
	float width = this->currentX - this->startX;
	if (this->startX > this->currentX) {
		x = this->currentX;
		width = this->startX - this->currentX;
	}
	float y = this->startY;
	float height = this->currentY - this->startY;
	if (this->startY > this->currentY) {
		y = this->currentY;
		height = this->startY - this->currentY;
	}

	QRectF drawRect(x, y, width, height);
	this->painter->DrawRect(drawRect);

	this->painter->SelectObject(*oldPen);
	this->painter->Update();
	if (pen != 0) {
		delete pen;
	}
	this->painter->SetCompositionMode(compositionMode);

	this->drawSelectingAreaFlag = false;
}

void DrawingPaper::DrawActiveShape(NShape *entity) {
	//원래 dc생성해서 바로 그림(속성 Painter 사용 안함)
	QPainter dc(this);

	QRect rect = this->frameRect();
	QtPainter painter(rect.width(), rect.height());
	int bgMode = painter.GetBackgroundMode();
	painter.SetBackgroundMode(Qt::TransparentMode);

	painter.SetCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(0, 0, 255)), 1, Qt::DotLine);
	painter.SelectObject(*pen);
	GObject *brush = factory.MakeBrush(QColor(255, 255, 255));
	painter.SelectObject(*brush);
	painter.Update();

	entity->DrawActiveShape(&painter);

	painter.Render(&dc, 0, 0);
}

void DrawingPaper::DrawActiveShape2(NShape *entity) {
	int oldMode = this->painter->GetBackgroundMode();
	this->painter->SetBackgroundMode(Qt::TransparentMode);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(0, 0, 255)), 1, Qt::DashLine);
	GObject *oldPen = this->painter->SelectObject(*pen);
	GObject *brush = factory.MakeBrush(QColor(0, 0, 255)); //BS_NULL style
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	entity->DrawActiveShape(this->painter);

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}
	this->painter->SetBackgroundMode(oldMode);
}

void DrawingPaper::DrawSelectionMark(QPoint(*points), Long count) {
	//원래 dc 생성해서 바로 그림(속성 Painter 사용 안함)
	QPainter dc(this);
	QRect rect = this->frameRect();

	QtPainter painter(rect.width(), rect.height());

	painter.SetBackgroundMode(Qt::TransparentMode);
	painter.SetCompositionMode(QPainter::RasterOp_NotSourceXorDestination);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(0, 0, 255)), 1);
	painter.SelectObject(*pen);
	GObject *brush = factory.MakeBrush(QColor(255, 255, 255)); // NULL_BRUSH
	painter.SelectObject(*brush);

	QPoint selectionMarkPoints[BOXVERTECIES];
	Long i = 0;
	while (i < count) {
		selectionMarkPoints[0].setX(points[i].x() - BOXLENGTH);
		selectionMarkPoints[1].setX(points[i].x() + BOXLENGTH);
		selectionMarkPoints[2].setX(points[i].x() + BOXLENGTH);
		selectionMarkPoints[3].setX(points[i].x() - BOXLENGTH);

		selectionMarkPoints[0].setY(points[i].y() - BOXLENGTH);
		selectionMarkPoints[1].setY(points[i].y() - BOXLENGTH);
		selectionMarkPoints[2].setY(points[i].y() + BOXLENGTH);
		selectionMarkPoints[3].setY(points[i].y() + BOXLENGTH);

		painter.DrawPolygon(selectionMarkPoints, BOXVERTECIES);
		i++;
	}

	painter.Render(&dc, 0, 0);

	/* 어차피 dc격인 QPainter의 설정은 변경하지 않았고
	임시로 사용한 QtPainter는 없어질 것이기 때문에 따로 처리 안해도 됨.
	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);

	dc->SetBkMode(oldmode);
	this->ReleaseDC(dc);

	pen.DeleteObject();
	*/
}

void DrawingPaper::DrawSelectionMark2(QPoint(*points), Long count) {
	//속성 Painter 사용 버전
	int oldMode = this->painter->GetBackgroundMode();
	this->painter->SetBackgroundMode(Qt::OpaqueMode);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(0, 0, 255)), 1);
	GObject *oldPen = this->painter->SelectObject(*pen);
	GObject *brush = factory.MakeBrush(QColor(0, 0, 255)); //BS_NULL
	GObject *oldBrush = this->painter->SelectObject(*brush);
	this->painter->Update();

	QPoint selectionMarkPoints[BOXVERTECIES];
	Long i = 0;
	while (i < count) {
		selectionMarkPoints[0].setX(points[i].x() - BOXLENGTH);
		selectionMarkPoints[1].setX(points[i].x() + BOXLENGTH);
		selectionMarkPoints[2].setX(points[i].x() + BOXLENGTH);
		selectionMarkPoints[3].setX(points[i].x() - BOXLENGTH);

		selectionMarkPoints[0].setY(points[i].y() - BOXLENGTH);
		selectionMarkPoints[1].setY(points[i].y() - BOXLENGTH);
		selectionMarkPoints[2].setY(points[i].y() + BOXLENGTH);
		selectionMarkPoints[3].setY(points[i].y() + BOXLENGTH);

		this->painter->DrawPolygon(selectionMarkPoints, BOXVERTECIES);
		i++;
	}

	this->painter->SelectObject(*oldPen);
	this->painter->SelectObject(*oldBrush);
	this->painter->Update();
	this->painter->SetBackgroundMode(oldMode);

	if (pen != NULL) {
		delete pen;
	}
	if (brush != NULL) {
		delete brush;
	}
}

void DrawingPaper::FillSelectionMark(QPoint point) {
	//dc에 바로 그림
	QPainter dc(this);
	QRect rect = this->frameRect();
	QtPainter painter(rect.width(), rect.height());

	painter.SetBackgroundMode(Qt::OpaqueMode);
	painter.SetCompositionMode(QPainter::RasterOp_NotSourceXorDestination);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(0, 0, 255)), 1);
	painter.SelectObject(*pen);
	GObject *brush = factory.MakeBrush(QColor(0, 0, 255));
	painter.SelectObject(*brush);
	painter.Update();

	QRect selectionMark;
	selectionMark.setCoords(point.x() + 1 - MARKLENGTH, point.y() + 1 - MARKLENGTH,
		point.x() + MARKLENGTH, point.y() + MARKLENGTH);
	painter.DrawRect(selectionMark);

	painter.Render(&dc, 0, 0);
}

QCursor DrawingPaper::GetCursor(QPoint point) {
	QCursor result;
	Long i = 0;
	Long end;
	NShape *shape;

	if (this->mode == SELECT) {
		Long positionX = this->scrollController->GetScroll(1)->value();
		Long positionY = this->scrollController->GetScroll(0)->value();
		point.setX(point.x() + positionX);
		point.setY(point.y() + positionY);

		NShape *holdA4Paper = this->a4Paper->Clone();
		FlowChartVisitor *zoomVisitor = new ZoomVisitor(this->zoom);
		holdA4Paper->Accept(zoomVisitor);

		QPointF currentReal(point.x(), point.y());
		QPointF currentVirtual = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertVirtual(currentReal);

		currentVirtual.setX(currentVirtual.x() * 100 / this->zoom->GetRate());
		currentVirtual.setY(currentVirtual.y() * 100 / this->zoom->GetRate());

		currentReal = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertReal(currentVirtual);

		point.setX(currentReal.x());
		point.setY(currentReal.y());

		end = this->flowChart->GetLength();
		while (i < end) {
			shape = this->flowChart->GetAt(i);
			if (shape->IsSelected()) {
				int hitCode = shape->GetHitCode(point);
				if (hitCode != HIT_NONE && hitCode != HIT_BODY) {
					result = shape->GetCursor(hitCode);
				}
			}
			i++;
		}
	}
	else if (this->mode == DRAWING) {
		result.setShape(Qt::CrossCursor);
	}

	return result;
}

void DrawingPaper::OnSequenceMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->SequenceMake(this);

	this->zoom->Set(rate);

	this->repaint();
}

void DrawingPaper::OnIterationMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->IterationMake(this);

	this->zoom->Set(rate);

	this->repaint();
}

void DrawingPaper::OnSelectionMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->SelectionMake(this);

	this->zoom->Set(rate);

	this->repaint();
}

void DrawingPaper::OnMoveMakeMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->MoveMake(this);

	this->zoom->Set(rate);

	this->repaint();
}

void DrawingPaper::OnSizeMakeMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->SizeMake(this);

	this->zoom->Set(rate);

	this->repaint();
}

void DrawingPaper::OnIntervalMakeMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->IntervalMake(this);

	this->zoom->Set(rate);

	this->repaint();
}

void DrawingPaper::New() {
	FlowChartEditor *editor = static_cast<FlowChartEditor *>(this->parentWidget());

	NShape *last = editor->sketchBook->GetCanvas(editor->sketchBook->GetLength() - 1);
	float lastRight = last->GetX() + last->GetWidth();
	//마지막 캔버스 타이틀의 오른쪽이 윈도우의 오른쪽보다 작을 때만 추가로 열 수 있다.
	float right = this->x() + this->width();
	if (lastRight + 186 < right) { //186은 캔버스 타이틀의 최소 너비

		editor->sketchBook->Unfold(this->flowChart->Clone(),
			new Memory(*this->memoryController->GetUndoMemory()),
			new Memory(*this->memoryController->GetRedoMemory()),
			new VariableList(*this->variableList));

		NShape *previousTitle = editor->sketchBook->GetCanvas(editor->sketchBook->GetLength() - 1);
		NShape *newTitle = new WindowTitle(previousTitle->GetX() + previousTitle->GetWidth(),
			previousTitle->GetY(), 186.0F, previousTitle->GetHeight(), QColor(102, 204, 204),
			Qt::SolidLine, QColor(102, 204, 204), String(" 제목없음"));
		NShape *newFlowChart = new FlowChart;
		editor->sketchBook->Add(newTitle, newFlowChart);
		editor->sketchBook->Update();

		//비어 있는  순서도, 비어 있는 메모리들(-Add에서 빈 거 생성한거 가져와서 다시 넣는거임)
		this->flowChart = newFlowChart->Clone();
		Memory *undoMemory = new Memory(*editor->sketchBook->GetUndoMemory(editor->sketchBook->GetCurrent()));
		Memory *redoMemory = new Memory(*editor->sketchBook->GetRedoMemory(editor->sketchBook->GetCurrent()));
		this->memoryController->ChangeMemory(undoMemory, redoMemory);
		this->variableList = new VariableList;

		float windowCloseX = newTitle->GetX() + newTitle->GetWidth() - 26 - 3; //24=사각형길이,3=여유공간
		float windowCloseY = newTitle->GetY() + 4;
		editor->windowClose->Move(windowCloseX, windowCloseY);

		editor->repaint();
	}
	else {
		//메시지 박스
		QMessageBox messageBox(QMessageBox::Warning, QString::fromLocal8Bit("경고"),
			QString::fromLocal8Bit("더 열 수 없습니다. 파일을 닫은 후 여십시오."),
			QMessageBox::Ok, editor);
		int ret = messageBox.exec();
	}
}

Long DrawingPaper::Save(QString fileName) {
	File file;
	return file.Save(this, fileName);
}

Long DrawingPaper::Load(QString fileName) {
	File file;
	return file.Load(this, fileName);
}

void DrawingPaper::Close() {
	QString fileName;

	FlowChartEditor *editor = static_cast<FlowChartEditor *>(this->parentWidget());

	QMessageBox messageBox(QMessageBox::Question, QString::fromLocal8Bit("새로 만들기"),
		QString::fromLocal8Bit("변경 내용을 저장하시겠습니까?"),
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this);
	int ret = messageBox.exec();
	if (ret == QMessageBox::Yes) { //유저가 저장한다고 하면
		QString fileOpenPath = editor->sketchBook->GetFileOpenPath(editor->sketchBook->GetCurrent());
		if (fileOpenPath.isEmpty()) { //현재 순서도가 저장되어 있지 않다면 새로 저장한다.
			fileName = QFileDialog::getSaveFileName((QWidget*)editor,
				QObject::tr("Save File"),
				NULL,
				QObject::tr("Text files (*.txt)"));
			//fileName은 fileOpenPath를 대체할 새로운 경로
			QFile file(fileName);
			bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);
			if (isOpen == true) {
				editor->sketchBook->ModifyFileOpenPath(fileName); //빈 경로를 다이어로그에서 가져와서 고침.
				this->Save(fileName.toLocal8Bit().data());

				Long length = fileName.length();
				Long i = length - 1;
				while (i >= 0 && fileName[i] != '/') {
					length--;
					i--;
				}
				fileName.remove(0, length);
				fileName.remove(fileName.length() - 4, 4);
				fileName.insert(0, ' ');

				editor->sketchBook->GetCanvas(editor->sketchBook->GetCurrent())->Rewrite(fileName.toLocal8Bit().data());
			}
		}
		else { //현재 순서도가 저장되어 있으면 그대로 똑같은 경로와 이름으로 저장한다.
			this->Save(fileOpenPath.toLocal8Bit().data());
		}
	}

	if (ret != QMessageBox::Cancel) { //유저가 한번 더 물어봐도 닫는 걸 선택함
		//캔버스 윈도우를 비우다.
		this->flowChart->Clear();
		this->mode = IDLE;
		this->indexOfSelected = -1;

		//현재 캔버스 지우고/새로운 현재 설정해주고/닫기버튼 옮겨주기.
		editor->sketchBook->Remove(editor->sketchBook->GetCurrent());

		NShape *first = editor->sketchBook->GetCanvas(0); //새로운 현재 : 맨 앞에꺼
		editor->sketchBook->Fold(QPoint(first->GetX(), first->GetY()));
		editor->sketchBook->Update();
		this->flowChart = editor->sketchBook->GetFlowChart(editor->sketchBook->GetCurrent())->Clone();

		editor->sketchBook->Arrange(this->x());

		float windowCloseX = first->GetX() + first->GetWidth() - 26 - 3; //24=사각형길이,3=여유공간
		float windowCloseY = first->GetY() + 4;
		editor->windowClose->Move(windowCloseX, windowCloseY);
	}
}

QString DrawingPaper::GetCurrentMode() {
	QString mode;

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

	return mode;
}