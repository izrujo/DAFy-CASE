#include "Painter.h"
#include <cmath>

////////////////////////////////////////////////////////////////
// 선 속성 클래스

LineProperty::LineProperty(LONG style, LONG width, LONG capStyle, LONG joinType, COLORREF color) {
	this->style = style;
	this->width = width;
	this->capStyle = capStyle;
	this->joinType = joinType;
	this->color = color;
}

LineProperty::~LineProperty() {
}

void LineProperty::Change(LONG style, LONG width, LONG capStyle, LONG joinType, COLORREF color) {
	this->style = style;
	this->width = width;
	this->capStyle = capStyle;
	this->joinType = joinType;
	this->color = color;
}

////////////////////////////////////////////////////////////////////////////////
// 평면 속성 클래스

PlaneProperty::PlaneProperty(LONG style, COLORREF color) {
	this->style = style;
	this->color = color;
}

PlaneProperty::~PlaneProperty() {
}

void PlaneProperty::Change(LONG style, COLORREF color) {
	this->style = style;
	this->color = color;
}

//==========================================================================
Painter::Painter(CWnd *owner, LONG width, LONG height, COLORREF color, int bkMode) {
	CDC *dc = owner->GetDC();
	this->m_hdc = ::CreateCompatibleDC(dc->m_hDC);
	this->m_hbmp = ::CreateCompatibleBitmap(dc->m_hDC, width, height);
	this->m_holdbmp = (HBITMAP)::SelectObject(this->m_hdc, m_hbmp);

	this->bkMode = bkMode;

	CFont *cFont = dc->GetCurrentFont();
	cFont->GetLogFont(&(this->font));

	RECT rect = { 0, 0, width, height }; // 그리고자 하는 영역의 크기

	::FillRect(this->m_hdc, &rect, ::CreateSolidBrush(color)); // 배경을 칠하다

	owner->ReleaseDC(dc);
}

Painter::Painter(CDC *dc, LONG width, LONG height, COLORREF color, int bkMode) {
	this->m_hdc = ::CreateCompatibleDC(dc->m_hDC);
	this->m_hbmp = ::CreateCompatibleBitmap(dc->m_hDC, width, height);
	this->m_holdbmp = (HBITMAP)::SelectObject(this->m_hdc, m_hbmp);

	this->bkMode = bkMode;

	CFont *cFont = dc->GetCurrentFont();
	cFont->GetLogFont(&(this->font));

	RECT rect = { 0, 0, width, height }; // 그리고자 하는 영역의 크기

	::FillRect(this->m_hdc, &rect, ::CreateSolidBrush(color)); // 배경을 칠하다

}

Painter::~Painter() {
	// 메모리 DC를 정리하다
	if (m_hdc != NULL) {
		::SelectObject(m_hdc, m_holdbmp);
		::DeleteDC(m_hdc);
		m_hdc = NULL;
	}

	// 메모리 DC에 사용된 비트맵을 정리하다
	if (m_hbmp != NULL) {
		::DeleteObject(m_hbmp);
		m_hbmp = NULL;
	}
}

LONG Painter::SetBkMode(LONG bkMode) {
	LONG previousBkMode;
	previousBkMode = ::SetBkMode(this->m_hdc, bkMode);
	this->bkMode = bkMode;
	return previousBkMode;
}

LONG Painter::GetROP2() {
	return ::GetROP2(this->m_hdc);
}

LONG Painter::SetROP2(LONG nDrawMode) {
	return  ::SetROP2(this->m_hdc, nDrawMode);
}

void Painter::Resize(CWnd *owner, COLORREF color) {
	if (m_hdc != NULL) {
		::SelectObject(m_hdc, m_holdbmp);
		::DeleteDC(m_hdc);
		m_hdc = NULL;
	}
	if (m_hbmp != NULL) {
		::DeleteObject(m_hbmp);
		m_hbmp = NULL;
	}

	RECT rect;
	::GetClientRect(owner->m_hWnd, &rect); // 그리고자 하는 영역의 크기

	CDC *dc = owner->GetDC();

	this->m_hdc = ::CreateCompatibleDC(dc->m_hDC);
	this->m_hbmp = ::CreateCompatibleBitmap(dc->m_hDC, rect.right - rect.left, rect.bottom - rect.top);
	this->m_holdbmp = (HBITMAP)::SelectObject(this->m_hdc, m_hbmp);

	::FillRect(this->m_hdc, &rect, ::CreateSolidBrush(color)); // 배경을 칠하다
}

