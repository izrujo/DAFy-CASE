#include "DrawingPaper.h"
#include "../FlowChartEditor.h"
#include "FlowChart.h"
#include "Clipboard.h"
#include "MemoryController.h"
#include "VariableList.h"
#include "Zoom.h"
#include "A4Paper.h"
#include "QtPainter.h"
#include "DrawingTool.h"
#include "MovingTool.h"
#include "ResizingTool.h"
#include "SelectingTool.h"
#include "DrawVisitor.h"
#include "ZoomVisitor.h"
#include "Label.h"
#include "Preparation.h"
//#include "TutorialForm.h"
#include "ToolFactory.h"
#include "../Notepad/Note.h"
#include "TutorialController.h"
#include "FlowChartTemplate.h"
#include "ScrollController.h"
#include "Scroll.h"
#include "QtGObjectFactory.h"
#include "GObject.h"
#include "FlowChartKeyActionFactory.h"
#include "FlowChartKeyActions.h"
#include "CoordinateConverter.h"
#include "Decision.h"
#include "Tutorials.h"
#include "File.h"

#include <qscrollbar.h>
#include <qpainter.h>
#include <qevent.h>
#include <qmenu.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qtextedit.h>

DrawingPaper::DrawingPaper(QWidget *parent = Q_NULLPTR) {
	this->templateSelected = NULL;

	this->flowChart = NULL;

	this->label = NULL;
	this->painter = NULL;

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

	this->popup = NULL;

	QRect frameRect = this->frameRect();

	this->flowChart = new FlowChart;

	this->painter = new QtPainter(frameRect.width(), frameRect.height()); //트리플 버퍼링 유지하자.

	//this->SetFocus();

	this->clipboard = new Clipboard;

	this->memoryController = new MemoryController(this);

	this->variableList = new VariableList;

	this->zoom = new Zoom(100);

	this->a4Paper = new A4Paper(444, 615, 1653, 2338);
	this->zoom->Set(40);

	connect(this, &QWidget::customContextMenuRequested, this, &DrawingPaper::OnContextMenu);
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

void DrawingPaper::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	QRect rect = frameRect();

	FlowChartEditor *editor = (FlowChartEditor*)this->parent();

	//그리기 전 기본 설정 : 필요 없을 것 같음.
	//HFONT hFont = editor->font->Create();
	//this->painter->ChangeFont(hFont, editor->font->GetColor());
	//this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(0, 0, 0));
	//this->painter->EraseBackground((float)0, (float)0, (float)rect.Width(), (float)rect.Height());
	//POINT points[5] = { {0, 0}, {rect.right, rect.top}, {rect.right, rect.bottom}, {rect.left, rect.bottom}, {0, 0} };
	//this->painter->FillBackground(points, 5, RGB(235, 235, 235));

	//Visitor 패턴 적용	
	FlowChartVisitor *drawVisitor = new DrawVisitor(this->painter, this->scrollController);
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(this->zoom);
	FlowChartShape::Shape *cloneA4 = this->a4Paper->Clone();
	cloneA4->Accept(zoomVisitor);
	cloneA4->Accept(drawVisitor);

	//this->painter->ChangeLineProperty(PS_SOLID, 2, PS_ENDCAP_FLAT, PS_JOIN_MITER, RGB(102, 102, 102));
	FlowChartShape::Shape *cloneFlowChart = this->flowChart->Clone();
	cloneFlowChart->Accept(zoomVisitor);
	cloneFlowChart->Accept(drawVisitor);

	if (this->templateSelected != NULL && this->templateSelected->IsSelected())
	{
		this->templateSelected->Accept(drawVisitor);
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

	/* Status Bar
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
	*/
}

void DrawingPaper::mousePressEvent(QMouseEvent *event) {
	this->setFocus();

	if (this->label != NULL)
	{
		//19.09.03 Label의 (편집된)내용을 기호 안의 실제 데이터로 넣는 처리==================
		string content = this->label->toPlainText().toLocal8Bit().constData();
		String contents(content);

		FlowChartShape::Shape *shape = this->flowChart->GetAt(this->indexOfSelected);

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

		if (this->label != NULL) {
			delete this->label;
			this->label = NULL;
		}
		/*
		FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->parentWidget());
		TutorialForm *tutorialForm = (TutorialForm*)editor->windows[2];
		if (tutorialForm != NULL) {
			tutorialForm->tutorialController->Update();
		}
		*/
	}

	QPoint point = event->pos();
	this->tool = ToolFactory::Create(this, point);

	if (this->tool != NULL) {
		this->tool->OnLButtonDown(this, point);
		//this->SetCapture();
	}

	this->setMouseTracking(false);
}

void DrawingPaper::mouseMoveEvent(QMouseEvent *event) {
	if (this->hasMouseTracking() == false) { //마우스가 암거나 눌렸을 때
		QPoint point = event->pos();
		if (this->tool != NULL) {
			this->tool->OnMouseMove(this, point);
		}
	}
	else { //마우스가 암것도 안누르고 그냥 있는 상태일 때
		//OnSetCursor 부분
		QCursor cursor = this->GetCursor(event->pos());
		//if (cursor.shape() != Qt::ArrowCursor) {
		this->setCursor(cursor);
		//}
		//else {
		//	QFrame::mouseMoveEvent(event);
		//}

		/* Status Bar
		CString x;
		x.Format("X : %d", point.x);
		dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Modify(2, String((LPCTSTR)x));
		CString y;
		y.Format("Y : %d", point.y);
		dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Modify(3, String((LPCTSTR)y));
		dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Print();
		*/

		//템플릿 창 기호에 마우스 올릴 때 효과가 마우스가 떠나도 지속되는 오류 때문에 넣음.
		FlowChartTemplate *templateWnd = static_cast<FlowChartTemplate*>(static_cast<FlowChartEditor*>(this->parentWidget())->windows[1]);
		QColor selectedColor(235, 235, 235);
		FlowChartShape::Shape *shape;
		Long i = 0;
		while (i < templateWnd->flowChartTemplate->GetLength()) {
			shape = templateWnd->flowChartTemplate->GetAt(i);
			if (shape->GetBackGroundColor() == selectedColor && templateWnd->oldShapeSelected != NULL) {
				shape->Paint(templateWnd->oldShapeSelected->GetBackGroundColor(), shape->GetBorderLine(), shape->GetBorderColor());
			}
			i++;
		}
		templateWnd->repaint();
	}
}

void DrawingPaper::mouseReleaseEvent(QMouseEvent *event) {
	this->flowChart->AscendingSort();

	QPoint point = event->pos();
	if (this->tool != NULL) {
		this->tool->OnLButtonUp(this, point);
		ReleaseCapture();
	}
	if (this->scrollController != NULL) {
		this->scrollController->Update();
	}

	this->memoryController->Quadrate();

	this->setMouseTracking(true);
}

void DrawingPaper::mouseDoubleClickEvent(QMouseEvent *event) {
	// 상태 패턴 : 텍스트 조작자 Manipulator
	FlowChartShape::Shape *shape;
	Long left, top, right, bottom, halfHeight;

	QRect rect = this->frameRect();
	QPoint point = event->pos();
	Long positionX;
	Long positionY;
	if (this->scrollController != NULL) {
		positionX = this->scrollController->GetScroll(1)->value();
		positionY = this->scrollController->GetScroll(0)->value();
	}
	point.setX(point.x() + positionX);
	point.setY(point.y() + positionY);
	FlowChartShape::Shape *holdA4Paper = this->a4Paper->Clone();
	FlowChartShape::Shape *holdFlowChart = this->flowChart->Clone();
	FlowChartVisitor *zoomVisitor = new ZoomVisitor(this->zoom);
	holdA4Paper->Accept(zoomVisitor);
	holdFlowChart->Accept(zoomVisitor);

	this->indexOfSelected = holdFlowChart->Find(point);

	shape = holdFlowChart->GetAt(this->indexOfSelected);

	if (this->indexOfSelected != -1 &&
		((point.x() > shape->GetX() + 5 && point.x() < shape->GetX() + shape->GetWidth() - 5) ||
		(point.y() > shape->GetY() + 5 && point.y() < shape->GetY() + shape->GetHeight() - 5))) {

		this->clearFocus();

		QColor color = shape->GetBackGroundColor();
		this->label = new QTextEdit(this);

		halfHeight = shape->GetHeight() / 2;
		left = shape->GetX() + halfHeight - positionX;
		top = shape->GetY() + 1 - positionY;
		right = shape->GetX() + shape->GetWidth() - halfHeight + 5 - positionX;
		bottom = shape->GetY() + shape->GetHeight() - 1 - positionY;

		this->label->move(left, top);
		this->label->resize(right - left, bottom - top);
		//this->label->Open(left, top, right - left, bottom - top, &(shape->GetContents()));
		this->label->setWordWrapMode(QTextOption::NoWrap);
		this->label->setPlainText(QString::fromLocal8Bit(shape->GetContents()));
		this->label->show();
		//this->label->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), (CWnd*)this, -1);

		Long(*indexes) = new Long[this->flowChart->GetLength()];
		indexes[0] = this->indexOfSelected;
		this->memoryController->RememberOther(indexes, 1);

		shape = this->flowChart->GetAt(this->indexOfSelected);
		shape->Rewrite(String(""));
		this->label->setFocus();

		if (indexes != 0) {
			delete[] indexes;
		}
		/*
		FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->parentWidget());
		TutorialForm *tutorialForm = static_cast<TutorialForm*>(editor->windows[2]);
		if (tutorialForm != NULL) {
			tutorialForm->move(1230, 70);
			tutorialForm->resize(660, 940);
			tutorialForm->repaint();
		}
		*/
	}
}

void DrawingPaper::resizeEvent(QResizeEvent *event) {
	QRect frameRect = this->frameRect();
	if (this->painter != NULL) {
		delete this->painter;
		this->painter = new QtPainter(frameRect.width(), frameRect.height());
	}

	if (this->scrollController == NULL) {
		this->scrollController = new ScrollController(this);

		this->scrollController->GetScroll(0)->setValue(1311);
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
	if (event->modifiers() == Qt::Key_Control && this->scrollController->GetScroll(0) != NULL) { //zoom
		Long oldRate = this->zoom->GetRate();
		Long rate;
		//CString rateStatus;
		if (delta.y() > 0 && oldRate < 150) {
			rate = oldRate + 10;
			this->zoom->Set(rate);
			/*
			rateStatus.Format("%d", rate);
			rateStatus += "%";
			dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Modify(4, String((LPCTSTR)rateStatus));
			*/
		}
		else if (delta.y() < 0 && oldRate > 40) {
			rate = oldRate - 10;
			this->zoom->Set(rate);
			/*
			rateStatus.Format("%d", rate);
			rateStatus += "%";
			dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Modify(4, String((LPCTSTR)rateStatus));
			*/
		}
		//dynamic_cast<FlowChartEditor*>(this->GetParent())->statusBar->Print();
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
	}
	//CDC *dc = editor->GetDC();
	//editor->ReleaseDC(dc);
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
	FlowChartShape::Shape *shape;
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
				FlowChartShape::Shape *left = this->flowChart->GetAt(indexes[i]);
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
	/*
	FlowChartEditor *editor = static_cast<FlowChartEditor*>(this->parentWidget());
	TutorialForm *tutorialForm = static_cast<TutorialForm*>(editor->windows[2]);
	if (tutorialForm != NULL) {
		if (dynamic_cast<ContextMenuTutorial*>(tutorialForm->lastConcrete)) { //직전에 수행한 튜토리얼이 콘텍스트메뉴일 경우에만 다음걸 수행한다. 아니면 이 이벤트에서 시나리오 진행 안함.
			tutorialForm->tutorialController->Update();
		}
	}
	*/

	if (indexes != 0)
	{
		delete[] indexes;
	}

	this->popup->popup(pos);
	//::TrackPopupMenu(hPopup, TPM_LEFTALIGN, pos.x, pos.y, 0, pWnd->operator HWND(), NULL);

	if (this->popup != NULL) {
		delete this->popup;
		this->popup = NULL;
	}
	//BOOL ret = ::DestroyMenu(hPopup);
	//if (ret == TRUE) this->hPopup = NULL;

}

void DrawingPaper::DrawSelectingArea() {
	QPainter dc(this);

	QRect rect = this->frameRect();
	QtPainter painter(rect.width(), rect.height());

	painter.SetCompositionMode(QPainter::RasterOp_NotSourceXorDestination);

	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(QColor(166, 166, 166)), 1, Qt::DotLine);
	painter.SelectObject(*pen);
	painter.Update();

	QRect rect(this->startX, this->startY, this->currentX, this->currentY);
	painter.DrawRect(rect);

	painter.Render(&dc, 0, 0);

	//painter.SelectObject(*oldPen);
	//painter.Update();
	//this->ReleaseDC(dc);

}

void DrawingPaper::DrawActiveShape(FlowChartShape::Shape *entity) {
	//원래 dc생성해서 바로 그림(속성 Painter 사용 안함)
	QPainter dc(this);

	QRect rect = this->frameRect();
	QtPainter painter(rect.width(), rect.height());
	QRect rect = this->frameRect();
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

void DrawingPaper::DrawActiveShape2(FlowChartShape::Shape *entity) {
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
	FlowChartShape::Shape *shape;

	if (this->mode == SELECT) {
		Long positionX = this->scrollController->GetScroll(1)->value();
		Long positionY = this->scrollController->GetScroll(0)->value();
		point.setX(point.x() + positionX);
		point.setY(point.y() + positionY);

		FlowChartShape::Shape *holdA4Paper = this->a4Paper->Clone();
		FlowChartVisitor *zoomVisitor = new ZoomVisitor(this->zoom);
		holdA4Paper->Accept(zoomVisitor);

		Long quotient;
		Long remainder;

		QPoint currentReal(point.x(), point.y());
		QPoint currentVirtual = dynamic_cast<ZoomVisitor*>(zoomVisitor)->converter->ConvertVirtual(currentReal);

		quotient = currentVirtual.x() * 100 / this->zoom->GetRate();
		remainder = currentVirtual.x() * 100 % this->zoom->GetRate();
		if (remainder >= 50) quotient++;
		currentVirtual.setX(quotient);

		quotient = currentVirtual.y() * 100 / this->zoom->GetRate();
		remainder = currentVirtual.y() * 100 % this->zoom->GetRate();
		if (remainder >= 50) quotient++;
		currentVirtual.setY(quotient);

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
	/*
	TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(this->parentWidget())->windows[2];
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
	*/
}

void DrawingPaper::OnIterationMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->IterationMake(this);

	this->zoom->Set(rate);

	this->repaint();
	/*
	TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(this->parentWidget())->windows[2];
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
	*/
}

void DrawingPaper::OnSelectionMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->SelectionMake(this);

	this->zoom->Set(rate);

	this->repaint();
	/*
	TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(this->parentWidget())->windows[2];
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
	*/
}

void DrawingPaper::OnMoveMakeMenuClick() {
	float rate = this->zoom->GetRate();

	this->tool->MoveMake(this);

	this->zoom->Set(rate);

	this->repaint();
	/*
	TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(this->parentWidget())->windows[2];
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
	*/
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
	/*
	TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(this->parentWidget())->windows[2];
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
	*/
}

void DrawingPaper::New() {
	QString fileName;

	FlowChartEditor *editor = static_cast<FlowChartEditor *>(this->parentWidget());

	QMessageBox messageBox(QMessageBox::Question, QString::fromLocal8Bit("새로 만들기"),
		QString::fromLocal8Bit("변경 내용을 저장하시겠습니까?"),
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this);
	int ret = messageBox.exec();
	if (ret == QMessageBox::Yes) {
		//static char BASED_CODE szFilter[] = "txt Files (*.txt)|*.txt||";
		//CFileDialog dlg(FALSE, "*.txt", "*.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
		//if (dlg.DoModal() == IDOK) {

		fileName = QFileDialog::getSaveFileName((QWidget*)editor,
			QObject::tr("Save File"),
			NULL,
			QObject::tr("Text files (*.txt)"));

		QFile file(fileName);
		bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);
		if (isOpen == true) {
			editor->fileOpenPath = fileName;
			this->Save(editor->fileOpenPath.toLocal8Bit().data());
		}
		this->flowChart->Clear();
		editor->setWindowTitle(QString::fromLocal8Bit("제목없음 - FlowChart"));
		this->mode = IDLE;
		this->indexOfSelected = -1;
	}
	else if (ret == QMessageBox::No) {
		this->flowChart->Clear();
		editor->setWindowTitle(QString::fromLocal8Bit("제목없음 - FlowChart"));
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