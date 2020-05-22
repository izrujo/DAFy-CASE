#include "FlowChartEditor.h"
#include "FlowChart/FlowChartCommandFactory.h"
#include "FlowChart/FlowChartCommands.h"
#include "FlowChart/DrawingPaper.h"
#include "FlowChart/FlowChartTemplate.h"
#include "FlowChart/WindowTitle.h"
#include "GObject/GObject.h"
#include "GObject/QtGObjectFactory.h"
#include "GObject/QtPainter.h"
#include "FlowChart/WindowTitle.h"
#include "FlowChart/FlowChartVisitor.h"
#include "FlowChart/DrawVisitor.h"
#include "FlowChart/WindowClose.h"
#include "FlowChart/Zoom.h"
#include "FlowChart/VariableList.h"
#include "FlowChart/Clipboard.h"
#include "FlowChart/Decision.h"
#include "FlowChart/HistoryController.h"
#include "FlowChart/HistoryBook.h"
#include "FlowChart/Registrar.h"
#include "FlowChart/SheetManager.h"

#include <qmenubar.h>
#include <qevent.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qstatusbar.h>
#include <qlabel.h>
#include <qicon.h>

FlowChartEditor::FlowChartEditor(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);

	this->setMouseTracking(true);
	this->setFocusPolicy(Qt::StrongFocus);
	this->installEventFilter(this);

	this->setWindowState(Qt::WindowMaximized);

	this->setStyleSheet("QStatusBar { background:rgb(102,204,204); }"
		"QStatusBar QLabel { color:white;}"
		"QStatusBar::item { border:None;}"
	);

	this->setWindowTitle("Dafy Case");
	QIcon icon("iconTrans_ver.3");
	this->setWindowIcon(icon);

	this->menuBar = NULL;
	this->statusBar = NULL;

	QRect frameRect = this->frameRect();

	this->CreateActions();
	this->CreateMenus();
	this->menuBar->resize(frameRect.width(), this->menuBar->height());

	//자식 윈도우 생성 - 위치와 크기, 스타일 지정
	DrawingPaper *drawingPaper = new DrawingPaper(this);
	drawingPaper->move(200, this->menuBar->height() + 5 + 32);
	this->windows.Store(0, drawingPaper);

	FlowChartTemplate *fTemplate = new FlowChartTemplate(this);
	fTemplate->move(5, 5 + this->menuBar->height());
	this->windows.Store(1, fTemplate);

	this->painter = new QtPainter((Long)frameRect.width(), (Long)frameRect.height(), QColor(235, 235, 235));

	this->sheetManager = new SheetManager(drawingPaper);

	NShape *firstTitle = this->sheetManager->GetTitle(0);
	float windowCloseX = firstTitle->GetX() + firstTitle->GetWidth() - 26 - 3; //24=사각형길이,3=여유공간
	float windowCloseY = firstTitle->GetY() + 4;
	this->windowClose = new WindowClose(windowCloseX, windowCloseY, 26.0F, 23.0F, QColor(102, 204, 204),
		Qt::SolidLine, QColor(255, 255, 255));

	this->CreateStatusBar();
}

void FlowChartEditor::closeEvent(QCloseEvent *event) {
	QMessageBox messageBox(QMessageBox::Warning, QString::fromLocal8Bit("닫기"),
		QString::fromLocal8Bit("데이터가 손실될 수 있습니다. 파일을 모두 저장했는지 확인하십시오. 정말로 종료하시겠습니까?"),
		QMessageBox::Yes | QMessageBox::No, this);
	int ret = messageBox.exec();
	if (ret == QMessageBox::Yes) {
		if (this->menuBar != NULL) {
			delete this->menuBar;
		}
		if (this->statusBar != NULL) {
			delete this->statusBar;
		}
		if (this->painter != NULL) {
			delete this->painter;
		}
		if (this->sheetManager != NULL) {
			delete this->sheetManager;
		}

		Long i = 0;
		while (i < 2) {
			delete this->windows[i];
			i++;
		}

		QFrame::closeEvent(event);
	}
	else {
		event->ignore();
	}
}

