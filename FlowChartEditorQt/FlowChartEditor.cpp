#include "FlowChartEditor.h"
#include "FlowChart/FlowChartCommandFactory.h"
#include "FlowChart/FlowChartCommands.h"
#include "FlowChart/DrawingPaper.h"
#include "FlowChart/FlowChartTemplate.h"
#include "FlowChart/WindowTitle.h"

#include <qmenubar.h>
#include <qevent.h>
#include <qpainter.h>

FlowChartEditor::FlowChartEditor(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);

	this->setMouseTracking(true);
	
	this->menuBar = NULL;

	QRect frameRect = this->frameRect();
	
	this->CreateActions();
	this->CreateMenus();
	this->menuBar->resize(frameRect.width(), this->menuBar->height());

	//자식 윈도우 생성 - 위치와 크기, 스타일 지정
	DrawingPaper *drawingPaper = new DrawingPaper(this);
	drawingPaper->move(200, 1 + this->menuBar->height());
	this->windows.Store(0, drawingPaper);

	FlowChartTemplate *fTemplate = new FlowChartTemplate(this);
	fTemplate->move(5, 5 + this->menuBar->height());
	this->windows.Store(1, fTemplate);
	//this->windows.Store(2, NULL);

	//this->isUnModeMenuEnabled = FALSE; //메뉴 컨트롤에 관한 속성 초기화

	/*아이콘
	HICON flowChartEditorIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	this->SetIcon(flowChartEditorIcon, TRUE);
	*/

	/*상태 표시줄
	HINSTANCE hInstance = (HINSTANCE)::GetWindowLong(this->m_hWnd, GWL_HINSTANCE);
	this->GetClientRect(rect);
	// Create the status bar.
	HWND hWndStatusBar = ::CreateWindowEx(0, STATUSCLASSNAME, (PCTSTR)NULL, SBARS_SIZEGRIP | WS_CHILD | WS_VISIBLE | WS_BORDER,
		0, 0, 0, 0, this->m_hWnd, (HMENU)3000, hInstance, NULL);

	this->statusBar = new StatusBar(6, hWndStatusBar);

	int statusBars[7];
	statusBars[0] = rect.right - 700;
	statusBars[1] = statusBars[0] + 100;
	statusBars[2] = statusBars[1] + 100;
	statusBars[3] = statusBars[2] + 100;
	statusBars[4] = statusBars[3] + 100;
	statusBars[5] = statusBars[4] + 200;
	statusBars[6] = statusBars[5] + 100;
	// Tell the status bar to create the window parts.
	::SendMessage(this->statusBar->GetHandle(), SB_SETPARTS, (WPARAM)7, (LPARAM)statusBars);

	this->statusBar->Add(0, String(""));

	this->statusBar->Add(1, String(""));

	this->statusBar->Add(2, String("X: "));
	this->statusBar->Add(3, String("Y: "));
	CString rate;
	Long zoomRate = dynamic_cast<DrawingPaper*>(this->windows[0])->zoom->GetRate();
	rate.Format("%d", zoomRate);
	rate += "%";
	this->statusBar->Add(4, String((LPCTSTR)rate));

	this->statusBar->Add(5, String("문의 : 02)587-9424"));
	this->statusBar->Add(6, String("나아 코칭"));
	this->statusBar->Print();
	*/

	/*상단 메뉴
	menu.LoadMenuA(IDR_MENU);
	SetMenu(&menu);
	*/

	//파일처리에 관련된 것인듯
	//DragAcceptFiles(TRUE);

	//폰트
	//this->font = new FlowChartFont(this);

	//Accelerators
	//this->hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR));
}

void FlowChartEditor::closeEvent(QCloseEvent *event) {
	if (this->menuBar != NULL) {
		delete this->menuBar;
	}

	/*자식 윈도우 배열
	Long i = 0;
	while (i < this->windows.GetLength()) {
		if (this->windows[i] = NULL) {
			delete this->windows[i];
		}
		this->windows[i] = NULL;
		i++;
	}
	*/
	/*폰트
	if (this->font != NULL) {
		delete this->font;
	}
	*/
	/*상태 표시줄
	if (this->statusBar != NULL) {
		delete this->statusBar;
	}
	*/
	/*툴팁
	if (this->toolTip != NULL) {
		this->toolTip->Destroy();
	}
	*/
	//Accelerators
	//DestroyAcceleratorTable(this->hAccel);

	QFrame::closeEvent(event);
}

