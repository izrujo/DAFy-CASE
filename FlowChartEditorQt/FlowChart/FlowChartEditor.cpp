/******************************************************************
* 파일 이름 : FlowChartEditor.cpp
* 기능 :
* 작성자 : 송윤창
* 작성일자 :
*******************************************************************/

#include "FlowChartEditor.h"
#include "DrawingPaper.h"
#include "FlowChartTemplate.h"
#include "Tool.h"
#include "Label.h"
#include "resource.h"
#include <afxdlgs.h> // CFileDialog
#include "MemoryController.h"
#include "Memory.h"
#include "FlowChartKeyActions.h"
#include "FlowChartKeyActionFactory.h"
#include "FlowChartCommands.h"
#include "FlowChartCommandFactory.h"
#include "FlowChartFont.h"
#include "FlowChart.h"
#include "Clipboard.h"
#include "StatusBar.h"
#include "Zoom.h"
#include "Decision.h"
#include "TutorialForm.h"
#include "ToolTip.h"
#include "EditorIntroForm.h"
#pragma warning (disable : 4996)

// 메세지 맵
BEGIN_MESSAGE_MAP(FlowChartEditor, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_DROPFILES()
	ON_COMMAND_RANGE(IDM_FILE_SAVE, IDM_HELP_TUTORIAL, OnCommandRange)
	ON_COMMAND(IDM_FILE_EXIT, OnClose)
	//=======메뉴 활성화/비활성화=======
	ON_UPDATE_COMMAND_UI(IDM_ADD_UNMODE, OnUpdateDrawingUnModeCommand)
	ON_UPDATE_COMMAND_UI(IDM_ADD_MODE, OnUpdateDrawingModeCommand)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_EDIT_COPY, IDM_EDIT_DELETE, OnUpdateCopyCutDeleteCommand)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_PASTE, OnUpdatePasteCommand)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_UNDO, OnUpdateUndoCommand)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_REDO, OnUpdateRedoCommand)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_POSITION, OnUpdatePositionCommand)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_SIZE, OnUpdateSizeCommand)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_INTERVAL, OnUpdateIntervalCommand)
	ON_UPDATE_COMMAND_UI(IDM_CONTROL_SEQUENCE, OnUpdateSequenceCommand)
	ON_UPDATE_COMMAND_UI(IDM_CONTROL_ITERATION, OnUpdateIterationCommand)
	ON_UPDATE_COMMAND_UI(IDM_CONTROL_SELECTION, OnUpdateSelectionCommand)
	//=================================
	ON_WM_MENUSELECT() //메뉴 선택

END_MESSAGE_MAP()

FlowChartEditor::FlowChartEditor() {
	this->font = NULL;
	this->statusBar = NULL;
	this->toolTip = NULL;
}

int FlowChartEditor::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	
	CRect rect, rect2;
	this->GetClientRect(&rect);
	this->GetClientRect(&rect2);

	this->windows.Store(0, new DrawingPaper);
	this->windows.Store(1, new FlowChartTemplate);
	this->windows.Store(2, NULL);

	this->windows[0]->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS, rect, this, 1000);
	this->windows[1]->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS, rect, this, 2000);

	this->isUnModeMenuEnabled = FALSE;

	HICON flowChartEditorIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	this->SetIcon(flowChartEditorIcon, TRUE);

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

	menu.LoadMenuA(IDR_MENU);
	SetMenu(&menu);

	DragAcceptFiles(TRUE);

	this->font = new FlowChartFont(this);

	//Accelerators
	this->hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR));

	return 0;
}

void FlowChartEditor::OnClose() {
	Long i = 0;
	while (i < this->windows.GetLength()) {
		if (this->windows[i] = NULL) {
			delete this->windows[i];
		}
		this->windows[i] = NULL;
		i++;
	}
	if (this->font != NULL) {
		delete this->font;
	}
	if (this->statusBar != NULL) {
		delete this->statusBar;
	}
	if (this->toolTip != NULL) {
		this->toolTip->Destroy();
	}
	//Accelerators
	DestroyAcceleratorTable(this->hAccel);

	CFrameWnd::OnClose();
}

void FlowChartEditor::OnSize(UINT nType, int cx, int cy) {
	CRect rect, rect2;
	this->GetClientRect(&rect);
	this->GetClientRect(&rect2);

	rect.left = 205;
	rect2.right = 200;

	//상태 표시줄
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

	if (this->windows[0] != NULL && this->windows[1] != NULL) { //최대화해서 출력하니 OnClose 이후에 OnSize가 호출.
		this->windows[1]->MoveWindow(rect2);
		this->windows[0]->MoveWindow(rect);
	}

	CFrameWnd::OnSize(nType, cx, cy);
}

void FlowChartEditor::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) {
	CWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);
}

void FlowChartEditor::OnCommandRange(UINT uID) {
	FlowChartCommandFactory commandFactory(this);
	FlowChartCommand *command = commandFactory.Make(uID);
	if (command != NULL) {
		command->Execute();
		delete command;
	}
	this->Invalidate();
}

//Accelerators
BOOL FlowChartEditor::PreTranslateMessage(MSG *pMsg) {
	if (this->hAccel != NULL) {
		if (::TranslateAccelerator(*(AfxGetMainWnd()), this->hAccel, pMsg)) {
			return TRUE;
		}
	}
	return CWnd::PreTranslateMessage(pMsg);
}

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
		Shape *shape = dynamic_cast<FlowChart*>(dynamic_cast<DrawingPaper*>(this->windows[0])->
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
		Shape *shape = dynamic_cast<FlowChart*>(dynamic_cast<DrawingPaper*>(this->windows[0])->
			flowChart)->GetAt(indexes[0]);
		if (dynamic_cast<Decision*>(shape)) {
			Long leftCount = 0;
			Long i = 1;
			while (i < count) {
				Shape *left = dynamic_cast<FlowChart*>(dynamic_cast<DrawingPaper*>(this->windows[0])->flowChart)->GetAt(indexes[i]);
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