void Painter::Resize(CWnd *owner, LONG x, LONG y, LONG width, LONG height, COLORREF color) {

	if (m_hdc != NULL) {
		::SelectObject(m_hdc, m_holdbmp);
		::DeleteDC(m_hdc);
		m_hdc = NULL;
	}

	if (m_hbmp != NULL) {
		::DeleteObject(m_hbmp);
		m_hbmp = NULL;
	}

	RECT rect = { x, y, x + width, y + height };
	::GetClientRect(owner->m_hWnd, &rect); // 그리고자 하는 영역의 크기

	CDC *dc = owner->GetDC();

	this->m_hdc = ::CreateCompatibleDC(dc->m_hDC);
	this->m_hbmp = ::CreateCompatibleBitmap(dc->m_hDC, rect.right - rect.left, rect.bottom - rect.top);
	this->m_holdbmp = (HBITMAP)::SelectObject(this->m_hdc, m_hbmp);

	::FillRect(this->m_hdc, &rect, ::CreateSolidBrush(color)); // 배경을 칠하다
}

void Painter::Render(CDC *dc, LONG x, LONG y, LONG width, LONG height) {
	::BitBlt(dc->m_hDC, x, y, width, height, m_hdc, 0, 0, SRCCOPY);
}

void Painter::ChangeLineProperty(LONG style, LONG width, LONG capStyle, LONG joinType, COLORREF color) {
	this->lineProperty.Change(style, width, capStyle, joinType, color);
}

void Painter::ChangePlaneProperty(LONG style, COLORREF color) {
	this->planeProperty.Change(style, color);
}

void Painter::DrawGradientFill(COLORREF color1, COLORREF color2, LONG x, LONG y, LONG width, LONG height, BOOL vertical) {
	int internalWidth = width;
	int internalHeight = height;

	int r1 = GetRValue(color1);
	int g1 = GetGValue(color1);
	int b1 = GetBValue(color1);

	int r2 = GetRValue(color2);
	int g2 = GetGValue(color2);
	int b2 = GetBValue(color2);

	COLORREF oldBkColor = ::GetBkColor(this->m_hdc);

	if (vertical == TRUE) {
		for (int i = 0; i < internalWidth; ++i) {
			int r = r1 + (i * (r2 - r1) / internalWidth);
			int g = g1 + (i * (g2 - g1) / internalWidth);
			int b = b1 + (i * (b2 - b1) / internalWidth);

			::SetBkColor(this->m_hdc, RGB(r, g, b));
			RECT line = { i + x, y, i + 1 + x, y + internalHeight };
			::ExtTextOut(this->m_hdc, 0, 0, ETO_OPAQUE, &line, NULL, 0, 0);
		}
	}
	else {
		for (int i = 0; i < internalHeight; ++i) {
			int r = r1 + (i * (r2 - r1) / internalHeight);
			int g = g1 + (i * (g2 - g1) / internalHeight);
			int b = b1 + (i * (b2 - b1) / internalHeight);
			::SetBkColor(this->m_hdc, RGB(r, g, b));
			RECT line = { x, i + y, x + internalWidth, i + 1 + y };
			::ExtTextOut(this->m_hdc, 0, 0, ETO_OPAQUE, &line, NULL, 0, 0);
		}
	}

	::SetBkColor(this->m_hdc, oldBkColor);
}

/**
 *  선을 그리다
 */
void Painter::DrawLine(float x1, float y1, float x2, float y2) {
	// Geometric Pen를 만들다
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color), GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType, this->lineProperty.width, &log, 0, NULL);

	// 펜을 바꾸다
	HPEN old = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 선을 그리다
	::MoveToEx(this->m_hdc, x1, y1, NULL);
	::LineTo(this->m_hdc, x2, y2);

	::SelectObject(this->m_hdc, old);

	::DeleteObject(hPen); // 반드시 지워야 한다
}

/**
 * 한 개의 곡선을 그리다.
 *
 * 입력 : 네 개의 좌표(점)와 개수(=4) : 필요한 점들 = 그려질 곡선 수 * 3 + 1
 *
 */
void Painter::DrawBezier(POINT(*points), LONG count) {
	// 
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType, this->lineProperty.width, &log, 0, NULL); // 2, style);

	HPEN old = (HPEN)::SelectObject(this->m_hdc, hPen);

	::PolyBezier(this->m_hdc, points, count);

	::SelectObject(this->m_hdc, old);

	::DeleteObject(hPen); // 반드시 지워야 한다
}

void Painter::DrawBezierTo(POINT(*points), LONG count) {
	// 필요한 점들 = 그려질 곡선 수 * 3 + 1

	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color), GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType, this->lineProperty.width, &log, 0, NULL);

	HPEN old = (HPEN)::SelectObject(this->m_hdc, hPen);

	::PolyBezierTo(this->m_hdc, points, count);

	::SelectObject(this->m_hdc, old);

	::DeleteObject(hPen); // 반드시 지워야 한다
}

