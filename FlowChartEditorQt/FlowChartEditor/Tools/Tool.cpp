#include "Tool.h"
#include "SelectingTool.h"
#include "MovingTool.h"
#include "../Paint/Drawing/IterationMake.h"
#include "../Paint/Drawing/SelectionMake.h"
#include "../Paint/Drawing/SequenceMake.h"
#include "../Paint/Drawing/MoveMake.h"
#include "../Paint/Drawing/SizeMake.h"
#include "../Paint/Drawing/IntervalMake.h"

Tool::Tool() {
}

Tool* Tool::Instance() {
	return 0;
}

void Tool::IterationMake(DrawingPaper *canvas){
	IterationMake::Create(canvas);
}

void Tool::SelectionMake(DrawingPaper *canvas){
	SelectionMake::Create(canvas);
}

void Tool::SequenceMake(DrawingPaper *canvas){
	SequenceMake::Create(canvas);
}

void Tool::MoveMake(DrawingPaper *canvas){
	MoveMake::Create(canvas);
}

void Tool::SizeMake(DrawingPaper *canvas){
	SizeMake::Create(canvas);
}

void Tool::IntervalMake(DrawingPaper *canvas){
	IntervalMake::Create(canvas);
}