void FlowChartEditor::resizeEvent(QResizeEvent *event) {
	QRect frameRect = this->frameRect();

	this->menuBar->resize(frameRect.width(), this->menuBar->height());
	this->statusBar->move(frameRect.x(), frameRect.bottom() - this->statusBar->height());
	this->statusBar->resize(frameRect.width(), this->statusBar->height());

	this->windows[0]->resize(frameRect.width() - 200, frameRect.height() - this->menuBar->height() - 32 - 20 - this->statusBar->height());
	this->windows[0]->repaint();

	this->windows[1]->resize(190, frameRect.height() - 20 - this->menuBar->height() - this->statusBar->height());
	this->windows[1]->repaint();
}

void FlowChartEditor::paintEvent(QPaintEvent *event) {
	QPainter painter(this);

	QRect frameRect = this->frameRect();

	this->painter->Resize(frameRect.width(), frameRect.height(), QColor(235, 235, 235));

	DrawingPaper *canvas = dynamic_cast<DrawingPaper *>(this->windows[0]);
	QColor windowBorderColor = canvas->windowBorderColor;
	//=======창 테두리=========
	QtGObjectFactory factory;
	GObject *pen = factory.MakePen(QBrush(windowBorderColor), 3);
	GObject *oldPen = this->painter->SelectObject(*pen);
	this->painter->Update();

	QPoint p1(canvas->x() + 1, canvas->y() - 2);
	QPoint p2(canvas->x() + 1 + canvas->width(), canvas->y() - 2);
	this->painter->DrawLine(p1, p2);

	this->painter->SelectObject(*oldPen);
	this->painter->Update();
	if (pen != 0) {
		delete pen;
	}
	//=======창 테두리=========

	FlowChartVisitor *visitor = new DrawVisitor(this->painter);

	this->sheetManager->Draw(visitor);
	//닫기
	this->windowClose->Accept(visitor);

	this->painter->Render(&painter, 0, 0);
}

void FlowChartEditor::mouseMoveEvent(QMouseEvent *event) {
	//윈도우 핀
	QRectF pinRect(this->windowClose->GetX(), this->windowClose->GetY(), this->windowClose->GetWidth(), this->windowClose->GetHeight());
	bool isContain = pinRect.contains(event->localPos());
	if (isContain == true) {
		this->windowClose->Paint(QColor(102, 255, 255), Qt::SolidLine, this->windowClose->GetBorderColor());
	}
	else {
		this->windowClose->Paint(QColor(102, 204, 204), Qt::SolidLine, this->windowClose->GetBorderColor());
	}
	this->repaint();
}

void FlowChartEditor::mouseReleaseEvent(QMouseEvent *event) {
	DrawingPaper *canvas = static_cast<DrawingPaper *>(this->windows[0]);
	QRectF pinRect(this->windowClose->GetX(), this->windowClose->GetY(), this->windowClose->GetWidth(), this->windowClose->GetHeight());
	bool isContain = pinRect.contains(event->localPos());
	if (isContain == true) {
		if (this->sheetManager->GetBinderLength() > 1) { //두 개 이상일 때만 닫을 수 있음.
			canvas->Close(); //현재 캔버스 저장하거나 안하거나 처리해줌.
		}
		else {
			QMessageBox messageBox(QMessageBox::Warning, QString::fromLocal8Bit("경고"),
				QString::fromLocal8Bit("모두 닫을 수 없습니다."), QMessageBox::Ok, this);
			int ret = messageBox.exec();
		}
	}
	else {
		Long current = this->sheetManager->Select(event->pos());
		if (current >= 0) {
			this->sheetManager->Change(current);
			this->sheetManager->ModifyTitles();

			NShape *currentTitle = this->sheetManager->GetTitle(current);
			float windowCloseX = currentTitle->GetX() + currentTitle->GetWidth() - 26 - 3; //24=사각형길이,3=여유공간
			float windowCloseY = currentTitle->GetY() + 4;
			this->windowClose->Move(windowCloseX, windowCloseY);
		}
	}
	this->repaint();
	canvas->repaint();
}

