#ifndef _RULEKEEPER_H
#define _RULEKEEPER_H

#include "../Utilities/Array.h"
#include "String.h"

#define ALLOWEDKEYCOUNT 79

class VariableList;

class RuleKeeper {
public:
	RuleKeeper();
	RuleKeeper(const RuleKeeper& source);
	~RuleKeeper();
	RuleKeeper& operator=(const RuleKeeper& source);

	VariableList* CheckVariableNamingRule(Array<String> variables);
	bool CheckVariableUsingRule(Array<String> variables, VariableList *variableList);
	bool CheckOperatorRule(Array<String> operators);
};

#endif //_RULEKEEPER_H