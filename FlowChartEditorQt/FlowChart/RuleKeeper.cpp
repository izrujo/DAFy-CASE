#include "RuleKeeper.h"
#include "VariableList.h"

RuleKeeper::RuleKeeper() {

}

RuleKeeper::RuleKeeper(const RuleKeeper& source) {

}

RuleKeeper::~RuleKeeper() {
	
}

RuleKeeper& RuleKeeper::operator=(const RuleKeeper& source) {
	return *this;
}

VariableList* RuleKeeper::CheckVariableNamingRule(Array<String*> variables) {

}

bool RuleKeeper::CheckVariableUsingRule(Array<String*> variables, VariableList *variableList) {

}

bool RuleKeeper::CheckOperatorRule(Array<String*> operators) {

}