void FlowChartEditor::resizeEvent(QResizeEvent *event) {
	QRect frameRect = this->frameRect();

	this->menuBar->resize(frameRect.width(), this->menuBar->height());

	this->windows[0]->resize(frameRect.width() - 200, frameRect.height() - this->menuBar->height() + 1);
	this->windows[0]->repaint();
	
	Long height = frameRect.height() - this->menuBar->height() - 20;
	this->windows[1]->resize(190, frameRect.height() - this->menuBar->height() - 20);
	this->windows[1]->repaint();
	/*frameRect 값을 조정?
	rect.left = 205;
	rect2.right = 200;
	*/

	/*상태 표시줄
	Long gap;
	WINDOWPLACEMENT sbPosition;
	int statusBars[7];
	HWND hWndStatus = this->statusBar->GetHandle();
	if (hWndStatus != NULL) {
		::GetWindowPlacement(hWndStatus, &sbPosition);
		gap = sbPosition.rcNormalPosition.bottom - sbPosition.rcNormalPosition.top;
		rect.bottom = rect.bottom - gap;
		rect2.bottom = rect2.bottom - gap;
		::MoveWindow(hWndStatus, 0, rect.bottom, rect.right, gap, FALSE);

		statusBars[0] = rect.right - 700;
		statusBars[1] = statusBars[0] + 100;
		statusBars[2] = statusBars[1] + 100;
		statusBars[3] = statusBars[2] + 100;
		statusBars[4] = statusBars[3] + 100;
		statusBars[5] = statusBars[4] + 200;
		statusBars[6] = statusBars[5] + 100;
		::SendMessage(hWndStatus, SB_SETPARTS, (WPARAM)7, (LPARAM)statusBars);
	}
	*/
	/*mfc에서 오류 해결인듯
	if (this->windows[0] != NULL && this->windows[1] != NULL) { //최대화해서 출력하니 OnClose 이후에 OnSize가 호출.
		this->windows[1]->MoveWindow(rect2);
		this->windows[0]->MoveWindow(rect);
	}
	*/
}

void FlowChartEditor::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.fillRect(this->frameRect(), QColor(235, 235, 235));
}

/*우클릭 메뉴인가?
void FlowChartEditor::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) {
	CWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);
}
*/

/*메뉴 커맨드
void FlowChartEditor::OnCommandRange(UINT uID) {
	FlowChartCommandFactory commandFactory(this);
	FlowChartCommand *command = commandFactory.Make(uID);
	if (command != NULL) {
		command->Execute();
		delete command;
	}
	this->Invalidate();
}
*/

/*Accelerators
BOOL FlowChartEditor::PreTranslateMessage(MSG *pMsg) {
	if (this->hAccel != NULL) {
		if (::TranslateAccelerator(*(AfxGetMainWnd()), this->hAccel, pMsg)) {
			return TRUE;
		}
	}
	return CWnd::PreTranslateMessage(pMsg);
}
*/

/* 파일 로드 했을 때의 처리 내용 함수인듯
void FlowChartEditor::OnDropFiles(HDROP hDropInfo) {
	char filePath[256];
	CString fileName;
	int count;
	(static_cast<DrawingPaper *>(this->windows[0]))->New();

	count = ::DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	if (count > 0) {
		DragQueryFile(hDropInfo, 0, filePath, 255);
		this->fileOpenPath = filePath;
		(static_cast<DrawingPaper *>(this->windows[0]))->Load(this->fileOpenPath);
		fileName = this->fileOpenPath + " - FlowChart";
		this->SetWindowText(fileName);
		(static_cast<DrawingPaper *>(this->windows[0]))->SetFocus();
		this->RedrawWindow();
	}
}
*/

