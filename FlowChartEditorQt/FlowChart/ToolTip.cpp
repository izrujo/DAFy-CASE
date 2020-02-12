#include "ToolTip.h"
#include "Shape.h"

#include "FlowChart.h"
#include "FlowChartEditor.h"
#include "DrawingPaper.h"
#include <Imm.h>

#include "../Notepad/GlyphFactory.h"
#include "../Notepad/Glyph.h"
#include "../Notepad/Row.h"
#include "../Notepad/CharacterMetrics.h"
#include "Process.h"
#include "Creator.h"
#include "SizeController.h"
#include "VariableList.h"
#include "Preparation.h"
#include "../Notepad/GlyphFactory.h"
#include "../Notepad/Font.h"

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "imm32")
// ¸Þ¼¼Áö ¸Ê
BEGIN_MESSAGE_MAP(ToolTip, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

ToolTip* ToolTip::instance = 0;

ToolTip* ToolTip::Instance(char *text, COLORREF color)
{
	if (instance == 0)
	{
		instance = new ToolTip(text, color);
	}
	return instance;
}

ToolTip* ToolTip::Instance()
{
	if (instance == 0)
	{
		instance = new ToolTip;
	}
	return instance;
}


ToolTip::ToolTip() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

ToolTip::ToolTip(char *text, COLORREF color)
	: NotepadForm(text) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->color = color;
}

ToolTip::~ToolTip() {

}

void ToolTip::Destroy() {
	if (instance != 0)
	{
		delete instance;
	}
	instance = 0;
}

void ToolTip::Open(Long x, Long y, Long width, Long height, char* text) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

int ToolTip::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	NotepadForm::OnCreate(lpCreateStruct);

	if (this->font != NULL) {
		delete this->font;
	}
	LOGFONT logFont;
	CDC *dc = this->GetDC();
	CFont *dcFont = dc->GetCurrentFont();
	dcFont->GetLogFont(&logFont);
	logFont.lfHeight = 22;
	strcpy(logFont.lfFaceName, "±¼¸²");

	this->font = new Font(logFont, RGB(0, 0, 0), this);

	return 0;
}

void ToolTip::OnPaint() {
	NotepadForm::OnPaint();
}

BOOL ToolTip::OnEraseBkgnd(CDC* pDC) {
	RECT rect;
	this->GetClientRect(&rect);
	pDC->FillSolidRect(&rect, this->color);
	return CWnd::OnEraseBkgnd(pDC);
}