#ifndef _DRAWINGPAPER_H
#define _DRAWINGPAPER_H

// 팝업창
#define IDM_AE_SEQUENCE 10001
#define IDM_AE_SELECION 10002
#define IDM_AE_ITERATION 10003
#define IDM_AE_MOVEMAKE 10004
#define IDM_AE_SIZEMAKE 10005
#define IDM_AE_INTERVALMAKE 1006

#include <QtWidgets/QFrame>
#include "Array.h"
#include "Shape.h"
#include "../Notepad/Subject.h"

typedef unsigned long int DWORD;
typedef signed long int Long;

class Label;
class Tool;
class Painter;
class Label;
class Clipboard;

class ScrollController;
class HistoryController;
class Registrar;

class Zoom;
class QMenu;

class VariableList;

class DrawingPaper : public QFrame, public Subject
{
	Q_OBJECT

public:
	enum { IDLE, SELECT, DRAWING, MOVING, SIZING };

public:
	DrawingPaper(QWidget *parent = Q_NULLPTR);
	~DrawingPaper();


	void DrawSelectingArea();
	void DrawActiveShape(NShape *entity); // 라인은 모양이 다 다르다.
	void DrawActiveShape2(NShape *entity); // 라인은 모양이 다 다르다.

	void DrawSelectionMark(QPoint(*points), Long count);
	void DrawSelectionMark2(QPoint(*points), Long count);
	void FillSelectionMark(QPoint point);

	//void Move(Long xDistance, Long yDistance); //원래 정의 없었음.
	void New();
	Long Save(QString fileName);
	Long Load(QString fileName);
	void Close();
	QCursor GetCursor(QPoint point); //커서
	
	QString GetCurrentMode(); //200424 statusBar mode status

public:
	NShape *templateSelected;
	Painter *painter;

	//19.09.16 private에서 public : 스크롤 처리 위함
	NShape *flowChart; // 사용자들이 스텐실을 등록하기 위해서 패턴을 사용함
	ScrollController *scrollController;

	/////////////////////////////////////////////////////
	// 마우스 시작
	float startX;
	float startY;

	// 계속 움직일 때
	float currentX;
	float currentY;
	/////////////////////////////////////////////////////
	Long indexOfSelected;

	int mode; //2019.09.20 MemoryController에서 Undo 연산을 위해 옮김. 서로 속성을 가지면 혹시 private에서도 되려나?

	Label *label;
	Tool *tool;

	HistoryController *historyController;
	Registrar *registrar;

	Clipboard *clipboard;
	Zoom *zoom;
	NShape *a4Paper;

	QMenu *popup; //팝업메뉴(우클릭)

	bool drawSelectingAreaFlag;

	QColor windowBorderColor;

	VariableList *variableList;
private:
	friend class Label;
	friend class FlowChartTemplate;

	friend class ResizingTool;
	friend class MovingTool;
	friend class DrawingTool;
	friend class SelectingTool;
	friend class ToolFactory;

	friend class SequenceMake;
	friend class IterationMake;
	friend class SelectionMake;

	friend class SizeMake;
	friend class IntervalMake;
	friend class MoveMake;

	friend class ErasingTool;

	friend class File;

	friend class KeyFactory;
	friend class DeleteKey;
	friend class UpKey;
	friend class DownKey;
	friend class LeftKey;
	friend class RightKey;
	friend class EscapeKey;

	friend class Clipboard;

private:
	int hitCode; //도형 선택 종류 관련

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	void mousePressEvent(QMouseEvent *event); //마우스 왼쪽 버튼 다운, 오른쪽(콘텍스트메뉴)은?
	void mouseMoveEvent(QMouseEvent *event); //tracking 설정이 디폴트면 마우스 아무거나 눌렀을 때만 호출됨.
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void focusOutEvent(QFocusEvent *event);
	void focusInEvent(QFocusEvent *event);
public slots:
	void OnContextMenu(const QPoint &pos);
	
	void OnMoveMakeMenuClick();
	void OnSizeMakeMenuClick();
	void OnIntervalMakeMenuClick();
	void OnSequenceMenuClick();
	void OnIterationMenuClick();
	void OnSelectionMenuClick();
};

#endif  // _DRWAINGPAPER_H