#include "Creator.h"
#include "Shape.h"
#include "Terminal.h"
#include "Preparation.h"
#include "Process.h"
#include "Decision.h"
#include "Arrow.h"
#include "LeftDown.h"
#include "RightDown.h"
#include "Join.h"
#include "RepeatTrue.h"
#include "RepeatFalse.h"
#include "RightDownJoin.h"
#include "InputOutput.h"

Creator::Creator(){}

Creator::~Creator(){}

Shape* Creator::Create(Long shapeID, Long x, Long y, Long width, Long height, Long width2, Long height2, char (*contents)){
	Shape *shape;
	if( shapeID == ID_TERMINAL ){
		shape = new Terminal ( x, y, width, height, RGB(255, 153, 153), DASH, 20, contents);
	}else if( shapeID == ID_PREPARATION ){
		shape = new Preparation ( x, y, width, height, RGB(153, 153, 255), DASH, 20, contents);
	}else if( shapeID == ID_PUNCHEDCARD ){
		shape = new PunchedCard ( x, y, width, height, 20, DASH, 20, contents);
	}else if( shapeID == ID_PROCESS ){
		shape = new Process ( x, y, width, height, RGB(153, 255, 153), DASH, 20, contents);
	}else if( shapeID == ID_DECISION ){
		shape = new Decision ( x, y, width, height, RGB(255, 153, 255), DASH, 20, contents);
	}else if( shapeID == ID_DOCUMENT ){
		shape = new Document ( x, y, width, height, 20, DASH, 20, contents);
	}else if( shapeID == ID_ARROW ){
		shape = new Arrow ( x, y, width, height, 20, DASH, 20, contents);
	}else if( shapeID == ID_LEFTDOWN ){
		shape = new LeftDown ( x, y, width, height, 20, DASH, 20, contents);
	}else if( shapeID == ID_RIGHTDOWN ){
		shape = new RightDown ( x, y, width, height, 20, DASH, 20, contents);
	}else if( shapeID == ID_JOIN ){
		shape = new Join ( x, y, width, height, height2, 20, DASH, 20, contents);
	}else if( shapeID == ID_REPEATTRUE ){
		shape = new RepeatTrue ( x, y, width, height, width2, height2, 20, DASH, 20, contents);
	}else if( shapeID == ID_REPEATFALSE ){
		shape = new RepeatFalse ( x, y, width, height, width2, height2, 20, DASH, 20, contents);
	}else if( shapeID == ID_RIGHTDOWNJOIN ){
		shape = new RightDownJoin ( x, y, width, height, width2, height2, 20, DASH, 20, contents);
	}else if( shapeID == ID_INPUTOUTPUT ){
		shape = new InputOutput ( x, y, width, height, RGB(255, 255, 153), DASH, 20, contents);
	}

	return shape;
}