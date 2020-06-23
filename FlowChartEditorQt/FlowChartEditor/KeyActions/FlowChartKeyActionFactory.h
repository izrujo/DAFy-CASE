#ifndef _FLOWCHARTKEYACTIONFACTORY_H
#define _FLOWCHARTKEYACTIONFACTORY_H

#include "FlowChartKeyActions.h"

class FlowChartEditor;

class FlowChartKeyActionFactory {
public:
	FlowChartKeyActionFactory(FlowChartEditor *editor = 0);
	FlowChartKeyActionFactory(const FlowChartKeyActionFactory& source);
	~FlowChartKeyActionFactory();
	FlowChartKeyActionFactory& operator=(const FlowChartKeyActionFactory& source);

	FlowChartKeyAction* Make(int modifiers, int key);
private:
	FlowChartEditor *editor;
};


#endif //_FLOWCHARTKEYACTIONFACTORY_H