bool FlowChartEditor::eventFilter(QObject *o, QEvent *e) {
	if (o == this && e->type() == QEvent::ShortcutOverride) {
		e->accept();
	}
	return QFrame::eventFilter(o, e);
}

void FlowChartEditor::CommandRange(string text) { //문자열이 아닌 #define으로 선언해두고 쓰면 더 효율이 좋을까?
	FlowChartCommandFactory commandFactory(this);
	FlowChartCommand *command = commandFactory.Make(text); //action->text()
	if (command != NULL) {
		command->Execute();
		delete command;
	}
	DrawingPaper *drawingPaper = static_cast<DrawingPaper *>(this->windows[0]);

	QString mode = drawingPaper->GetCurrentMode();
	this->modeStatus->setText(mode);
	this->statusBar->repaint();

	this->repaint();
}

void FlowChartEditor::UpdateEditMenu() {
	DrawingPaper *canvas = static_cast<DrawingPaper *>(this->windows[0]);

	//복사, 잘라내기, 삭제
	//선택 상태가 아니면 비활성화한다.
	if (canvas->mode != DrawingPaper::SELECT) {
		this->copyAction->setEnabled(false);
		this->cutAction->setEnabled(false);
		this->deleteAction->setEnabled(false);
		this->selectAllAction->setEnabled(false);
	}
	else {
		this->copyAction->setEnabled(true);
		this->cutAction->setEnabled(true);
		this->deleteAction->setEnabled(true);
		this->selectAllAction->setEnabled(true);
	}

	//붙여넣기
	//클립보드 버퍼에 아무것도 없으면 비활성화한다.
	(canvas->clipboard->GetLength() < 1) ?
		(this->pasteAction->setEnabled(false)) : (this->pasteAction->setEnabled(true));

	//실행 취소
	//UndoMemory에 아무것도 없으면 비활성화한다.
	(canvas->historyController->GetUndoHistoryBook()->GetLength() < 1) ?
		(this->undoAction->setEnabled(false)) : (this->undoAction->setEnabled(true));

	//다시 실행
	//RedoMemory에 아무것도 없으면 비활성화한다.
	(canvas->historyController->GetRedoHistoryBook()->GetLength() < 1) ?
		(this->redoAction->setEnabled(false)) : (this->redoAction->setEnabled(true));

	//기호 위치 같게, 기호 크기 같게, 기호 간격 같게
	//선택된 기호가 1개 초과면 활성화한다.
	Long(*indexes);
	Long count;
	canvas->flowChart->GetSelecteds(&indexes, &count);
	if (count <= 1) {
		this->positionAction->setEnabled(false);
		this->sizeAction->setEnabled(false);
		this->intervalAction->setEnabled(false);
	}
	else {
		this->positionAction->setEnabled(true);
		this->sizeAction->setEnabled(true);
		this->intervalAction->setEnabled(true);
	}
}

