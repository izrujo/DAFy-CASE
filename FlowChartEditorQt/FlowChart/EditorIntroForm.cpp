#include "EditorIntroForm.h"
#include "resource.h"
#include <afxwin.h>

BEGIN_MESSAGE_MAP(EditorIntroForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

EditorIntroForm::EditorIntroForm() {

}

int EditorIntroForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	return 0;
}

void EditorIntroForm::OnClose() {
	CFrameWnd::OnClose();
}

void EditorIntroForm::OnPaint() {
	CPaintDC dc(this);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	BITMAP bitmapInfo;
	CBitmap bitmap;
	CBitmap *oldBitmap;

	bitmap.LoadBitmapA(IDB_BITMAP1);

	bitmap.GetBitmap(&bitmapInfo);
	oldBitmap = memDC.SelectObject(&bitmap);

	CRect rect(270, 80, 330, 140);
	dc.TransparentBlt(rect.left, rect.top, rect.Width(), rect.Height(),
		&memDC, 0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, RGB(255, 255, 255));

	memDC.SelectObject(oldBitmap);

	memDC.DeleteDC();

	CFont *font;
	LOGFONT logFont;

	font = dc.GetCurrentFont();
	font->GetLogFont(&logFont);
	strcpy_s(logFont.lfFaceName, _T("¸¼Àº °íµñ"));
	////////////////////////////////////////

	logFont.lfHeight = -14;
	logFont.lfWidth = -7;
#if 0
	font->CreateFontIndirectA(&logFont);
	CFont *oldFont = (CFont*)dc.SelectObject(font);
#endif
	CRect rect2(10, 10, 120, 120);
	//dc.DrawText("³ª¾Æ ÄÚÄª", rect2, DT_LEFT);
#if 0
	dc.SelectObject(oldFont);
	//////////////////////////////////////
	logFont.lfHeight = -36;
	logFont.lfWidth = -18;
	logFont.lfWeight = 700;
	font->CreateFontIndirectA(&logFont);
	oldFont = (CFont*)dc.SelectObject(font);
#endif
	CRect rect3(100, 150, 500, 200);
	dc.DrawText("FlowChartEditor", rect3, DT_CENTER);
#if 0
	dc.SelectObject(oldFont);
	/////////////////////////////////////
	logFont.lfHeight = -24;
	logFont.lfWidth = -12;
	logFont.lfWeight = 400;
	font->CreateFontIndirectA(&logFont);
	oldFont = (CFont*)dc.SelectObject(font);
#endif
	CRect rect4(100, 200, 500, 250);
	dc.DrawText("ver 0.05", rect4, DT_CENTER);
	CRect rect5(100, 300, 500, 350);
	dc.DrawText("NaACoaching.com", rect5, DT_CENTER);
#if 0
	dc.SelectObject(oldFont);
	font->DeleteObject();
#endif
}