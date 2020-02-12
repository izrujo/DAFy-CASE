#ifndef _EXPRESSIONS_H
#define _EXPRESSIONS_H

#include <afxwin.h>
#include "String.h"
#include "Array.h"

typedef signed long int Long;
class FlowChartEditor;
class Shape;

//ScenarioCheckExpression
class ScenarioCheckExpression {
public:
	ScenarioCheckExpression();
	ScenarioCheckExpression(const ScenarioCheckExpression& source);
	virtual ~ScenarioCheckExpression() = 0;
	ScenarioCheckExpression& operator=(const ScenarioCheckExpression& source);

	virtual ScenarioCheckExpression* Clone() = 0;

	virtual bool Evaluate();
	virtual bool Evaluate(int idA, int idB);
	virtual bool Evaluate(String stringA, String stringB);
	virtual bool Evaluate(Long integerA, Long integerB);
	virtual bool Evaluate(HMENU hPopup);

	virtual Long Add(Long index, ScenarioCheckExpression *expression);
	virtual Long Remove(Long index);
	virtual ScenarioCheckExpression* GetAt(Long index);
};

//NonterminalExpression
class NonterminalExpression : public ScenarioCheckExpression {
public:
	NonterminalExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	NonterminalExpression(const NonterminalExpression& source);
	virtual ~NonterminalExpression() = 0;
	NonterminalExpression& operator=(const NonterminalExpression& source);

	virtual Long Add(Long index, ScenarioCheckExpression *expression);
	virtual Long Remove(Long index);
	virtual ScenarioCheckExpression* GetAt(Long index);

	Long GetCapacity() const;
	Long GetLength() const;
protected:
	FlowChartEditor *editor;
	Array<ScenarioCheckExpression*> expressions;
	Long capacity;
	Long length;
};

inline Long NonterminalExpression::GetCapacity() const {
	return this->capacity;
}
inline Long NonterminalExpression::GetLength() const {
	return this->length;
}

