#include "Expressions.h"
#include "TutorialForm.h"
#include "FlowChartTemplate.h"
#include "Shape.h"
#include "TutorialMark.h"
#include "FlowChart.h"
#include "FlowChartEditor.h"
#include "Terminal.h"
#include "InputOutput.h"
#include "DrawingPaper.h"
#include "FlowChartFont.h"
#include "Tutorials.h"
#include "Arrow.h"
#include "Join.h"

//ScenarioCheckExpression
ScenarioCheckExpression::ScenarioCheckExpression() {

}

ScenarioCheckExpression::ScenarioCheckExpression(const ScenarioCheckExpression& source) {

}

ScenarioCheckExpression::~ScenarioCheckExpression() {

}

ScenarioCheckExpression& ScenarioCheckExpression::operator=(const ScenarioCheckExpression& source) {
	return *this;
}

bool ScenarioCheckExpression::Evaluate() {
	return false;
}

bool ScenarioCheckExpression::Evaluate(int symbolIDA, int symbolIDB) {
	return false;
}

bool ScenarioCheckExpression::Evaluate(String stringA, String stringB) {
	return false;
}

bool ScenarioCheckExpression::Evaluate(Long integerA, Long integerB) {
	return false;
}

bool ScenarioCheckExpression::Evaluate(HMENU hPopup) {
	return false;
}

Long ScenarioCheckExpression::Add(Long index, ScenarioCheckExpression *expression) {
	return -1;
}

Long ScenarioCheckExpression::Remove(Long index) {
	return -1;
}

ScenarioCheckExpression* ScenarioCheckExpression::GetAt(Long index) {
	return 0;
}

//NonterminalExpression
NonterminalExpression::NonterminalExpression(FlowChartEditor *editor, Long capacity)
	: expressions(capacity) {
	this->editor = editor;
	this->capacity = capacity;
	this->length = 0;
}

