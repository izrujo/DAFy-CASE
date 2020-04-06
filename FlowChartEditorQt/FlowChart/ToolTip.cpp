#include "ToolTip.h"
#include "Shape.h"

#include "FlowChart.h"
#include "../FlowChartEditor.h"
#include "DrawingPaper.h"

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

ToolTip* ToolTip::instance = 0;

ToolTip* ToolTip::Instance(char(*text), QColor color)
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

ToolTip::ToolTip(char(*text), QColor color)
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

void ToolTip::Open(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;



	LOGFONT logFont;
	CDC *dc = this->GetDC();
	CFont *dcFont = dc->GetCurrentFont();
	dcFont->GetLogFont(&logFont);
	logFont.lfHeight = 22;
	strcpy(logFont.lfFaceName, "±¼¸²");

	this->font = new Font(logFont, RGB(0, 0, 0), this);
}

void ToolTip::paintEvent(QPaintEvent *event) {
	NotepadForm::paintEvent(event);
}
/*
BOOL ToolTip::OnEraseBkgnd(CDC* pDC) {
	RECT rect;
	this->GetClientRect(&rect);
	pDC->FillSolidRect(&rect, this->color);
	return CWnd::OnEraseBkgnd(pDC);
}
*/