// FlowChartVisitor.h

#ifndef _FLOWCHARTVISITOR_H
#define _FLOWCHARTVISITOR_H

class Terminal;
class Preparation;
class InputOutput;
class Process;
class Arrow;
class LeftDown;
class RightDown;
class Join;
class RightDownJoin;
class RepeatTrue;
class RepeatFalse;
class Annotation;
class Decision;
class FlowChart;
class Template;

class NumberBox;
class A4Paper;
class TextRegion;

//class TutorialMark;

class FlowChartVisitor {
public:
	FlowChartVisitor();
	virtual ~FlowChartVisitor() = 0;

	virtual void Visit(Annotation *element) {};
	virtual void Visit(Terminal *element) = 0;
	virtual void Visit(Preparation *element) = 0;
	virtual void Visit(InputOutput *element) = 0;
	virtual void Visit(Process *element) = 0;
	virtual void Visit(Decision *element) = 0;
	virtual void Visit(Arrow *element) = 0;
	virtual void Visit(LeftDown *element) = 0;
	virtual void Visit(RightDown *element) = 0;
	virtual void Visit(Join *element) = 0;
	virtual void Visit(RightDownJoin *element) = 0;
	virtual void Visit(RepeatTrue *element) = 0;
	virtual void Visit(RepeatFalse *element) = 0;
	virtual void Visit(FlowChart *element) = 0;
	virtual void Visit(Template *element) = 0;

	virtual void Visit(NumberBox *numberBox) {};
	virtual void Visit(A4Paper *a4Paper) = 0;
	//virtual void Visit(TutorialMark *tutorialMark) {};
};

#endif _FLOWCHARTVISITOR_H