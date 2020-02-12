// Clipboard.c

#ifndef _CLIPBOARD_H
#define _CLIPBOARD_H

#include "FlowChart.h"
class DrawingPaper;

typedef signed long int Long;

class Clipboard{
public:
	Clipboard();
	~Clipboard();
	Long Copy(DrawingPaper *canvas);
	Long Paste(DrawingPaper *canvas);
	Long Cut(DrawingPaper *canvas);

	Long GetLength() const;
private:
	FlowChart *buffer;
};

inline Long Clipboard::GetLength() const {
	return this->buffer->GetLength();
}
#endif // _CLIPBOARD_H