void FlowChartEditor::UpdateControlArchitectureMenu() {
	DrawingPaper *canvas = static_cast<DrawingPaper *>(this->windows[0]);

	//순차구조
	//선택된 기호가 1개 초과면 활성화한다.
	Long(*indexes);
	Long count;
	canvas->flowChart->GetSelecteds(&indexes, &count);
	if (count <= 1) {
		this->sequenceArchitectureAction->setEnabled(false);
	}
	else {
		this->sequenceArchitectureAction->setEnabled(true);
	}

	//반복구조
	//선택된 기호가 1개 이상이면서 선택된 첫 번째 기호가 판단기호이면 활성화한다.
	this->iterationArchitectureAction->setEnabled(false);
	if (count > 1) {
		NShape *shape = dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper *>(this->windows[0])->
			flowChart)->GetAt(indexes[0]);
		if (dynamic_cast<Decision *>(shape)) {
			this->iterationArchitectureAction->setEnabled(true);
		}
	}

	//선택구조
	//선택된 기호가 1개 이상이면서 선택된 첫 번째 기호가 판단기호이면서 판단기호 밑 왼쪽에 기호가 하나 이상 있으면 활성화한다.
	this->selectionArchitectureAction->setEnabled(false);
	if (count > 1) {
		NShape *shape = dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper *>(this->windows[0])->
			flowChart)->GetAt(indexes[0]);
		if (dynamic_cast<Decision *>(shape)) {
			Long leftCount = 0;
			Long i = 1;
			while (i < count) {
				NShape *left = dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper *>(this->windows[0])->flowChart)->GetAt(indexes[i]);
				if (left->CenterOfGravityX() < shape->CenterOfGravityX()) {
					leftCount++;
				}
				i++;
			}
			if (leftCount > 0) {
				this->selectionArchitectureAction->setEnabled(true);
			}
		}
	}


	if (indexes != 0) {
		delete[] indexes;
	}
}

