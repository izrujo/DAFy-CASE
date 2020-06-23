#include "Zoom.h"
#include "../../Interface/DrawingPaper.h"
#include "../../Interface/Scroll.h"
#include "../../Shapes/Composite/FlowChart.h"
#include "../../Shapes/Lines/RightDownJoin.h"
#include "../../Shapes/Lines/RepeatFalse.h"
#include "../../Shapes/Lines/RepeatTrue.h"
#include "../../Shapes/Lines/Join.h"
#include "../../Shapes/Lines/LeftDown.h"
#include "../../Shapes/Lines/RightDown.h"
#include "../../Observer/ScrollController.h"

#include "../../../Graphic Objects/Composite/Painter.h"

#include <cmath>

Zoom::Zoom(Long rate) {
	this->rate = rate;
}

Zoom::Zoom(const Zoom& source) {
	this->rate = source.rate;
}

Zoom::~Zoom() {

}

Zoom& Zoom::operator=(const Zoom& source) {
	this->rate = source.rate;

	return *this;
}

void Zoom::Set(Long changeRate) {
	this->rate = changeRate;
}