//Composite...
//SymbolSelectExpression
class SymbolSelectExpression : public NonterminalExpression {
public:
	SymbolSelectExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	SymbolSelectExpression(const SymbolSelectExpression& source);
	virtual ~SymbolSelectExpression();
	SymbolSelectExpression& operator=(const SymbolSelectExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//DrawExpression
class DrawExpression : public NonterminalExpression {
public:
	DrawExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	DrawExpression(const DrawExpression& source);
	virtual ~DrawExpression();
	DrawExpression& operator=(const DrawExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//EditContentsExpression
class EditContentsExpression : public NonterminalExpression {
public:
	EditContentsExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	EditContentsExpression(const EditContentsExpression& source);
	virtual ~EditContentsExpression();
	EditContentsExpression& operator=(const EditContentsExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//ReSizeExpression
class ReSizeExpression : public NonterminalExpression {
public:
	ReSizeExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	ReSizeExpression(const ReSizeExpression& source);
	virtual ~ReSizeExpression();
	ReSizeExpression& operator=(const ReSizeExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//MoveExpression
class MoveExpression : public NonterminalExpression {
public:
	MoveExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	MoveExpression(const MoveExpression& source);
	virtual ~MoveExpression();
	MoveExpression& operator=(const MoveExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//GroupExpression
class GroupExpression : public NonterminalExpression {
public:
	GroupExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	GroupExpression(const GroupExpression& source);
	virtual ~GroupExpression();
	GroupExpression& operator=(const GroupExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//ContextMenuExpression
class ContextMenuExpression : public NonterminalExpression {
public:
	ContextMenuExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	ContextMenuExpression(const ContextMenuExpression& source);
	virtual ~ContextMenuExpression();
	ContextMenuExpression& operator=(const ContextMenuExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//PositionExpression
class PositionExpression : public NonterminalExpression {
public:
	PositionExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	PositionExpression(const PositionExpression& source);
	virtual ~PositionExpression();
	PositionExpression& operator=(const PositionExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//IntervalExpression
class IntervalExpression : public NonterminalExpression {
public:
	IntervalExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	IntervalExpression(const IntervalExpression& source);
	virtual ~IntervalExpression();
	IntervalExpression& operator=(const IntervalExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//SequenceMakeExpression
class SequenceMakeExpression : public NonterminalExpression {
public:
	SequenceMakeExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	SequenceMakeExpression(const SequenceMakeExpression& source);
	virtual ~SequenceMakeExpression();
	SequenceMakeExpression& operator=(const SequenceMakeExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//SelectionMakeExpression
class SelectionMakeExpression : public NonterminalExpression {
public:
	SelectionMakeExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	SelectionMakeExpression(const SelectionMakeExpression& source);
	virtual ~SelectionMakeExpression();
	SelectionMakeExpression& operator=(const SelectionMakeExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//IterationMakeExpression
class IterationMakeExpression : public NonterminalExpression {
public:
	IterationMakeExpression(FlowChartEditor *editor = 0, Long capacity = 5);
	IterationMakeExpression(const IterationMakeExpression& source);
	virtual ~IterationMakeExpression();
	IterationMakeExpression& operator=(const IterationMakeExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate();
};

//Leaf...
//IDEqualExpression
class IDEqualExpression : public ScenarioCheckExpression {
public:
	IDEqualExpression();
	IDEqualExpression(const IDEqualExpression & source);
	virtual ~IDEqualExpression();
	IDEqualExpression& operator=(const IDEqualExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate(int idA, int idB);
};

//StringEqualExpression
class StringEqualExpression : public ScenarioCheckExpression {
public:
	StringEqualExpression();
	StringEqualExpression(const StringEqualExpression& source);
	virtual ~StringEqualExpression();
	StringEqualExpression& operator=(const StringEqualExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate(String stringA, String stringB);
};

//IntegerOrOverExpression
class IntegerOrOverExpression : public ScenarioCheckExpression {
public:
	IntegerOrOverExpression();
	IntegerOrOverExpression(const IntegerOrOverExpression& source);
	virtual ~IntegerOrOverExpression();
	IntegerOrOverExpression& operator=(const IntegerOrOverExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate(Long integerA, Long integerB);
};

//IntegerOrUnderExpression
class IntegerOrUnderExpression : public ScenarioCheckExpression {
public:
	IntegerOrUnderExpression();
	IntegerOrUnderExpression(const IntegerOrUnderExpression& source);
	virtual ~IntegerOrUnderExpression();
	IntegerOrUnderExpression& operator=(const IntegerOrUnderExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate(Long integerA, Long integerB);
};

//IntegerOverExpression
class IntegerOverExpression : public ScenarioCheckExpression {
public:
	IntegerOverExpression();
	IntegerOverExpression(const IntegerOverExpression& source);
	virtual ~IntegerOverExpression();
	IntegerOverExpression& operator=(const IntegerOverExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate(Long integerA, Long integerB);
};

//IntegerEqualExpression
class IntegerEqualExpression : public ScenarioCheckExpression {
public:
	IntegerEqualExpression();
	IntegerEqualExpression(const IntegerEqualExpression& source);
	virtual ~IntegerEqualExpression();
	IntegerEqualExpression& operator=(const IntegerEqualExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate(Long integerA, Long integerB);
};

//MenuNotEqualExpression
class MenuNotEqualExpression : public ScenarioCheckExpression {
public:
	MenuNotEqualExpression();
	MenuNotEqualExpression(const MenuNotEqualExpression& source);
	virtual ~MenuNotEqualExpression();
	MenuNotEqualExpression& operator=(const MenuNotEqualExpression& source);

	virtual ScenarioCheckExpression* Clone();

	virtual bool Evaluate(HMENU hPopup);
};

#endif //_EXPRESSIONS_H