void FlowChartEditor::CreateActions() {
	//==================== File Menu ====================
	this->newAction = new QAction(QString::fromLocal8Bit(("새 파일(&N)")), this);
	this->newAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	connect(this->newAction, &QAction::triggered, this, [=]() { this->CommandRange("New"); });

	this->openAction = new QAction(QString::fromLocal8Bit(("열기(&O)")), this);
	this->openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
	connect(this->openAction, &QAction::triggered, this, [=]() { this->CommandRange("Open"); });

	this->saveAction = new QAction(QString::fromLocal8Bit(("저장(&S)")), this);
	this->saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	connect(this->saveAction, &QAction::triggered, this, [=]() { this->CommandRange("Save"); });

	this->saveAsAction = new QAction(QString::fromLocal8Bit(("다른 이름으로 저장(&A)...")), this);
	this->saveAsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_S));
	connect(this->saveAsAction, &QAction::triggered, this, [=]() { this->CommandRange("SaveAs"); });

	this->saveAsImageAction = new QAction(QString::fromLocal8Bit(("이미지(JPG)로 저장(&I)...")), this);
	this->saveAsImageAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_I));
	connect(this->saveAsImageAction, &QAction::triggered, this, [=]() { this->CommandRange("SaveAsImage"); });

	this->printAction = new QAction(QString::fromLocal8Bit(("인쇄(&P)...")), this);
	this->printAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
	connect(this->printAction, &QAction::triggered, this, [=]() { this->CommandRange("Print"); });

	this->exitAction = new QAction(QString::fromLocal8Bit(("끝내기(&X)...")), this);
	this->exitAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F4));
	connect(this->exitAction, &QAction::triggered, this, [=]() { this->CommandRange("Close"); });
	//==================== File Menu ====================

	//==================== Edit Menu ====================
	this->undoAction = new QAction(QString::fromLocal8Bit(("실행 취소(&U)")), this); //실행 취소(U) Ctrl + Z
	this->undoAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
	connect(this->undoAction, &QAction::triggered, this, [=]() { this->CommandRange("Undo"); });

	this->redoAction = new QAction(QString::fromLocal8Bit(("다시 실행(&R)")), this); //다시 실행(R) Ctrl + Y
	this->redoAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
	connect(this->redoAction, &QAction::triggered, this, [=]() { this->CommandRange("Redo"); });

	this->copyAction = new QAction(QString::fromLocal8Bit(("복사하기(&C)")), this); //복사하기(C) Ctrl + C
	this->copyAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
	connect(this->copyAction, &QAction::triggered, this, [=]() { this->CommandRange("Copy"); });

	this->pasteAction = new QAction(QString::fromLocal8Bit(("붙여넣기(&P)")), this); //붙여넣기(P) Ctrl + V
	this->pasteAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
	connect(this->pasteAction, &QAction::triggered, this, [=]() { this->CommandRange("Paste"); });

	this->cutAction = new QAction(QString::fromLocal8Bit(("잘라내기(&T)")), this); //잘라내기(T) Ctrl + X
	this->cutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
	connect(this->cutAction, &QAction::triggered, this, [=]() { this->CommandRange("Cut"); });

	this->deleteAction = new QAction(QString::fromLocal8Bit(("삭제(&L)")), this); //삭제(L) Del
	this->deleteAction->setShortcut(QKeySequence(Qt::Key_Delete));
	connect(this->deleteAction, &QAction::triggered, this, [=]() { this->CommandRange("Delete"); });

	this->selectAllAction = new QAction(QString::fromLocal8Bit(("모두 선택(&A)")), this); //모두 선택(A) Ctrl + A
	this->selectAllAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
	connect(this->selectAllAction, &QAction::triggered, this, [=]() { this->CommandRange("SelectAll"); });

	this->positionAction = new QAction(QString::fromLocal8Bit(("기호 위치 같게(&O)")), this); //기호 위치 같게(O)
	connect(this->positionAction, &QAction::triggered, this, [=]() { this->CommandRange("Position"); });

	this->sizeAction = new QAction(QString::fromLocal8Bit(("기호 크기 같게(&S)")), this); //기호 크기 같게(S)
	connect(this->sizeAction, &QAction::triggered, this, [=]() { this->CommandRange("Size"); });

	this->intervalAction = new QAction(QString::fromLocal8Bit(("기호 같격 같게(&I)")), this); //기호 간격 같게(I)
	connect(this->intervalAction, &QAction::triggered, this, [=]() { this->CommandRange("Interval"); });

	this->ruleKeepAction = new QAction(QString::fromLocal8Bit(("규칙 검사(&K)")), this); //규칙 검사(K)
	this->ruleKeepAction->setCheckable(true);
	this->ruleKeepAction->setChecked(true);
	connect(this->ruleKeepAction, &QAction::triggered, this, [=]() { this->CommandRange("RuleKeep"); });
	//==================== Edit Menu ====================

	//==================== Format Menu ====================
	this->fontSetAction = new QAction(QString::fromLocal8Bit(("글꼴(&F)...")), this);
	connect(this->fontSetAction, &QAction::triggered, this, [=]() { this->CommandRange("FontSet"); });

	this->pageSetAction = new QAction(QString::fromLocal8Bit(("페이지 설정(&U)...")), this);
	connect(this->pageSetAction, &QAction::triggered, this, [=]() { this->CommandRange("PageSet"); });
	//==================== Format Menu ====================

	//==================== Add Menu ====================
	this->drawingModeAction = new QAction(QString::fromLocal8Bit(("그리기 모드(&M)")), this); //그리기 모드(M) Ctrl + D
	this->drawingModeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
	this->drawingModeAction->setCheckable(true);
	this->drawingModeAction->setChecked(false);
	connect(this->drawingModeAction, &QAction::triggered, this, [=]() { this->CommandRange("DrawingMode"); });

	this->startTerminalSymbolAction = new QAction(QString::fromLocal8Bit(("시작 단말 기호(&S)")), this); //시작 단말 기호(S)
	connect(this->startTerminalSymbolAction, &QAction::triggered, this, [=]() { this->CommandRange("StartTerminalSymbol"); });

	this->preparationSymbolAction = new QAction(QString::fromLocal8Bit(("준비 기호(&P)")), this); //준비 기호(P)
	connect(this->preparationSymbolAction, &QAction::triggered, this, [=]() { this->CommandRange("PreparationSymbol"); });

	this->inputSymbolAction = new QAction(QString::fromLocal8Bit(("입력 기호(&I)")), this); //입력 기호(I)
	connect(this->inputSymbolAction, &QAction::triggered, this, [=]() { this->CommandRange("InputSymbol"); });

	this->processSymbolAction = new QAction(QString::fromLocal8Bit(("처리 기호(&R)")), this); //처리 기호(R)
	connect(this->processSymbolAction, &QAction::triggered, this, [=]() { this->CommandRange("ProcessSymbol"); });

	this->decisionSymbolAction = new QAction(QString::fromLocal8Bit(("판단 기호(&D)")), this); //판단 기호(D)
	connect(this->decisionSymbolAction, &QAction::triggered, this, [=]() { this->CommandRange("DecisionSymbol"); });

	this->outputSymbolAction = new QAction(QString::fromLocal8Bit(("출력 기호(&O)")), this); //출력 기호(O)
	connect(this->outputSymbolAction, &QAction::triggered, this, [=]() { this->CommandRange("OutputSymbol"); });

	this->stopTerminalSymbolAction = new QAction(QString::fromLocal8Bit(("종료 단말 기호(&T)")), this); //종료 단말 기호(T)
	connect(this->stopTerminalSymbolAction, &QAction::triggered, this, [=]() { this->CommandRange("StopTerminalSymbol"); });
	//==================== Add Menu ====================

	//==================== ControlArchitecture Menu ====================
	this->sequenceArchitectureAction = new QAction(QString::fromLocal8Bit(("순차구조(&S)")), this); //순차구조(S)
	connect(this->sequenceArchitectureAction, &QAction::triggered, this, [=]() { this->CommandRange("SequenceArchitecture"); });

	this->iterationArchitectureAction = new QAction(QString::fromLocal8Bit(("반복구조(&I)")), this); //반복구조(I)
	connect(this->iterationArchitectureAction, &QAction::triggered, this, [=]() { this->CommandRange("IterationArchitecture"); });

	this->selectionArchitectureAction = new QAction(QString::fromLocal8Bit(("선택구조(&E)")), this); //선택구조(E)
	connect(this->selectionArchitectureAction, &QAction::triggered, this, [=]() { this->CommandRange("SelectionArchitecture"); });
	//==================== ControlArchitecture Menu ====================

	//==================== Help Menu ====================
	this->helpAction = new QAction(QString::fromLocal8Bit(("도움말(&H)")), this); //도움말(H)
	connect(this->helpAction, &QAction::triggered, this, [=]() { this->CommandRange("Help"); });
	//==================== Help Menu ====================
}

