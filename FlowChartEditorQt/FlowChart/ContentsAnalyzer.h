#ifndef _CONTENTSANALYZER_H
#define _CONTENTSANALYZER_H

#include "Array.h"
#include "String.h"

class ContentsAnalyzer {
public:
	ContentsAnalyzer(String contents = static_cast<String>(""));
	~ContentsAnalyzer();

	Array<String*> MakeOperators();
	Array<String*> MakeVariables();
	String CorrectOperators();
private:
	String contents;
};

#endif //_CONTENTSANALYZER_H