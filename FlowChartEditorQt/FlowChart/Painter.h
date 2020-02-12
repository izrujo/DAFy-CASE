#ifndef _PAINTER_H
#define _PAINTER_H

#include <afxwin.h>
typedef signed long int Long;
///////////////////////////////////////////////////////////////////////////////////////////////
// 선의 속성
class LineProperty {
	friend class Painter;

public:
	LineProperty(LONG style = PS_SOLID, LONG width = 1, 
		LONG capStyle = PS_ENDCAP_SQUARE, LONG joinType = PS_JOIN_MITER, COLORREF color = RGB(0, 0, 0));
	~LineProperty();

	void Change(LONG style, LONG width, LONG capStyle, LONG joinType, COLORREF color );

	LONG GetStyle() const;
	LONG GetWidth() const;
	COLORREF GetColor() const;
	LONG GetCapStyle() const;
	LONG GetJoinType() const;

private:
	LONG style; // 형식
	LONG width; // 굵기
	LONG capStyle; // 가장자리 형식
	LONG joinType; // 이움새 형식
	COLORREF color; // 색깔
};

inline LONG LineProperty::GetStyle() const {
	return this->style;
}

inline LONG LineProperty::GetWidth() const {
	return this->width;
}

inline LONG LineProperty::GetCapStyle() const {
	return this->capStyle;
}

inline LONG LineProperty::GetJoinType() const {
	return this->joinType;
}

inline COLORREF LineProperty::GetColor() const {
	return this->color;
}

///////////////////////////////////////////////////////////////////////////
// 면의 속성
class PlaneProperty {
	friend class Painter;

public:
	PlaneProperty(LONG style = BS_HOLLOW, COLORREF color = RGB(255, 255, 255));
	~PlaneProperty();

	void Change(LONG style, COLORREF color);

	LONG GetStyle() const;
	COLORREF GetColor() const;
	
	// 면 관련
	// --------------------------------------
	// 색깔 스타일 : 채우기 스타일
	// 색깔 
	// 붓 스타일

	// Gradient 관련
	//--------------------------------------
private:
	LONG style;  // 채우기 형식 NONE | SOLID | GRADIENT | BITMAP
	COLORREF color;  // 색깔	
	// LONG brushStyle; // BS_DIBPATTERN | BS_HATCHED | BS_HOLLOW | BS_NULL | BS_PATTERN | BS_SOLID
	// LONG hatchStyle; // HS_BDIAGONAL | HS_CROSS | HS_DIAGCROSS | HS_FDIAGONAL | HS_HORIZONTAL | HS_VERTICAL
};

inline LONG PlaneProperty::GetStyle() const {
	return this->style;
}

inline COLORREF PlaneProperty::GetColor() const {
	return this->color;
}

///////////////////////////////////////////////////////////////////////////
class Painter {
public:
	Painter(CWnd *owner, LONG width, LONG height, COLORREF color = RGB(255, 255, 255), int bkMode=OPAQUE );
	Painter(CDC *dc, LONG width, LONG height, COLORREF color = RGB(255, 255, 255), int bkMode=OPAQUE );
	~Painter();

	// BK MODE
	LONG GetBkMode() const;
	LONG SetBkMode(LONG bkMode);

	LONG GetROP2( );
	LONG SetROP2(LONG nDrawMode );

	// 크기를 조정하다
	void Resize(CWnd *owner, COLORREF color = RGB(255, 255, 255));
	void Resize(CWnd *owner, LONG x, LONG y, LONG width, LONG height, COLORREF color = RGB(255, 255, 255));

	// 배경을 지우다
	void EraseBackground(float x1, float y1, float w1, float h1);
	
	void BeginPath();
	void CreateFromPath(CRgn *region);
	void EndPath();

	void FillRegion(CRgn &region,COLORREF nIndex);
	void FillPolygon(POINT (*points), Long count,COLORREF color);
	
	void FrameRegion(CRgn &region,LONG width, LONG heigth, COLORREF nIndex);
	// 배경을 칠하다.	
	void FillBackground(POINT (*points), LONG count, COLORREF nIndex);	

	// 화면에 출력하다
	void Render(CDC *dc, LONG x, LONG y, LONG width, LONG height);
	void StretchRender(CDC *dc, LONG x, LONG y, LONG width, LONG height, LONG xSrc, LONG ySrc, LONG widthSrc, LONG heightSrc);

