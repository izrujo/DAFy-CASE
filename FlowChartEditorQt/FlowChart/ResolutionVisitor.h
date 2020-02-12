#ifndef _RESOLUTIONVISITOR_H
#define _RESOLUTIONVISITOR_H

#include "FlowChartVisitor.h"
class CoordinateConverter;

class ResolutionVisitor : public FlowChartVisitor {
public:
	ResolutionVisitor(Long dpi = 600, Long mmWidth = 210, Long mmHeight = 297);
	ResolutionVisitor(const ResolutionVisitor& source);
	virtual ~ResolutionVisitor();
	ResolutionVisitor& operator=(const ResolutionVisitor& source);
	
	virtual void Visit(Terminal *element);
	virtual void Visit(Preparation *element);
	virtual void Visit(InputOutput *element);
	virtual void Visit(Process *element);
	virtual void Visit(Decision *element);
	virtual void Visit(Arrow *element);
	virtual void Visit(LeftDown *element);
	virtual void Visit(RightDown *element);
	virtual void Visit(Join *element);
	virtual void Visit(RightDownJoin *element);
	virtual void Visit(RepeatTrue *element);
	virtual void Visit(RepeatFalse *element);
	virtual void Visit(FlowChart *element);
	virtual void Visit(Template *element);
	virtual void Visit(A4Paper *element);
private:
	CoordinateConverter *converter;
	Long dpi;
	Long mmWidth;
	Long mmHeight;
	Long pixelWidth;
	Long pixelHeight;
};

#endif //_RESOLUTIONVISITOR_H