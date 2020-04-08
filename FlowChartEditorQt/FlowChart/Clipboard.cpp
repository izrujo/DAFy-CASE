// Clipboard.cpp

#include "Clipboard.h"

#include "DrawingPaper.h"
#include "FlowChart.h"

Clipboard::Clipboard() {
	buffer = new FlowChart;
}

Clipboard::~Clipboard() {
	if (buffer != 0) {
		delete buffer;
	}
}

Long Clipboard::Copy(DrawingPaper *canvas) {
	NShape *shape;
	buffer->Clear();
	for (Long i = 0; i < canvas->flowChart->GetLength(); i++) {
		shape = canvas->flowChart->GetAt(i);
		if (shape->IsSelected()) {
			buffer->Attach(shape->Clone());
		}
	}
	return buffer->GetLength();
}

Long Clipboard::Paste(DrawingPaper *canvas) {
	NShape *shape;
	canvas->flowChart->UnSelectAll();
	canvas->mode = DrawingPaper::IDLE;
	for (Long i = 0; i < buffer->GetLength(); i++) {
		Long x, y;
		shape = buffer->GetAt(i);
		x = shape->GetX();
		y = shape->GetY();
		shape->Move(x + 50, y + 30);
		canvas->flowChart->Attach(shape->Clone());
		canvas->mode = DrawingPaper::SELECT;
	}
	return buffer->GetLength();
}

Long Clipboard::Cut(DrawingPaper *canvas) {
	NShape *shape;
	buffer->Clear();
	for (Long i = 0; i < canvas->flowChart->GetLength(); i++) {
		shape = canvas->flowChart->GetAt(i);
		if (shape->IsSelected()) {
			buffer->Attach(shape->Clone());
		}
	}

	canvas->flowChart->DetachSelectedAll();

	return buffer->GetLength();
}