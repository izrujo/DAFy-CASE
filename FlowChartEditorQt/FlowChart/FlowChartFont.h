#ifndef _FLOWCHARTFONT_H
#define _FLOWCHARTFONT_H

#include <afxwin.h>
class FlowChartEditor;

class FlowChartFont {
public:
	FlowChartFont(FlowChartEditor *editor = 0);
	FlowChartFont(FlowChartEditor *editor, LOGFONT font, COLORREF color);
	FlowChartFont(const FlowChartFont& source);
	~FlowChartFont();
	FlowChartFont& operator=(const FlowChartFont& source);

	HFONT Create();

	LOGFONT& GetFont() const;
	COLORREF& GetColor() const;
private:
	FlowChartEditor *editor;
	LOGFONT font;
	COLORREF color;
};

inline LOGFONT& FlowChartFont::GetFont() const {
	return const_cast<LOGFONT&>(this->font);
}
inline COLORREF& FlowChartFont::GetColor() const {
	return const_cast<COLORREF&>(this->color);
}

#endif //_FLOWCHARTFONT_H