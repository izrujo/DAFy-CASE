// Clipboard.cpp

#include "Clipboard.h"

#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Registrar.h"
#include "ContentsAnalyzer.h"
#include "RuleKeeper.h"
#include "Preparation.h"

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

	Long index;
	Long j = 0;
	for (Long i = 0; i < this->buffer->GetLength(); i++) {
		float x, y;
		shape = this->buffer->GetAt(i);
		x = shape->GetX();
		y = shape->GetY();
		shape->Move(x + 50, y + 30);
		index = canvas->flowChart->Attach(shape->Clone());
		canvas->registrar->Register(canvas->flowChart->GetAt(index));
		canvas->mode = DrawingPaper::SELECT;
		//=====================intellisense========================
		if (canvas->variableList != NULL && dynamic_cast<Preparation*>(shape)) {
			if (canvas->variableList != NULL) {
				delete canvas->variableList;
				canvas->variableList = NULL;
			}
			ContentsAnalyzer analyzer;
			RuleKeeper ruleKeeper;
			Array<String> variables = analyzer.MakeVariables(shape->GetContents());
			canvas->variableList = ruleKeeper.CheckVariableNamingRule(variables);
		}
		//=========================================================
	}

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