/* 메뉴 컨트롤
void FlowChartEditor::OnUpdateDrawingUnModeCommand(CCmdUI *cCmdUI) {
	if (this->isUnModeMenuEnabled == FALSE) { //해제가 비활성화되어야 하면
		cCmdUI->Enable(FALSE); //해제를 비활성화한다.
	}
	else {
		cCmdUI->Enable(TRUE); //해제를 활성화한다.
	}
}

void FlowChartEditor::OnUpdateDrawingModeCommand(CCmdUI *cCmdUI) {
	if (this->isUnModeMenuEnabled == FALSE) { //해제가 비활성화되어야 하면
		cCmdUI->Enable(TRUE); //설정을 활성화한다.
	}
	else {
		cCmdUI->Enable(FALSE); //설정을 비활성화한다.
	}
}

void FlowChartEditor::OnUpdateCopyCutDeleteCommand(CCmdUI *cCmdUI) {
	if (dynamic_cast<DrawingPaper*>(this->windows[0])->mode != DrawingPaper::SELECT) { //선택 상태가 아니면 비활성화한다.
		cCmdUI->Enable(FALSE);
	}
	else { //선택 상태면 활성화한다.
		cCmdUI->Enable(TRUE);
	}
}

void FlowChartEditor::OnUpdatePasteCommand(CCmdUI *cCmdUI) {
	if (dynamic_cast<DrawingPaper*>(this->windows[0])->clipboard->GetLength() <= 0) { //클립보드 버퍼에 아무것도 없으면 비활성화한다.
		cCmdUI->Enable(FALSE);
	}
	else {
		cCmdUI->Enable(TRUE);
	}
}

void FlowChartEditor::OnUpdateUndoCommand(CCmdUI *cCmdUI) {
	if (dynamic_cast<DrawingPaper*>(this->windows[0])->memoryController->GetUndoMemory()->GetLength() <= 0) { //UndoMemory에 아무것도 없으면 비활성화한다.
		cCmdUI->Enable(FALSE);
	}
	else {
		cCmdUI->Enable(TRUE);
	}
}

void FlowChartEditor::OnUpdateRedoCommand(CCmdUI *cCmdUI) {
	if (dynamic_cast<DrawingPaper*>(this->windows[0])->memoryController->GetRedoMemory()->GetLength() <= 0) { //RedoMemory에 아무것도 없으면 비활성화한다.
		cCmdUI->Enable(FALSE);
	}
	else {
		cCmdUI->Enable(TRUE);
	}
}

void FlowChartEditor::OnUpdatePositionCommand(CCmdUI *cCmdUI) {
	Long(*indexes);
	Long count;
	(dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->windows[0])->flowChart))->GetSelecteds(&indexes, &count);

	if (count > 1) {
		cCmdUI->Enable(TRUE);
	}
	else {
		cCmdUI->Enable(FALSE);
	}
}

void FlowChartEditor::OnUpdateSizeCommand(CCmdUI *cCmdUI) {
	Long(*indexes);
	Long count;
	(dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->windows[0])->flowChart))->GetSelecteds(&indexes, &count);

	if (count > 1) {
		cCmdUI->Enable(TRUE);
	}
	else {
		cCmdUI->Enable(FALSE);
	}
}

void FlowChartEditor::OnUpdateIntervalCommand(CCmdUI *cCmdUI) {
	Long(*indexes);
	Long count;
	(dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->windows[0])->flowChart))->GetSelecteds(&indexes, &count);

	if (count > 1) {
		cCmdUI->Enable(TRUE);
	}
	else {
		cCmdUI->Enable(FALSE);
	}
}

void FlowChartEditor::OnUpdateSequenceCommand(CCmdUI *cCmdUI) {
	Long(*indexes);
	Long count;
	(dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->windows[0])->flowChart))->GetSelecteds(&indexes, &count);

	if (count > 1) {
		cCmdUI->Enable(TRUE);
	}
	else {
		cCmdUI->Enable(FALSE);
	}
}

void FlowChartEditor::OnUpdateIterationCommand(CCmdUI *cCmdUI) {
	Long(*indexes);
	Long count;
	(dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->windows[0])->flowChart))->GetSelecteds(&indexes, &count);
	if (count > 1) {
		NShape *shape = dynamic_cast<FlowChart*>(dynamic_cast<DrawingPaper*>(this->windows[0])->
			flowChart)->GetAt(indexes[0]);
		if (dynamic_cast<Decision*>(shape)) {
			cCmdUI->Enable(TRUE);
		}
		else {
			cCmdUI->Enable(FALSE);
		}
	}
}

void FlowChartEditor::OnUpdateSelectionCommand(CCmdUI *cCmdUI) {
	Long(*indexes);
	Long count;
	(dynamic_cast<FlowChart *>(dynamic_cast<DrawingPaper*>(this->windows[0])->flowChart))->GetSelecteds(&indexes, &count);
	if (count > 1) {
		NShape *shape = dynamic_cast<FlowChart*>(dynamic_cast<DrawingPaper*>(this->windows[0])->
			flowChart)->GetAt(indexes[0]);
		if (dynamic_cast<Decision*>(shape)) {
			Long leftCount = 0;
			Long i = 1;
			while (i < count) {
				NShape *left = dynamic_cast<FlowChart*>(dynamic_cast<DrawingPaper*>(this->windows[0])->flowChart)->GetAt(indexes[i]);
				if (left->CenterOfGravityX() < shape->CenterOfGravityX()) {
					leftCount++;
				}
				i++;
			}
			if (leftCount > 0) {
				cCmdUI->Enable(TRUE);
			}
			else {
				cCmdUI->Enable(FALSE);
			}
		}
		else {
			cCmdUI->Enable(FALSE);
		}
	}
}
*/

