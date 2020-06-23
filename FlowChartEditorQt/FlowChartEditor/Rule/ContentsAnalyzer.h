#ifndef _CONTENTSANALYZER_H
#define _CONTENTSANALYZER_H

#include "../Utilities/Array.h"
#include "String.h"

class ContentsAnalyzer {
public:
	ContentsAnalyzer();
	~ContentsAnalyzer();

	Array<String> MakeOperators(String contents);
	Array<String> MakeVariables(String contents);
	String CorrectOperators(String contents);
	
	String RollBackOperators(String contents);
};

#endif //_CONTENTSANALYZER_H