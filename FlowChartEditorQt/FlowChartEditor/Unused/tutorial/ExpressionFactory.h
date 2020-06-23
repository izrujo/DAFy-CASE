#ifndef _EXPRESSIONFACTORY_H
#define _EXPRESSIONFACTORY_H

class FlowChartEditor;
class ScenarioCheckExpression;
class Tutorial;

class ExpressionFactory {
public:
	ExpressionFactory(FlowChartEditor *editor = 0);
	ExpressionFactory(const ExpressionFactory& source);
	~ExpressionFactory();
	ExpressionFactory& operator=(const ExpressionFactory& source);

	ScenarioCheckExpression* Make(Tutorial *tutorial);
private:
	FlowChartEditor *editor;
};

#endif //_EXPRESSIONFACTORY_H