#include "ExpressionFactory.h"
#include "Tutorials.h"
#include "Expressions.h"

ExpressionFactory::ExpressionFactory(FlowChartEditor *editor) {
	this->editor = editor;
}

ExpressionFactory::ExpressionFactory(const ExpressionFactory& source) {
	this->editor = source.editor;
}

ExpressionFactory::~ExpressionFactory() {

}

ExpressionFactory& ExpressionFactory::operator=(const ExpressionFactory& source) {
	this->editor = editor;

	return *this;
}

ScenarioCheckExpression* ExpressionFactory::Make(Tutorial *tutorial) {
	ScenarioCheckExpression *expression;

	if (dynamic_cast<SymbolSelectTutorial*>(tutorial)) {
		expression = new SymbolSelectExpression(this->editor);
		expression->Add(0, new IDEqualExpression);
		expression->Add(1, new StringEqualExpression);
	}
	else if (dynamic_cast<DrawTutorial*>(tutorial)) {
		expression = new DrawExpression(this->editor);
		expression->Add(0, new IntegerOrOverExpression);
		expression->Add(1, new IntegerOrUnderExpression);
	}
	else if (dynamic_cast<EditContentsTutorial*>(tutorial)) {
		expression = new EditContentsExpression(this->editor);
		expression->Add(0, new StringEqualExpression);
	}
	else if (dynamic_cast<ReSizeTutorial*>(tutorial)) {
		expression = new ReSizeExpression(this->editor);
		expression->Add(0, new IntegerOverExpression);
	}
	else if (dynamic_cast<MoveTutorial*>(tutorial)) {
		expression = new MoveExpression(this->editor);
	}
	else if (dynamic_cast<GroupTutorial*>(tutorial)) {
		expression = new GroupExpression(this->editor);
		expression->Add(0, new IntegerEqualExpression);
	}
	else if (dynamic_cast<ContextMenuTutorial*>(tutorial)) {
		expression = new ContextMenuExpression(this->editor);
		expression->Add(0, new MenuNotEqualExpression);
	}
	else if (dynamic_cast<PositionTutorial*>(tutorial)) {
		expression = new PositionExpression(this->editor);
		expression->Add(0, new IntegerEqualExpression);
	}
	else if (dynamic_cast<IntervalTutorial*>(tutorial)) {
		expression = new IntervalExpression(this->editor);
		expression->Add(0, new IntegerEqualExpression);
	}
	else if (dynamic_cast<SequenceMakeTutorial*>(tutorial)) {
		expression = new SequenceMakeExpression(this->editor);
		expression->Add(0, new IntegerEqualExpression);
	}
	else if (dynamic_cast<SelectionMakeTutorial*>(tutorial)) {
		expression = new SelectionMakeExpression(this->editor);
		expression->Add(0, new IDEqualExpression);
	}
	else if (dynamic_cast<IterationMakeTutorial*>(tutorial)) {
		expression = new IterationMakeExpression(this->editor);
		expression->Add(0, new IDEqualExpression);
	}

	return expression;
}