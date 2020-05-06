#ifndef _CONTENTSANALYZER_H
#define _CONTENTSANALYZER_H

#include "../Notepad/Array.h"
#include "String.h"

class ContentsAnalyzer {
public:
	ContentsAnalyzer();
	~ContentsAnalyzer();

	Array<String> MakeOperators(String contents);
	Array<String> MakeVariables(String contents);
	String CorrectOperators(String contents);
};

#endif //_CONTENTSANALYZER_H