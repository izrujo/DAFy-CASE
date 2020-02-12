#ifndef _ZOOMVISITOR_H
#define _ZOOMVISITOR_H

#include "FlowChartVisitor.h"

class Zoom;
class CoordinateConverter;

class ZoomVisitor : public FlowChartVisitor {
public:
	ZoomVisitor(Zoom *zoom);
	ZoomVisitor(const ZoomVisitor& source);
	virtual ~ZoomVisitor();
	ZoomVisitor& operator=(const ZoomVisitor& source);

	//virtual void Visit(Annotation *element);
	virtual void Visit(Terminal *element);
	virtual void Visit(Preparation *element);
	//virtual void Visit(PunchedCard *element);
	virtual void Visit(InputOutput *element);
	virtual void Visit(Process *element);
	virtual void Visit(Decision *element);
	//virtual void Visit(Document *element);
	virtual void Visit(Arrow *element);
	virtual void Visit(LeftDown *element);
	virtual void Visit(RightDown *element);
	virtual void Visit(Join *element);
	virtual void Visit(RightDownJoin *element);
	virtual void Visit(RepeatTrue *element);
	virtual void Visit(RepeatFalse *element);
	virtual void Visit(FlowChart *element);
	virtual void Visit(Template *element);

	//virtual void Visit(NumberBox *numberBox);
	virtual void Visit(A4Paper *a4Paper);
private:
	Zoom *zoom;
public:
	CoordinateConverter *converter;
};

#endif //_ZOOMVISITOR_H