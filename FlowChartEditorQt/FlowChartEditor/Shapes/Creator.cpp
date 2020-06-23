#include "Creator.h"
#include "Shape.h"
#include "Symbols/Terminal.h"
#include "Symbols/Preparation.h"
#include "Symbols/Process.h"
#include "Symbols/Decision.h"
#include "Symbols/InputOutput.h"
#include "Lines/Arrow.h"
#include "Lines/LeftDown.h"
#include "Lines/RightDown.h"
#include "Lines/Join.h"
#include "Lines/RepeatTrue.h"
#include "Lines/RepeatFalse.h"
#include "Lines/RightDownJoin.h"

Creator::Creator() {}

Creator::~Creator() {}

NShape* Creator::Create(Long shapeID, float x, float y, float width, float height, float width2, float height2, char(*contents)) {
	NShape *shape;
	if (shapeID == ID_TERMINAL) {
		shape = new Terminal(x, y, width, height, QColor(255, 153, 153), Qt::SolidLine, QColor(0, 0, 0), contents);
	}
	else if (shapeID == ID_PREPARATION) {
		shape = new Preparation(x, y, width, height, QColor(153, 153, 255), Qt::SolidLine, QColor(0, 0, 0), contents);
	}
	else if (shapeID == ID_PROCESS) {
		shape = new Process(x, y, width, height, QColor(153, 255, 153), Qt::SolidLine, QColor(0, 0, 0), contents);
	}
	else if (shapeID == ID_DECISION) {
		shape = new Decision(x, y, width, height, QColor(255, 153, 255), Qt::SolidLine, QColor(0, 0, 0), contents);
	}
	else if (shapeID == ID_ARROW) {
		shape = new Arrow(x, y, width, height, QColor(0, 0, 0), Qt::SolidLine, QColor(0, 0, 0), contents);
	}
	else if (shapeID == ID_LEFTDOWN) {
		shape = new LeftDown(x, y, width, height, QColor(0, 0, 0), Qt::SolidLine, QColor(0, 0, 0), contents);
	}
	else if (shapeID == ID_RIGHTDOWN) {
		shape = new RightDown(x, y, width, height, QColor(0, 0, 0), Qt::SolidLine, QColor(0, 0, 0), contents);
	}
	else if (shapeID == ID_JOIN) {
		shape = new Join(x, y, width, height, height2, QColor(0, 0, 0), Qt::SolidLine, QColor(0, 0, 0), contents);
	}
	else if (shapeID == ID_REPEATTRUE) {
		shape = new RepeatTrue(x, y, width, height, width2, height2, QColor(0, 0, 0), Qt::SolidLine, QColor(0, 0, 0), contents);
	}
	else if (shapeID == ID_REPEATFALSE) {
		shape = new RepeatFalse(x, y, width, height, width2, height2, QColor(0, 0, 0), Qt::SolidLine, QColor(0, 0, 0), contents);
	}
	else if (shapeID == ID_RIGHTDOWNJOIN) {
		shape = new RightDownJoin(x, y, width, height, width2, height2, QColor(0, 0, 0), Qt::SolidLine, QColor(0, 0, 0), contents);
	}
	else if (shapeID == ID_INPUTOUTPUT) {
		shape = new InputOutput(x, y, width, height, QColor(255, 255, 153), Qt::SolidLine, QColor(0, 0, 0), contents);
	}

	return shape;
}