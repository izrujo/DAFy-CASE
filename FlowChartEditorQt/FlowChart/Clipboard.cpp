// Clipboard.cpp

#include "Clipboard.h"

#include "DrawingPaper.h"
#include "FlowChart.h"
#include "MemoryController.h"

Clipboard::Clipboard() {
	this->buffer = new FlowChart;
}

Clipboard::~Clipboard() {
	if (this->buffer != 0) {
		delete this->buffer;
	}
}

Long Clipboard::Copy(DrawingPaper *canvas) {
	NShape *shape;
	this->buffer->Clear();
	for (Long i = 0; i < canvas->flowChart->GetLength(); i++) {
		shape = canvas->flowChart->GetAt(i);
		if (shape->IsSelected()) {
			this->buffer->Attach(shape->Clone());
		}
	}
	return this->buffer->GetLength();
}

Long Clipboard::Paste(DrawingPaper *canvas) {
	NShape *shape;
	canvas->flowChart->UnSelectAll();
	canvas->mode = DrawingPaper::IDLE;

	Long(*positions) = new Long[this->buffer->GetLength()];
	Long count = 0;
	Long j = 0;

	for (Long i = 0; i < this->buffer->GetLength(); i++) {
		float x, y;
		shape = this->buffer->GetAt(i);
		x = shape->GetX();
		y = shape->GetY();
		shape->Move(x + 50, y + 30);
		positions[j++] = canvas->flowChart->Attach(shape->Clone());
		count++;
		canvas->mode = DrawingPaper::SELECT;
	}
	canvas->memoryController->RememberAdd(positions, count);

	return this->buffer->GetLength();
}

Long Clipboard::Cut(DrawingPaper *canvas) {
	NShape *shape;
	this->buffer->Clear();
	for (Long i = 0; i < canvas->flowChart->GetLength(); i++) {
		shape = canvas->flowChart->GetAt(i);
		if (shape->IsSelected()) {
			this->buffer->Attach(shape->Clone());
		}
	}

	canvas->flowChart->DetachSelectedAll();

	return this->buffer->GetLength();
}