void FlowChartEditor::CommandRange(string text) { //문자열이 아닌 #define으로 선언해두고 쓰면 더 효율이 좋을까?
	FlowChartCommandFactory commandFactory(this);
	FlowChartCommand *command = commandFactory.Make(text); //action->text()
	if (command != NULL) {
		command->Execute();
		delete command;
	}

	this->repaint();
}

void FlowChartEditor::CreateActions() {
	//this->fontSetAction->setStatusTip(tr("Set Font"));

	//==================== File Menu ====================
	this->newAction = new QAction(QString::fromLocal8Bit(("새 파일(&N)")), this);
	connect(this->newAction, &QAction::triggered, this, [=]() { this->CommandRange("New"); });

	this->openAction = new QAction(QString::fromLocal8Bit(("열기(&O)")), this);
	connect(this->openAction, &QAction::triggered, this, [=]() { this->CommandRange("Open"); });

	this->saveAction = new QAction(QString::fromLocal8Bit(("저장(&S)")), this);
	connect(this->saveAction, &QAction::triggered, this, [=]() { this->CommandRange("Save"); });

	this->saveAsAction = new QAction(QString::fromLocal8Bit(("다른 이름으로 저장(&A)...")), this);
	connect(this->saveAsAction, &QAction::triggered, this, [=]() { this->CommandRange("SaveAs"); });

	this->saveAsImageAction = new QAction(QString::fromLocal8Bit(("이미지(JPG)로 저장(&I)...")), this);
	connect(this->saveAsImageAction, &QAction::triggered, this, [=]() { this->CommandRange("SaveAsImage"); });

	this->printAction = new QAction(QString::fromLocal8Bit(("인쇄(&P)...")), this);
	connect(this->printAction, &QAction::triggered, this, [=]() { this->CommandRange("Print"); });

	this->exitAction = new QAction(QString::fromLocal8Bit(("끝내기(&X)...")), this);
	connect(this->exitAction, &QAction::triggered, this, [=]() { this->CommandRange("Exit"); });
	//==================== File Menu ====================

	//==================== Edit Menu ====================
	this->undoAction = new QAction(QString::fromLocal8Bit(("실행 취소(&U)")), this); //실행 취소(U) Ctrl + Z
	connect(this->undoAction, &QAction::triggered, this, [=]() { this->CommandRange("Undo"); });

	this->redoAction = new QAction(QString::fromLocal8Bit(("다시 실행(&R)")), this); //다시 실행(R) Ctrl + Y
	connect(this->redoAction, &QAction::triggered, this, [=]() { this->CommandRange("Redo"); });

	this->copyAction = new QAction(QString::fromLocal8Bit(("복사하기(&C)")), this); //복사하기(C) Ctrl + C
	connect(this->copyAction, &QAction::triggered, this, [=]() { this->CommandRange("Copy"); });

	this->pasteAction = new QAction(QString::fromLocal8Bit(("붙여넣기(&P)")), this); //붙여넣기(P) Ctrl + V
	connect(this->pasteAction, &QAction::triggered, this, [=]() { this->CommandRange("Paste"); });

	this->cutAction = new QAction(QString::fromLocal8Bit(("잘라내기(&T)")), this); //잘라내기(T) Ctrl + X
	connect(this->cutAction, &QAction::triggered, this, [=]() { this->CommandRange("Cut"); });

	this->deleteAction = new QAction(QString::fromLocal8Bit(("삭제(&L)")), this); //삭제(L) Del
	connect(this->deleteAction, &QAction::triggered, this, [=]() { this->CommandRange("Delete"); });

	this->selectAllAction = new QAction(QString::fromLocal8Bit(("모두 선택(&A)")), this); //모두 선택(A) Ctrl + A
	connect(this->selectAllAction, &QAction::triggered, this, [=]() { this->CommandRange("SelectAll"); });

	this->positionAction = new QAction(QString::fromLocal8Bit(("기호 위치 같게(&O)")), this); //기호 위치 같게(O)
	connect(this->positionAction, &QAction::triggered, this, [=]() { this->CommandRange("Position"); });

	this->sizeAction = new QAction(QString::fromLocal8Bit(("기호 크기 같게(&S)")), this); //기호 크기 같게(S)
	connect(this->sizeAction, &QAction::triggered, this, [=]() { this->CommandRange("Size"); });

	this->intervalAction = new QAction(QString::fromLocal8Bit(("기호 같격 같게(&I)")), this); //기호 간격 같게(I)
	connect(this->intervalAction, &QAction::triggered, this, [=]() { this->CommandRange("Interval"); });
	//==================== Edit Menu ====================

	//==================== Format Menu ====================
	this->fontSetAction = new QAction(QString::fromLocal8Bit(("글꼴(&F)...")), this);
	connect(this->fontSetAction, &QAction::triggered, this, [=]() { this->CommandRange("FontSet"); });

	this->pageSetAction = new QAction(QString::fromLocal8Bit(("페이지 설정(&U)...")), this);
	connect(this->pageSetAction, &QAction::triggered, this, [=]() { this->CommandRange("PageSet"); });
	//==================== Format Menu ====================

	//==================== Add Menu ====================
	this->drawingModeAction = new QAction(QString::fromLocal8Bit(("그리기 모드(&M)")), this); //그리기 모드(M) Ctrl + D
	connect(this->drawingModeAction, &QAction::triggered, this, [=]() { this->CommandRange("DrawingMode"); });

	this->drawingUnModeAction = new QAction(QString::fromLocal8Bit(("그리기 모드 해제(&U)")), this); //그리기 모드 해제 ESC
	connect(this->drawingUnModeAction, &QAction::triggered, this, [=]() { this->CommandRange("DrawingUnMode"); });

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

	this->formatMenu = this->menuBar->addMenu(QString::fromLocal8Bit(("서식(&O)")));
	this->formatMenu->addAction(this->fontSetAction); //글꼴(F)...
	this->formatMenu->addAction(this->pageSetAction); //페이지 설정(U)...

	this->addMenu = this->menuBar->addMenu(QString::fromLocal8Bit(("삽입(&A)")));
	this->addMenu->addAction(this->drawingModeAction); //그리기 모드(M) Ctrl + D
	this->addMenu->addAction(this->drawingUnModeAction); //그리기 모드 해제 ESC
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

	this->helpMenu = this->menuBar->addMenu(QString::fromLocal8Bit(("도움말(&H)")));
}