void FlowChartEditor::CreateMenus() {
	this->menuBar = new QMenuBar(this);

	this->fileMenu = this->menuBar->addMenu(QString::fromLocal8Bit(("파일(&F)")));
	this->fileMenu->addAction(this->newAction); //새 파일(N) Ctrl + N
	this->fileMenu->addAction(this->openAction); //열기(O) Ctrl + O
	this->fileMenu->addAction(this->saveAction); //저장(S) Ctrl + S
	this->fileMenu->addAction(this->saveAsAction); //다른 이름으로 저장(A)... Ctrl + Alt + S
	this->fileMenu->addAction(this->saveAsImageAction); //이미지(JPG)로 저장(I)... Ctrl + Alt + I
	this->fileMenu->addSeparator(); //구분선
	this->fileMenu->addAction(this->printAction); //인쇄(P)... Ctrl + P
	this->fileMenu->addSeparator(); //구분선
	this->fileMenu->addAction(this->exitAction); //끝내기(X) Alt + F4

	this->editMenu = this->menuBar->addMenu(QString::fromLocal8Bit(("편집(&E)")));
	this->editMenu->addAction(this->undoAction); //실행 취소(U) Ctrl + Z
	this->editMenu->addAction(this->redoAction); //다시 실행(R) Ctrl + Y
	this->editMenu->addSeparator(); //구분선
	this->editMenu->addAction(this->copyAction); //복사하기(C) Ctrl + C
	this->editMenu->addAction(this->pasteAction); //붙여넣기(P) Ctrl + V
	this->editMenu->addAction(this->cutAction); //잘라내기(T) Ctrl + X
	this->editMenu->addAction(this->deleteAction); //삭제(L) Del
	this->editMenu->addSeparator(); //구분선
	this->editMenu->addAction(this->selectAllAction); //모두 선택(A) Ctrl + A
	this->editMenu->addSeparator(); //구분선
	this->editMenu->addAction(this->positionAction); //기호 위치 같게(O)
	this->editMenu->addAction(this->sizeAction); //기호 크기 같게(S)
	this->editMenu->addAction(this->intervalAction); //기호 간격 같게(I)
	this->editMenu->addSeparator(); //구분선
	this->editMenu->addAction(this->ruleKeepAction); //규칙 검사(K)
	connect(this->editMenu, &QMenu::aboutToShow, this, [=]() { this->UpdateEditMenu(); });

	this->formatMenu = this->menuBar->addMenu(QString::fromLocal8Bit(("서식(&O)")));
	this->formatMenu->addAction(this->fontSetAction); //글꼴(F)...
	this->formatMenu->addAction(this->pageSetAction); //페이지 설정(U)...

	this->addMenu = this->menuBar->addMenu(QString::fromLocal8Bit(("삽입(&A)")));
	this->addMenu->addAction(this->drawingModeAction); //그리기 모드(M) Ctrl + D
	this->addMenu->addSeparator(); //구분선
	this->addMenu->addAction(this->startTerminalSymbolAction); //시작 단말 기호(S)
	this->addMenu->addAction(this->preparationSymbolAction); //준비 기호(P)
	this->addMenu->addAction(this->inputSymbolAction); //입력 기호(I)
	this->addMenu->addAction(this->processSymbolAction); //처리 기호(R)
	this->addMenu->addAction(this->decisionSymbolAction); //판단 기호(D)
	this->addMenu->addAction(this->outputSymbolAction); //출력 기호(O)
	this->addMenu->addAction(this->stopTerminalSymbolAction); //종료 단말 기호(T)

	this->controlArchitectureMenu = this->menuBar->addMenu(QString::fromLocal8Bit(("제어구조(&C)")));
	this->controlArchitectureMenu->addAction(this->sequenceArchitectureAction); //순차구조(S)
	this->controlArchitectureMenu->addAction(this->iterationArchitectureAction); //반복구조(I)
	this->controlArchitectureMenu->addAction(this->selectionArchitectureAction); //선택구조(E)
	connect(this->controlArchitectureMenu, &QMenu::aboutToShow, this, [=]() { this->UpdateControlArchitectureMenu(); });

	this->helpMenu = this->menuBar->addMenu(QString::fromLocal8Bit(("도움말(&H)")));
	this->helpMenu->addAction(this->helpAction); //도움말(H)
}