// 배경이 없는 사각형을 그리다
void Painter::DrawRectangle(float x1, float y1, float w1, float h1) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(
		PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType,
		this->lineProperty.width, &log, 0, NULL); // 2, style);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::Rectangle(this->m_hdc, x1, y1, w1, h1);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

// 배경이 칠해진 사각형을 그리다.
void Painter::FillRectangle(float x1, float y1, float w1, float h1) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(
		PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType,
		this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::Rectangle(this->m_hdc, x1, y1, w1, h1);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::DrawRoundRectangle(float x1, float y1, float w1, float h1, float a1, float a2) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(
		PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType,
		this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::RoundRect(this->m_hdc, x1, y1, w1, h1, a1, a2);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::FillRoundRectangle(float x1, float y1, float w1, float h1, float a1, float a2) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(
		PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType,
		this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::RoundRect(this->m_hdc, x1, y1, w1, h1, a1, a2);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::FrameRectangle(float x1, float y1, float w1, float h1) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(
		PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType,
		this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	RECT rect = { x1, y1, w1, h1 };

	::FrameRect(this->m_hdc, &rect, hBrush);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::InvertRectangle(float x1, float y1, float w1, float h1) {
	RECT rect = { x1, y1, x1 + w1, y1 + h1 };

	::InvertRect(this->m_hdc, &rect);
}

void Painter::DrawPolyline(POINT(*points), LONG count) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color), GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType, this->lineProperty.width, &log, 0, NULL);
	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::Polyline(this->m_hdc, points, count);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::DrawPolygon(POINT(*points), LONG count) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color), GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType, this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::Polygon(this->m_hdc, points, count);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::DrawArc(float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(
		PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType,
		this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	::Arc(this->m_hdc, x1, y1, w1, h1, xStart, yStart, xEnd, yEnd);

	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hPen);
}

void Painter::DrawPie(float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(
		PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType,
		this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::Pie(this->m_hdc, x1, y1, w1, h1, xStart, yStart, xEnd, yEnd);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::FillPie(float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(
		PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType,
		this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::Pie(this->m_hdc, x1, y1, w1, h1, xStart, yStart, xEnd, yEnd);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::DrawChord(float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(
		PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType,
		this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::Chord(this->m_hdc, x1, y1, w1, h1, xStart, yStart, xEnd, yEnd);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::FillChord(float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color), GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType, this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::Chord(this->m_hdc, x1, y1, w1, h1, xStart, yStart, xEnd, yEnd);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::DrawEllipse(float x1, float y1, float w1, float h1) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color), GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType, this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::Ellipse(this->m_hdc, x1, y1, w1, h1);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::FillEllipse(float x1, float y1, float w1, float h1) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(
		PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType,
		this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color;
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::Ellipse(this->m_hdc, x1, y1, w1, h1);

	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::PaintOverRectangle(float x1, float y1, float w1, float h1) {
	// 펜 바꾸기
	LOGBRUSH log = { 0, };

	log.lbStyle = BS_SOLID;
	log.lbColor = RGB(GetRValue(this->lineProperty.color),
		GetGValue(this->lineProperty.color), GetBValue(this->lineProperty.color));
	log.lbHatch = 0;

	HPEN hPen = ::ExtCreatePen(
		PS_GEOMETRIC | this->lineProperty.style | this->lineProperty.capStyle | this->lineProperty.joinType,
		this->lineProperty.width, &log, 0, NULL);

	HPEN oldPen = (HPEN)::SelectObject(this->m_hdc, hPen);

	// 붓 바꾸기
	log.lbStyle = this->planeProperty.style;
	log.lbColor = this->planeProperty.color; // RGB(248, 252, 248);
	log.lbHatch = 0; // HS_DIAGCROSS;

	HBRUSH hBrush = (HBRUSH)::CreateBrushIndirect(&log);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(this->m_hdc, hBrush);

	::Rectangle(this->m_hdc, x1, y1, w1, h1);

	// 오른쪽으로 2픽셀 이동시키다.
	RECT rect = { x1, y1, w1, h1 };
	::OffsetRect(&rect, -1, -1);
	// ::InflateRect(&rect, 0, 15);

	::Rectangle(this->m_hdc, rect.left, rect.top, rect.right, rect.bottom);

	::OffsetRect(&rect, -1, -1);
	// ::InflateRect(&rect, 0, 15);

	::Rectangle(this->m_hdc, rect.left, rect.top, rect.right, rect.bottom);


	::SelectObject(this->m_hdc, oldBrush);
	::SelectObject(this->m_hdc, oldPen);

	::DeleteObject(hBrush);
	::DeleteObject(hPen);
}

void Painter::TextOut(LONG fontHeight, LONG x, LONG y, LPCTSTR lpString, int nCount) {
	int oldMode;

	oldMode = ::SetBkMode(this->m_hdc, this->bkMode);

	::TextOutA(this->m_hdc, x, y, lpString, nCount);
	::SetBkMode(this->m_hdc, oldMode);
}

int Painter::DrawText(LONG fontHeight, LPCTSTR lpString, int nCount, LPRECT lpRect, UINT uFormat) {
	int oldMode;
	int height;
	oldMode = ::SetBkMode(this->m_hdc, this->bkMode);

	height = ::DrawText(this->m_hdc, lpString, nCount, lpRect, uFormat);
	::SetBkMode(this->m_hdc, oldMode);
	return height;
}

void Painter::EraseBackground(float x1, float y1, float w1, float h1) {
	RECT rect = { x1, y1, w1, h1 };
	CRgn region;

	region.CreateRectRgn(x1, y1, w1, h1);

	CBrush brush;

	brush.CreateSolidBrush(RGB(255, 255, 255));

	::FillRgn(this->m_hdc, (HRGN)region, brush.operator HBRUSH());

	region.DeleteObject();
}

void Painter::BeginPath() {
	::BeginPath(this->m_hdc);
}

void Painter::CreateFromPath(CRgn *region) {
	region->CreateFromPath(CDC::FromHandle(this->m_hdc));
}

void Painter::EndPath() {
	::EndPath(this->m_hdc);
}

void Painter::FillRegion(CRgn &region, COLORREF nIndex) {
	CBrush brush(nIndex);
	::FillRgn(this->m_hdc, (HRGN)region, brush.operator HBRUSH());
}

void Painter::FillPolygon(POINT(*points), Long count, COLORREF color) {
	CRgn region;
	CBrush brush(color);
	region.CreatePolygonRgn(points, count, WINDING);

	::FillRgn(this->m_hdc, region, brush);

	brush.DeleteObject();
	region.DeleteObject();
}

void Painter::FrameRegion(CRgn &region, LONG width, LONG heigth, COLORREF nIndex) {
	CBrush brush;
	brush.CreateStockObject(nIndex);

	::FrameRgn(this->m_hdc, (HRGN)region, brush.operator HBRUSH(), width, heigth);
}

void Painter::FillBackground(POINT(*points), LONG count, COLORREF nIndex) {
	CRgn region;
	region.CreatePolygonRgn(points, count, WINDING);
	CBrush brush;

	brush.CreateSolidBrush(nIndex);

	::FillRgn(this->m_hdc, (HRGN)region, brush.operator HBRUSH());
	region.DeleteObject();
}

void Painter::ChangeFont(HFONT font, COLORREF color) {
	CFont *cFont = CFont::FromHandle(font);
	cFont->GetLogFont(&this->font);
	::SetTextColor(this->m_hdc, color);
	::SelectObject(this->m_hdc, font);
}

void Painter::Resize(CWnd *owner, CSize size, CPoint point) {
	if (m_hdc != NULL) {
		::SelectObject(m_hdc, m_holdbmp);
		::DeleteDC(m_hdc);
		m_hdc = NULL;
	}
	if (m_hbmp != NULL) {
		::DeleteObject(m_hbmp);
		m_hbmp = NULL;
	}

	CDC *dc = owner->GetDC();
	dc->SetMapMode(MM_ISOTROPIC);
	dc->SetWindowExt(size.cx, size.cy);
	size = dc->GetWindowExt();
	dc->SetWindowOrg(point.x, point.y);
	point = dc->GetWindowOrg();

	this->m_hdc = ::CreateCompatibleDC(dc->m_hDC);
	this->m_hbmp = ::CreateCompatibleBitmap(dc->m_hDC, size.cx, size.cy);
	this->m_holdbmp = (HBITMAP)::SelectObject(this->m_hdc, m_hbmp);

	RECT rect = { point.x, point.y, point.x + size.cx, point.y + size.cy };
	::FillRect(this->m_hdc, &rect, ::CreateSolidBrush(RGB(255, 255, 255))); // 배경을 칠하다
}

void Painter::StretchRender(CDC *dc, LONG x, LONG y, LONG width, LONG height, LONG xSrc, LONG ySrc, LONG widthSrc, LONG heightSrc) {
	::StretchBlt(dc->m_hDC, x, y, width, height, this->m_hdc, xSrc, ySrc, widthSrc, heightSrc, SRCCOPY);
}

HBITMAP Painter::GetCurrentBitmap() {
	return this->m_hbmp;
}