NonterminalExpression::NonterminalExpression(const NonterminalExpression& source)
	: expressions(source.capacity) {
	this->editor = source.editor;

	Long i = 0;
	while (i < source.length) {
		this->expressions.Store(i, const_cast<NonterminalExpression&>(source).expressions[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

NonterminalExpression::~NonterminalExpression() {
	Long i = 0;
	while (i < this->length) {
		if (this->expressions[i] != 0) {
			delete this->expressions[i];
		}
		i++;
	}
}

NonterminalExpression& NonterminalExpression::operator=(const NonterminalExpression& source) {
	this->editor = source.editor;

	Long i = 0;
	while (i < this->length) {
		if (this->expressions[i] != 0) {
			delete this->expressions[i];
		}
		i++;
	}

	this->expressions = source.expressions;
	i = 0;
	while (i < source.length) {
		this->expressions.Modify(i, const_cast<NonterminalExpression&>(source).expressions[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long NonterminalExpression::Add(Long index, ScenarioCheckExpression *expression) {
	if (this->length < this->capacity) {
		index = this->expressions.Store(index, expression);
	}
	else {
		index = this->expressions.AppendFromRear(expression);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long NonterminalExpression::Remove(Long index) {
	if (this->expressions[index] != 0) {
		delete this->expressions[index];
	}
	index = this->expressions.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}

ScenarioCheckExpression* NonterminalExpression::GetAt(Long index) {
	return this->expressions.GetAt(index);
}

//SymbolSelectExpression
SymbolSelectExpression::SymbolSelectExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

SymbolSelectExpression::SymbolSelectExpression(const SymbolSelectExpression& source)
	: NonterminalExpression(source) {

}

SymbolSelectExpression::~SymbolSelectExpression() {

}

SymbolSelectExpression& SymbolSelectExpression::operator=(const SymbolSelectExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* SymbolSelectExpression::Clone() {
	return new SymbolSelectExpression(*this);
}

bool SymbolSelectExpression::Evaluate() {
	bool ret = false;

	TutorialForm *tutorialForm = static_cast<TutorialForm*>(this->editor->windows[2]);
	Long centerX = tutorialForm->current->GetX() + tutorialForm->current->GetWidth() / 2;
	Long centerY = tutorialForm->current->GetY() + tutorialForm->current->GetHeight() / 2;
	Long index = tutorialForm->sample->Find(tutorialForm->painter, centerX, centerY);
	Shape *currentSample = tutorialForm->sample->GetAt(index);
	Shape *shapeSelected = dynamic_cast<FlowChartTemplate*>(this->editor->windows[1])->shapeSelected;

	ret = this->expressions[0]->Evaluate(currentSample->GetSymbolID(), shapeSelected->GetSymbolID());
	if (ret == true) {
		if (dynamic_cast<Terminal*>(currentSample)) {
			ret = this->expressions[1]->Evaluate(currentSample->GetContents(), shapeSelected->GetContents());
		}
		else if (dynamic_cast<InputOutput*>(currentSample)) {
			String currentContents(currentSample->GetContents());
			String selectedContents(shapeSelected->GetContents());
			currentContents.RemoveFrom(5);
			selectedContents.RemoveFrom(5);
			ret = this->expressions[1]->Evaluate(currentContents, selectedContents);
		}
	}

	return ret;
}

//DrawExpression
DrawExpression::DrawExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

DrawExpression::DrawExpression(const DrawExpression& source)
	: NonterminalExpression(source) {

}

DrawExpression::~DrawExpression() {

}

DrawExpression& DrawExpression::operator=(const DrawExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* DrawExpression::Clone() {
	return new DrawExpression(*this);
}

bool DrawExpression::Evaluate() {
	bool ret = false;

	DrawingPaper *drawingPaper = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Shape *currentShape = dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(drawingPaper->indexOfSelected);
	Shape *a4Paper = drawingPaper->a4Paper;
	Long shapeLeft = currentShape->GetX();
	Long shapeTop = currentShape->GetY();
	Long shapeRight = shapeLeft + currentShape->GetWidth();
	Long shapeBottom = shapeTop + currentShape->GetHeight();
	Long a4Left = a4Paper->GetX();
	Long a4Top = a4Paper->GetY();
	Long a4Right = a4Left + a4Paper->GetWidth();
	Long a4Bottom = a4Top + a4Paper->GetHeight();

	ret = this->expressions[0]->Evaluate(shapeLeft, a4Left) && this->expressions[0]->Evaluate(shapeTop, a4Top)
		&& this->expressions[1]->Evaluate(shapeRight, a4Right) && this->expressions[1]->Evaluate(shapeBottom, a4Bottom);

	return ret;
}

//EditContentsExpression
EditContentsExpression::EditContentsExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

EditContentsExpression::EditContentsExpression(const EditContentsExpression& source)
	: NonterminalExpression(source) {

}

EditContentsExpression::~EditContentsExpression() {

}

EditContentsExpression& EditContentsExpression::operator=(const EditContentsExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* EditContentsExpression::Clone() {
	return new EditContentsExpression(*this);
}

bool EditContentsExpression::Evaluate() {
	bool ret = false;

	DrawingPaper *drawingPaper = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Shape *currentShape = dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(drawingPaper->indexOfSelected);

	TutorialForm *tutorialForm = static_cast<TutorialForm*>(this->editor->windows[2]);
	Long centerX = tutorialForm->current->GetX() + tutorialForm->current->GetWidth() / 2;
	Long centerY = tutorialForm->current->GetY() + tutorialForm->current->GetHeight() / 2;
	Long index = tutorialForm->sample->Find(tutorialForm->painter, centerX, centerY);
	Shape *currentSample = tutorialForm->sample->GetAt(index);

	//curretnShape와 currentSample의 contents들에서 공백을 전부 다 빼버린다.
	if (drawingPaper->indexOfSelected != -1) { //오류 방지 - 이 expression을 부르는 것은 마우스 클릭인데 두 번 연속으로 눌리면 currentShape가 없어서 오류남
		String shapeContents = currentShape->GetContents();
		String sampleContents = currentSample->GetContents();
		shapeContents.Remove(' ');
		shapeContents.Remove('\n');
		sampleContents.Remove(' ');
		sampleContents.Remove('\n');

		//그리고 똑같은지 확인한다.
		ret = this->expressions[0]->Evaluate(shapeContents, sampleContents);
	}

	return ret;
}

//ReSizeExpression
ReSizeExpression::ReSizeExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

ReSizeExpression::ReSizeExpression(const ReSizeExpression& source)
	: NonterminalExpression(source) {

}

ReSizeExpression::~ReSizeExpression() {

}

ReSizeExpression& ReSizeExpression::operator=(const ReSizeExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* ReSizeExpression::Clone() {
	return new ReSizeExpression(*this);
}

bool ReSizeExpression::Evaluate() {
	bool ret = false;

	DrawingPaper *drawingPaper = static_cast<DrawingPaper*>(this->editor->windows[0]);
	if (drawingPaper->indexOfSelected != -1) { //오류 방지
		Shape *currentShape = dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(drawingPaper->indexOfSelected);
		LOGFONT font = this->editor->font->GetFont();
		Long leastWidth = currentShape->GetContents().CountLongestLine() * (font.lfHeight/2 * -1)
			+ currentShape->GetHeight();
		Long leastHeight = currentShape->GetContents().CountLine() * (font.lfHeight * -1);

		ret = this->expressions[0]->Evaluate(currentShape->GetWidth(), leastWidth)
			&& this->expressions[0]->Evaluate(currentShape->GetHeight(), leastHeight);
	}

	return ret;
}

//MoveExpression
MoveExpression::MoveExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

MoveExpression::MoveExpression(const MoveExpression& source)
	: NonterminalExpression(source) {

}

MoveExpression::~MoveExpression() {

}

MoveExpression& MoveExpression::operator=(const MoveExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* MoveExpression::Clone() {
	return new MoveExpression(*this);
}

bool MoveExpression::Evaluate() {
	bool ret = true;

	return ret;
}

//GroupExpression
GroupExpression::GroupExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

GroupExpression::GroupExpression(const GroupExpression& source)
	: NonterminalExpression(source) {

}

GroupExpression::~GroupExpression() {

}

GroupExpression& GroupExpression::operator=(const GroupExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* GroupExpression::Clone() {
	return new GroupExpression(*this);
}

bool GroupExpression::Evaluate() {
	bool ret = false;

	TutorialForm *tutorialForm = static_cast<TutorialForm*>(this->editor->windows[2]);
	Long top = tutorialForm->main->GetTop();
	DrawingPaper *drawingPaper = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);
	dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetSelecteds(&indexes, &count);

	ret = (this->expressions[0]->Evaluate(top, (Long)8) && this->expressions[0]->Evaluate(count, (Long)8))
		|| (this->expressions[0]->Evaluate(top, (Long)5) && this->expressions[0]->Evaluate(count, (Long)3)
			&& this->expressions[0]->Evaluate(indexes[0], (Long)14) && this->expressions[0]->Evaluate(indexes[2], (Long)16))
		|| (this->expressions[0]->Evaluate(top, (Long)2) && this->expressions[0]->Evaluate(count, (Long)2)
			&& this->expressions[0]->Evaluate(indexes[0], (Long)21) && this->expressions[0]->Evaluate(indexes[1], (Long)22))
		|| (this->expressions[0]->Evaluate(top, (Long)1) && this->expressions[0]->Evaluate(count, (Long)18)
			&& this->expressions[0]->Evaluate(indexes[0], (Long)6) && this->expressions[0]->Evaluate(indexes[17], (Long)23));

	if (indexes != NULL) {
		delete indexes;
	}

	return ret;
}

//ContextMenuExpression
ContextMenuExpression::ContextMenuExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

ContextMenuExpression::ContextMenuExpression(const ContextMenuExpression& source)
	: NonterminalExpression(source) {

}

ContextMenuExpression::~ContextMenuExpression() {

}

ContextMenuExpression& ContextMenuExpression::operator=(const ContextMenuExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* ContextMenuExpression::Clone() {
	return new ContextMenuExpression(*this);
}

bool ContextMenuExpression::Evaluate() {
	bool ret = false;

	DrawingPaper *drawingPaper = static_cast<DrawingPaper*>(this->editor->windows[0]);
	ret = this->expressions[0]->Evaluate(drawingPaper->hPopup);

	return ret;
}

//PositionExpression
PositionExpression::PositionExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

PositionExpression::PositionExpression(const PositionExpression& source)
	: NonterminalExpression(source) {

}

PositionExpression::~PositionExpression() {

}

PositionExpression& PositionExpression::operator=(const PositionExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* PositionExpression::Clone() {
	return new PositionExpression(*this);
}

bool PositionExpression::Evaluate() {
	bool ret = false;

	DrawingPaper *drawingPaper = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);
	dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetSelecteds(&indexes, &count);
	Long gravityX = dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[0])->CenterOfGravityX();
	Long i = 1;
	Long nextGravityX = dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[i])->CenterOfGravityX();
	ret = this->expressions[0]->Evaluate(nextGravityX, gravityX);
	while (i < count && ret == true) {
		nextGravityX = dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[i])->CenterOfGravityX();
		ret = this->expressions[0]->Evaluate(nextGravityX, gravityX);
		i++;
	}

	if (indexes != NULL) {
		delete indexes;
	}

	return ret;
}

//IntervalExpression
IntervalExpression::IntervalExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

IntervalExpression::IntervalExpression(const IntervalExpression& source)
	: NonterminalExpression(source) {

}

IntervalExpression::~IntervalExpression() {

}

IntervalExpression& IntervalExpression::operator=(const IntervalExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* IntervalExpression::Clone() {
	return new IntervalExpression(*this);
}

bool IntervalExpression::Evaluate() {
	bool ret = false;

	DrawingPaper *drawingPaper = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);
	dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetSelecteds(&indexes, &count);
	Long interval = dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[1])->GetY() -
		(dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[0])->GetY() +
			dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[0])->GetHeight());
	Long nextInterval = dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[2])->GetY() -
		(dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[1])->GetY() +
			dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[1])->GetHeight());
	ret = this->expressions[0]->Evaluate(nextInterval, interval);
	Long i = 2;
	while (i < count - 1 && ret == true) {
		nextInterval = dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[i + 1])->GetY() -
			(dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[i])->GetY() +
				dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[i])->GetHeight());
		ret = this->expressions[0]->Evaluate(nextInterval, interval);
		i++;
	}

	if (indexes != NULL) {
		delete indexes;
	}

	return ret;
}

//SequenceMakeExpression
SequenceMakeExpression::SequenceMakeExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

SequenceMakeExpression::SequenceMakeExpression(const SequenceMakeExpression& source)
	: NonterminalExpression(source) {

}

SequenceMakeExpression::~SequenceMakeExpression() {

}

SequenceMakeExpression& SequenceMakeExpression::operator=(const SequenceMakeExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* SequenceMakeExpression::Clone() {
	return new SequenceMakeExpression(*this);
}

bool SequenceMakeExpression::Evaluate() {
	bool ret = false;

	DrawingPaper *drawingPaper = static_cast<DrawingPaper*>(this->editor->windows[0]);
	Long count;
	Long(*indexes);
	dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetSelecteds(&indexes, &count);

	Long symbolCount = 0;
	Long arrowCount = 0;
	Shape *shape;
	Long i = 0;
	while (i < count) {
		shape = dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(indexes[i]);
		if (dynamic_cast<Symbol*>(shape)) {
			symbolCount++;
		}
		else if (dynamic_cast<Arrow*>(shape)) {
			arrowCount++;
		}
		i++;
	}

	ret = this->expressions[0]->Evaluate(arrowCount, symbolCount - 1);

	if (indexes != NULL) {
		delete indexes;
	}

	return ret;
}

//SelectionMakeExpression
SelectionMakeExpression::SelectionMakeExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

SelectionMakeExpression::SelectionMakeExpression(const SelectionMakeExpression& source)
	: NonterminalExpression(source) {

}

SelectionMakeExpression::~SelectionMakeExpression() {

}

SelectionMakeExpression& SelectionMakeExpression::operator=(const SelectionMakeExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* SelectionMakeExpression::Clone() {
	return new SelectionMakeExpression(*this);
}

bool SelectionMakeExpression::Evaluate() {
	bool ret = false;

	DrawingPaper *drawingPaper = static_cast<DrawingPaper*>(this->editor->windows[0]);
	FlowChart *flowChart = static_cast<FlowChart*>(drawingPaper->flowChart);
	int id = flowChart->GetAt(flowChart->GetLength() - 2)->GetLineID();

	ret = this->expressions[0]->Evaluate(id, ID_JOIN);

	return ret;
}

//IterationMakeExpression
IterationMakeExpression::IterationMakeExpression(FlowChartEditor *editor, Long capacity)
	: NonterminalExpression(editor, capacity) {

}

IterationMakeExpression::IterationMakeExpression(const IterationMakeExpression& source)
	: NonterminalExpression(source) {

}

IterationMakeExpression::~IterationMakeExpression() {

}

IterationMakeExpression& IterationMakeExpression::operator=(const IterationMakeExpression& source) {
	NonterminalExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* IterationMakeExpression::Clone() {
	return new IterationMakeExpression(*this);
}

bool IterationMakeExpression::Evaluate() {
	bool ret = false;

	DrawingPaper *drawingPaper = static_cast<DrawingPaper*>(this->editor->windows[0]);
	FlowChart *flowChart = static_cast<FlowChart*>(drawingPaper->flowChart);
	int id = flowChart->GetAt(flowChart->GetLength() - 1)->GetLineID();

	ret = this->expressions[0]->Evaluate(id, ID_REPEATFALSE);

	return ret;
}

//Leaf
//IDEqualExpression
IDEqualExpression::IDEqualExpression()
	: ScenarioCheckExpression() {

}

IDEqualExpression::IDEqualExpression(const IDEqualExpression& source)
	: ScenarioCheckExpression(source) {

}

IDEqualExpression::~IDEqualExpression() {

}

IDEqualExpression& IDEqualExpression::operator=(const IDEqualExpression& source) {
	ScenarioCheckExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* IDEqualExpression::Clone() {
	return new IDEqualExpression(*this);
}

bool IDEqualExpression::Evaluate(int idA, int idB) {
	return idA == idB;
}

//StringEqualExpression
StringEqualExpression::StringEqualExpression()
	: ScenarioCheckExpression() {

}

StringEqualExpression::StringEqualExpression(const StringEqualExpression& source)
	: ScenarioCheckExpression(source) {

}

StringEqualExpression::~StringEqualExpression() {

}

StringEqualExpression& StringEqualExpression::operator=(const StringEqualExpression& source) {
	ScenarioCheckExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* StringEqualExpression::Clone() {
	return new StringEqualExpression(*this);
}

bool StringEqualExpression::Evaluate(String stringA, String stringB) {
	return stringA == stringB;
}

//IntegerOrOverExpression
IntegerOrOverExpression::IntegerOrOverExpression()
	: ScenarioCheckExpression() {

}

IntegerOrOverExpression::IntegerOrOverExpression(const IntegerOrOverExpression& source)
	: ScenarioCheckExpression(source) {

}

IntegerOrOverExpression::~IntegerOrOverExpression() {

}

IntegerOrOverExpression& IntegerOrOverExpression::operator=(const IntegerOrOverExpression& source) {
	ScenarioCheckExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* IntegerOrOverExpression::Clone() {
	return new IntegerOrOverExpression(*this);
}

bool IntegerOrOverExpression::Evaluate(Long integerA, Long integerB) {
	return integerA >= integerB;
}

//IntegerOrUnderExpression
IntegerOrUnderExpression::IntegerOrUnderExpression()
	: ScenarioCheckExpression() {

}

IntegerOrUnderExpression::IntegerOrUnderExpression(const IntegerOrUnderExpression& source)
	: ScenarioCheckExpression(source) {

}

IntegerOrUnderExpression::~IntegerOrUnderExpression() {

}

IntegerOrUnderExpression& IntegerOrUnderExpression::operator=(const IntegerOrUnderExpression& source) {
	ScenarioCheckExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* IntegerOrUnderExpression::Clone() {
	return new IntegerOrUnderExpression(*this);
}

bool IntegerOrUnderExpression::Evaluate(Long integerA, Long integerB) {
	return integerA <= integerB;
}

//IntegerOverExpression
IntegerOverExpression::IntegerOverExpression()
	: ScenarioCheckExpression() {

}

IntegerOverExpression::IntegerOverExpression(const IntegerOverExpression& source)
	: ScenarioCheckExpression(source) {

}

IntegerOverExpression::~IntegerOverExpression() {

}

IntegerOverExpression& IntegerOverExpression::operator=(const IntegerOverExpression& source) {
	ScenarioCheckExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* IntegerOverExpression::Clone() {
	return new IntegerOverExpression(*this);
}

bool IntegerOverExpression::Evaluate(Long integerA, Long integerB) {
	return integerA > integerB;
}

//IntegerEqualExpression
IntegerEqualExpression::IntegerEqualExpression()
	: ScenarioCheckExpression() {

}

IntegerEqualExpression::IntegerEqualExpression(const IntegerEqualExpression& source)
	: ScenarioCheckExpression(source) {

}

IntegerEqualExpression::~IntegerEqualExpression() {

}

IntegerEqualExpression& IntegerEqualExpression::operator=(const IntegerEqualExpression& source) {
	ScenarioCheckExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* IntegerEqualExpression::Clone() {
	return new IntegerEqualExpression(*this);
}

bool IntegerEqualExpression::Evaluate(Long integerA, Long integerB) {
	return integerA == integerB;
}

//MenuNotEqualExpression
MenuNotEqualExpression::MenuNotEqualExpression()
	: ScenarioCheckExpression() {

}

MenuNotEqualExpression::MenuNotEqualExpression(const MenuNotEqualExpression& source)
	: ScenarioCheckExpression(source) {

}

MenuNotEqualExpression::~MenuNotEqualExpression() {

}

MenuNotEqualExpression& MenuNotEqualExpression::operator=(const MenuNotEqualExpression& source) {
	ScenarioCheckExpression::operator=(source);

	return *this;
}

ScenarioCheckExpression* MenuNotEqualExpression::Clone() {
	return new MenuNotEqualExpression(*this);
}

bool MenuNotEqualExpression::Evaluate(HMENU hPopup) {
	return hPopup != NULL;
}