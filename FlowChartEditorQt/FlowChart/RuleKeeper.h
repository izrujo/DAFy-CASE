#ifndef _RULEKEEPER_H
#define _RULEKEEPER_H

#include "String.h"

class VariableList;

class RuleKeeper {
public:
	RuleKeeper();
	RuleKeeper(const RuleKeeper& source);
	~RuleKeeper();
	RuleKeeper& operator=(const RuleKeeper& source);

	bool IsAllowed(char key);
	bool IsKeptVariableRule(String allContents);
	Long FindVariable(String allContents);
	bool CorrectOperator(String allContents);

	VariableList* GetVariableList();
	char GetAllowedKey(Long index);

private:
	VariableList *variableList;
	char allowedKeys[77];
	bool isQuotes;
};

inline VariableList* RuleKeeper::GetVariableList() {
	return this->variableList;
}
inline char RuleKeeper::GetAllowedKey(Long index) {
	return this->allowedKeys[index];
}

#endif //_RULEKEEPER_H