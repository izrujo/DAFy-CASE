/******************************************************************
* 파일 이름 : FlowChartEditor.h
* 기능 : 
* 작성자 : 송윤창
* 작성일자 :
*******************************************************************/

#ifndef _FLOWCHARTEDITOR_H
#define _FLOWCHARTEDITOR_H
#include <afxwin.h>

#include "Array.h"

#define INVALID_SPACE 5

class DrawingPaper;
class FlowChartTemplate;
class FlowChartFont;
class StatusBar;
class ToolTip;

class FlowChartEditor: public CFrameWnd{
public:
	FlowChartEditor();

public:
	Array<CWnd*> windows;	
	CMenu menu;
	CString fileOpenPath;
	FlowChartFont *font;
	BOOL isUnModeMenuEnabled;
	//HWND hWndStatus;
	StatusBar *statusBar;
	ToolTip *toolTip;
private:
	HACCEL hAccel; //Accelerator
	
protected:
	BOOL PreTranslateMessage(MSG *pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnDropFiles( HDROP hDropInfo );
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnCommandRange(UINT uID);

	afx_msg void OnUpdateDrawingUnModeCommand(CCmdUI *cCmdUI);
	afx_msg void OnUpdateDrawingModeCommand(CCmdUI *cCmdUI);
	afx_msg void OnUpdateCopyCutDeleteCommand(CCmdUI *cCmdUI);
	afx_msg void OnUpdatePasteCommand(CCmdUI *cCmdUI);
	afx_msg void OnUpdateUndoCommand(CCmdUI *cCmdUI);
	afx_msg void OnUpdateRedoCommand(CCmdUI *cCmdUI);
	afx_msg void OnUpdatePositionCommand(CCmdUI *cCmdUI);
	afx_msg void OnUpdateSizeCommand(CCmdUI *cCmdUI);
	afx_msg void OnUpdateIntervalCommand(CCmdUI *cCmdUI);
	afx_msg void OnUpdateSequenceCommand(CCmdUI *cCmdUI);
	afx_msg void OnUpdateIterationCommand(CCmdUI *cCmdUI);
	afx_msg void OnUpdateSelectionCommand(CCmdUI *cCmdUI);

	DECLARE_MESSAGE_MAP()          //윈32에서 ON_COMMAND ON_NOTIFY 같은것을 정의
};

#endif _FLOWCHARTEDITOR_H