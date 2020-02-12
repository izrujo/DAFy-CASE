#ifndef _TUTORIALS_H
#define _TUTORIALS_H

#include "Stack.h"
class FlowChartEditor;

//Tutorial - Component
class Tutorial {
public:
	Tutorial(FlowChartEditor *editor = 0);
	Tutorial(const Tutorial& source);
	virtual ~Tutorial() = 0;
	Tutorial& operator=(const Tutorial& source);

	virtual Long Add(Tutorial *tutorial);
	virtual Tutorial* TakeOut();
	virtual Tutorial* Top();

	virtual Tutorial* Clone() = 0;

	virtual void Execute() = 0;

	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long GetTop() const;
protected:
	FlowChartEditor *editor;
};

//MacroTutorial - Composite
class MacroTutorial : public Tutorial {
public:
	MacroTutorial(Long capacity = 11);
	MacroTutorial(const MacroTutorial& source);
	virtual ~MacroTutorial() = 0;
	MacroTutorial& operator=(const MacroTutorial& source);

	virtual Long Add(Tutorial *tutorial);
	virtual Tutorial* TakeOut();
	virtual Tutorial* Top();

	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long GetTop() const;
protected:
	Stack<Tutorial*> tutorials;
	Long capacity;
	Long length;
	Long top;
};
inline Long MacroTutorial::GetCapacity() const {
	return this->capacity;
}
inline Long MacroTutorial::GetLength() const {
	return this->length;
}
inline Long MacroTutorial::GetTop() const {
	return this->top;
}

//================================Main=======================================
//MainTutorial (- 다른 Composite 포함하는 클래스)
class MainTutorial : public MacroTutorial {
public:
	MainTutorial(Long capacity = 11);
	MainTutorial(const MainTutorial& source);
	virtual ~MainTutorial();
	MainTutorial& operator=(const MainTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//SeveralTutorial
class SeveralTutorial : public MacroTutorial {
public:
	SeveralTutorial(Long capacity = 11);
	SeveralTutorial(const SeveralTutorial& source);
	virtual ~SeveralTutorial();
	SeveralTutorial& operator=(const SeveralTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};
//===========================================================================

//================================Detail=====================================
//- Leaf
//SymbolSelectTutorial
class SymbolSelectTutorial : public Tutorial {
public:
	SymbolSelectTutorial(FlowChartEditor *editor = 0);
	SymbolSelectTutorial(const SymbolSelectTutorial& source);
	virtual ~SymbolSelectTutorial();
	SymbolSelectTutorial& operator=(const SymbolSelectTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//DrawTutorial
class DrawTutorial : public Tutorial {
public:
	DrawTutorial(FlowChartEditor *editor = 0);
	DrawTutorial(const DrawTutorial& source);
	virtual ~DrawTutorial();
	DrawTutorial& operator=(const DrawTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//EditContentsTutorial
class EditContentsTutorial : public Tutorial {
public:
	EditContentsTutorial(FlowChartEditor *editor = 0);
	EditContentsTutorial(const EditContentsTutorial& source);
	virtual ~EditContentsTutorial();
	EditContentsTutorial& operator=(const EditContentsTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//MoveTutorial
class MoveTutorial : public Tutorial {
public:
	MoveTutorial(FlowChartEditor *editor = 0);
	MoveTutorial(const MoveTutorial& source);
	virtual ~MoveTutorial();
	MoveTutorial& operator=(const MoveTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//ReSizeTutorial
class ReSizeTutorial : public Tutorial {
public:
	ReSizeTutorial(FlowChartEditor *editor = 0);
	ReSizeTutorial(const ReSizeTutorial& source);
	virtual ~ReSizeTutorial();
	ReSizeTutorial& operator=(const ReSizeTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//GroupTutorial
class GroupTutorial : public Tutorial {
public:
	GroupTutorial(FlowChartEditor *editor = 0);
	GroupTutorial(const GroupTutorial& source);
	virtual ~GroupTutorial();
	GroupTutorial& operator=(const GroupTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//ContextMenuTutorial
class ContextMenuTutorial : public Tutorial {
public:
	ContextMenuTutorial(FlowChartEditor *editor = 0);
	ContextMenuTutorial(const ContextMenuTutorial& source);
	virtual ~ContextMenuTutorial();
	ContextMenuTutorial& operator=(const ContextMenuTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//PositionTutorial
class PositionTutorial : public Tutorial {
public:
	PositionTutorial(FlowChartEditor *editor = 0);
	PositionTutorial(const PositionTutorial& source);
	virtual ~PositionTutorial();
	PositionTutorial& operator=(const PositionTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//IntervalTutorial
class IntervalTutorial : public Tutorial {
public:
	IntervalTutorial(FlowChartEditor *editor = 0);
	IntervalTutorial(const IntervalTutorial& source);
	virtual ~IntervalTutorial();
	IntervalTutorial& operator=(const IntervalTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//SequenceMakeTutorial
class SequenceMakeTutorial : public Tutorial {
public:
	SequenceMakeTutorial(FlowChartEditor *editor = 0);
	SequenceMakeTutorial(const SequenceMakeTutorial& source);
	virtual ~SequenceMakeTutorial();
	SequenceMakeTutorial& operator=(const SequenceMakeTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//SelectionMakeTutorial
class SelectionMakeTutorial : public Tutorial {
public:
	SelectionMakeTutorial(FlowChartEditor *editor = 0);
	SelectionMakeTutorial(const SelectionMakeTutorial& source);
	virtual ~SelectionMakeTutorial();
	SelectionMakeTutorial& operator=(const SelectionMakeTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

//IterationMakeTutorial
class IterationMakeTutorial : public Tutorial {
public:
	IterationMakeTutorial(FlowChartEditor *editor = 0);
	IterationMakeTutorial(const IterationMakeTutorial& source);
	virtual ~IterationMakeTutorial();
	IterationMakeTutorial& operator=(const IterationMakeTutorial& source);

	virtual void Execute();

	virtual Tutorial* Clone();
};

#endif //_TUTORIALS_H