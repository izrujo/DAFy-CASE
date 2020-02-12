#ifndef _FLOWCHARTKEYACTIONFACTORY_H
#define _FLOWCHARTKEYACTIONFACTORY_H

#include <afxwin.h>

class FlowChartEditor;
class FlowChartKeyAction;

class FlowChartKeyActionFactory {
public:
	FlowChartKeyActionFactory(FlowChartEditor *editor = 0);
	FlowChartKeyActionFactory(const FlowChartKeyActionFactory& source);
	~FlowChartKeyActionFactory();
	FlowChartKeyActionFactory& operator=(const FlowChartKeyActionFactory& source);

	FlowChartKeyAction* Make(UINT nChar);
private:
	FlowChartEditor *editor;
};


#endif //_FLOWCHARTKEYACTIONFACTORY_H