void FlowChartEditor::CreateStatusBar() {
	this->statusBar = new QStatusBar(this);

	this->messageStatus = new QLabel(QString::fromLocal8Bit(""));
	this->statusBar->addPermanentWidget(this->messageStatus, 5);

	this->modeStatus = new QLabel(QString::fromLocal8Bit("IDLE"));
	this->statusBar->addPermanentWidget(this->modeStatus, 2);

	this->xStatus = new QLabel(QString::fromLocal8Bit("X: "));
	this->statusBar->addPermanentWidget(this->xStatus, 2);

	this->yStatus = new QLabel(QString::fromLocal8Bit("Y: "));
	this->statusBar->addPermanentWidget(this->yStatus, 2);

	Long zoomRate = dynamic_cast<DrawingPaper *>(this->windows[0])->zoom->GetRate();
	QString zoomString = QString::number(zoomRate);
	zoomString += '%';
	this->zoomStatus = new QLabel(zoomString);
	this->statusBar->addPermanentWidget(this->zoomStatus, 2);

	this->adStatus1 = new QLabel(QString::fromLocal8Bit("나아 코칭"));
	this->adStatus1->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	this->statusBar->addPermanentWidget(this->adStatus1, 2);

	this->adStatus2 = new QLabel(QString::fromLocal8Bit("02)587-9424"));
	this->statusBar->addPermanentWidget(this->adStatus2, 1);
}