	// 선과 면의 속성을 바꾸다
	void ChangeLineProperty(LONG style, LONG width, LONG capStyle, LONG joinType, COLORREF color );
	void ChangePlaneProperty(LONG style, COLORREF color );

	// 
	void DrawGradientFill(COLORREF color1, COLORREF color2, LONG x, LONG y, LONG width, LONG height, BOOL vertical = TRUE);

	// 선
	void DrawLine(float x1, float y1, float x2, float y2);
	
	// 곡선
	void DrawBezier( POINT (*points), LONG count );
	void DrawBezierTo( POINT (*points), LONG count );

	// 다각형
	void DrawRectangle( float x1, float y1, float w1, float h1 ); // 그리다
	void FillRectangle( float x1, float y1, float w1, float h1 ); // 칠하다
	void FrameRectangle( float x1, float y1, float w1, float h1 ); // 테두리를 그리다
	void InvertRectangle( float x1, float y1, float w1, float h1 ); // 반전시키다

	void DrawRoundRectangle( float x1, float y1, float w1, float h1, float a1, float a2 );
	void FillRoundRectangle( float x1, float y1, float w1, float h1, float a1, float a2 );

	void DrawPolyline( POINT (*points), LONG count );
	void DrawPolygon( POINT (*points), LONG count );
	
	// 원, 호, 부채꼴
	void DrawArc( float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd );
	void DrawPie( float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd );
	void FillPie( float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd );
	void DrawChord(  float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd );
	void FillChord( float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd );
	void DrawEllipse( float x1, float y1, float w1, float h1 );
	void FillEllipse( float x1, float y1, float w1, float h1 );
	
	//안티에일리어싱 시도
	//void DrawArc(float x, float y, float width, float height, float startAngle, float sweepAngle);
	//void DrawPolyLine(POINT(*points), LONG count);
	
	// Rect를 이용하여 돌출 도형 그리기
	void PaintOverRectangle(float x1, float y1, float w1, float h1 );
	
	// 비트맵 처리
	HBITMAP GetCurrentBitmap();
	
	// 텍스트 출력
	void TextOut(LONG fontHeight, LONG x,LONG y, LPCTSTR lpString, int nCount );
	int DrawText(LONG fontHeight, LPCTSTR lpString, int nCount, LPRECT lpRect, UINT uFormat );
	void ChangeFont(HFONT font, COLORREF color);

	void Resize(CWnd *owner, CSize size, CPoint point);

	// 색처리
	// Path 처리

	// LineProperty
	LONG GetLineStyle() const;
	LONG GetLineWidth() const;
	COLORREF GetLineColor() const;
	LONG GetLineCapStyle() const;
	LONG GetLineJoinType() const;

	// PlaneProperty
	LONG GetPlaneStyle() const;
	COLORREF GetPlanColor() const;

	LOGFONT& GetFont() const;

private:
	//Double Buffering 관련 메모리 DC와 비트맵
	/////////////////////////////////////////////////////
	HDC m_hdc; // 메모리 DC
	////////////////////////////////////////////////////
	HBITMAP m_hbmp;
	HBITMAP m_holdbmp;

	LONG bkMode;  // OPAQUE|TRANSPARENT

	// 선 관련
	LineProperty lineProperty;
	// 평면 관련
	PlaneProperty planeProperty;

	
	// 텍스트 관련
	//--------------------------------------------
	// 폰트
	LOGFONT font;
	// 색깔
	// 맞춤방식
};

inline LONG Painter::GetLineStyle() const {
	return lineProperty.GetStyle();
}

inline LONG Painter::GetLineWidth() const{
	return lineProperty.GetWidth();
}

inline COLORREF Painter::GetLineColor() const{
	return lineProperty.GetColor();
}

inline LONG Painter::GetLineCapStyle() const{
	return lineProperty.GetCapStyle();
}

inline LONG Painter::GetLineJoinType() const{
	return lineProperty.GetJoinType();
}

inline LONG Painter::GetPlaneStyle() const{
	return planeProperty.GetStyle();
}

inline COLORREF Painter::GetPlanColor() const{
	return planeProperty.GetColor();
}

inline LONG Painter::GetBkMode() const{
	return this->bkMode;
}

inline LOGFONT& Painter::GetFont() const {
	return const_cast<LOGFONT&>(this->font);
}

#endif // _PAINTER_H
